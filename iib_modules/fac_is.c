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

volatile fac_is_t fac_is;

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
    fac_is.DriverVoltageItlkSts      = 0;
    fac_is.Driver1CurrentItlkSts     = 0;
    fac_is.BoardTemperatureItlkSts   = 0;
    fac_is.RelativeHumidityItlkSts   = 0;

    fac_is.InterlocksRegister.u32    = 0;

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
    test |= fac_is.DriverVoltageItlkSts;
    test |= fac_is.Driver1CurrentItlkSts;
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
    fac_is.DriverVoltageAlarmSts     = 0;
    fac_is.Driver1CurrentAlarmSts    = 0;
    fac_is.BoardTemperatureAlarmSts  = 0;
    fac_is.RelativeHumidityAlarmSts  = 0;

    fac_is.AlarmsRegister.u32        = 0;

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
    test |= fac_is.DriverVoltageAlarmSts;
    test |= fac_is.Driver1CurrentAlarmSts;
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
    if(fac_is.DriverVoltageItlkSts || fac_is.Driver1CurrentItlkSts) Led8TurnOff();
    else if(fac_is.DriverVoltageAlarmSts || fac_is.Driver1CurrentAlarmSts) Led8Toggle();
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
    fac_is.TempHeatSink.f = Pt100Ch1Read();
    fac_is.TempHeatSinkAlarmSts = Pt100Ch1AlarmStatusRead();
    if(!fac_is.TempHeatSinkItlkSts)fac_is.TempHeatSinkItlkSts = Pt100Ch1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH2 Indutor
    fac_is.TempL.f = Pt100Ch2Read();
    fac_is.TempLAlarmSts = Pt100Ch2AlarmStatusRead();
    if(!fac_is.TempLItlkSts)fac_is.TempLItlkSts = Pt100Ch2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT1
    fac_is.TempIGBT1.f = TempIgbt1Read();
    fac_is.TempIGBT1AlarmSts = TempIgbt1AlarmStatusRead();
    if(!fac_is.TempIGBT1ItlkSts)fac_is.TempIGBT1ItlkSts = TempIgbt1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT1 Hardware
    fac_is.TempIGBT1HwrItlk = Driver1OverTempRead();//Variavel usada para debug
    if(!fac_is.TempIGBT1HwrItlkSts)fac_is.TempIGBT1HwrItlkSts = Driver1OverTempRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura PCB IIB
    fac_is.BoardTemperature.f = BoardTempRead();
    fac_is.BoardTemperatureAlarmSts = BoardTempAlarmStatusRead();

#if (ItlkBoardTempEnable == 1)

    if(!fac_is.BoardTemperatureItlkSts)fac_is.BoardTemperatureItlkSts = BoardTempTripStatusRead();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //Umidade Relativa
    fac_is.RelativeHumidity.f = RhRead();
    fac_is.RelativeHumidityAlarmSts = RhAlarmStatusRead();

