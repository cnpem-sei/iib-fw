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
 * @file q1_module.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

#include "q1_module.h"
#include "iib_data.h"

#include "adc_internal.h"
#include "application.h"

#include "BoardTempHum.h"
#include "pt100.h"
#include "output.h"
#include "leds.h"
#include "can_bus.h"
#include "input.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * TODO: Put here your defines. Just what is local. If you don't
 * need to access it from other module, consider use a constant (const)
 */
#define Q1_INPUT_OVERVOLTAGE_ALM                    40.0
#define Q1_INPUT_OVERVOLTAGE_ITLK                   45.0
#define Q1_OUTPUT_OVERVOLTAGE_ALM                   9.0
#define Q1_OUTPUT_OVERVOLTAGE_ITLK                  10.0
#define Q1_OUTPUT_OVERCURRENT_1_ALM                 80.0
#define Q1_OUTPUT_OVERCURRENT_1_ITLK                85.0
#define Q1_OUTPUT_OVERCURRENT_2_ALM                 80.0
#define Q1_OUTPUT_OVERCURRENT_2_ITLK                85.0
#define Q1_IGBT1_OVERTEMP_ALM                       00.0    // Not in use
#define Q1_IGBT1_OVERTEMP_ITLK                      00.0    // Not in use
#define Q1_IGBT2_OVERTEMP_ALM                       00.0    // Not in use
#define Q1_IGBT2_OVERTEMP_ITLK                      00.0    // Not in use
#define Q1_DRIVER_OVERVOLTAGE_ALM                   00.0    // Not in use
#define Q1_DRIVER_OVERVOLTAGE_ITLK                  00.0    // Not in use
#define Q1_DRIVER1_OVERCURRENT_ALM                  00.0    // Not in use
#define Q1_DRIVER1_OVERCURRENT_ITLK                 00.0    // Not in use
#define Q1_DRIVER2_OVERCURRENT_ALM                  00.0    // Not in use
#define Q1_DRIVER2_OVERCURRENT_ITLK                 00.0    // Not in use
#define Q1_INDUC_OVERTEMP_ALM                       50.0
#define Q1_INDUC_OVERTEMP_ITLK                      60.0
#define Q1_HS_OVERTEMP_ALM                          80
#define Q1_HS_OVERTEMP_ITLK                         60
#define Q1_RH_ALM                                   80
#define Q1_RH_ITLK                                  90
#define Q1_BOARD_TEMP_ALM                           80
#define Q1_BOARD_TEMP_ITLK                          90

typedef struct
{
    union {
        float   f;
        uint8_t u8[4];
    } Vin;

    bool VinAlarmSts;
    bool VinItlkSts;

    union {
        float   f;
        uint8_t u8[4];
    } Vout;

    bool VoutAlarmSts;
    bool VoutItlkSts;

    union {
        float   f;
        uint8_t u8[4];
    } IoutA1;

    bool IoutA1AlarmSts;
    bool IoutA1ItlkSts;

    union {
        float   f;
        uint8_t u8[4];
    } IoutA2;

    bool IoutA2AlarmSts;
    bool IoutA2ItlkSts;

    union {
        float   f;
        uint8_t u8[4];
    } TempIGBT1;

    bool TempIGBT1AlarmSts;
    bool TempIGBT1ItlkSts;
    bool TempIGBT1HwrItlk;
    bool TempIGBT1HwrItlkSts;

    union {
        float   f;
        uint8_t u8[4];
    } TempIGBT2;

    bool TempIGBT2AlarmSts;
    bool TempIGBT2ItlkSts;
    bool TempIGBT2HwrItlk;
    bool TempIGBT2HwrItlkSts;

    union {
        float   f;
        uint8_t u[4];
    } DriveVoltage;

    union {
        float   f;
        uint8_t u[4];
    } Drive1Current;

    union {
        float   f;
        uint8_t u[4];
    } Drive2Current;

    bool Driver1Error;
    bool Driver1ErrorItlk;
    bool Driver2Error;
    bool Driver2ErrorItlk;

    union {
        float   f;
        uint8_t u[4];
    } TempL;

    bool TempLAlarmSts;
    bool TempLItlkSts;

    union {
        float   f;
        uint8_t u[4];
    } TempHeatSink;

    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    bool Relay;
    bool ExternalItlk;
    bool ExternalItlkSts;
    bool LeakageCurrent;
    bool LeakageCurrentSts;
    bool Rack;
    bool RackSts;
} q1_module_t;

