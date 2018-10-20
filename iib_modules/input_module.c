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
 * @file input_module.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

#include "input_module.h"
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

#define IM_INPUT_OVERCURRENT_ALM            160.0
#define IM_INPUT_OVERCURRENT_ITLK           170.0
#define IM_DCLINK_OVERVOLTAGE_ALM           535.0
#define IM_DCLINK_OVERVOLTAGE_ITLK          540.0
#define IM_HS_OVERTEMP_ALM                  45.0
#define IM_HS_OVERTEMP_ITLK                 50.0
#define IM_INDUC_OVERTEMP_ALM               55.0
#define IM_INDUC_OVERTEMP_ITLK              60.0
#define IM_RH_ALM                           80.0
#define IM_RH_ITLK                          90.0
#define IM_BOARD_TEMP_ALM                   80.0
#define IM_BOARD_TEMP_ITLK                  90.0

typedef struct
{

    float Iin;
    bool IinAlarmSts;
    bool IinItlkSts;
    float VdcLink;
    bool VdcLinkAlarmSts;
    bool VdcLinkItlkSts;
    uint8_t TempHeatsink;
    bool TempHeatsinkAlarmSts;
    bool TempHeatsinkItlkSts;
    uint8_t TempL;
    bool TempLAlarmSts;
    bool TempLItlkSts;
    bool Driver1Error;
    bool Driver1ErrorItlk;
    bool Driver2Error;
    bool Driver2ErrorItlk;

} input_module_t;

/**
 * TODO: Put here your defines. Just what is local. If you don't
 * need to access it from other module, consider use a constant (const)
 */


/**
 * TODO: Put here your constants and variables. Always use static for 
 * private members.
 */
input_module_t input_module;
uint32_t im_interlocks_indication = 0;
uint32_t im_alarms_indication = 0;

/**
 * TODO: Put here your function prototypes for private functions. Use
 * static in declaration.
 */

void init_input_module()
{
    //Set Current Range
    CurrentCh1Init(300.0, 0.150, 50.0, 10);    // INPUT CURRENT

    //Set Protection Limits
    CurrentCh1AlarmLevelSet(IM_INPUT_OVERCURRENT_ALM); // INPUT CURRENT ALARM LEVEL
    CurrentCh1TripLevelSet(IM_INPUT_OVERCURRENT_ITLK); // INPUT CURRENT TRIP LEVEL

    //LV20-P INPUTS
    LvCurrentCh1Init(550.0, 0.025, 120.0, 10); // CONFIG CHANNEL FOR DC_LINK MEASURE

    //LV20-P LIMITS
    CurrentCh1AlarmLevelSet(IM_DCLINK_OVERVOLTAGE_ALM); // INPUT DC_LINK VOLTAGE ALARM LEVEL
    CurrentCh1TripLevelSet(IM_DCLINK_OVERVOLTAGE_ITLK); // INPUT DC_LINK VOLTAGE TRIP LEVEL

    // PT100 configuration limits
    Pt100SetCh1AlarmLevel(IM_HS_OVERTEMP_ALM); // HEATSINK TEMPERATURE ALARM LEVEL
    Pt100SetCh1TripLevel(IM_HS_OVERTEMP_ITLK); // HEATSINK TEMPERATURE TRIP LEVEL
    Pt100SetCh2AlarmLevel(IM_INDUC_OVERTEMP_ALM); // INDUCTOR TEMPERATURE ALARM LEVEL
    Pt100SetCh2TripLevel(IM_INPUT_OVERCURRENT_ITLK); // INDUCTOR TEMPERATURE TRIP LEVEL

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

    // Rh configuration limits
    RhAlarmLimitSet(IM_RH_ALM);
    RhTripLimitSet(IM_RH_ITLK);

    // Temp board configuration limits
    TempBoardAlarmLimitSet(IM_BOARD_TEMP_ALM);
    TempBoardTripLimitSet(IM_BOARD_TEMP_ITLK);

    // Disable all Driver Error Monitoring
    Driver1ErrDisable();
    Driver2ErrDisable();

    // Init Variables
    input_module.Iin                        = 0.0;
    input_module.IinAlarmSts                = 0;
    input_module.IinItlkSts                 = 0;

    input_module.VdcLink                    = 0.0;
    input_module.VdcLinkAlarmSts            = 0;
    input_module.VdcLinkItlkSts             = 0;

    input_module.TempHeatsink               = 0.0;
    input_module.TempHeatsinkAlarmSts       = 0;
    input_module.TempHeatsinkItlkSts        = 0;

    input_module.TempL                      = 0.0;
    input_module.TempLAlarmSts              = 0;
    input_module.TempLItlkSts               = 0;

    input_module.Driver1Error               = 0;
    input_module.Driver1ErrorItlk           = 0;

    input_module.Driver2Error               = 0;
    input_module.Driver2ErrorItlk           = 0;
}

void clear_input_module_interlocks()
{
    input_module.IinItlkSts                = 0;
    input_module.VdcLinkItlkSts            = 0;
    input_module.TempHeatsinkItlkSts       = 0;
    input_module.TempLItlkSts              = 0;
    input_module.Driver1ErrorItlk          = 0;
    input_module.Driver2ErrorItlk          = 0;
}

