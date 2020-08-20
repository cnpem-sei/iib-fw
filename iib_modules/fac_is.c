/******************************************************************************
 * Copyright (C) 2017 by LNLS - Brazilian Synchrotron Light Laboratory
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. LNLS and
 * the Brazilian Center for Research in Energy and Materials (CNPEM) are not
 * liable for any misuse of this material.
 *
 *****************************************************************************/

/**
 * @file fac_is.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#include <iib_modules/fac_is.h>
#include "iib_data.h"

#include "adc_internal.h"
#include "application.h"

#include "BoardTempHum.h"
#include "ntc_isolated_i2c.h"
#include "pt100.h"
#include "output.h"
#include "leds.h"
#include "can_bus.h"
#include "input.h"

#include <stdbool.h>
#include <stdint.h>

#include "peripheral_drivers/timer/timer.h"
#include "inc/hw_ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"

/////////////////////////////////////////////////////////////////////////////////////////////

fac_is_t fac_is;

/////////////////////////////////////////////////////////////////////////////////////////////

static uint32_t fac_is_interlocks_indication;
static uint32_t fac_is_alarms_indication;

static uint32_t ResetInterlocksRegister = 0;
static uint32_t ResetAlarmsRegister = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

static uint32_t itlk_id;
static uint32_t alarm_id;

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_fac_is_interlocks()
{
    fac_is.VdcLinkItlkSts            = 0;
    fac_is.IinItlkSts                = 0;
    fac_is.TempIGBT1ItlkSts          = 0;
    fac_is.TempIGBT1HwrItlkSts       = 0;
    fac_is.Driver1ErrorTopItlkSts    = 0;
    fac_is.Driver1ErrorBotItlkSts    = 0;
    fac_is.TempLItlkSts              = 0;
    fac_is.TempHeatSinkItlkSts       = 0;
    fac_is.DriveVoltageItlkSts       = 0;
    fac_is.Drive1CurrentItlkSts      = 0;
    fac_is.BoardTemperatureItlkSts   = 0;
    fac_is.RelativeHumidityItlkSts   = 0;

    itlk_id = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t check_fac_is_interlocks()
{
    uint8_t test = 0;

    test |= fac_is.VdcLinkItlkSts;
    test |= fac_is.IinItlkSts;
    test |= fac_is.TempIGBT1ItlkSts;
    test |= fac_is.TempIGBT1HwrItlkSts;
    test |= fac_is.Driver1ErrorTopItlkSts;
    test |= fac_is.Driver1ErrorBotItlkSts;
    test |= fac_is.TempLItlkSts;
    test |= fac_is.TempHeatSinkItlkSts;
    test |= fac_is.DriveVoltageItlkSts;
    test |= fac_is.Drive1CurrentItlkSts;
    test |= fac_is.BoardTemperatureItlkSts;
    test |= fac_is.RelativeHumidityItlkSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_fac_is_alarms()
{
    fac_is.VdcLinkAlarmSts           = 0;
    fac_is.IinAlarmSts               = 0;
    fac_is.TempIGBT1AlarmSts         = 0;
    fac_is.TempLAlarmSts             = 0;
    fac_is.TempHeatSinkAlarmSts      = 0;
    fac_is.DriveVoltageAlarmSts      = 0;
    fac_is.Drive1CurrentAlarmSts     = 0;
    fac_is.BoardTemperatureAlarmSts  = 0;
    fac_is.RelativeHumidityAlarmSts  = 0;

    alarm_id = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t check_fac_is_alarms()
{
    uint8_t test = 0;

    test |= fac_is.VdcLinkAlarmSts;
    test |= fac_is.IinAlarmSts;
    test |= fac_is.TempIGBT1AlarmSts;
    test |= fac_is.TempLAlarmSts;
    test |= fac_is.TempHeatSinkAlarmSts;
    test |= fac_is.DriveVoltageAlarmSts;
    test |= fac_is.Drive1CurrentAlarmSts;
    test |= fac_is.BoardTemperatureAlarmSts;
    test |= fac_is.RelativeHumidityAlarmSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void check_fac_is_indication_leds()
{
    // Dc-Link Overvoltage
    if(fac_is.VdcLinkItlkSts) Led2TurnOff();
    else if(fac_is.VdcLinkAlarmSts) Led2Toggle();
    else Led2TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    // Input Over Current
    if(fac_is.IinItlkSts) Led3TurnOff();
    else if(fac_is.IinAlarmSts) Led3Toggle();
    else Led3TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks do Driver 1
    if(fac_is.Driver1ErrorTopItlkSts || fac_is.Driver1ErrorBotItlkSts) Led4TurnOff();
    else Led4TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    // Heatsink Over Temperature
    if(fac_is.TempHeatSinkItlkSts) Led5TurnOff();
    else if(fac_is.TempHeatSinkAlarmSts) Led5Toggle();
    else Led5TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    // Inductor Over Temperature
    if(fac_is.TempLItlkSts) Led6TurnOff();
    else if(fac_is.TempLAlarmSts) Led6Toggle();
    else Led6TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Over temperature igbt1
    if(fac_is.TempIGBT1ItlkSts || fac_is.TempIGBT1HwrItlkSts) Led7TurnOff();
    else if(fac_is.TempIGBT1AlarmSts) Led7Toggle();
    else Led7TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks do Driver
    if(fac_is.DriveVoltageItlkSts || fac_is.Drive1CurrentItlkSts) Led8TurnOff();
    else if(fac_is.DriveVoltageAlarmSts || fac_is.Drive1CurrentAlarmSts) Led8Toggle();
    else Led8TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock Temperatura PCB
    if(fac_is.BoardTemperatureItlkSts) Led9TurnOff();
    else if(fac_is.BoardTemperatureAlarmSts) Led9Toggle();
    else Led9TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock Umidade Relativa
    if(fac_is.RelativeHumidityItlkSts) Led10TurnOff();
    else if(fac_is.RelativeHumidityAlarmSts) Led10Toggle();
    else Led10TurnOn();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void fac_is_application_readings()
{
    //PT100 CH1 Dissipador
    fac_is.TempHeatSink.f = (float) Pt100ReadCh1();
    fac_is.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
    if(!fac_is.TempHeatSinkItlkSts)fac_is.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH2 Indutor
    fac_is.TempL.f = (float) Pt100ReadCh2();
    fac_is.TempLAlarmSts = Pt100ReadCh2AlarmSts();
    if(!fac_is.TempLItlkSts)fac_is.TempLItlkSts = Pt100ReadCh2TripSts();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT1
    fac_is.TempIGBT1.f = (float) TempIgbt1Read();
    fac_is.TempIGBT1AlarmSts = TempIgbt1AlarmStatusRead();
    if(!fac_is.TempIGBT1ItlkSts)fac_is.TempIGBT1ItlkSts = TempIgbt1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT1 Hardware
    fac_is.TempIGBT1HwrItlk = Driver1OverTempRead();//Variavel usada para debug
    if(!fac_is.TempIGBT1HwrItlkSts)fac_is.TempIGBT1HwrItlkSts = Driver1OverTempRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura PCB IIB
    fac_is.BoardTemperature.f = (float) BoardTempRead();
    fac_is.BoardTemperatureAlarmSts = BoardTempAlarmStatusRead();
    if(!fac_is.BoardTemperatureItlkSts)fac_is.BoardTemperatureItlkSts = BoardTempTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Umidade Relativa
    fac_is.RelativeHumidity.f = (float) RhRead();
    fac_is.RelativeHumidityAlarmSts = RhAlarmStatusRead();
    if(!fac_is.RelativeHumidityItlkSts)fac_is.RelativeHumidityItlkSts = RhTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //DriverVotage
    fac_is.DriveVoltage.f = DriverVoltageRead();
    fac_is.DriveVoltageAlarmSts = DriverVoltageAlarmStatusRead();
    if(!fac_is.DriveVoltageItlkSts)fac_is.DriveVoltageItlkSts = DriverVolatgeTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Drive1Current
    fac_is.Drive1Current.f = Driver1CurrentRead();
    fac_is.Drive1CurrentAlarmSts = Driver1CurrentAlarmStatusRead();
    if(!fac_is.Drive1CurrentItlkSts)fac_is.Drive1CurrentItlkSts = Driver1CurrentTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    fac_is.VdcLink.f = LvCurrentCh1Read();
    fac_is.VdcLinkAlarmSts = LvCurrentCh1AlarmStatusRead();
    if(!fac_is.VdcLinkItlkSts)fac_is.VdcLinkItlkSts = LvCurrentCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    fac_is.Iin.f = CurrentCh1Read();
    fac_is.IinAlarmSts = CurrentCh1AlarmStatusRead();
    if(!fac_is.IinItlkSts)fac_is.IinItlkSts = CurrentCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 1 Top
    fac_is.Driver1ErrorTop = Driver1TopErrorRead();//Variavel usada para debug
    if(!fac_is.Driver1ErrorTopItlkSts)fac_is.Driver1ErrorTopItlkSts = Driver1TopErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 1 Bot
    fac_is.Driver1ErrorBot = Driver1BotErrorRead();//Variavel usada para debug
    if(!fac_is.Driver1ErrorBotItlkSts)fac_is.Driver1ErrorBotItlkSts = Driver1BotErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Se nao houver sinal na entrada digital dos 3 sinais, defina a acao como Interlock.
    if(fac_is.Driver1ErrorTopItlkSts || fac_is.Driver1ErrorBotItlkSts || fac_is.TempIGBT1HwrItlkSts) InterlockSet();

/////////////////////////////////////////////////////////////////////////////////////////////

    if (fac_is.VdcLinkItlkSts)              itlk_id |= FAC_IS_DCLINK_OVERVOLTAGE_ITLK;
    if (fac_is.IinItlkSts)                  itlk_id |= FAC_IS_INPUT_OVERCURRENT_ITLK;
    if (fac_is.TempIGBT1ItlkSts)            itlk_id |= FAC_IS_IGBT1_OVERTEMP_ITLK;
    if (fac_is.TempIGBT1HwrItlkSts)         itlk_id |= FAC_IS_IGBT1_HWR_OVERTEMP_ITLK;
    if (fac_is.DriveVoltageItlkSts)         itlk_id |= FAC_IS_DRIVER_OVERVOLTAGE_ITLK;
    if (fac_is.Drive1CurrentItlkSts)        itlk_id |= FAC_IS_DRIVER1_OVERCURRENT_ITLK;
    if (fac_is.Driver1ErrorTopItlkSts)      itlk_id |= FAC_IS_DRIVER1_ERROR_TOP_ITLK;
    if (fac_is.Driver1ErrorBotItlkSts)      itlk_id |= FAC_IS_DRIVER1_ERROR_BOT_ITLK;
    if (fac_is.TempLItlkSts)                itlk_id |= FAC_IS_INDUC_OVERTEMP_ITLK;
    if (fac_is.TempHeatSinkItlkSts)         itlk_id |= FAC_IS_HS_OVERTEMP_ITLK;
    if (fac_is.BoardTemperatureItlkSts)     itlk_id |= FAC_IS_BOARD_IIB_OVERTEMP_ITLK;
    if (fac_is.RelativeHumidityItlkSts)     itlk_id |= FAC_IS_BOARD_IIB_OVERHUMIDITY_ITLK;

/////////////////////////////////////////////////////////////////////////////////////////////

    if (fac_is.VdcLinkAlarmSts)             alarm_id |= FAC_IS_DCLINK_OVERVOLTAGE_ALM;
    if (fac_is.IinAlarmSts)                 alarm_id |= FAC_IS_INPUT_OVERCURRENT_ALM;
    if (fac_is.TempIGBT1AlarmSts)           alarm_id |= FAC_IS_IGBT1_OVERTEMP_ALM;
    if (fac_is.DriveVoltageAlarmSts)        alarm_id |= FAC_IS_DRIVER_OVERVOLTAGE_ALM;
    if (fac_is.Drive1CurrentAlarmSts)       alarm_id |= FAC_IS_DRIVER1_OVERCURRENT_ALM;
    if (fac_is.TempLAlarmSts)               alarm_id |= FAC_IS_INDUC_OVERTEMP_ALM;
    if (fac_is.TempHeatSinkAlarmSts)        alarm_id |= FAC_IS_HS_OVERTEMP_ALM;
    if (fac_is.BoardTemperatureAlarmSts)    alarm_id |= FAC_IS_BOARD_IIB_OVERTEMP_ALM;
    if (fac_is.RelativeHumidityAlarmSts)    alarm_id |= FAC_IS_BOARD_IIB_OVERHUMIDITY_ALM;

/////////////////////////////////////////////////////////////////////////////////////////////

    fac_is_interlocks_indication = itlk_id;
    fac_is_alarms_indication = alarm_id;

    g_controller_iib.iib_itlk[0].u32        = fac_is_interlocks_indication;
    g_controller_iib.iib_itlk[1].u32        = ResetInterlocksRegister;

    g_controller_iib.iib_alarm[0].u32       = fac_is_alarms_indication;
    g_controller_iib.iib_alarm[1].u32       = ResetAlarmsRegister;

    g_controller_iib.iib_signals[0].f       = fac_is.VdcLink.f;
    g_controller_iib.iib_signals[1].f       = fac_is.Iin.f;
    g_controller_iib.iib_signals[2].f       = fac_is.TempIGBT1.f;
    g_controller_iib.iib_signals[3].f       = fac_is.DriveVoltage.f;
    g_controller_iib.iib_signals[4].f       = fac_is.Drive1Current.f;
    g_controller_iib.iib_signals[5].f       = fac_is.TempL.f;
    g_controller_iib.iib_signals[6].f       = fac_is.TempHeatSink.f;
    g_controller_iib.iib_signals[7].f       = fac_is.BoardTemperature.f;
    g_controller_iib.iib_signals[8].f       = fac_is.RelativeHumidity.f;

}

/////////////////////////////////////////////////////////////////////////////////////////////

void config_module_fac_is(void)
{

#ifdef FAC_IS

    /* Set current range */
    CurrentCh1Init(Hall_Primary_Current, Hall_Secondary_Current, Hall_Burden_Resistor, Hall_Delay); /* Input current */

    /* Protection Limits */
    CurrentCh1AlarmLevelSet(FAC_IS_INPUT_OVERCURRENT_ALM_LIM);
    CurrentCh1TripLevelSet(FAC_IS_INPUT_OVERCURRENT_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    /* Isolated Voltage */
    LvCurrentCh1Init(LV_Primary_Voltage_Vin, LV_Secondary_Current_Vin, LV_Burden_Resistor, Delay_Voltage_Vin); /* Input Voltage */

    /* Protection Limits */
    LvCurrentCh1AlarmLevelSet(FAC_IS_DCLINK_OVERVOLTAGE_ALM_LIM);
    LvCurrentCh1TripLevelSet(FAC_IS_DCLINK_OVERVOLTAGE_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 configuration
    //Delay 2 seconds
    Pt100SetCh1Delay(Delay_PT100CH1);
    Pt100SetCh2Delay(Delay_PT100CH2);

    /* Pt-100 Configuration Limits */
    Pt100SetCh1AlarmLevel(FAC_IS_HS_OVERTEMP_ALM_LIM);
    Pt100SetCh1TripLevel(FAC_IS_HS_OVERTEMP_ITLK_LIM);
    Pt100SetCh2AlarmLevel(FAC_IS_INDUC_OVERTEMP_ALM_LIM);
    Pt100SetCh2TripLevel(FAC_IS_INDUC_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature igbt1 configuration
    TempIgbt1Delay(Delay_IGBT1); //Inserir valor de delay

    //Temp Igbt1 configuration limits
    TempIgbt1AlarmLevelSet(FAC_IS_IGBT1_OVERTEMP_ALM_LIM);
    TempIgbt1TripLevelSet(FAC_IS_IGBT1_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature Board configuration
    BoardTempDelay(Delay_BoardTemp); //Inserir valor de delay

    //Temp board configuration limits
    BoardTempAlarmLevelSet(FAC_IS_BOARD_OVERTEMP_ALM_LIM);
    BoardTempTripLevelSet(FAC_IS_BOARD_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Humidity Board configuration
    RhDelay(Delay_BoardRh); //Inserir valor de delay

    //Rh configuration limits
    RhAlarmLevelSet(FAC_IS_RH_OVERHUMIDITY_ALM_LIM);
    RhTripLevelSet(FAC_IS_RH_OVERHUMIDITY_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Voltage configuration
    DriverVoltageInit();

    DriverVoltageDelay(Delay_DriverVoltage); //Inserir valor de delay

    //Limite de alarme e interlock da tensao dos drivers
    DriverVoltageAlarmLevelSet(FAC_IS_DRIVER_OVERVOLTAGE_ALM_LIM);
    DriverVoltageTripLevelSet(FAC_IS_DRIVER_OVERVOLTAGE_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Current configuration
    DriverCurrentInit();

    DriverCurrentDelay(Delay_DriverCurrent); //Inserir valor de delay

    //Limite de alarme e interlock da corrente do driver 1
    Driver1CurrentAlarmLevelSet(FAC_IS_DRIVER1_OVERCURRENT_ALM_LIM);
    Driver1CurrentTripLevelSet(FAC_IS_DRIVER1_OVERCURRENT_ITLK_LIM);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    // Init Variables
    fac_is.Iin.f                      = 0.0;
    fac_is.IinAlarmSts                = 0;
    fac_is.IinItlkSts                 = 0;
    fac_is.VdcLink.f                  = 0.0;
    fac_is.VdcLinkAlarmSts            = 0;
    fac_is.VdcLinkItlkSts             = 0;
    fac_is.TempIGBT1.f                = 0.0;
    fac_is.TempIGBT1AlarmSts          = 0;
    fac_is.TempIGBT1ItlkSts           = 0;
    fac_is.TempIGBT1HwrItlk           = 0;
    fac_is.TempIGBT1HwrItlkSts        = 0;
    fac_is.DriveVoltage.f             = 0.0;
    fac_is.DriveVoltageAlarmSts       = 0;
    fac_is.DriveVoltageItlkSts        = 0;
    fac_is.Drive1Current.f            = 0.0;
    fac_is.Drive1CurrentAlarmSts      = 0;
    fac_is.Drive1CurrentItlkSts       = 0;
    fac_is.Driver1ErrorTop            = 0;
    fac_is.Driver1ErrorTopItlkSts     = 0;
    fac_is.Driver1ErrorBot            = 0;
    fac_is.Driver1ErrorBotItlkSts     = 0;
    fac_is.TempL.f                    = 0.0;
    fac_is.TempLAlarmSts              = 0;
    fac_is.TempLItlkSts               = 0;
    fac_is.TempHeatSink.f             = 0.0;
    fac_is.TempHeatSinkAlarmSts       = 0;
    fac_is.TempHeatSinkItlkSts        = 0;
    fac_is.BoardTemperature.f         = 0.0;
    fac_is.BoardTemperatureAlarmSts   = 0;
    fac_is.BoardTemperatureItlkSts    = 0;
    fac_is.RelativeHumidity.f         = 0.0;
    fac_is.RelativeHumidityAlarmSts   = 0;
    fac_is.RelativeHumidityItlkSts    = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////