/**
 * TODO: Put here your constants and variables. Always use static for 
 * private members.
 */

/**
 * TODO: Put here your function prototypes for private functions. Use
 * static in declaration.
 */
q1_module_t q1_module;
uint32_t q1_interlocks_indication   = 0;
uint32_t q1_alarms_indication       = 0;

static void get_itlks_id();
static void get_alarms_id();

/**
 * TODO: Put here the implementation for your public functions.
 */

void init_q1_module()
{
    //Set current range FAP 150 A
    CurrentCh1Init(130.0, 0.130, 50.0, 3); // Corrente braço1: Sensor Hall
    CurrentCh2Init(130.0, 0.130, 50.0, 3); // Corrente braço2: LEM LA 130-P

    //Set protection limits FAP 150 A
    //     These interlocks are bypassed due to the fact that their ADC's
    //     will most probably saturate during operation at 300 A. These
    //     measures are also performed by UDC, which guarantees these
    //     protections
    CurrentCh1AlarmLevelSet(Q1_OUTPUT_OVERCURRENT_1_ALM);  // Corrente braço1
    CurrentCh1TripLevelSet(Q1_OUTPUT_OVERCURRENT_1_ITLK);  // Corrente braço1
    CurrentCh2AlarmLevelSet(Q1_OUTPUT_OVERCURRENT_2_ALM);  // Corrente braço2
    CurrentCh2TripLevelSet(Q1_OUTPUT_OVERCURRENT_2_ITLK);  // Corrente braço2

    // NTC contiguration type
    //ConfigNtcType(SEMIX);

    //Leitura de tensão isolada
    LvCurrentCh1Init(450.0, 0.025, 120.0, 3); // Tensão de entrada
    LvCurrentCh2Init(250.0, 0.025, 120.0, 3); // Tensão de saída

    LvCurrentCh1AlarmLevelSet(Q1_INPUT_OVERVOLTAGE_ALM);   // Tensão de entrada Alarme
    LvCurrentCh1TripLevelSet(Q1_INPUT_OVERVOLTAGE_ITLK);   // Tensão de entrada Interlock
    LvCurrentCh2AlarmLevelSet(Q1_OUTPUT_OVERVOLTAGE_ALM);  // Tensão de saída Alarme
    LvCurrentCh2TripLevelSet(Q1_OUTPUT_OVERVOLTAGE_ITLK);  // Tensão de saída Interlock

    // PT100 configuration limits
    Pt100SetCh1AlarmLevel(Q1_HS_OVERTEMP_ALM);     // Temperatura Dissipador
    Pt100SetCh1TripLevel(Q1_HS_OVERTEMP_ITLK);     // Temperatura Dissipador
    Pt100SetCh2AlarmLevel(Q1_INDUC_OVERTEMP_ALM);  // Temperatura L
    Pt100SetCh2TripLevel(Q1_INDUC_OVERTEMP_ITLK);  // Temperatura L

    // Delay 4 seconds
    Pt100SetCh1Delay(4);
    // Delay 4 seconds
    Pt100SetCh2Delay(4);

    // PT100 channel enable
    Pt100Ch1Enable(); // Temperatura Dissipador
    Pt100Ch2Enable(); // Temperatura L
    Pt100Ch3Disable();
    Pt100Ch4Disable();

    // Rh configuration limits
    RhAlarmLimitSet(Q1_RH_ALM);
    RhTripLimitSet(Q1_RH_ITLK);

    // Temp board configuration limits
    TempBoardAlarmLimitSet(Q1_BOARD_TEMP_ALM);
    TempBoardTripLimitSet(Q1_BOARD_TEMP_ITLK);

    Driver1ErrEnable();
    Driver2ErrEnable();

    // Init Variables
    q1_module.Vin.f                 = 0.0;
    q1_module.VinAlarmSts           = 0;
    q1_module.VinItlkSts            = 0;
    q1_module.Vout.f                = 0.0;
    q1_module.VoutAlarmSts          = 0;
    q1_module.VoutItlkSts           = 0;
    q1_module.IoutA1.f              = 0.0;
    q1_module.IoutA1AlarmSts        = 0;
    q1_module.IoutA1ItlkSts         = 0;
    q1_module.IoutA2.f              = 0.0;
    q1_module.IoutA2AlarmSts        = 0;
    q1_module.IoutA2ItlkSts         = 0;
    q1_module.TempIGBT1.f           = 0.0;
    q1_module.TempIGBT1AlarmSts     = 0;
    q1_module.TempIGBT1ItlkSts      = 0;
    q1_module.TempIGBT1HwrItlk      = 0;
    q1_module.TempIGBT1HwrItlkSts   = 0;
    q1_module.TempIGBT2.f           = 0.0;
    q1_module.TempIGBT2AlarmSts     = 0;
    q1_module.TempIGBT2ItlkSts      = 0;
    q1_module.TempIGBT2HwrItlk      = 0;
    q1_module.TempIGBT2HwrItlkSts   = 0;
    q1_module.DriveVoltage.f        = 0.0;
    q1_module.Drive1Current.f       = 0.0;
    q1_module.Drive2Current.f       = 0.0;
    q1_module.Driver1Error          = 0;
    q1_module.Driver1ErrorItlk      = 0;
    q1_module.Driver2Error          = 0;
    q1_module.Driver2ErrorItlk      = 0;
    q1_module.TempL.f               = 0;
    q1_module.TempLAlarmSts         = 0;
    q1_module.TempLItlkSts          = 0;
    q1_module.TempHeatSink.f        = 0;
    q1_module.TempHeatSinkAlarmSts  = 0;
    q1_module.TempHeatSinkItlkSts   = 0;
    q1_module.Relay                 = 0;
    q1_module.ExternalItlk          = 0;
    q1_module.ExternalItlkSts       = 0;
    q1_module.LeakageCurrent        = 0;
    q1_module.LeakageCurrentSts     = 0;
    q1_module.Rack                  = 0;
    q1_module.RackSts               = 0;
}

