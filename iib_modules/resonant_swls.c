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

static volatile uint8_t flag3 = 0;
static volatile uint32_t FiltroUP3 = 1024;

static volatile uint8_t flag4 = 0;
static volatile uint32_t FiltroUP4 = 1024;

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_resonant_swls_interlocks()
{
	resonant_swls.ContactorK1OpenItlkSts = 0;
	resonant_swls.ContactorK1ContactStickingItlkSts = 0;

	resonant_swls.ContactorK2OpenItlkSts = 0;
	resonant_swls.ContactorK2ContactStickingItlkSts = 0;

    resonant_swls.ReleAuxItlkSts = 0;

    flag1 = 0;
    FiltroUP1 = 1024;

    flag2 = 0;
    FiltroUP2 = 1024;

    flag3 = 0;
    FiltroUP3 = 1024;

    flag4 = 0;
    FiltroUP4 = 1024;

////////////////////////////////////////

    resonant_swls.VinItlkSts                  		= 0;
    resonant_swls.VoutItlkSts                 		= 0;
    resonant_swls.IinItlkSts                  		= 0;
    resonant_swls.IoutItlkSts                 		= 0;
    resonant_swls.GroundLeakageItlkSts        		= 0;
    resonant_swls.TempHeatSinkTransformerPfcItlkSts	= 0;
    resonant_swls.TempOutputInductorItlkSts   		= 0;
    resonant_swls.TempHeatSinkDiodesItlkSts  		= 0;
    resonant_swls.TempHeatSinkClampItlkSts  		= 0;
    resonant_swls.DriverAuxVoltageItlkSts        	= 0;
    resonant_swls.Driver1CurrentItlkSts         	= 0;
    resonant_swls.DriverFlagHSErrorItlkSts          = 0;
    resonant_swls.DriverFlagLSErrorItlkSts          = 0;
    resonant_swls.AuxCurrentItlkSts             	= 0;
    resonant_swls.ContactorK1OverCurrentItlkSts     = 0;
    resonant_swls.EmergencyButtonItlkSts            = 0;
    resonant_swls.BoardTemperatureItlkSts     		= 0;
    resonant_swls.RelativeHumidityItlkSts     		= 0;

    resonant_swls.InterlocksRegister.u32      		= 0;

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
    test |= resonant_swls.TempHeatSinkTransformerPfcItlkSts;
    test |= resonant_swls.TempOutputInductorItlkSts;
    test |= resonant_swls.TempHeatSinkDiodesItlkSts;
    test |= resonant_swls.TempHeatSinkClampItlkSts;
    test |= resonant_swls.DriverAuxVoltageItlkSts;
    test |= resonant_swls.Driver1CurrentItlkSts;
    test |= resonant_swls.DriverFlagHSErrorItlkSts;
    test |= resonant_swls.DriverFlagLSErrorItlkSts;
    test |= resonant_swls.AuxCurrentItlkSts;
    test |= resonant_swls.ContactorK1OverCurrentItlkSts;
    test |= resonant_swls.EmergencyButtonItlkSts;
    test |= resonant_swls.BoardTemperatureItlkSts;
    test |= resonant_swls.RelativeHumidityItlkSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void clear_resonant_swls_alarms()
{
    resonant_swls.VinAlarmSts                  		 = 0;
    resonant_swls.VoutAlarmSts                 		 = 0;
    resonant_swls.IinAlarmSts                  		 = 0;
    resonant_swls.IoutAlarmSts                 		 = 0;
    resonant_swls.TempHeatSinkTransformerPfcAlarmSts = 0;
    resonant_swls.TempOutputInductorAlarmSts   		 = 0;
    resonant_swls.TempHeatSinkDiodesAlarmSts  	     = 0;
    resonant_swls.TempHeatSinkClampAlarmSts   	     = 0;
    resonant_swls.DriverAuxVoltageAlarmSts        	 = 0;
    resonant_swls.Driver1CurrentAlarmSts       		 = 0;
    resonant_swls.AuxCurrentAlarmSts             	 = 0;
    resonant_swls.GroundLeakageAlarmSts        		 = 0;
    resonant_swls.BoardTemperatureAlarmSts     		 = 0;
    resonant_swls.RelativeHumidityAlarmSts     		 = 0;

    resonant_swls.AlarmsRegister.u32           		 = 0;

}

/////////////////////////////////////////////////////////////////////////////////////////////

uint8_t check_resonant_swls_alarms()
{
    uint8_t test = 0;

    test |= resonant_swls.VinAlarmSts;
    test |= resonant_swls.VoutAlarmSts;
    test |= resonant_swls.IinAlarmSts;
    test |= resonant_swls.IoutAlarmSts;
    test |= resonant_swls.TempHeatSinkTransformerPfcAlarmSts;
    test |= resonant_swls.TempOutputInductorAlarmSts;
    test |= resonant_swls.TempHeatSinkDiodesAlarmSts;
    test |= resonant_swls.TempHeatSinkClampAlarmSts;
    test |= resonant_swls.DriverAuxVoltageAlarmSts;
    test |= resonant_swls.Driver1CurrentAlarmSts;
    test |= resonant_swls.AuxCurrentAlarmSts;
    test |= resonant_swls.GroundLeakageAlarmSts;
    test |= resonant_swls.BoardTemperatureAlarmSts;
    test |= resonant_swls.RelativeHumidityAlarmSts;

    return test;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void check_resonant_swls_indication_leds()
{
	//Status do Contator K1 e K2 to PreCharge
	if(resonant_swls.ContactorK1 == 0 && resonant_swls.ContactorK2 == 1) Led1Toggle();
	else if(resonant_swls.ContactorK1 == 0 && resonant_swls.ContactorK2 == 0) Led1TurnOn();
	else Led1TurnOff();

/////////////////////////////////////////////////////////////////////////////////////////////

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
    if(resonant_swls.TempHeatSinkTransformerPfcItlkSts || resonant_swls.TempOutputInductorItlkSts
    		||  resonant_swls.TempHeatSinkDiodesItlkSts || resonant_swls.TempHeatSinkClampItlkSts) Led6TurnOff();
    else if(resonant_swls.TempHeatSinkTransformerPfcAlarmSts || resonant_swls.TempOutputInductorAlarmSts
    		||  resonant_swls.TempHeatSinkDiodesAlarmSts || resonant_swls.TempHeatSinkClampAlarmSts) Led6Toggle();
    else Led6TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Fuga para o Terra
    if(resonant_swls.GroundLeakageItlkSts) Led7TurnOff();
    else if(resonant_swls.GroundLeakageAlarmSts) Led7Toggle();
    else Led7TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks dos Drivers
    if(resonant_swls.DriverAuxVoltageItlkSts || resonant_swls.Driver1CurrentItlkSts
    || resonant_swls.DriverFlagHSErrorItlkSts || resonant_swls.DriverFlagLSErrorItlkSts || resonant_swls.AuxCurrentItlkSts) Led8TurnOff();
    else if(resonant_swls.DriverAuxVoltageAlarmSts || resonant_swls.Driver1CurrentAlarmSts || resonant_swls.AuxCurrentAlarmSts) Led8Toggle();
    else Led8TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock Temperatura PCB e Umidade Relativa
    if(resonant_swls.BoardTemperatureItlkSts || resonant_swls.RelativeHumidityItlkSts) Led9TurnOff();
    else if(resonant_swls.BoardTemperatureAlarmSts || resonant_swls.RelativeHumidityAlarmSts) Led9Toggle();
    else Led9TurnOn();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlocks Contactor K1 over current and emergency button
    if(resonant_swls.ContactorK1OverCurrentItlkSts || resonant_swls.EmergencyButtonItlkSts) Led10TurnOff();
    else Led10TurnOn();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void resonant_swls_application_readings()
{
    //PT100 CH1 Temperatura Dissipador Transformador e PFC
    resonant_swls.TempHeatSinkTransformerPfc.f = Pt100Ch1Read();
    resonant_swls.TempHeatSinkTransformerPfcAlarmSts = Pt100Ch1AlarmStatusRead();
    if(!resonant_swls.TempHeatSinkTransformerPfcItlkSts)resonant_swls.TempHeatSinkTransformerPfcItlkSts = Pt100Ch1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH2 Temperatura Indutor de sa�da
    resonant_swls.TempOutputInductor.f = Pt100Ch2Read();
    resonant_swls.TempOutputInductorAlarmSts = Pt100Ch2AlarmStatusRead();
    if(!resonant_swls.TempOutputInductorItlkSts)resonant_swls.TempOutputInductorItlkSts = Pt100Ch2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH3 Temperatura Dissipador Diodos
    resonant_swls.TempHeatSinkDiodes.f = Pt100Ch3Read();
    resonant_swls.TempHeatSinkDiodesAlarmSts = Pt100Ch3AlarmStatusRead();
    if(!resonant_swls.TempHeatSinkDiodesItlkSts)resonant_swls.TempHeatSinkDiodesItlkSts = Pt100Ch3TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 CH4 Temperatura Dissipador Clamp
    resonant_swls.TempHeatSinkClamp.f = Pt100Ch4Read();
    resonant_swls.TempHeatSinkClampAlarmSts = Pt100Ch4AlarmStatusRead();
    if(!resonant_swls.TempHeatSinkClampItlkSts)resonant_swls.TempHeatSinkClampItlkSts = Pt100Ch4TripStatusRead();

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

    //DriverAuxVoltage
    resonant_swls.DriverAuxVoltage.f = DriverVoltageRead();
    resonant_swls.DriverAuxVoltageAlarmSts = DriverVoltageAlarmStatusRead();
    if(!resonant_swls.DriverAuxVoltageItlkSts)resonant_swls.DriverAuxVoltageItlkSts = DriverVoltageTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Drive1Current
    resonant_swls.Driver1Current.f = Driver1CurrentRead();
    resonant_swls.Driver1CurrentAlarmSts = Driver1CurrentAlarmStatusRead();
    if(!resonant_swls.Driver1CurrentItlkSts)resonant_swls.Driver1CurrentItlkSts = Driver1CurrentTripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //AuxCurrent
    resonant_swls.AuxCurrent.f = Driver2CurrentRead();
    resonant_swls.AuxCurrentAlarmSts = Driver2CurrentAlarmStatusRead();
    if(!resonant_swls.AuxCurrentItlkSts)resonant_swls.AuxCurrentItlkSts = Driver2CurrentTripStatusRead();

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

    //Corrente de Entrada
    resonant_swls.Iin.f = CurrentCh1Read();//HALL CH1
    resonant_swls.IinAlarmSts = CurrentCh1AlarmStatusRead();
    if(!resonant_swls.IinItlkSts)resonant_swls.IinItlkSts = CurrentCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Corrente de Saida
    resonant_swls.Iout.f = CurrentCh2Read();//HALL CH2
    resonant_swls.IoutAlarmSts = CurrentCh2AlarmStatusRead();
    if(!resonant_swls.IoutItlkSts)resonant_swls.IoutItlkSts = CurrentCh2TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Medida de Fuga para o Terra
    resonant_swls.GroundLeakage.f = VoltageCh1Read();
    resonant_swls.GroundLeakageAlarmSts = VoltageCh1AlarmStatusRead();
    if(!resonant_swls.GroundLeakageItlkSts)resonant_swls.GroundLeakageItlkSts = VoltageCh1TripStatusRead();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Status do Botao de Emergencia
    resonant_swls.EmergencyButtonItlk = Gpdi5Read();//Variavel usada para debug
    if(!resonant_swls.EmergencyButtonItlkSts)resonant_swls.EmergencyButtonItlkSts = Gpdi5Read();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Interlock Contactor K1 over current
    resonant_swls.ContactorK1OverCurrentItlk = Gpdi6Read();//Variavel usada para debug
    if(!resonant_swls.ContactorK1OverCurrentItlkSts)resonant_swls.ContactorK1OverCurrentItlkSts = Gpdi6Read();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver Flag HS
    resonant_swls.DriverFlagHSError = Gpdi7Read();//Variavel usada para debug
    if(resonant_swls.DriverFlagHSError == 0)resonant_swls.DriverFlagHSErrorItlkSts = 1;

/////////////////////////////////////////////////////////////////////////////////////////////

    //Erro do Driver Flag LS
    resonant_swls.DriverFlagLSError = Gpdi8Read();//Variavel usada para debug
    if(resonant_swls.DriverFlagLSError == 0)resonant_swls.DriverFlagLSErrorItlkSts = 1;

/////////////////////////////////////////////////////////////////////////////////////////////

    //Status do Contator K1
    resonant_swls.ContactorK1 = Gpdi9Read();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Status do Contator K2
    resonant_swls.ContactorK2 = Gpdi10Read();

/////////////////////////////////////////////////////////////////////////////////////////////

    resonant_swls.ReleAuxItlkSts = ReleAuxSts();//Rele CON19

    if(resonant_swls.ReleAuxItlkSts == 0 && resonant_swls.ContactorK1 == 1 && flag1 == 0)
    {
    	if(!FiltroUP1)
    	{
    		resonant_swls.ContactorK1OpenItlkSts = 1;
    		resonant_swls.ContactorK1ContactStickingItlkSts = 0;

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

    if(resonant_swls.ReleAuxItlkSts == 0 && resonant_swls.ContactorK1 == 0 && flag2 == 0)
    {
    	if(!FiltroUP2)
    	{
    		resonant_swls.ContactorK1ContactStickingItlkSts = 1;
    		resonant_swls.ContactorK1OpenItlkSts = 0;

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

    if(resonant_swls.ReleAuxItlkSts == 0 && resonant_swls.ContactorK2 == 1 && flag3 == 0)
    {
    	if(!FiltroUP3)
    	{
    		resonant_swls.ContactorK2OpenItlkSts = 1;
    		resonant_swls.ContactorK2ContactStickingItlkSts = 0;

    		FiltroUP3 = 1024;
    		flag3 = 1;
    	}
    	else FiltroUP3--;

    }
    else if(flag3 == 1)
    {
    	flag3 = 0;
    	FiltroUP3 = 1024;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    if(resonant_swls.ReleAuxItlkSts == 0 && resonant_swls.ContactorK2 == 0 && flag4 == 0)
    {
    	if(!FiltroUP4)
    	{
    		resonant_swls.ContactorK2ContactStickingItlkSts = 1;
    		resonant_swls.ContactorK2OpenItlkSts = 0;

    		FiltroUP4 = 1024;
    		flag4 = 1;
    	}
    	else FiltroUP4--;

    }
    else if(flag4 == 1)
    {
    	flag4 = 0;
    	FiltroUP4 = 1024;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    //Se nao houver sinal na entrada digital, defina a acao como Interlock.
    if(resonant_swls.ContactorK1OverCurrentItlkSts || resonant_swls.EmergencyButtonItlkSts) InterlockSet();

/////////////////////////////////////////////////////////////////////////////////////////////

    if(Interlock == 1)
    {
    	if (resonant_swls.VinItlkSts)                     	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_INPUT_OVERVOLTAGE_ITLK;
    	if (resonant_swls.VoutItlkSts)                    	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_OUTPUT_OVERVOLTAGE_ITLK;
    	if (resonant_swls.IinItlkSts)                     	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_INPUT_OVERCURRENT_ITLK;
    	if (resonant_swls.IoutItlkSts)                    	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_OUTPUT_OVERCURRENT_ITLK;
    	if (resonant_swls.TempHeatSinkTransformerPfcItlkSts)  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_HS_TRANSFORMER_AND_PFC_OVERTEMP_ITLK;
    	if (resonant_swls.TempOutputInductorItlkSts)      	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_INDUC_OUTPUT_OVERTEMP_ITLK;
    	if (resonant_swls.TempHeatSinkDiodesItlkSts)          resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_HS_DIODES_OVERTEMP_ITLK;
    	if (resonant_swls.TempHeatSinkClampItlkSts)           resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_HS_CLAMP_OVERTEMP_ITLK;
    	if (resonant_swls.DriverAuxVoltageItlkSts)            resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_DRIVER_MOSFETS_AND_AUX_OVERVOLTAGE_ITLK;
    	if (resonant_swls.Driver1CurrentItlkSts)          	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_DRIVER1_MOSFETS_OVERCURRENT_ITLK;
    	if (resonant_swls.DriverFlagHSErrorItlkSts)           resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_DRIVER_FLAG_HS_ERROR_ITLK;
    	if (resonant_swls.DriverFlagLSErrorItlkSts)           resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_DRIVER_FLAG_LS_ERROR_ITLK;
    	if (resonant_swls.AuxCurrentItlkSts)				  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_AUX_SUPPLY_OVERCURRENT_ITLK;
    	if (resonant_swls.GroundLeakageItlkSts)           	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_GROUND_LKG_ITLK;
    	if (resonant_swls.BoardTemperatureItlkSts)        	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_BOARD_IIB_OVERTEMP_ITLK;
    	if (resonant_swls.RelativeHumidityItlkSts)        	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_BOARD_IIB_OVERHUMIDITY_ITLK;
    	if (resonant_swls.ContactorK1OverCurrentItlkSts)      resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_CONTACTOR_K1_OVER_CURRENT_ITLK;
    	if (resonant_swls.ContactorK1OpenItlkSts)             resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_CONTACTOR_K1_OPEN_ITLK;
    	if (resonant_swls.ContactorK1ContactStickingItlkSts)  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_CONTACTOR_K1_CONTACT_STICKING_ITLK;
    	if (resonant_swls.ContactorK2OpenItlkSts)             resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_CONTACTOR_K2_OPEN_ITLK;
    	if (resonant_swls.ContactorK2ContactStickingItlkSts)  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_CONTACTOR_K2_CONTACT_STICKING_ITLK;
    	if (resonant_swls.EmergencyButtonItlkSts)         	  resonant_swls.InterlocksRegister.u32 |= RESONANT_SWLS_EMERGENCY_BUTTON_ITLK;
    }

    else
    {
    	resonant_swls.InterlocksRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    if(Alarm == 1)
    {
    	if (resonant_swls.VinAlarmSts)                    	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_INPUT_OVERVOLTAGE_ALM;
    	if (resonant_swls.VoutAlarmSts)                   	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_OUTPUT_OVERVOLTAGE_ALM;
    	if (resonant_swls.IinAlarmSts)                    	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_INPUT_OVERCURRENT_ALM;
    	if (resonant_swls.IoutAlarmSts)                   	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_OUTPUT_OVERCURRENT_ALM;
    	if (resonant_swls.TempHeatSinkTransformerPfcAlarmSts)  resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_HS_TRANSFORMER_AND_PFC_OVERTEMP_ALM;
    	if (resonant_swls.TempOutputInductorAlarmSts)     	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_INDUC_OUTPUT_OVERTEMP_ALM;
    	if (resonant_swls.TempHeatSinkDiodesAlarmSts)    	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_HS_DIODES_OVERTEMP_ALM;
    	if (resonant_swls.TempHeatSinkClampAlarmSts)           resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_HS_CLAMP_OVERTEMP_ALM;
    	if (resonant_swls.DriverAuxVoltageAlarmSts)            resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_DRIVER_MOSFETS_AND_AUX_OVERVOLTAGE_ALM;
    	if (resonant_swls.Driver1CurrentAlarmSts)         	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_DRIVER1_MOSFETS_OVERCURRENT_ALM;
    	if (resonant_swls.AuxCurrentAlarmSts)				   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_AUX_SUPPLY_OVERCURRENT_ALM;
    	if (resonant_swls.GroundLeakageAlarmSts)          	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_GROUND_LKG_ALM;
    	if (resonant_swls.BoardTemperatureAlarmSts)       	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_BOARD_IIB_OVERTEMP_ALM;
    	if (resonant_swls.RelativeHumidityAlarmSts)       	   resonant_swls.AlarmsRegister.u32 |= RESONANT_SWLS_BOARD_IIB_OVERHUMIDITY_ALM;
    }

    else
    {
    	resonant_swls.AlarmsRegister.u32 = 0x00000000;
    }

/////////////////////////////////////////////////////////////////////////////////////////////

    g_controller_iib.iib_signals[0].f       = resonant_swls.Vin.f;
    g_controller_iib.iib_signals[1].f       = resonant_swls.Vout.f;
    g_controller_iib.iib_signals[2].f       = resonant_swls.Iin.f;
    g_controller_iib.iib_signals[3].f       = resonant_swls.Iout.f;
    g_controller_iib.iib_signals[4].f       = resonant_swls.TempHeatSinkTransformerPfc.f;
    g_controller_iib.iib_signals[5].f       = resonant_swls.TempOutputInductor.f;
    g_controller_iib.iib_signals[6].f       = resonant_swls.TempHeatSinkDiodes.f;
    g_controller_iib.iib_signals[7].f       = resonant_swls.TempHeatSinkClamp.f;
    g_controller_iib.iib_signals[8].f       = resonant_swls.DriverAuxVoltage.f;
    g_controller_iib.iib_signals[9].f       = resonant_swls.Driver1Current.f;
    g_controller_iib.iib_signals[10].f      = resonant_swls.AuxCurrent.f;
    g_controller_iib.iib_signals[11].f      = resonant_swls.GroundLeakage.f;
    g_controller_iib.iib_signals[12].f      = resonant_swls.BoardTemperature.f;
    g_controller_iib.iib_signals[13].f      = resonant_swls.RelativeHumidity.f;
    g_controller_iib.iib_signals[14].u32    = resonant_swls.InterlocksRegister.u32;
    g_controller_iib.iib_signals[15].u32    = resonant_swls.AlarmsRegister.u32;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void config_module_resonant_swls(void)
{

#ifdef RES_SWLS

	//Leitura de tensao isolada
	LvCurrentCh1Init(LV_Primary_Voltage_Vin, LV_Secondary_Current_Vin, LV_Burden_Resistor, Delay_Vin);   // Vin
	LvCurrentCh2Init(LV_Primary_Voltage_Vout, LV_Secondary_Current_Vin, LV_Burden_Resistor, Delay_Vout); // Vout

	LvCurrentCh1AlarmLevelSet(RESONANT_SWLS_INPUT_OVERVOLTAGE_ALM_LIM);  //Tens�o de entrada Alarme
	LvCurrentCh1TripLevelSet(RESONANT_SWLS_INPUT_OVERVOLTAGE_ITLK_LIM);  //Tens�o de entrada Interlock
	LvCurrentCh2AlarmLevelSet(RESONANT_SWLS_OUTPUT_OVERVOLTAGE_ALM_LIM); //Tens�o de sa�da Alarme
	LvCurrentCh2TripLevelSet(RESONANT_SWLS_OUTPUT_OVERVOLTAGE_ITLK_LIM); //Tens�o de sa�da Interlock

/////////////////////////////////////////////////////////////////////////////////////////////

	//Set current range RESONANT_SWLS 130 A and 800 A
    CurrentCh1Init(LA_Primary_Current, LA_Secondary_Current, LA_Burden_Resistor, LA_Delay);         //Corrente Sensor Hall LEM LA 130-P
    CurrentCh2Init(Hall_Primary_Current, Hall_Secondary_Current, Hall_Burden_Resistor, Hall_Delay); //Corrente Sensor Hall LEM LF 510-S

    //Set protection limits FAP 130 A and 300 A
    CurrentCh1AlarmLevelSet(RESONANT_SWLS_INPUT_OVERCURRENT_ALM_LIM);   // Alarme Corrente Iin
    CurrentCh1TripLevelSet(RESONANT_SWLS_INPUT_OVERCURRENT_ITLK_LIM);   // Interlock Corrente Iin
    CurrentCh2AlarmLevelSet(RESONANT_SWLS_OUTPUT_OVERCURRENT_ALM_LIM);  // Alarme Corrente Iout
    CurrentCh2TripLevelSet(RESONANT_SWLS_OUTPUT_OVERCURRENT_ITLK_LIM);  // Interlock Corrente Iout

/////////////////////////////////////////////////////////////////////////////////////////////

    //Leitura de tensao (LDC)
    VoltageCh1Init(Current_GND_Leakage, Delay_GND_Leakage); //Ground Leakage

    VoltageCh1AlarmLevelSet(RESONANT_SWLS_GROUND_LEAKAGE_ALM_LIM); //Fuga para o terra alarme
    VoltageCh1TripLevelSet(RESONANT_SWLS_GROUND_LEAKAGE_ITLK_LIM); //Fuga para o terra interlock

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 configuration
    //Debouncing Delay seconds
    Pt100Ch1Delay(Delay_PT100CH1);
    Pt100Ch2Delay(Delay_PT100CH2);
    Pt100Ch3Delay(Delay_PT100CH3);
    Pt100Ch4Delay(Delay_PT100CH4);

    //PT100 configuration limits
    Pt100Ch1AlarmLevelSet(RESONANT_SWLS_HS_TRANSFORMER_AND_PFC_OVERTEMP_ALM_LIM);	//Alarme temperatura dissipador transformador e PFC
    Pt100Ch1TripLevelSet(RESONANT_SWLS_HS_TRANSFORMER_AND_PFC_OVERTEMP_ITLK_LIM);	//Interlock temperatura dissipador transformador e PFC

    Pt100Ch2AlarmLevelSet(RESONANT_SWLS_INDUC_OUTPUT_OVERTEMP_ALM_LIM);		//Alarme temperatura indutor de saida
    Pt100Ch2TripLevelSet(RESONANT_SWLS_INDUC_OUTPUT_OVERTEMP_ITLK_LIM);		//Interlock temperatura indutor de saida

    Pt100Ch3AlarmLevelSet(RESONANT_SWLS_HS_DIODES_OVERTEMP_ALM_LIM);		//Alarme temperatura dissipador diodos
    Pt100Ch3TripLevelSet(RESONANT_SWLS_HS_DIODES_OVERTEMP_ITLK_LIM);		//Interlock temperatura dissipador diodos

    Pt100Ch4AlarmLevelSet(RESONANT_SWLS_HS_CLAMP_OVERTEMP_ALM_LIM);		//Alarme temperatura dissipador clamp
    Pt100Ch4TripLevelSet(RESONANT_SWLS_HS_CLAMP_OVERTEMP_ITLK_LIM);		//Interlock temperatura dissipador clamp

/////////////////////////////////////////////////////////////////////////////////////////////

    //Temperature Board configuration
    BoardTempDelay(Delay_BoardTemp); //Inserir valor de delay

    //Temp board configuration limits
    BoardTempAlarmLevelSet(RESONANT_SWLS_BOARD_IIB_OVERTEMP_ALM_LIM);
    BoardTempTripLevelSet(RESONANT_SWLS_BOARD_IIB_OVERTEMP_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Humidity Board configuration
    RhDelay(Delay_BoardRh); //Inserir valor de delay

    //Rh configuration limits
    RhAlarmLevelSet(RESONANT_SWLS_BOARD_IIB_OVERHUMIDITY_ALM_LIM);
    RhTripLevelSet(RESONANT_SWLS_BOARD_IIB_OVERHUMIDITY_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Voltage configuration
    DriverVoltageInit();

    DriverVoltageDelay(Delay_DriverVoltage); //Inserir valor de delay

    //Limite de alarme e interlock da tensao dos drivers
    DriverVoltageAlarmLevelSet(RESONANT_SWLS_DRIVER_MOSFETS_AND_AUX_OVERVOLTAGE_ALM_LIM);
    DriverVoltageTripLevelSet(RESONANT_SWLS_DRIVER_MOSFETS_AND_AUX_OVERVOLTAGE_ITLK_LIM);

/////////////////////////////////////////////////////////////////////////////////////////////

    //Driver Current configuration
    DriverCurrentInit();

    DriverCurrentDelay(Delay_DriverCurrent); //Inserir valor de delay

    //Limite de alarme e interlock da corrente do driver 1
    Driver1CurrentAlarmLevelSet(RESONANT_SWLS_DRIVER1_MOSFETS_OVERCURRENT_ALM_LIM);
    Driver1CurrentTripLevelSet(RESONANT_SWLS_DRIVER1_MOSFETS_OVERCURRENT_ITLK_LIM);

    //Limite de alarme e interlock da corrente da placa auxiliar
    Driver2CurrentAlarmLevelSet(RESONANT_SWLS_AUX_SUPPLY_OVERCURRENT_ALM_LIM);
    Driver2CurrentTripLevelSet(RESONANT_SWLS_AUX_SUPPLY_OVERCURRENT_ITLK_LIM);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    //Init Variables
    resonant_swls.Vin.f                        		   = 0.0;
    resonant_swls.VinAlarmSts                  		   = 0;
    resonant_swls.VinItlkSts                   		   = 0;
    resonant_swls.Vout.f                       		   = 0.0;
    resonant_swls.VoutAlarmSts                 		   = 0;
    resonant_swls.VoutItlkSts                  		   = 0;
    resonant_swls.Iin.f                        		   = 0.0;
    resonant_swls.IinAlarmSts                  		   = 0;
    resonant_swls.IinItlkSts                   		   = 0;
    resonant_swls.Iout.f                       		   = 0.0;
    resonant_swls.IoutAlarmSts                 		   = 0;
    resonant_swls.IoutItlkSts                  		   = 0;
    resonant_swls.GroundLeakage.f              		   = 0.0;
    resonant_swls.GroundLeakageAlarmSts        		   = 0;
    resonant_swls.GroundLeakageItlkSts         		   = 0;
    resonant_swls.TempHeatSinkTransformerPfc.f         = 0.0;
    resonant_swls.TempHeatSinkTransformerPfcAlarmSts   = 0;
    resonant_swls.TempHeatSinkTransformerPfcItlkSts    = 0;
    resonant_swls.TempOutputInductor.f         		   = 0.0;
    resonant_swls.TempOutputInductorAlarmSts   		   = 0;
    resonant_swls.TempOutputInductorItlkSts    		   = 0;
    resonant_swls.TempHeatSinkDiodes.f        	       = 0.0;
    resonant_swls.TempHeatSinkDiodesAlarmSts  	       = 0;
    resonant_swls.TempHeatSinkDiodesItlkSts   	       = 0;
    resonant_swls.TempHeatSinkClamp.f         	       = 0.0;
    resonant_swls.TempHeatSinkClampAlarmSts   	       = 0;
    resonant_swls.TempHeatSinkClampItlkSts    	       = 0;
    resonant_swls.DriverAuxVoltage.f              	   = 0.0;
    resonant_swls.DriverAuxVoltageAlarmSts        	   = 0;
    resonant_swls.DriverAuxVoltageItlkSts         	   = 0;
    resonant_swls.Driver1Current.f             		   = 0.0;
    resonant_swls.Driver1CurrentAlarmSts       		   = 0;
    resonant_swls.Driver1CurrentItlkSts        		   = 0;
    resonant_swls.DriverFlagHSError                    = 0;
	resonant_swls.DriverFlagHSErrorItlkSts             = 0;
	resonant_swls.DriverFlagLSError                    = 0;
	resonant_swls.DriverFlagLSErrorItlkSts             = 0;
    resonant_swls.AuxCurrent.f                  	   = 0.0;
    resonant_swls.AuxCurrentAlarmSts             	   = 0;
    resonant_swls.AuxCurrentItlkSts              	   = 0;
    resonant_swls.BoardTemperature.f           		   = 0.0;
    resonant_swls.BoardTemperatureAlarmSts     		   = 0;
    resonant_swls.BoardTemperatureItlkSts      		   = 0;
    resonant_swls.RelativeHumidity.f           		   = 0.0;
    resonant_swls.RelativeHumidityAlarmSts     		   = 0;
    resonant_swls.RelativeHumidityItlkSts      		   = 0;
    resonant_swls.ContactorK1                          = 0;
    resonant_swls.ContactorK1OpenItlkSts               = 0;
    resonant_swls.ContactorK1ContactStickingItlkSts    = 0;
    resonant_swls.ContactorK2                          = 0;
    resonant_swls.ContactorK2OpenItlkSts               = 0;
    resonant_swls.ContactorK2ContactStickingItlkSts    = 0;
    resonant_swls.ContactorK1OverCurrentItlk           = 0;
    resonant_swls.ContactorK1OverCurrentItlkSts        = 0;
    resonant_swls.EmergencyButtonItlk          		   = 0;
    resonant_swls.EmergencyButtonItlkSts       		   = 0;
    resonant_swls.ReleAuxItlkSts               		   = 0;
    resonant_swls.InterlocksRegister.u32       		   = 0;
    resonant_swls.AlarmsRegister.u32           		   = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////




