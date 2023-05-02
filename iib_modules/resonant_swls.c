/******************************************************************************
 * Copyright (C) 2023 by LNLS - Brazilian Synchrotron Light Laboratory
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. LNLS and
 * the Brazilian Center for Research in Energy and Materials (CNPEM) are not
 * liable for any misuse of this material.
 *
 *****************************************************************************/

/**
 * @file resonant_swls.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author rogerio.marcondeli
 * @date 02/05/2023
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#include <iib_modules/resonant_swls.h>
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

volatile resonant_swls_t resonant_swls;

/////////////////////////////////////////////////////////////////////////////////////////////

static volatile uint8_t flag1 = 0;
static volatile uint32_t FiltroUP1 = 1024;

static volatile uint8_t flag2 = 0;
static volatile uint32_t FiltroUP2 = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_resonant_swls_interlocks()
{
    resonant_swls.RelayOpenItlkSts = 0;
    resonant_swls.RelayContactStickingItlkSts = 0;
    resonant_swls.ReleAuxItlkSts = 0;
    resonant_swls.ReleExtItlkSts = 0;

    flag1 = 0;
    FiltroUP1 = 1024;

    flag2 = 0;
    FiltroUP2 = 1024;

////////////////////////////////////////

    resonant_swls.VinItlkSts                  = 0;
    resonant_swls.VoutItlkSts                 = 0;
    resonant_swls.IinItlkSts                  = 0;
    resonant_swls.IoutItlkSts                 = 0;
    resonant_swls.GroundLeakageItlkSts        = 0;
    resonant_swls.TempInputInductorItlkSts    = 0;
    resonant_swls.TempOutputInductorItlkSts   = 0;
    resonant_swls.TempHeatSinkMosfetsItlkSts  = 0;
    resonant_swls.TempHeatSinkDiodesItlkSts   = 0;
    resonant_swls.DriverVoltageItlkSts        = 0;
    resonant_swls.Driver1CurrentItlkSts    	  = 0;
    resonant_swls.BoardTemperatureItlkSts     = 0;
    resonant_swls.RelativeHumidityItlkSts     = 0;

    resonant_swls.InterlocksRegister.u32      = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t check_resonant_swls_interlocks()
{
    uint8_t test = 0;

    test |= resonant_swls.VinItlkSts;
    test |= resonant_swls.VoutItlkSts;
    test |= resonant_swls.IinItlkSts;
    test |= resonant_swls.IoutItlkSts;
    test |= resonant_swls.GroundLeakageItlkSts;
    test |= resonant_swls.TempInputInductorItlkSts;
    test |= resonant_swls.TempOutputInductorItlkSts;
    test |= resonant_swls.TempHeatSinkMosfetsItlkSts;
    test |= resonant_swls.TempHeatSinkDiodesItlkSts;
    test |= resonant_swls.DriverVoltageItlkSts;
    test |= resonant_swls.Driver1CurrentItlkSts;
    test |= resonant_swls.BoardTemperatureItlkSts;
    test |= resonant_swls.RelativeHumidityItlkSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_resonant_swls_alarms()
{
    resonant_swls.VinAlarmSts                  = 0;
    resonant_swls.VoutAlarmSts                 = 0;
    resonant_swls.IinAlarmSts                  = 0;
    resonant_swls.IoutAlarmSts                 = 0;
    resonant_swls.TempInputInductorAlarmSts    = 0;
    resonant_swls.TempOutputInductorAlarmSts   = 0;
    resonant_swls.TempHeatSinkMosfetsAlarmSts  = 0;
    resonant_swls.TempHeatSinkDiodesAlarmSts   = 0;
    resonant_swls.DriverVoltageAlarmSts        = 0;
    resonant_swls.Driver1CurrentAlarmSts       = 0;
    resonant_swls.GroundLeakageAlarmSts        = 0;
    resonant_swls.BoardTemperatureAlarmSts     = 0;
    resonant_swls.RelativeHumidityAlarmSts     = 0;

    resonant_swls.AlarmsRegister.u32           = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t check_resonant_swls_alarms()
{
    uint8_t test = 0;

    test |= resonant_swls.VinAlarmSts;
    test |= resonant_swls.VoutAlarmSts;
    test |= resonant_swls.IinAlarmSts;
    test |= resonant_swls.IoutAlarmSts;
    test |= resonant_swls.TempInputInductorAlarmSts;
    test |= resonant_swls.TempOutputInductorAlarmSts;
    test |= resonant_swls.TempHeatSinkMosfetsAlarmSts;
    test |= resonant_swls.TempHeatSinkDiodesAlarmSts;
    test |= resonant_swls.DriverVoltageAlarmSts;
    test |= resonant_swls.Driver1CurrentAlarmSts;
    test |= resonant_swls.GroundLeakageAlarmSts;
    test |= resonant_swls.BoardTemperatureAlarmSts;
    test |= resonant_swls.RelativeHumidityAlarmSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void check_resonant_swls_indication_leds()
{
    //Input over voltage
    if(resonant_swls.VinItlkSts) Led2TurnOff();
    else if(resonant_swls.VinAlarmSts) Led2Toggle();
    else Led2TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Output  over voltage
    if(resonant_swls.VoutItlkSts) Led3TurnOff();
    else if(resonant_swls.VoutAlarmSts) Led3Toggle();
    else Led3TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Input over current
    if(resonant_swls.IinItlkSts) Led4TurnOff();
    else if(resonant_swls.IinAlarmSts) Led4Toggle();
    else Led4TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Output over current
    if(resonant_swls.IoutItlkSts) Led5TurnOff();
    else if(resonant_swls.IoutAlarmSts) Led5Toggle();
    else Led5TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Over temperature
    if(resonant_swls.TempInputInductorItlkSts || resonant_swls.TempOutputInductorItlkSts
    		||  resonant_swls.TempHeatSinkMosfetsItlkSts || resonant_swls.TempHeatSinkDiodesItlkSts) Led6TurnOff();
    else if(resonant_swls.TempInputInductorAlarmSts || resonant_swls.TempOutputInductorAlarmSts
    		||  resonant_swls.TempHeatSinkMosfetsAlarmSts || resonant_swls.TempHeatSinkDiodesAlarmSts) Led6Toggle();
    else Led6TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Fuga para o Terra
    if(resonant_swls.GroundLeakageItlkSts) Led7TurnOff();
    else if(resonant_swls.GroundLeakageAlarmSts) Led7Toggle();
    else Led7TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks dos Drivers
    if(resonant_swls.DriverVoltageItlkSts || resonant_swls.Driver1CurrentItlkSts) Led8TurnOff();
    else if(resonant_swls.DriverVoltageAlarmSts || resonant_swls.Driver1CurrentAlarmSts) Led8Toggle();
    else Led8TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock Temperatura PCB e Umidade Relativa
    if(resonant_swls.BoardTemperatureItlkSts || resonant_swls.RelativeHumidityItlkSts) Led9TurnOff();
    else if(resonant_swls.BoardTemperatureAlarmSts || resonant_swls.RelativeHumidityAlarmSts) Led9Toggle();
    else Led9TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks emergency button
    if(resonant_swls.EmergencyButtonItlkSts) Led10TurnOff();
    else Led10TurnOn();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void resonant_swls_application_readings()
{
    //PT100 CH1 Temperatura Indutor de entrada
    resonant_swls.TempInputInductor.f = Pt100Ch1Read();
    resonant_swls.TempInputInductorAlarmSts = Pt100Ch1AlarmStatusRead();
    if(!resonant_swls.TempInputInductorItlkSts)resonant_swls.TempInputInductorItlkSts = Pt100Ch1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH2 Temperatura Indutor de saída
    resonant_swls.TempOutputInductor.f = Pt100Ch2Read();
    resonant_swls.TempOutputInductorAlarmSts = Pt100Ch2AlarmStatusRead();
    if(!resonant_swls.TempOutputInductorItlkSts)resonant_swls.TempOutputInductorItlkSts = Pt100Ch2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH3 Temperatura Dissipador Mosfets
    resonant_swls.TempHeatSinkMosfets.f = Pt100Ch3Read();
    resonant_swls.TempHeatSinkMosfetsAlarmSts = Pt100Ch3AlarmStatusRead();
    if(!resonant_swls.TempHeatSinkMosfetsItlkSts)resonant_swls.TempHeatSinkMosfetsItlkSts = Pt100Ch3TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH4 Temperatura Dissipador Diodos
    resonant_swls.TempHeatSinkDiodes.f = Pt100Ch4Read();
    resonant_swls.TempHeatSinkDiodesAlarmSts = Pt100Ch4AlarmStatusRead();
    if(!resonant_swls.TempHeatSinkDiodesItlkSts)resonant_swls.TempHeatSinkDiodesItlkSts = Pt100Ch4TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperatura PCB IIB
    resonant_swls.BoardTemperature.f = BoardTempRead();
    resonant_swls.BoardTemperatureAlarmSts = BoardTempAlarmStatusRead();

#if (ItlkBoardTempEnable == 1)

    if(!resonant_swls.BoardTemperatureItlkSts)resonant_swls.BoardTemperatureItlkSts = BoardTempTripStatusRead();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //Umidade Relativa
    resonant_swls.RelativeHumidity.f = RhRead();
    resonant_swls.RelativeHumidityAlarmSts = RhAlarmStatusRead();

#if (ItlkRhEnable == 1)

    if(!resonant_swls.RelativeHumidityItlkSts)resonant_swls.RelativeHumidityItlkSts = RhTripStatusRead();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //DriverVoltage
    resonant_swls.DriverVoltage.f = DriverVoltageRead();
    resonant_swls.DriverVoltageAlarmSts = DriverVoltageAlarmStatusRead();
    if(!resonant_swls.DriverVoltageItlkSts)resonant_swls.DriverVoltageItlkSts = DriverVoltageTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Drive1Current
    resonant_swls.Driver1Current.f = Driver1CurrentRead();
    resonant_swls.Driver1CurrentAlarmSts = Driver1CurrentAlarmStatusRead();
    if(!resonant_swls.Driver1CurrentItlkSts)resonant_swls.Driver1CurrentItlkSts = Driver1CurrentTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////










    //Corrente de Saida IGBT1
    resonant_swls.IoutA1.f = CurrentCh1Read();//HALL CH1
    resonant_swls.IoutA1AlarmSts = CurrentCh1AlarmStatusRead();
    if(!resonant_swls.IoutA1ItlkSts)resonant_swls.IoutA1ItlkSts = CurrentCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Corrente de Saida IGBT2
    resonant_swls.IoutA2.f = CurrentCh2Read();//HALL CH2
    resonant_swls.IoutA2AlarmSts = CurrentCh2AlarmStatusRead();
    if(!resonant_swls.IoutA2ItlkSts)resonant_swls.IoutA2ItlkSts = CurrentCh2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Tensao de Entrada
    resonant_swls.Vin.f = LvCurrentCh1Read();
    resonant_swls.VinAlarmSts = LvCurrentCh1AlarmStatusRead();
    if(!resonant_swls.VinItlkSts)resonant_swls.VinItlkSts = LvCurrentCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Tensao de Saida
    resonant_swls.Vout.f = LvCurrentCh2Read();
    resonant_swls.VoutAlarmSts = LvCurrentCh2AlarmStatusRead();
    if(!resonant_swls.VoutItlkSts)resonant_swls.VoutItlkSts = LvCurrentCh2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Medida de Fuga para o Terra
    resonant_swls.GroundLeakage.f = VoltageCh1Read();
    resonant_swls.GroundLeakageAlarmSts = VoltageCh1AlarmStatusRead();
    if(!resonant_swls.GroundLeakageItlkSts)resonant_swls.GroundLeakageItlkSts = VoltageCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock externo
    resonant_swls.ExternalItlk = Gpdi5Read();//Variavel usada para debug
    if(!resonant_swls.ExternalItlkSts)resonant_swls.ExternalItlkSts = Gpdi5Read();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock do Rack
    resonant_swls.Rack = Gpdi6Read();//Variavel usada para debug
    if(!resonant_swls.RackItlkSts)resonant_swls.RackItlkSts = Gpdi6Read();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Status do Contato do Rele
    resonant_swls.Relay = Gpdi7Read();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 1
    resonant_swls.Driver1Error = Driver1TopErrorRead();//Variavel usada para debug
    if(!resonant_swls.Driver1ErrorItlkSts)resonant_swls.Driver1ErrorItlkSts = Driver1TopErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver 2
    resonant_swls.Driver2Error = Driver2TopErrorRead();//Variavel usada para debug
    if(!resonant_swls.Driver2ErrorItlkSts)resonant_swls.Driver2ErrorItlkSts = Driver2TopErrorRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    resonant_swls.ReleAuxItlkSts = ReleAuxSts();

    resonant_swls.ReleExtItlkSts = ReleExtItlkSts();

    if(resonant_swls.ReleAuxItlkSts == 0 && resonant_swls.ReleExtItlkSts == 0 && flag1 == 0)
    {
        if(!FiltroUP1)
        {
            resonant_swls.RelayOpenItlkSts = 1;
            resonant_swls.RelayContactStickingItlkSts = 0;

            FiltroUP1 = 1024;
            flag1 = 1;
        }
        else FiltroUP1--;

    }
    else if(flag1 == 1)
    {
        flag1 = 0;
        FiltroUP1 = 1024;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    if(resonant_swls.ReleAuxItlkSts == 0 && resonant_swls.ReleExtItlkSts == 1 && flag2 == 0)
    {
        if(!FiltroUP2)
        {
            resonant_swls.RelayContactStickingItlkSts = 1;
            resonant_swls.RelayOpenItlkSts = 0;

            FiltroUP2 = 1024;
            flag2 = 1;
        }
        else FiltroUP2--;

    }
    else if(flag2 == 1)
    {
        flag2 = 0;
        FiltroUP2 = 1024;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    //Se nao houver sinal na entrada digital dos 4 sinais, defina a acao como Interlock.
    if(resonant_swls.ExternalItlkSts || resonant_swls.RackItlkSts || resonant_swls.Driver1ErrorItlkSts || resonant_swls.Driver2ErrorItlkSts) InterlockSet();

/////////////////////////////////////////////////////////////////////////////////////////////

    if(Interlock == 1)
    {
    	if (resonant_swls.VinItlkSts)                     resonant_swls.InterlocksRegister.u32 |= FAP_INPUT_OVERVOLTAGE_ITLK;
    	if (resonant_swls.VoutItlkSts)                    resonant_swls.InterlocksRegister.u32 |= FAP_OUTPUT_OVERVOLTAGE_ITLK;
    	if (resonant_swls.IoutA1ItlkSts)                  resonant_swls.InterlocksRegister.u32 |= FAP_OUTPUT_OVERCURRENT_1_ITLK;
    	if (resonant_swls.IoutA2ItlkSts)                  resonant_swls.InterlocksRegister.u32 |= FAP_OUTPUT_OVERCURRENT_2_ITLK;
    	if (resonant_swls.TempIGBT1ItlkSts)               resonant_swls.InterlocksRegister.u32 |= FAP_IGBT1_OVERTEMP_ITLK;
    	if (resonant_swls.TempIGBT2ItlkSts)               resonant_swls.InterlocksRegister.u32 |= FAP_IGBT2_OVERTEMP_ITLK;
    	if (resonant_swls.DriverVoltageItlkSts)           resonant_swls.InterlocksRegister.u32 |= FAP_DRIVER_OVERVOLTAGE_ITLK;
    	if (resonant_swls.Driver1CurrentItlkSts)          resonant_swls.InterlocksRegister.u32 |= FAP_DRIVER1_OVERCURRENT_ITLK;
    	if (resonant_swls.Driver2CurrentItlkSts)          resonant_swls.InterlocksRegister.u32 |= FAP_DRIVER2_OVERCURRENT_ITLK;
    	if (resonant_swls.Driver1ErrorItlkSts)            resonant_swls.InterlocksRegister.u32 |= FAP_DRIVER1_ERROR_ITLK;
    	if (resonant_swls.Driver2ErrorItlkSts)            resonant_swls.InterlocksRegister.u32 |= FAP_DRIVER2_ERROR_ITLK;
    	if (resonant_swls.TempLItlkSts)                   resonant_swls.InterlocksRegister.u32 |= FAP_INDUC_OVERTEMP_ITLK;
    	if (resonant_swls.TempHeatSinkItlkSts)            resonant_swls.InterlocksRegister.u32 |= FAP_HS_OVERTEMP_ITLK;
    	if (resonant_swls.RelayOpenItlkSts)               resonant_swls.InterlocksRegister.u32 |= FAP_RELAY_ITLK;
    	if (resonant_swls.RelayContactStickingItlkSts)    resonant_swls.InterlocksRegister.u32 |= FAP_RELAY_CONTACT_STICKING_ITLK;
    	if (resonant_swls.ExternalItlkSts)                resonant_swls.InterlocksRegister.u32 |= FAP_EXTERNAL_ITLK;
    	if (resonant_swls.RackItlkSts)                    resonant_swls.InterlocksRegister.u32 |= FAP_RACK_ITLK;
    	if (resonant_swls.GroundLeakageItlkSts)           resonant_swls.InterlocksRegister.u32 |= FAP_GROUND_LKG_ITLK;
    	if (resonant_swls.BoardTemperatureItlkSts)        resonant_swls.InterlocksRegister.u32 |= FAP_BOARD_IIB_OVERTEMP_ITLK;
    	if (resonant_swls.RelativeHumidityItlkSts)        resonant_swls.InterlocksRegister.u32 |= FAP_BOARD_IIB_OVERHUMIDITY_ITLK;
    }

    else
    {
    	resonant_swls.InterlocksRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    if(Alarm == 1)
    {
    	if (resonant_swls.VinAlarmSts)                    resonant_swls.AlarmsRegister.u32 |= FAP_INPUT_OVERVOLTAGE_ALM;
    	if (resonant_swls.VoutAlarmSts)                   resonant_swls.AlarmsRegister.u32 |= FAP_OUTPUT_OVERVOLTAGE_ALM;
    	if (resonant_swls.IoutA1AlarmSts)                 resonant_swls.AlarmsRegister.u32 |= FAP_OUTPUT_OVERCURRENT_1_ALM;
    	if (resonant_swls.IoutA2AlarmSts)                 resonant_swls.AlarmsRegister.u32 |= FAP_OUTPUT_OVERCURRENT_2_ALM;
    	if (resonant_swls.TempIGBT1AlarmSts)              resonant_swls.AlarmsRegister.u32 |= FAP_IGBT1_OVERTEMP_ALM;
    	if (resonant_swls.TempIGBT2AlarmSts)              resonant_swls.AlarmsRegister.u32 |= FAP_IGBT2_OVERTEMP_ALM;
    	if (resonant_swls.TempLAlarmSts)                  resonant_swls.AlarmsRegister.u32 |= FAP_INDUC_OVERTEMP_ALM;
    	if (resonant_swls.TempHeatSinkAlarmSts)           resonant_swls.AlarmsRegister.u32 |= FAP_HS_OVERTEMP_ALM;
    	if (resonant_swls.GroundLeakageAlarmSts)          resonant_swls.AlarmsRegister.u32 |= FAP_GROUND_LKG_ALM;
    	if (resonant_swls.DriverVoltageAlarmSts)          resonant_swls.AlarmsRegister.u32 |= FAP_DRIVER_OVERVOLTAGE_ALM;
    	if (resonant_swls.Driver1CurrentAlarmSts)         resonant_swls.AlarmsRegister.u32 |= FAP_DRIVER1_OVERCURRENT_ALM;
    	if (resonant_swls.Driver2CurrentAlarmSts)         resonant_swls.AlarmsRegister.u32 |= FAP_DRIVER2_OVERCURRENT_ALM;
    	if (resonant_swls.BoardTemperatureAlarmSts)       resonant_swls.AlarmsRegister.u32 |= FAP_BOARD_IIB_OVERTEMP_ALM;
    	if (resonant_swls.RelativeHumidityAlarmSts)       resonant_swls.AlarmsRegister.u32 |= FAP_BOARD_IIB_OVERHUMIDITY_ALM;
    }

    else
    {
    	resonant_swls.AlarmsRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    g_controller_iib.iib_signals[0].f       = resonant_swls.Vin.f;
    g_controller_iib.iib_signals[1].f       = resonant_swls.Vout.f;
    g_controller_iib.iib_signals[2].f       = resonant_swls.IoutA1.f;
    g_controller_iib.iib_signals[3].f       = resonant_swls.IoutA2.f;
    g_controller_iib.iib_signals[4].f       = resonant_swls.TempIGBT1.f;
    g_controller_iib.iib_signals[5].f       = resonant_swls.TempIGBT2.f;
    g_controller_iib.iib_signals[6].f       = resonant_swls.DriverVoltage.f;
    g_controller_iib.iib_signals[7].f       = resonant_swls.Driver1Current.f;
    g_controller_iib.iib_signals[8].f       = resonant_swls.Driver2Current.f;
    g_controller_iib.iib_signals[9].f       = resonant_swls.TempL.f;
    g_controller_iib.iib_signals[10].f      = resonant_swls.TempHeatSink.f;
    g_controller_iib.iib_signals[11].f      = resonant_swls.GroundLeakage.f;
    g_controller_iib.iib_signals[12].f      = resonant_swls.BoardTemperature.f;
    g_controller_iib.iib_signals[13].f      = resonant_swls.RelativeHumidity.f;
    g_controller_iib.iib_signals[14].u32    = resonant_swls.InterlocksRegister.u32;
    g_controller_iib.iib_signals[15].u32    = resonant_swls.AlarmsRegister.u32;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void config_module_fap(void)
{

#ifdef FAP

    //Set current range FAP 130 A
    CurrentCh1Init(LA_Primary_Current, LA_Secondary_Current, LA_Burden_Resistor, LA_Delay); //Corrente braço1: Sensor Hall
    CurrentCh2Init(LA_Primary_Current, LA_Secondary_Current, LA_Burden_Resistor, LA_Delay); //Corrente braço2: LEM LA 130-P

    //Set protection limits FAP 130 A
    CurrentCh1AlarmLevelSet(FAP_OUTPUT_OVERCURRENT_1_ALM_LIM);  //Corrente braço1
    CurrentCh1TripLevelSet(FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM);  //Corrente braço1
    CurrentCh2AlarmLevelSet(FAP_OUTPUT_OVERCURRENT_2_ALM_LIM);  //Corrente braço2
    CurrentCh2TripLevelSet(FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM);  //Corrente braço2

/////////////////////////////////////////////////////////////////////////////////////////////

    //Leitura de tensão isolada
    LvCurrentCh1Init(LV_Primary_Voltage_Vin, LV_Secondary_Current_Vin, LV_Burden_Resistor, Delay_Vin); // Vin
    LvCurrentCh2Init(LV_Primary_Voltage_Vout, LV_Secondary_Current_Vin, LV_Burden_Resistor, Delay_Vout); // Vout

    LvCurrentCh1AlarmLevelSet(FAP_INPUT_OVERVOLTAGE_ALM_LIM);  //Tensão de entrada Alarme
    LvCurrentCh1TripLevelSet(FAP_INPUT_OVERVOLTAGE_ITLK_LIM);  //Tensão de entrada Interlock
    LvCurrentCh2AlarmLevelSet(FAP_OUTPUT_OVERVOLTAGE_ALM_LIM); //Tensão de saída Alarme
    LvCurrentCh2TripLevelSet(FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM); //Tensão de saída Interlock

/////////////////////////////////////////////////////////////////////////////////////////////

    //Leitura de tensão
    VoltageCh1Init(Current_GND_Leakage, Delay_GND_Leakage); //Ground Leakage

    VoltageCh1AlarmLevelSet(FAP_GROUND_LEAKAGE_ALM_LIM); //Fuga para o terra alarme
    VoltageCh1TripLevelSet(FAP_GROUND_LEAKAGE_ITLK_LIM); //Fuga para o terra interlock

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 configuration
    //Debouncing Delay seconds
    Pt100Ch1Delay(Delay_PT100CH1);
    Pt100Ch2Delay(Delay_PT100CH2);

    //PT100 configuration limits
    Pt100Ch1AlarmLevelSet(FAP_HS_OVERTEMP_ALM_LIM);     //Temperatura Dissipador
    Pt100Ch1TripLevelSet(FAP_HS_OVERTEMP_ITLK_LIM);     //Temperatura Dissipador
    Pt100Ch2AlarmLevelSet(FAP_INDUC_OVERTEMP_ALM_LIM);  //Temperatura L
    Pt100Ch2TripLevelSet(FAP_INDUC_OVERTEMP_ITLK_LIM);  //Temperatura L

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature igbt1 configuration
    TempIgbt1Delay(Delay_IGBT1); //Inserir valor de delay

    //Temp Igbt1 configuration limits
    TempIgbt1AlarmLevelSet(FAP_IGBT1_OVERTEMP_ALM_LIM);
    TempIgbt1TripLevelSet(FAP_IGBT1_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature igbt2 configuration
    TempIgbt2Delay(Delay_IGBT2); //Inserir valor de delay

    //Temp Igbt2 configuration limits
    TempIgbt2AlarmLevelSet(FAP_IGBT2_OVERTEMP_ALM_LIM);
    TempIgbt2TripLevelSet(FAP_IGBT2_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature Board configuration
    BoardTempDelay(Delay_BoardTemp); //Inserir valor de delay

    //Temp board configuration limits
    BoardTempAlarmLevelSet(FAP_BOARD_OVERTEMP_ALM_LIM);
    BoardTempTripLevelSet(FAP_BOARD_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Humidity Board configuration
    RhDelay(Delay_BoardRh); //Inserir valor de delay

    //Rh configuration limits
    RhAlarmLevelSet(FAP_RH_OVERHUMIDITY_ALM_LIM);
    RhTripLevelSet(FAP_RH_OVERHUMIDITY_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Voltage configuration
    DriverVoltageInit();

    DriverVoltageDelay(Delay_DriverVoltage); //Inserir valor de delay

    //Limite de alarme e interlock da tensao dos drivers
    DriverVoltageAlarmLevelSet(FAP_DRIVER_OVERVOLTAGE_ALM_LIM);
    DriverVoltageTripLevelSet(FAP_DRIVER_OVERVOLTAGE_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Current configuration
    DriverCurrentInit();

    DriverCurrentDelay(Delay_DriverCurrent); //Inserir valor de delay

    //Limite de alarme e interlock da corrente do driver 1
    Driver1CurrentAlarmLevelSet(FAP_DRIVER1_OVERCURRENT_ALM_LIM);
    Driver1CurrentTripLevelSet(FAP_DRIVER1_OVERCURRENT_ITLK_LIM);

    //Limite de alarme e interlock da corrente do driver 2
    Driver2CurrentAlarmLevelSet(FAP_DRIVER2_OVERCURRENT_ALM_LIM);
    Driver2CurrentTripLevelSet(FAP_DRIVER2_OVERCURRENT_ITLK_LIM);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //Init Variables
    resonant_swls.Vin.f                        = 0.0;
    resonant_swls.VinAlarmSts                  = 0;
    resonant_swls.VinItlkSts                   = 0;
    resonant_swls.Vout.f                       = 0.0;
    resonant_swls.VoutAlarmSts                 = 0;
    resonant_swls.VoutItlkSts                  = 0;
    resonant_swls.IoutA1.f                     = 0.0;
    resonant_swls.IoutA1AlarmSts               = 0;
    resonant_swls.IoutA1ItlkSts                = 0;
    resonant_swls.IoutA2.f                     = 0.0;
    resonant_swls.IoutA2AlarmSts               = 0;
    resonant_swls.IoutA2ItlkSts                = 0;
    resonant_swls.TempIGBT1.f                  = 0.0;
    resonant_swls.TempIGBT1AlarmSts            = 0;
    resonant_swls.TempIGBT1ItlkSts             = 0;
    resonant_swls.TempIGBT2.f                  = 0.0;
    resonant_swls.TempIGBT2AlarmSts            = 0;
    resonant_swls.TempIGBT2ItlkSts             = 0;
    resonant_swls.DriverVoltage.f              = 0.0;
    resonant_swls.DriverVoltageAlarmSts        = 0;
    resonant_swls.DriverVoltageItlkSts         = 0;
    resonant_swls.Driver1Current.f             = 0.0;
    resonant_swls.Driver1CurrentAlarmSts       = 0;
    resonant_swls.Driver1CurrentItlkSts        = 0;
    resonant_swls.Driver2Current.f             = 0.0;
    resonant_swls.Driver2CurrentAlarmSts       = 0;
    resonant_swls.Driver2CurrentItlkSts        = 0;
    resonant_swls.Driver1Error                 = 0;
    resonant_swls.Driver1ErrorItlkSts          = 0;
    resonant_swls.Driver2Error                 = 0;
    resonant_swls.Driver2ErrorItlkSts          = 0;
    resonant_swls.TempL.f                      = 0.0;
    resonant_swls.TempLAlarmSts                = 0;
    resonant_swls.TempLItlkSts                 = 0;
    resonant_swls.TempHeatSink.f               = 0.0;
    resonant_swls.TempHeatSinkAlarmSts         = 0;
    resonant_swls.TempHeatSinkItlkSts          = 0;
    resonant_swls.Relay                        = 0;
    resonant_swls.ExternalItlk                 = 0;
    resonant_swls.ExternalItlkSts              = 0;
    resonant_swls.Rack                         = 0;
    resonant_swls.RackItlkSts                  = 0;
    resonant_swls.GroundLeakage.f              = 0.0;
    resonant_swls.GroundLeakageAlarmSts        = 0;
    resonant_swls.GroundLeakageItlkSts         = 0;
    resonant_swls.BoardTemperature.f           = 0.0;
    resonant_swls.BoardTemperatureAlarmSts     = 0;
    resonant_swls.BoardTemperatureItlkSts      = 0;
    resonant_swls.RelativeHumidity.f           = 0.0;
    resonant_swls.RelativeHumidityAlarmSts     = 0;
    resonant_swls.RelativeHumidityItlkSts      = 0;
    resonant_swls.ReleAuxItlkSts               = 0;
    resonant_swls.ReleExtItlkSts               = 0;
    resonant_swls.RelayOpenItlkSts             = 0;
    resonant_swls.RelayContactStickingItlkSts  = 0;
    resonant_swls.InterlocksRegister.u32       = 0;
    resonant_swls.AlarmsRegister.u32           = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