void clear_q1_interlocks()
{
    q1_module.VinItlkSts            = 0;
    q1_module.VoutItlkSts           = 0;
    q1_module.IoutA1ItlkSts         = 0;
    q1_module.IoutA2ItlkSts         = 0;
    q1_module.TempIGBT1ItlkSts      = 0;
    q1_module.TempIGBT1HwrItlkSts   = 0;
    q1_module.TempIGBT2ItlkSts      = 0;
    q1_module.TempIGBT2HwrItlkSts   = 0;
    q1_module.Driver1ErrorItlk      = 0;
    q1_module.Driver2ErrorItlk      = 0;
    q1_module.TempLItlkSts          = 0;
    q1_module.TempHeatSinkItlkSts   = 0;
    q1_module.ExternalItlkSts       = 0;
    q1_module.LeakageCurrentSts     = 0;
    q1_module.RackSts               = 0;
}

uint8_t check_q1_interlocks()
{
    uint8_t test = 0;

    test |= q1_module.VinItlkSts;
    test |= q1_module.VoutItlkSts;
    test |= q1_module.IoutA1ItlkSts;
    test |= q1_module.IoutA2ItlkSts;
    test |= q1_module.TempIGBT1ItlkSts;
    test |= q1_module.TempIGBT1HwrItlkSts;
    test |= q1_module.TempIGBT2ItlkSts;
    test |= q1_module.TempIGBT2HwrItlkSts;
    test |= q1_module.Driver1ErrorItlk;
    test |= q1_module.Driver2ErrorItlk;
    test |= q1_module.TempLItlkSts;
    test |= q1_module.TempHeatSinkItlkSts;
    test |= q1_module.ExternalItlkSts;
    test |= q1_module.LeakageCurrentSts;
    test |= q1_module.RackSts;

    return test;
}

