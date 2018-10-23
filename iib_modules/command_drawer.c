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
 * @file command_drawer.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

#include "command_drawer.h"
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

#define CM_CAPBANK_OVERVOLTAGE_ITLK        300.0
#define CM_CAPBANK_OVERVOLTAGE_ALM         250.0
#define CM_OUTPUT_OVERVOLTAGE_ITLK         210.0
#define CM_OUTPUT_OVERVOLTAGE_ALM          180.0
#define CM_HS_OVERTEMP_ITLK                60.0
#define CM_HS_OVERTEMP_ALM                 55.0
#define CM_INDUC_OVERTEMP_ITLK             60.0
#define CM_INDUC_OVERTEMP_ALM              55.0

typedef struct
{
    /* PT100CH1 */
    uint8_t TempHeatSink;
    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    /* PT100CH2 */
    uint8_t TempL;
    bool TempLAlarmSts;
    bool TempLItlkSts;
    /* LCH1 */
    float VcapBank;
    bool VcapBankAlarmSts;
    bool VcapBankItlkSts;
    /* LCH2 */
    float Vout;
    bool VoutAlarmSts;
    bool VoutItlkSts;
    /* GPDIO1 */
    bool ExtItlkSts;
    /* GPDI05*/
    bool ExtItlk2Sts;

} command_module_t;

/**
 * TODO: Put here your constants and variables. Always use static for
 * private members.
 */

/**
 * TODO: Put here your function prototypes for private functions. Use
 * static in declaration.
 */

command_module_t command_module;
uint32_t command_module_interlocks_indication   = 0;
uint32_t command_module_alarms_indication       = 0;

static void get_itlks_id();
static void get_alarms_id();

/**
 * TODO: Put here the implementation for your public functions.
 */

void init_command_module()
{
    //Setar ranges de entrada
    VoltageCh1Init(330.0, 3);                 // Capacitors Voltage Configuration.
    VoltageCh2Init(250.0, 3);                 // Output Voltage Configuration.

    ConfigVoltCh1AsNtc(0);                 // Config Voltage Ch1 as a voltage input
    ConfigVoltCh2AsNtc(0);                 // Config Voltage Ch2 as a voltage input

    //Setar limites
    VoltageCh1AlarmLevelSet(CM_CAPBANK_OVERVOLTAGE_ALM); // Rectifier1 Voltage Alarm
    VoltageCh1TripLevelSet(CM_CAPBANK_OVERVOLTAGE_ITLK); // Rectifier1 Voltage Trip
    VoltageCh2AlarmLevelSet(CM_OUTPUT_OVERVOLTAGE_ALM); // Rectifier2 Voltage Alarm
    VoltageCh2TripLevelSet(CM_OUTPUT_OVERVOLTAGE_ITLK); // Rectifier2 Voltage Trip

    // PT100 configuration limits
    Pt100SetCh1AlarmLevel(CM_HS_OVERTEMP_ALM); // HEATSINK TEMPERATURE ALARM LEVEL
    Pt100SetCh1TripLevel(CM_HS_OVERTEMP_ITLK); // HEATSINK TEMPERATURE TRIP LEVEL
    Pt100SetCh2AlarmLevel(CM_INDUC_OVERTEMP_ALM); // INDUCTOR TEMPERATURE ALARM LEVEL
    Pt100SetCh2TripLevel(CM_INDUC_OVERTEMP_ITLK); // INDUCTOR TEMPERATURE TRIP LEVEL

    // PT100 channel enable
    Pt100Ch1Enable();                     // HEATSINK TEMPERATURE CHANNEL ENABLE
    Pt100Ch2Enable();                     // INDUCTOR TEMPERATURE CHANNEL ENABLE
    Pt100Ch3Disable();
    Pt100Ch4Disable();

    // Delay 4 seconds
    Pt100SetCh1Delay(4);
    // Delay 4 seconds
    Pt100SetCh2Delay(4);
    // Delay 4 seconds
    Pt100SetCh3Delay(4);
    // Delay 4 seconds
    Pt100SetCh4Delay(4);

    command_module.VcapBank                 = 0.0;
    command_module.VcapBankAlarmSts         = 0;
    command_module.VcapBankItlkSts          = 0;

    command_module.Vout                     = 0.0;
    command_module.VoutAlarmSts             = 0;
    command_module.VoutItlkSts              = 0;

    command_module.TempHeatSink             = 0;
    command_module.TempHeatSinkAlarmSts     = 0;
    command_module.TempHeatSinkItlkSts      = 0;

    command_module.TempL                    = 0;
    command_module.TempLAlarmSts            = 0;
    command_module.TempLItlkSts             = 0;

    command_module.ExtItlkSts               = 0;

    command_module.ExtItlk2Sts              = 0;
}