uint8_t check_input_module_interlocks()
{
    uint8_t test = 0;

    test |= input_module.IinItlkSts;
    test |= input_module.VdcLinkItlkSts;
    test |= input_module.TempHeatsinkItlkSts;
    test |= input_module.TempLItlkSts;
    test |= input_module.Driver1ErrorItlk;
    test |= input_module.Driver2ErrorItlk;

    return test;
}

void clear_input_module_alarms()
{
    input_module.IinAlarmSts               = 0;
    input_module.VdcLinkAlarmSts           = 0;
    input_module.TempHeatsinkAlarmSts      = 0;
    input_module.TempLAlarmSts             = 0;
}

uint8_t check_input_module_alarms()
{
    uint8_t test = 0;

    test |= input_module.IinAlarmSts;
    test |= input_module.TempHeatsinkAlarmSts;
    test |= input_module.TempLAlarmSts;
    test |= input_module.VdcLinkAlarmSts;

    return test;
}

void check_input_module_indication_leds()
{
    // Input Over Current
    if(input_module.IinItlkSts) Led2TurnOn();
    else if(input_module.IinAlarmSts) Led2Toggle();
    else Led2TurnOff();

    // Dc-Link Overvoltage
    if(input_module.VdcLinkItlkSts) Led3TurnOn();
    else if(input_module.VdcLinkAlarmSts) Led3Toggle();
    else Led3TurnOff();

    // Heatsink Over Temperature
    if(input_module.TempHeatsinkItlkSts) Led4TurnOn();
    else if(input_module.TempHeatsinkAlarmSts) Led4Toggle();
    else Led4TurnOff();

    // Inductor Over Temperature
    if(input_module.TempLItlkSts) Led5TurnOn();
    else if(input_module.TempLAlarmSts) Led5Toggle();
    else Led5TurnOff();

    // Driver Error
    if(input_module.Driver1ErrorItlk || input_module.Driver2ErrorItlk) Led6TurnOn();
    else Led6TurnOff();
}

void input_module_application_readings()
{
    input_module.Iin = CurrentCh1Read();
    input_module.IinAlarmSts = CurrentCh1AlarmStatusRead();
    if(!input_module.IinItlkSts) input_module.IinItlkSts                  = CurrentCh1TripStatusRead();

    input_module.VdcLink = LvCurrentCh1Read();
    input_module.VdcLinkAlarmSts = CurrentCh1AlarmStatusRead();
    if(!input_module.VdcLinkItlkSts) input_module.VdcLinkItlkSts          = CurrentCh1TripStatusRead();

    input_module.TempHeatsink = Pt100ReadCh1();
    input_module.TempHeatsinkAlarmSts = Pt100ReadCh1AlarmSts();
    if(!input_module.TempHeatsinkItlkSts) input_module.TempHeatsinkItlkSts  = Pt100ReadCh1TripSts();

    input_module.TempL = Pt100ReadCh2();
    input_module.TempLAlarmSts = Pt100ReadCh2AlarmSts();
    if(!input_module.TempLItlkSts) input_module.TempLItlkSts                = Pt100ReadCh2TripSts();

    input_module_map_vars();
}

void input_module_map_vars()
{
    g_controller_iib.iib_signals[0].u32     = im_interlocks_indication;
    g_controller_iib.iib_signals[1].u32     = im_alarms_indication;
    g_controller_iib.iib_signals[2].f       = input_module.Iin;
    g_controller_iib.iib_signals[3].f       = input_module.VdcLink;
    g_controller_iib.iib_signals[4].u8[0]   = input_module.TempL;
    g_controller_iib.iib_signals[5].u8[0]   = input_module.TempHeatsink;
}

float input_module_iin_read(void)
{
    return input_module.Iin;
}

unsigned char input_module_iin_alarm_sts_read(void)
{
    return input_module.IinAlarmSts;
}

unsigned char input_module_iin_itlk_sts_read(void)
{
    return input_module.IinItlkSts;
}

//******************************************************************************
float input_module_vdclink_read(void)
{
    return input_module.VdcLink;
}

unsigned char input_module_vdclink_alarm_sts_read(void)
{
    return input_module.VdcLinkAlarmSts;
}

unsigned char input_module_vdclink_itlk_sts_read(void)
{
    return input_module.VdcLinkItlkSts;
}

//******************************************************************************
unsigned char input_module_temp_heatsink_read(void)
{
    return input_module.TempHeatsink;
}

unsigned char input_module_temp_heatsink_alarm_sts_read(void)
{
    return input_module.TempHeatsinkAlarmSts;
}

unsigned char input_module_temp_heatsink_itlk_sts_read(void)
{
    return input_module.TempHeatsinkItlkSts;
}

//******************************************************************************
unsigned char input_module_tempL_read(void)
{
    return input_module.TempL;
}

unsigned char input_module_tempL_alarm_sts_read(void)
{
    return input_module.TempLAlarmSts;
}

unsigned char input_module_tempL_itlk_sts_read(void)
{
    return input_module.TempLItlkSts;
}