void clear_q1_alarms()
{
    q1_module.VinItlkSts             = 0;
    q1_module.VoutItlkSts            = 0;
    q1_module.IoutA1ItlkSts          = 0;
    q1_module.IoutA2ItlkSts          = 0;
    q1_module.TempIGBT1ItlkSts       = 0;
    q1_module.TempIGBT1HwrItlkSts    = 0;
    q1_module.TempIGBT2ItlkSts       = 0;
    q1_module.TempIGBT2HwrItlkSts    = 0;
    q1_module.Driver1ErrorItlk       = 0;
    q1_module.Driver2ErrorItlk       = 0;
    q1_module.TempLItlkSts           = 0;
    q1_module.TempHeatSinkItlkSts    = 0;
    q1_module.ExternalItlkSts        = 0;
    q1_module.LeakageCurrentSts      = 0;
    q1_module.RackSts                = 0;
}

uint8_t check_q1_alarms()
{
    uint8_t test = 0;

    test |= q1_module.VinAlarmSts;
    test |= q1_module.VoutAlarmSts;
    test |= q1_module.IoutA1AlarmSts;
    test |= q1_module.IoutA2AlarmSts;
    test |= q1_module.TempIGBT1AlarmSts;
    test |= q1_module.TempIGBT2AlarmSts;
    test |= q1_module.TempLAlarmSts;
    test |= q1_module.TempHeatSinkAlarmSts;

    return test;
}

void check_q1_indication_leds()
{
    // Output over voltage
    if(q1_module.VoutItlkSts) Led2TurnOn();
    else if(q1_module.VoutAlarmSts) Led2Toggle();
    else Led2TurnOff();

    // Input over voltage
    if(q1_module.VinItlkSts) Led3TurnOn();
    else if(q1_module.VinAlarmSts) Led3Toggle();
    else Led3TurnOff();

    // Output over current
    if (q1_module.IoutA1ItlkSts || q1_module.IoutA2ItlkSts) Led4TurnOn();
    else if(q1_module.IoutA1AlarmSts || q1_module.IoutA2AlarmSts) Led4Toggle();
    else Led4TurnOff();

    // Over temperature
    if(q1_module.TempIGBT1ItlkSts || q1_module.TempIGBT2ItlkSts ||  q1_module.TempLItlkSts || q1_module.TempHeatSinkItlkSts || q1_module.TempIGBT1HwrItlkSts || q1_module.TempIGBT2HwrItlkSts) Led5TurnOn();
    else if(q1_module.TempIGBT1AlarmSts || q1_module.TempIGBT2AlarmSts ||  q1_module.TempLAlarmSts || q1_module.TempHeatSinkAlarmSts) Led5Toggle();
    else Led5TurnOff();

    if(q1_module.ExternalItlkSts) Led6TurnOn();
    else Led6TurnOff();

    if(q1_module.LeakageCurrentSts) Led7TurnOn();
    else Led7TurnOff();

    if(q1_module.RackSts) Led8TurnOn();
    else Led8TurnOff();

    if(q1_module.Driver1ErrorItlk || q1_module.Driver2ErrorItlk) Led9TurnOn();
    else if(!InterlockRead()) Led9TurnOff();

    if(InterlockRead()) Led10TurnOn();
    else Led10TurnOff();
}