void clear_command_module_interlocks()
{
    command_module.VcapBankItlkSts         = 0;
    command_module.VoutItlkSts             = 0;
    command_module.TempHeatSinkItlkSts     = 0;
    command_module.TempLItlkSts            = 0;
    command_module.ExtItlkSts              = 0;
    command_module.ExtItlk2Sts             = 0;
}

uint8_t check_command_module_interlocks()
{
    uint8_t test = 0;

    test |= command_module.TempHeatSinkItlkSts;
    test |= command_module.TempLItlkSts;
    test |= command_module.VcapBankItlkSts;
    test |= command_module.VoutItlkSts;
    test |= command_module.ExtItlkSts;
    test |= command_module.ExtItlk2Sts;

    return test;
}

void clear_command_module_alarms()
{
    command_module.VcapBankAlarmSts        = 0;
    command_module.VoutAlarmSts            = 0;
    command_module.TempHeatSinkAlarmSts    = 0;
    command_module.TempLAlarmSts           = 0;
}

uint8_t check_command_module_alarms()
{
    uint8_t test = 0;

    test |= command_module.TempHeatSinkAlarmSts;
    test |= command_module.TempLAlarmSts;
    test |= command_module.VcapBankAlarmSts;
    test |= command_module.VoutAlarmSts;

    return 0;
}

void check_command_module_indication_leds()
{
    if (command_module.VcapBankItlkSts) Led2TurnOn();
    else if (command_module.VcapBankAlarmSts) Led2Toggle();
    else Led2TurnOff();

    if (command_module.VoutItlkSts) Led3TurnOn();
    else if (command_module.VoutAlarmSts) Led3Toggle();
    else Led3TurnOff();

    if (command_module.TempHeatSinkItlkSts) Led4TurnOn();
    else if (command_module.TempHeatSinkAlarmSts) Led4Toggle();
    else Led4TurnOff();

    if (command_module.TempLItlkSts) Led5TurnOn();
    else if (command_module.TempLAlarmSts) Led5TurnOff();
    else Led5TurnOff();

    if (command_module.ExtItlkSts) Led6TurnOn();
    else Led6TurnOff();

    if (command_module.ExtItlk2Sts) Led7TurnOn();
    else Led7TurnOff();
}

void command_module_application_readings()
{
    command_module.TempHeatSink = Pt100ReadCh1();
    command_module.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
    if (!command_module.TempHeatSinkItlkSts) command_module.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();

    command_module.TempL = Pt100ReadCh2();
    command_module.TempLAlarmSts = Pt100ReadCh2AlarmSts();
    if (!command_module.TempLItlkSts) command_module.TempLItlkSts          = Pt100ReadCh2TripSts();

    command_module.VcapBank = VoltageCh1Read();
    command_module.VcapBankAlarmSts = VoltageCh1AlarmStatusRead();
    if (!command_module.VcapBankItlkSts) command_module.VcapBankItlkSts    = VoltageCh1TripStatusRead();

    command_module.Vout = VoltageCh2Read();
    command_module.VoutAlarmSts = VoltageCh2AlarmStatusRead();
    if (!command_module.VoutItlkSts) command_module.VoutItlkSts            = VoltageCh2TripStatusRead();

    if(!command_module.ExtItlkSts) command_module.ExtItlkSts               = Gpdi1Read();

    if(!command_module.ExtItlk2Sts) command_module.ExtItlk2Sts             = Gpdi5Read();

    command_module_map_vars();

    get_alarms_id();
    get_itlks_id();
}

