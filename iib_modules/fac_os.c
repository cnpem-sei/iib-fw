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
 * @file fac_os.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 28 de ago de 2018
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#include <iib_modules/fac_os.h>
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

volatile fac_os_t fac_os;

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_fac_os_interlocks()
{
    fac_os.VdcLinkItlkSts           = 0;
    fac_os.IinItlkSts               = 0;
    fac_os.IoutItlkSts              = 0;
    fac_os.TempIGBT1ItlkSts         = 0;
    fac_os.TempIGBT1HwrItlkSts      = 0;
    fac_os.TempIGBT2ItlkSts         = 0;
    fac_os.TempIGBT2HwrItlkSts      = 0;
    fac_os.Driver1ErrorTopItlkSts   = 0;
    fac_os.Driver1ErrorBotItlkSts   = 0;
    fac_os.Driver2ErrorTopItlkSts   = 0;
    fac_os.Driver2ErrorBotItlkSts   = 0;
    fac_os.GroundLeakageItlkSts     = 0;
    fac_os.TempLItlkSts             = 0;
    fac_os.TempHeatSinkItlkSts      = 0;
    fac_os.DriverVoltageItlkSts     = 0;
    fac_os.Driver1CurrentItlkSts    = 0;
    fac_os.Driver2CurrentItlkSts    = 0;
    fac_os.BoardTemperatureItlkSts  = 0;
    fac_os.RelativeHumidityItlkSts  = 0;

    fac_os.InterlocksRegister.u32   = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t check_fac_os_interlocks()
{
    uint8_t test = 0;

    test |= fac_os.VdcLinkItlkSts;
    test |= fac_os.IinItlkSts;
    test |= fac_os.IoutItlkSts;
    test |= fac_os.TempIGBT1ItlkSts;
    test |= fac_os.TempIGBT1HwrItlkSts;
    test |= fac_os.TempIGBT2ItlkSts;
    test |= fac_os.TempIGBT2HwrItlkSts;
    test |= fac_os.Driver1ErrorTopItlkSts;
    test |= fac_os.Driver1ErrorBotItlkSts;
    test |= fac_os.Driver2ErrorTopItlkSts;
    test |= fac_os.Driver2ErrorBotItlkSts;
    test |= fac_os.GroundLeakageItlkSts;
    test |= fac_os.TempLItlkSts;
    test |= fac_os.TempHeatSinkItlkSts;
    test |= fac_os.DriverVoltageItlkSts;
    test |= fac_os.Driver1CurrentItlkSts;
    test |= fac_os.Driver2CurrentItlkSts;
    test |= fac_os.BoardTemperatureItlkSts;
    test |= fac_os.RelativeHumidityItlkSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_fac_os_alarms()
{
    fac_os.VdcLinkAlarmSts           = 0;
    fac_os.IinAlarmSts               = 0;
    fac_os.IoutAlarmSts              = 0;
    fac_os.TempIGBT1AlarmSts         = 0;
    fac_os.TempIGBT2AlarmSts         = 0;
    fac_os.GroundLeakageAlarmSts     = 0;
    fac_os.TempLAlarmSts             = 0;
    fac_os.TempHeatSinkAlarmSts      = 0;
    fac_os.DriverVoltageAlarmSts     = 0;
    fac_os.Driver1CurrentAlarmSts    = 0;
    fac_os.Driver2CurrentAlarmSts    = 0;
    fac_os.BoardTemperatureAlarmSts  = 0;
    fac_os.RelativeHumidityAlarmSts  = 0;

    fac_os.AlarmsRegister.u32        = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t check_fac_os_alarms()
{
    uint8_t test = 0;

    test |= fac_os.VdcLinkAlarmSts;
    test |= fac_os.IinAlarmSts;
    test |= fac_os.IoutAlarmSts;
    test |= fac_os.TempIGBT1AlarmSts;
    test |= fac_os.TempIGBT2AlarmSts;
    test |= fac_os.GroundLeakageAlarmSts;
    test |= fac_os.TempLAlarmSts;
    test |= fac_os.TempHeatSinkAlarmSts;
    test |= fac_os.DriverVoltageAlarmSts;
    test |= fac_os.Driver1CurrentAlarmSts;
    test |= fac_os.Driver2CurrentAlarmSts;
    test |= fac_os.BoardTemperatureAlarmSts;
    test |= fac_os.RelativeHumidityAlarmSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void check_fac_os_indication_leds()
{
    //Input over voltage
    if(fac_os.VdcLinkItlkSts) Led2TurnOff();
    else if(fac_os.VdcLinkAlarmSts) Led2Toggle();
    else Led2TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Input over current
    if(fac_os.IinItlkSts) Led3TurnOff();
    else if(fac_os.IinAlarmSts) Led3Toggle();
    else Led3TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Output over current
    if(fac_os.IoutItlkSts) Led4TurnOff();
    else if(fac_os.IoutAlarmSts) Led4Toggle();
    else Led4TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks dos Drivers
    if(fac_os.Driver1ErrorTopItlkSts || fac_os.Driver1ErrorBotItlkSts || fac_os.Driver2ErrorTopItlkSts || fac_os.Driver2ErrorBotItlkSts) Led5TurnOff();
    else Led5TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    // Heatsink and Inductor Over temperature
    if(fac_os.TempHeatSinkItlkSts || fac_os.TempLItlkSts) Led6TurnOff();
    else if(fac_os.TempHeatSinkAlarmSts || fac_os.TempLAlarmSts) Led6Toggle();
    else Led6TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Fuga para o Terra
    if(fac_os.GroundLeakageItlkSts) Led7TurnOff();
    else if(fac_os.GroundLeakageAlarmSts) Led7Toggle();
    else Led7TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Over temperature igbt1 and igbt2
    if(fac_os.TempIGBT1ItlkSts || fac_os.TempIGBT1HwrItlkSts || fac_os.TempIGBT2ItlkSts || fac_os.TempIGBT2HwrItlkSts) Led8TurnOff();
    else if(fac_os.TempIGBT1AlarmSts || fac_os.TempIGBT2AlarmSts) Led8Toggle();
    else Led8TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks dos Drivers
    if(fac_os.DriverVoltageItlkSts || fac_os.Driver1CurrentItlkSts || fac_os.Driver2CurrentItlkSts) Led9TurnOff();
    else if(fac_os.DriverVoltageAlarmSts || fac_os.Driver1CurrentAlarmSts || fac_os.Driver2CurrentAlarmSts) Led9Toggle();
    else Led9TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock Temperatura PCB e Umidade Relativa
    if(fac_os.BoardTemperatureItlkSts || fac_os.RelativeHumidityItlkSts) Led10TurnOff();
    else if(fac_os.BoardTemperatureAlarmSts || fac_os.RelativeHumidityAlarmSts) Led10Toggle();
    else Led10TurnOn();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void fac_os_application_readings()
{
    //PT100 CH1 Dissipador
    fac_os.TempHeatSink.f = Pt100Ch1Read();
    fac_os.TempHeatSinkAlarmSts = Pt100Ch1AlarmStatusRead();
    if(!fac_os.TempHeatSinkItlkSts)fac_os.TempHeatSinkItlkSts = Pt100Ch1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH2 Indutor
    fac_os.TempL.f = Pt100Ch2Read();
    fac_os.TempLAlarmSts = Pt100Ch2AlarmStatusRead();
    if(!fac_os.TempLItlkSts)fac_os.TempLItlkSts = Pt100Ch2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT1
    fac_os.TempIGBT1.f = TempIgbt1Read();
    fac_os.TempIGBT1AlarmSts = TempIgbt1AlarmStatusRead();
    if(!fac_os.TempIGBT1ItlkSts)fac_os.TempIGBT1ItlkSts = TempIgbt1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT1 Hardware
    fac_os.TempIGBT1HwrItlk = Driver1OverTempRead();//Variavel usada para debug
    if(!fac_os.TempIGBT1HwrItlkSts)fac_os.TempIGBT1HwrItlkSts = Driver1OverTempRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT2
    fac_os.TempIGBT2.f = TempIgbt2Read();
    fac_os.TempIGBT2AlarmSts = TempIgbt2AlarmStatusRead();
    if(!fac_os.TempIGBT2ItlkSts)fac_os.TempIGBT2ItlkSts = TempIgbt2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura IGBT2 Hardware
    fac_os.TempIGBT2HwrItlk = Driver2OverTempRead();//Variavel usada para debug
    if(!fac_os.TempIGBT2HwrItlkSts)fac_os.TempIGBT2HwrItlkSts = Driver2OverTempRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura PCB IIB
    fac_os.BoardTemperature.f = BoardTempRead();
    fac_os.BoardTemperatureAlarmSts = BoardTempAlarmStatusRead();

#if (ItlkBoardTempEnable == 1)

    if(!fac_os.BoardTemperatureItlkSts)fac_os.BoardTemperatureItlkSts = BoardTempTripStatusRead();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //Umidade Relativa
    fac_os.RelativeHumidity.f = RhRead();
    fac_os.RelativeHumidityAlarmSts = RhAlarmStatusRead();

#if (ItlkRhEnable == 1)

    if(!fac_os.RelativeHumidityItlkSts)fac_os.RelativeHumidityItlkSts = RhTripStatusRead();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //DriverVotage
    fac_os.DriverVoltage.f = DriverVoltageRead();
    fac_os.DriverVoltageAlarmSts = DriverVoltageAlarmStatusRead();
    if(!fac_os.DriverVoltageItlkSts)fac_os.DriverVoltageItlkSts = DriverVolatgeTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Drive1Current
    fac_os.Driver1Current.f = Driver1CurrentRead();
    fac_os.Driver1CurrentAlarmSts = Driver1CurrentAlarmStatusRead();
    if(!fac_os.Driver1CurrentItlkSts)fac_os.Driver1CurrentItlkSts = Driver1CurrentTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Drive2Current
    fac_os.Driver2Current.f = Driver2CurrentRead();
    fac_os.Driver2CurrentAlarmSts = Driver2CurrentAlarmStatusRead();
    if(!fac_os.Driver2CurrentItlkSts)fac_os.Driver2CurrentItlkSts = Driver2CurrentTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    fac_os.VdcLink.f = LvCurrentCh1Read();
    fac_os.VdcLinkAlarmSts = LvCurrentCh1AlarmStatusRead();
    if(!fac_os.VdcLinkItlkSts)fac_os.VdcLinkItlkSts = LvCurrentCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Medida de Fuga para o Terra
    fac_os.GroundLeakage.f = LvCurrentCh3Read();
    fac_os.GroundLeakageAlarmSts = LvCurrentCh3AlarmStatusRead();
    if(!fac_os.GroundLeakageItlkSts)fac_os.GroundLeakageItlkSts = LvCurrentCh3TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    fac_os.Iin.f = CurrentCh1Read();
    fac_os.IinAlarmSts = CurrentCh1AlarmStatusRead();
    if(!fac_os.IinItlkSts)fac_os.IinItlkSts = CurrentCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    fac_os.Iout.f = CurrentCh2Read();
    fac_os.IoutAlarmSts = CurrentCh2AlarmStatusRead();
    if(!fac_os.IoutItlkSts)fac_os.IoutItlkSts = CurrentCh2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 1 Top
    fac_os.Driver1ErrorTop = Driver1TopErrorRead();//Variavel usada para debug
    if(!fac_os.Driver1ErrorTopItlkSts)fac_os.Driver1ErrorTopItlkSts = Driver1TopErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 1 Bot
    fac_os.Driver1ErrorBot = Driver1BotErrorRead();//Variavel usada para debug
    if(!fac_os.Driver1ErrorBotItlkSts)fac_os.Driver1ErrorBotItlkSts = Driver1BotErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 2 Top
    fac_os.Driver2ErrorTop = Driver2TopErrorRead();//Variavel usada para debug
    if(!fac_os.Driver2ErrorTopItlkSts)fac_os.Driver2ErrorTopItlkSts = Driver2TopErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 2 Bot
    fac_os.Driver2ErrorBot = Driver2BotErrorRead();//Variavel usada para debug
    if(!fac_os.Driver2ErrorBotItlkSts)fac_os.Driver2ErrorBotItlkSts = Driver2BotErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Se nao houver sinal na entrada digital dos 6 sinais, defina a acao como Interlock.
    if(fac_os.Driver1ErrorTopItlkSts || fac_os.Driver1ErrorBotItlkSts || fac_os.Driver2ErrorTopItlkSts || fac_os.Driver2ErrorBotItlkSts
       || fac_os.TempIGBT1HwrItlkSts || fac_os.TempIGBT2HwrItlkSts) InterlockSet();

/////////////////////////////////////////////////////////////////////////////////////////////

    if(Interlock == 1)
    {
    	if (fac_os.VdcLinkItlkSts)              fac_os.InterlocksRegister.u32 |= FAC_OS_INPUT_OVERVOLTAGE_ITLK;
    	if (fac_os.IinItlkSts)                  fac_os.InterlocksRegister.u32 |= FAC_OS_INPUT_OVERCURRENT_ITLK;
    	if (fac_os.IoutItlkSts)                 fac_os.InterlocksRegister.u32 |= FAC_OS_OUTPUT_OVERCURRENT_ITLK;
    	if (fac_os.TempIGBT1ItlkSts)            fac_os.InterlocksRegister.u32 |= FAC_OS_IGBT1_OVERTEMP_ITLK;
    	if (fac_os.TempIGBT1HwrItlkSts)         fac_os.InterlocksRegister.u32 |= FAC_OS_IGBT1_HWR_OVERTEMP_ITLK;
    	if (fac_os.TempIGBT2ItlkSts)            fac_os.InterlocksRegister.u32 |= FAC_OS_IGBT2_OVERTEMP_ITLK;
    	if (fac_os.TempIGBT2HwrItlkSts)         fac_os.InterlocksRegister.u32 |= FAC_OS_IGBT2_HWR_OVERTEMP_ITLK;
    	if (fac_os.DriverVoltageItlkSts)        fac_os.InterlocksRegister.u32 |= FAC_OS_DRIVER_OVERVOLTAGE_ITLK;
    	if (fac_os.Driver1CurrentItlkSts)       fac_os.InterlocksRegister.u32 |= FAC_OS_DRIVER1_OVERCURRENT_ITLK;
    	if (fac_os.Driver2CurrentItlkSts)       fac_os.InterlocksRegister.u32 |= FAC_OS_DRIVER2_OVERCURRENT_ITLK;
    	if (fac_os.Driver1ErrorTopItlkSts)      fac_os.InterlocksRegister.u32 |= FAC_OS_DRIVER1_ERROR_TOP_ITLK;
    	if (fac_os.Driver1ErrorBotItlkSts)      fac_os.InterlocksRegister.u32 |= FAC_OS_DRIVER1_ERROR_BOT_ITLK;
    	if (fac_os.Driver2ErrorTopItlkSts)      fac_os.InterlocksRegister.u32 |= FAC_OS_DRIVER2_ERROR_TOP_ITLK;
    	if (fac_os.Driver2ErrorBotItlkSts)      fac_os.InterlocksRegister.u32 |= FAC_OS_DRIVER2_ERROR_BOT_ITLK;
    	if (fac_os.TempLItlkSts)                fac_os.InterlocksRegister.u32 |= FAC_OS_INDUC_OVERTEMP_ITLK;
    	if (fac_os.TempHeatSinkItlkSts)         fac_os.InterlocksRegister.u32 |= FAC_OS_HS_OVERTEMP_ITLK;
    	if (fac_os.GroundLeakageItlkSts)        fac_os.InterlocksRegister.u32 |= FAC_OS_GROUND_LKG_ITLK;
    	if (fac_os.BoardTemperatureItlkSts)     fac_os.InterlocksRegister.u32 |= FAC_OS_BOARD_IIB_OVERTEMP_ITLK;
    	if (fac_os.RelativeHumidityItlkSts)     fac_os.InterlocksRegister.u32 |= FAC_OS_BOARD_IIB_OVERHUMIDITY_ITLK;
    }

    else
    {
    	fac_os.InterlocksRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    if(Alarm == 1)
    {
    	if (fac_os.VdcLinkAlarmSts)             fac_os.AlarmsRegister.u32 |= FAC_OS_INPUT_OVERVOLTAGE_ALM;
    	if (fac_os.IinAlarmSts)                 fac_os.AlarmsRegister.u32 |= FAC_OS_INPUT_OVERCURRENT_ALM;
    	if (fac_os.IoutAlarmSts)                fac_os.AlarmsRegister.u32 |= FAC_OS_OUTPUT_OVERCURRENT_ALM;
    	if (fac_os.TempIGBT1AlarmSts)           fac_os.AlarmsRegister.u32 |= FAC_OS_IGBT1_OVERTEMP_ALM;
    	if (fac_os.TempIGBT2AlarmSts)           fac_os.AlarmsRegister.u32 |= FAC_OS_IGBT2_OVERTEMP_ALM;
    	if (fac_os.DriverVoltageAlarmSts)       fac_os.AlarmsRegister.u32 |= FAC_OS_DRIVER_OVERVOLTAGE_ALM;
    	if (fac_os.Driver1CurrentAlarmSts)      fac_os.AlarmsRegister.u32 |= FAC_OS_DRIVER1_OVERCURRENT_ALM;
    	if (fac_os.Driver2CurrentAlarmSts)      fac_os.AlarmsRegister.u32 |= FAC_OS_DRIVER2_OVERCURRENT_ALM;
    	if (fac_os.TempLAlarmSts)               fac_os.AlarmsRegister.u32 |= FAC_OS_INDUC_OVERTEMP_ALM;
    	if (fac_os.TempHeatSinkAlarmSts)        fac_os.AlarmsRegister.u32 |= FAC_OS_HS_OVERTEMP_ALM;
    	if (fac_os.GroundLeakageAlarmSts)       fac_os.AlarmsRegister.u32 |= FAC_OS_GROUND_LKG_ALM;
    	if (fac_os.BoardTemperatureAlarmSts)    fac_os.AlarmsRegister.u32 |= FAC_OS_BOARD_IIB_OVERTEMP_ALM;
    	if (fac_os.RelativeHumidityAlarmSts)    fac_os.AlarmsRegister.u32 |= FAC_OS_BOARD_IIB_OVERHUMIDITY_ALM;
    }

    else
    {
    	fac_os.AlarmsRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    g_controller_iib.iib_signals[0].f       = fac_os.VdcLink.f;
    g_controller_iib.iib_signals[1].f       = fac_os.Iin.f;
    g_controller_iib.iib_signals[2].f       = fac_os.Iout.f;
    g_controller_iib.iib_signals[3].f       = fac_os.TempIGBT1.f;
    g_controller_iib.iib_signals[4].f       = fac_os.TempIGBT2.f;
    g_controller_iib.iib_signals[5].f       = fac_os.DriverVoltage.f;
    g_controller_iib.iib_signals[6].f       = fac_os.Driver1Current.f;
    g_controller_iib.iib_signals[7].f       = fac_os.Driver2Current.f;
    g_controller_iib.iib_signals[8].f       = fac_os.GroundLeakage.f;
    g_controller_iib.iib_signals[9].f       = fac_os.TempL.f;
    g_controller_iib.iib_signals[10].f      = fac_os.TempHeatSink.f;
    g_controller_iib.iib_signals[11].f      = fac_os.BoardTemperature.f;
    g_controller_iib.iib_signals[12].f      = fac_os.RelativeHumidity.f;
    g_controller_iib.iib_signals[13].u32    = fac_os.InterlocksRegister.u32;
    g_controller_iib.iib_signals[14].u32    = fac_os.AlarmsRegister.u32;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void config_module_fac_os(void)
{

#ifdef FAC_OS

    /* Set current range */
    CurrentCh1Init(Hall_Primary_Current_Iin, Hall_Secondary_Current_Iin, Hall_Burden_Resistor, Hall_Delay); /* Input */
    CurrentCh2Init(Hall_Primary_Current_Iout, Hall_Secondary_Current_Iout, Hall_Burden_Resistor, Hall_Delay); /* Output */

    /* Protection Limits */
    CurrentCh1AlarmLevelSet(FAC_OS_INPUT_OVERCURRENT_ALM_LIM);
    CurrentCh1TripLevelSet(FAC_OS_INPUT_OVERCURRENT_ITLK_LIM);
    CurrentCh2AlarmLevelSet(FAC_OS_OUTPUT_OVERCURRENT_ALM_LIM);
    CurrentCh2TripLevelSet(FAC_OS_OUTPUT_OVERCURRENT_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    /* Isolated Voltage */
    LvCurrentCh1Init(LV_Primary_Voltage_Vin, LV_Secondary_Current_Vin, LV_Burden_Resistor, Delay_Voltage_Vin); /* Input Voltage */
    LvCurrentCh3Init(LV_Primary_Voltage_GND_Leakage, LV_Secondary_Current_Vin, LV_Burden_Resistor, Delay_GND_Leakage);  /* GND Leakage */

    /* Protection Limits */
    LvCurrentCh1AlarmLevelSet(FAC_OS_INPUT_OVERVOLTAGE_ALM_LIM);
    LvCurrentCh1TripLevelSet(FAC_OS_INPUT_OVERVOLTAGE_ITLK_LIM);
    LvCurrentCh3AlarmLevelSet(FAC_OS_GROUND_LEAKAGE_ALM_LIM);
    LvCurrentCh3TripLevelSet(FAC_OS_GROUND_LEAKAGE_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 configuration
    //Delay 2 seconds
    Pt100Ch1Delay(Delay_PT100CH1);
    Pt100Ch2Delay(Delay_PT100CH2);

    /* Pt-100 Configuration Limits */
    Pt100Ch1AlarmLevelSet(FAC_OS_HS_OVERTEMP_ALM_LIM);
    Pt100Ch1TripLevelSet(FAC_OS_HS_OVERTEMP_ITLK_LIM);
    Pt100Ch2AlarmLevelSet(FAC_OS_INDUC_OVERTEMP_ALM_LIM);
    Pt100Ch2TripLevelSet(FAC_OS_INDUC_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature igbt1 configuration
    TempIgbt1Delay(Delay_IGBT1); //Inserir valor de delay

    //Temp Igbt1 configuration limits
    TempIgbt1AlarmLevelSet(FAC_OS_IGBT1_OVERTEMP_ALM_LIM);
    TempIgbt1TripLevelSet(FAC_OS_IGBT1_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature igbt2 configuration
    TempIgbt2Delay(Delay_IGBT2); //Inserir valor de delay

    //Temp Igbt2 configuration limits
    TempIgbt2AlarmLevelSet(FAC_OS_IGBT2_OVERTEMP_ALM_LIM);
    TempIgbt2TripLevelSet(FAC_OS_IGBT2_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature Board configuration
    BoardTempDelay(Delay_BoardTemp); //Inserir valor de delay

    //Temp board configuration limits
    BoardTempAlarmLevelSet(FAC_OS_BOARD_OVERTEMP_ALM_LIM);
    BoardTempTripLevelSet(FAC_OS_BOARD_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Humidity Board configuration
    RhDelay(Delay_BoardRh); //Inserir valor de delay

    //Rh configuration limits
    RhAlarmLevelSet(FAC_OS_RH_OVERHUMIDITY_ALM_LIM);
    RhTripLevelSet(FAC_OS_RH_OVERHUMIDITY_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Voltage configuration
    DriverVoltageInit();

    DriverVoltageDelay(Delay_DriverVoltage); //Inserir valor de delay

    //Limite de alarme e interlock da tensao dos drivers
    DriverVoltageAlarmLevelSet(FAC_OS_DRIVER_OVERVOLTAGE_ALM_LIM);
    DriverVoltageTripLevelSet(FAC_OS_DRIVER_OVERVOLTAGE_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Current configuration
    DriverCurrentInit();

    DriverCurrentDelay(Delay_DriverCurrent); //Inserir valor de delay

    //Limite de alarme e interlock da corrente do driver 1
    Driver1CurrentAlarmLevelSet(FAC_OS_DRIVER1_OVERCURRENT_ALM_LIM);
    Driver1CurrentTripLevelSet(FAC_OS_DRIVER1_OVERCURRENT_ITLK_LIM);

    //Limite de alarme e interlock da corrente do driver 2
    Driver2CurrentAlarmLevelSet(FAC_OS_DRIVER2_OVERCURRENT_ALM_LIM);
    Driver2CurrentTripLevelSet(FAC_OS_DRIVER2_OVERCURRENT_ITLK_LIM);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //Init Variables
    fac_os.Iin.f                        = 0.0;
    fac_os.IinAlarmSts                  = 0;
    fac_os.IinItlkSts                   = 0;
    fac_os.Iout.f                       = 0.0;
    fac_os.IoutAlarmSts                 = 0;
    fac_os.IoutItlkSts                  = 0;
    fac_os.VdcLink.f                    = 0.0;
    fac_os.VdcLinkAlarmSts              = 0;
    fac_os.VdcLinkItlkSts               = 0;
    fac_os.TempIGBT1.f                  = 0.0;
    fac_os.TempIGBT1AlarmSts            = 0;
    fac_os.TempIGBT1ItlkSts             = 0;
    fac_os.TempIGBT1HwrItlk             = 0;
    fac_os.TempIGBT1HwrItlkSts          = 0;
    fac_os.TempIGBT2.f                  = 0.0;
    fac_os.TempIGBT2AlarmSts            = 0;
    fac_os.TempIGBT2ItlkSts             = 0;
    fac_os.TempIGBT2HwrItlk             = 0;
    fac_os.TempIGBT2HwrItlkSts          = 0;
    fac_os.DriverVoltage.f              = 0.0;
    fac_os.DriverVoltageAlarmSts        = 0;
    fac_os.DriverVoltageItlkSts         = 0;
    fac_os.Driver1Current.f             = 0.0;
    fac_os.Driver1CurrentAlarmSts       = 0;
    fac_os.Driver1CurrentItlkSts        = 0;
    fac_os.Driver2Current.f             = 0.0;
    fac_os.Driver2CurrentAlarmSts       = 0;
    fac_os.Driver2CurrentItlkSts        = 0;
    fac_os.Driver1ErrorTop              = 0;
    fac_os.Driver1ErrorTopItlkSts       = 0;
    fac_os.Driver1ErrorBot              = 0;
    fac_os.Driver1ErrorBotItlkSts       = 0;
    fac_os.Driver2ErrorTop              = 0;
    fac_os.Driver2ErrorTopItlkSts       = 0;
    fac_os.Driver2ErrorBot              = 0;
    fac_os.Driver2ErrorBotItlkSts       = 0;
    fac_os.GroundLeakage.f              = 0.0;
    fac_os.GroundLeakageAlarmSts        = 0;
    fac_os.GroundLeakageItlkSts         = 0;
    fac_os.TempL.f                      = 0.0;
    fac_os.TempLAlarmSts                = 0;
    fac_os.TempLItlkSts                 = 0;
    fac_os.TempHeatSink.f               = 0.0;
    fac_os.TempHeatSinkAlarmSts         = 0;
    fac_os.TempHeatSinkItlkSts          = 0;
    fac_os.BoardTemperature.f           = 0.0;
    fac_os.BoardTemperatureAlarmSts     = 0;
    fac_os.BoardTemperatureItlkSts      = 0;
    fac_os.RelativeHumidity.f           = 0.0;
    fac_os.RelativeHumidityAlarmSts     = 0;
    fac_os.RelativeHumidityItlkSts      = 0;
    fac_os.InterlocksRegister.u32       = 0;
    fac_os.AlarmsRegister.u32           = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////