void q1_application_readings()
{
    q1_module.TempHeatSink.f = (float) Pt100ReadCh1();//PT100 CH1
    q1_module.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
    if(!q1_module.TempHeatSinkItlkSts)q1_module.TempHeatSinkItlkSts        = Pt100ReadCh1TripSts();

    q1_module.TempL.f = (float) Pt100ReadCh2();//PT100 CH2
    q1_module.TempLAlarmSts = Pt100ReadCh2AlarmSts();
    if(!q1_module.TempLItlkSts)q1_module.TempLItlkSts                      = Pt100ReadCh2TripSts();

    q1_module.TempIGBT1.f = 0.0;
    q1_module.TempIGBT1AlarmSts = 0;
    q1_module.TempIGBT1ItlkSts = 0;

    if(!q1_module.TempIGBT1HwrItlkSts) q1_module.TempIGBT1HwrItlkSts       = Driver1OverTempRead();

    q1_module.TempIGBT2.f = 0.0;
    q1_module.TempIGBT2AlarmSts = 0;
    q1_module.TempIGBT2ItlkSts = 0;

    if(!q1_module.TempIGBT2HwrItlkSts) q1_module.TempIGBT2HwrItlkSts       = Driver2OverTempRead();

    q1_module.IoutA1.f = CurrentCh1Read();//HALL CH1
    q1_module.IoutA1AlarmSts = CurrentCh1AlarmStatusRead();
    if(!q1_module.IoutA1ItlkSts)q1_module.IoutA1ItlkSts                    = CurrentCh1TripStatusRead();

    q1_module.IoutA2.f = CurrentCh2Read();//HALL CH2
    q1_module.IoutA2AlarmSts = CurrentCh2AlarmStatusRead();
    if(!q1_module.IoutA2ItlkSts)q1_module.IoutA2ItlkSts                    = CurrentCh2TripStatusRead();

    q1_module.Vin.f = LvCurrentCh1Read();
    q1_module.VinAlarmSts = LvCurrentCh1AlarmStatusRead();
    if(!q1_module.VinItlkSts)q1_module.VinItlkSts                          = LvCurrentCh1TripStatusRead();

    q1_module.Vout.f = LvCurrentCh2Read();
    q1_module.VoutAlarmSts = LvCurrentCh2AlarmStatusRead();
    if(!q1_module.VoutItlkSts)q1_module.VoutItlkSts                        = LvCurrentCh2TripStatusRead();

    q1_module.ExternalItlk = Gpdi1Read();
    if(!q1_module.ExternalItlkSts) q1_module.ExternalItlkSts               = Gpdi1Read();

    q1_module.LeakageCurrent = Gpdi2Read();
    if(!q1_module.LeakageCurrentSts) q1_module.LeakageCurrentSts           = Gpdi2Read();

    q1_module.Rack = Gpdi3Read();
    if(!q1_module.RackSts) q1_module.RackSts                               = Gpdi3Read();

    q1_module.Relay = !Gpdi4Read();

    q1_module.Driver1Error = Driver1TopErrRead();
    if(!q1_module.Driver1ErrorItlk) q1_module.Driver1ErrorItlk             = Driver1TopErrRead();

    q1_module.Driver2Error = Driver2TopErrRead();
    if(!q1_module.Driver2ErrorItlk) q1_module.Driver2ErrorItlk             = Driver2TopErrRead();

    if(q1_module.ExternalItlkSts || q1_module.Driver2ErrorItlk || q1_module.Driver2ErrorItlk) InterlockSet(); // If no signal over the port, then set Interlock action

    q1_map_vars();
    get_itlks_id();
    get_alarms_id();
}

void q1_map_vars()
{
    g_controller_iib.iib_signals[0].u32     = q1_interlocks_indication;
    g_controller_iib.iib_signals[1].u32     = q1_alarms_indication;
    g_controller_iib.iib_signals[2].f       = q1_module.Vin.f;
    g_controller_iib.iib_signals[3].f       = q1_module.Vout.f;
    g_controller_iib.iib_signals[4].f       = q1_module.IoutA1.f;
    g_controller_iib.iib_signals[5].f       = q1_module.IoutA2.f;
    g_controller_iib.iib_signals[6].f       = q1_module.TempIGBT1.f;
    g_controller_iib.iib_signals[7].f       = q1_module.TempIGBT2.f;
    g_controller_iib.iib_signals[8].f       = q1_module.DriveVoltage.f;
    g_controller_iib.iib_signals[9].f       = q1_module.Drive1Current.f;
    g_controller_iib.iib_signals[10].f      = q1_module.Drive2Current.f;
    g_controller_iib.iib_signals[11].f      = q1_module.TempL.f;
    g_controller_iib.iib_signals[12].f      = q1_module.TempHeatSink.f;
}