void command_module_map_vars()
{
    g_controller_iib.iib_signals[0].u32     = command_module_interlocks_indication;
    g_controller_iib.iib_signals[1].u32     = command_module_alarms_indication;
    g_controller_iib.iib_signals[2].f       = command_module.VcapBank;
    g_controller_iib.iib_signals[3].f       = command_module.Vout;
    g_controller_iib.iib_signals[4].u8[0]   = command_module.TempL;
    g_controller_iib.iib_signals[5].u8[0]   = command_module.TempHeatSink;
}

static void get_itlks_id()
{
    if (command_module.VcapBankItlkSts)         g_itlk_id |= CAPBANK_OVERVOLTAGE_ITLK;
    if (command_module.VoutItlkSts)             g_itlk_id |= OUTPUT_OVERVOLTAGE_ITLK;
    if (command_module.TempHeatSinkItlkSts)     g_itlk_id |= HS_OVERTEMP_ITLK;
    if (command_module.TempLItlkSts)            g_itlk_id |= INDUC_OVERTEMP_ITLK;
    if (command_module.ExtItlkSts)              g_itlk_id |= EXTERNAL1_ITLK;
    if (command_module.ExtItlk2Sts)             g_itlk_id |= EXTERNAL2_ITLK;
}

static void get_alarms_id()
{
    if (command_module.VcapBankAlarmSts)     g_alarm_id |= CAPBANK_OVERVOLTAGE_ALM;
    if (command_module.VoutItlkSts)          g_alarm_id |= OUTPUT_OVERVOLTAGE_ALM;
    if (command_module.TempHeatSinkAlarmSts) g_alarm_id |= HS_OVERTEMP_ALM;
    if (command_module.TempLAlarmSts)        g_alarm_id |= INDUC_OVERTEMP_ALM;
}

unsigned char command_drawer_temp_heatsink_read(void)
{
    return command_module.TempHeatSink;
}

unsigned char command_drawer_temp_heatsink_alarm_sts_read(void)
{
    return command_module.TempHeatSinkAlarmSts;
}

unsigned char Command_Drawer_Temp_HeatSink_Itlk_sts_read(void)
{
    return command_module.TempHeatSinkItlkSts;
}

//******************************************************************************
unsigned char command_drawer_tempL_read(void)
{
    return command_module.TempL;
}

unsigned char command_drawer_tempL_alarm_sts_read(void)
{
    return command_module.TempLAlarmSts;
}

unsigned char command_drawer_tempL_itlk_sts_read(void)
{
    return command_module.TempLItlkSts;
}

//******************************************************************************

float command_drawer_vcapbank_read(void)
{
    return command_module.VcapBank;
}

unsigned char command_drawer_vcapbank_alarm_sts_read(void)
{
    return command_module.VcapBankAlarmSts;
}

unsigned char command_drawer_vcapbank_itlk_sts_read(void)
{
    return command_module.VcapBankItlkSts;
}

//******************************************************************************
float command_drawer_vout_read(void)
{
    return command_module.Vout;
}

unsigned char command_drawer_vout_alarm_sts_read(void)
{
    return command_module.VoutAlarmSts;
}

unsigned char command_drawer_vout_itlk_sts_read(void)
{
    return command_module.VoutItlkSts;
}

unsigned char command_drawer_ext_itlk_sts_read()
{
    return command_module.ExtItlkSts;
}

unsigned char command_drawer_ext2_itlk_sts_read()
{
    return command_module.ExtItlk2Sts;
}