#if (ItlkRhEnable == 1)

    if(!fac_is.RelativeHumidityItlkSts)fac_is.RelativeHumidityItlkSts = RhTripStatusRead();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //DriverVotage
    fac_is.DriverVoltage.f = DriverVoltageRead();
    fac_is.DriverVoltageAlarmSts = DriverVoltageAlarmStatusRead();
    if(!fac_is.DriverVoltageItlkSts)fac_is.DriverVoltageItlkSts = DriverVolatgeTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Drive1Current
    fac_is.Driver1Current.f = Driver1CurrentRead();
    fac_is.Driver1CurrentAlarmSts = Driver1CurrentAlarmStatusRead();
    if(!fac_is.Driver1CurrentItlkSts)fac_is.Driver1CurrentItlkSts = Driver1CurrentTripStatusRead();

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

    if(Interlock == 1)
    {
    	if (fac_is.VdcLinkItlkSts)              fac_is.InterlocksRegister.u32 |= FAC_IS_DCLINK_OVERVOLTAGE_ITLK;
    	if (fac_is.IinItlkSts)                  fac_is.InterlocksRegister.u32 |= FAC_IS_INPUT_OVERCURRENT_ITLK;
    	if (fac_is.TempIGBT1ItlkSts)            fac_is.InterlocksRegister.u32 |= FAC_IS_IGBT1_OVERTEMP_ITLK;
    	if (fac_is.TempIGBT1HwrItlkSts)         fac_is.InterlocksRegister.u32 |= FAC_IS_IGBT1_HWR_OVERTEMP_ITLK;
    	if (fac_is.DriverVoltageItlkSts)        fac_is.InterlocksRegister.u32 |= FAC_IS_DRIVER_OVERVOLTAGE_ITLK;
    	if (fac_is.Driver1CurrentItlkSts)       fac_is.InterlocksRegister.u32 |= FAC_IS_DRIVER1_OVERCURRENT_ITLK;
    	if (fac_is.Driver1ErrorTopItlkSts)      fac_is.InterlocksRegister.u32 |= FAC_IS_DRIVER1_ERROR_TOP_ITLK;
    	if (fac_is.Driver1ErrorBotItlkSts)      fac_is.InterlocksRegister.u32 |= FAC_IS_DRIVER1_ERROR_BOT_ITLK;
    	if (fac_is.TempLItlkSts)                fac_is.InterlocksRegister.u32 |= FAC_IS_INDUC_OVERTEMP_ITLK;
    	if (fac_is.TempHeatSinkItlkSts)         fac_is.InterlocksRegister.u32 |= FAC_IS_HS_OVERTEMP_ITLK;
    	if (fac_is.BoardTemperatureItlkSts)     fac_is.InterlocksRegister.u32 |= FAC_IS_BOARD_IIB_OVERTEMP_ITLK;
    	if (fac_is.RelativeHumidityItlkSts)     fac_is.InterlocksRegister.u32 |= FAC_IS_BOARD_IIB_OVERHUMIDITY_ITLK;
    }

    else
    {
    	fac_is.InterlocksRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    if(Alarm == 1)
    {
    	if (fac_is.VdcLinkAlarmSts)             fac_is.AlarmsRegister.u32 |= FAC_IS_DCLINK_OVERVOLTAGE_ALM;
    	if (fac_is.IinAlarmSts)                 fac_is.AlarmsRegister.u32 |= FAC_IS_INPUT_OVERCURRENT_ALM;
    	if (fac_is.TempIGBT1AlarmSts)           fac_is.AlarmsRegister.u32 |= FAC_IS_IGBT1_OVERTEMP_ALM;
    	if (fac_is.DriverVoltageAlarmSts)       fac_is.AlarmsRegister.u32 |= FAC_IS_DRIVER_OVERVOLTAGE_ALM;
    	if (fac_is.Driver1CurrentAlarmSts)      fac_is.AlarmsRegister.u32 |= FAC_IS_DRIVER1_OVERCURRENT_ALM;
    	if (fac_is.TempLAlarmSts)               fac_is.AlarmsRegister.u32 |= FAC_IS_INDUC_OVERTEMP_ALM;
    	if (fac_is.TempHeatSinkAlarmSts)        fac_is.AlarmsRegister.u32 |= FAC_IS_HS_OVERTEMP_ALM;
    	if (fac_is.BoardTemperatureAlarmSts)    fac_is.AlarmsRegister.u32 |= FAC_IS_BOARD_IIB_OVERTEMP_ALM;
    	if (fac_is.RelativeHumidityAlarmSts)    fac_is.AlarmsRegister.u32 |= FAC_IS_BOARD_IIB_OVERHUMIDITY_ALM;
    }

    else
    {
    	fac_is.AlarmsRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    g_controller_iib.iib_signals[0].f       = fac_is.VdcLink.f;
    g_controller_iib.iib_signals[1].f       = fac_is.Iin.f;
    g_controller_iib.iib_signals[2].f       = fac_is.TempIGBT1.f;
    g_controller_iib.iib_signals[3].f       = fac_is.DriverVoltage.f;
    g_controller_iib.iib_signals[4].f       = fac_is.Driver1Current.f;
    g_controller_iib.iib_signals[5].f       = fac_is.TempL.f;
    g_controller_iib.iib_signals[6].f       = fac_is.TempHeatSink.f;
    g_controller_iib.iib_signals[7].f       = fac_is.BoardTemperature.f;
    g_controller_iib.iib_signals[8].f       = fac_is.RelativeHumidity.f;
    g_controller_iib.iib_signals[9].u32     = fac_is.InterlocksRegister.u32;
    g_controller_iib.iib_signals[10].u32    = fac_is.AlarmsRegister.u32;
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
    Pt100Ch1Delay(Delay_PT100CH1);
    Pt100Ch2Delay(Delay_PT100CH2);

    /* Pt-100 Configuration Limits */
    Pt100Ch1AlarmLevelSet(FAC_IS_HS_OVERTEMP_ALM_LIM);
    Pt100Ch1TripLevelSet(FAC_IS_HS_OVERTEMP_ITLK_LIM);
    Pt100Ch2AlarmLevelSet(FAC_IS_INDUC_OVERTEMP_ALM_LIM);
    Pt100Ch2TripLevelSet(FAC_IS_INDUC_OVERTEMP_ITLK_LIM);

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
    fac_is.DriverVoltage.f            = 0.0;
    fac_is.DriverVoltageAlarmSts      = 0;
    fac_is.DriverVoltageItlkSts       = 0;
    fac_is.Driver1Current.f           = 0.0;
    fac_is.Driver1CurrentAlarmSts     = 0;
    fac_is.Driver1CurrentItlkSts      = 0;
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
    fac_is.InterlocksRegister.u32     = 0;
    fac_is.AlarmsRegister.u32         = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////