void send_q1_module_data()
{
    uint8_t i;
    for (i = 0; i < 13; i++) send_data_message(i);
}

static void get_itlks_id()
{
    if (q1_module.VinItlkSts)           g_itlk_id |= INPUT_OVERVOLTAGE_ITLK;
    if (q1_module.VoutItlkSts)          g_itlk_id |= OUTPUT_OVERVOLTAGE_ITLK;
    if (q1_module.IoutA1ItlkSts)        g_itlk_id |= OUTPUT_OVERCURRENT_1_ITLK;
    if (q1_module.IoutA2ItlkSts)        g_itlk_id |= OUTPUT_OVERCURRENT_2_ITLK;
    if (q1_module.TempIGBT1ItlkSts)     g_itlk_id |= IGBT1_OVERTEMP_ITLK;
    if (q1_module.TempIGBT2ItlkSts)     g_itlk_id |= IGBT2_OVERTEMP_ITLK;
    if (q1_module.Driver1ErrorItlk)     g_itlk_id |= DRIVER1_ERROR_ITLK;
    if (q1_module.Driver2ErrorItlk)     g_itlk_id |= DRIVER2_ERROR_ITLK;
    if (q1_module.TempLItlkSts)         g_itlk_id |= INDUC_OVERTEMP_ITLK;
    if (q1_module.TempHeatSinkItlkSts)  g_itlk_id |= HS_OVERTEMP_ITLK;
    if (q1_module.Relay)                g_itlk_id |= RELAY_ITLK;
    if (q1_module.ExternalItlkSts)      g_itlk_id |= EXTERNAL_ITLK;
    if (q1_module.LeakageCurrentSts)    g_itlk_id |= LEAKAGE_CURRENT_ITLK;
    if (q1_module.RackSts)              g_itlk_id |= RACK_ITLK;
}

static void get_alarms_id()
{
    if (q1_module.VinAlarmSts)          g_alarm_id |= INPUT_OVERVOLTAGE_ALM;
    if (q1_module.VoutAlarmSts)         g_alarm_id |= OUTPUT_OVERVOLTAGE_ALM;
    if (q1_module.IoutA1AlarmSts)       g_alarm_id |= OUTPUT_OVERCURRENT_1_ALM;
    if (q1_module.IoutA2AlarmSts)       g_alarm_id |= OUTPUT_OVERCURRENT_2_ALM;
    if (q1_module.TempIGBT1AlarmSts)    g_alarm_id |= IGBT1_OVERTEMP_ALM;
    if (q1_module.TempIGBT2AlarmSts)    g_alarm_id |= IGBT2_OVERTEMP_ALM;
    if (q1_module.TempLAlarmSts)        g_alarm_id |= INDUC_OVERTEMP_ALM;
    if (q1_module.TempHeatSinkAlarmSts) g_alarm_id |= HS_OVERTEMP_ALM;
}

float q1_module_vout_read(void)
{
    return q1_module.Vout.f;
}

unsigned char q1_module_vout_alarm_sts_read(void)
{
    return q1_module.VoutAlarmSts;
}

unsigned char q1_module_vout_itlk_sts_read(void)
{
    return q1_module.VoutItlkSts;
}

//**********************************************
float q1_module_vin_read(void)
{
    return q1_module.Vin.f;
}

unsigned char q1_module_vin_alarm_sts_read(void)
{
    return q1_module.VinAlarmSts;
}

unsigned char q1_module_vin_itlk_sts_read(void)
{
    return q1_module.VinItlkSts;
}

//**********************************************
float q1_module_iout_a1_read(void)
{
    return q1_module.IoutA1.f;
}

unsigned char q1_module_iout_a1_alarm_sts_read(void)
{
    return q1_module.IoutA1AlarmSts;
}

unsigned char q1_module_iout_a1_itlk_sts_read(void)
{
    return q1_module.IoutA1ItlkSts;
}

//**********************************************
float q1_module_iout_a2_read(void)
{
    return q1_module.IoutA2.f;
}

unsigned char q1_module_iout_a2_alarm_sts_read(void)
{
    return q1_module.IoutA2AlarmSts;
}

unsigned char q1_module_iout_a2_itlk_sts_read(void)
{
    return q1_module.IoutA2ItlkSts;
}

//**********************************************
unsigned char q1_module_temp_IGBT1_read(void)
{
    return q1_module.TempIGBT1.f;
}

unsigned char q1_module_temp_IGBT1_alarm_sts_read(void)
{
    return q1_module.TempIGBT1AlarmSts;
}

unsigned char q1_module_temp_IGBT1_itlk_sts_read(void)
{
    return q1_module.TempIGBT1ItlkSts;
}

unsigned char q1_module_temp_IGBT1_hwr_itlk_read(void)
{
    return q1_module.TempIGBT1HwrItlk;
}

unsigned char q1_module_temp_IGBT1_hwr_itlk_sts_read(void)
{
    return q1_module.TempIGBT1HwrItlkSts;
}

//**********************************************
unsigned char q1_module_temp_IGBT2_read(void)
{
    return q1_module.TempIGBT2.f;
}

unsigned char q1_module_temp_IGBT2_alarm_sts_read(void)
{
    return q1_module.TempIGBT2AlarmSts;
}

unsigned char q1_module_temp_IGBT2_itlk_sts_read(void)
{
    return q1_module.TempIGBT2ItlkSts;
}

unsigned char q1_module_temp_IGBT2_hwr_itlk_read(void)
{
    return q1_module.TempIGBT2HwrItlk;
}

unsigned char q1_module_temp_IGBT2_hwr_itlk_sts_read(void)
{
    return q1_module.TempIGBT2HwrItlkSts;
}

//**********************************************
unsigned char q1_module_temp_heatsink_read(void)
{
    return q1_module.TempHeatSink.f;
}

unsigned char q1_module_temp_heatsink_alarm_sts_read(void)
{
    return q1_module.TempHeatSinkAlarmSts;
}

unsigned char q1_module_temp_heatsink_itlk_sts_read(void)
{
    return q1_module.TempHeatSinkItlkSts;
}

//**********************************************
unsigned char q1_module_tempL_read(void)
{
    return q1_module.TempL.f;
}

unsigned char q1_module_tempL_alarm_sts_read(void)
{
    return q1_module.TempLAlarmSts;
}

unsigned char q1_module_tempL_itlk_sts_read(void)
{
    return q1_module.TempLItlkSts;
}

//**********************************************
unsigned char q1_module_relay_read(void)
{
    return q1_module.Relay;
}

//**********************************************
unsigned char q1_module_driver1_error_read(void)
{
    return q1_module.Driver1Error;
}

unsigned char q1_module_driver1_error_itlk_read(void)
{
    return q1_module.Driver1ErrorItlk;
}

//**********************************************
unsigned char q1_module_driver2_error_read(void)
{
    return q1_module.Driver2Error;
}

unsigned char q1_module_driver2_error_itlk_read(void)
{
    return q1_module.Driver2ErrorItlk;
}

//**********************************************
unsigned char q1_module_external_itlk_read(void)
{
    return q1_module.ExternalItlk;
}

unsigned char q1_module_external_itlk_sts_read(void)
{
    return q1_module.ExternalItlkSts;
}

//**********************************************
unsigned char q1_module_leakage_current_read(void)
{
    return q1_module.LeakageCurrent;

}

unsigned char q1_module_leakage_current_sts_read(void)
{
    return q1_module.LeakageCurrentSts;

}

//**********************************************
unsigned char q1_moduleRackRead(void)
{
    return q1_module.Rack;

}

unsigned char q1_module_rack_sts_read(void)
{
    return q1_module.RackSts;
}
