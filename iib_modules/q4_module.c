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
 * @file q4_module.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 28 de ago de 2018
 *
 */

#include "q4_module.h"
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

#define Q4_INPUT_CURRENT_ALM        430.0
#define Q4_INPUT_CURRENT_ITLK       440.0
#define Q4_OUTPUT_CURRENT_ALM       550.0
#define Q4_OUTPUT_CURRENT_ITLK      560.0
#define Q4_INPUT_VOLTAGE_ALM        295.0
#define Q4_INPUT_VOLTAGE_ITLK       300.0
#define Q4_HS_TEMP_ALM              35
#define Q4_HS_TEMP_ITLK             40
#define Q4_INDUC_TEMP_ALM           55
#define Q4_INDUC_TEMP_ITLK          60
#define Q4_RH_TEMP_ALM              80
#define Q4_RH_TEMP_ITLK             90

typedef struct
{
    float Iin;
    bool IinAlarmSts;
    bool IinItlkSts;
    float Iout;
    bool IoutAlarmSts;
    bool IoutItlkSts;
    float VdcLink;
    bool VdcLinkAlarmSts;
    bool VdcLinkItlkSts;
    uint8_t TempIGBT1;
    bool TempIGBT1AlarmSts;
    bool TempIGBT1ItlkSts;
    bool TempIGBT1HwrItlk;
    bool TempIGBT1HwrItlkSts;
    uint8_t TempIGBT2;
    bool TempIGBT2AlarmSts;
    bool TempIGBT2ItlkSts;
    bool TempIGBT2HwrItlk;
    bool TempIGBT2HwrItlkSts;
    uint8_t TempL;
    bool TempLAlarmSts;
    bool TempLItlkSts;
    uint8_t TempHeatSink;
    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    bool Driver1Error;
    bool Driver1ErrorItlk;
    bool Driver2Error;
    bool Driver2ErrorItlk;
} q4_module_t;


/**
 * TODO: Put here your constants and variables. Always use static for 
 * private members.
 */


/**
 * TODO: Put here your function prototypes for private functions. Use
 * static in declaration.
 */
q4_module_t q4_module;
uint32_t q4_interlocks_indication = 0;
uint32_t q4_alarms_indication = 0;

/**
 * TODO: Put here the implementation for your public functions.
 */

void init_q4_module()
{
    /* Set current range */
    CurrentCh1Init(300.0, 0.150, 50.0, 0); /* Input */
    CurrentCh2Init(500.0, 0.100, 50.0, 0); /* Output */

    /* Protection Limits */
    CurrentCh1AlarmLevelSet(Q4_INPUT_CURRENT_ALM);
    CurrentCh1TripLevelSet(Q4_INPUT_CURRENT_ITLK);
    CurrentCh2AlarmLevelSet(Q4_OUTPUT_CURRENT_ALM);
    CurrentCh2TripLevelSet(Q4_OUTPUT_CURRENT_ITLK);

    /* Isolated Voltage */
    LvCurrentCh1Init(330.0, 0.025, 120.0, 3); /* Input Voltage */

    LvCurrentCh1AlarmLevelSet(Q4_INPUT_VOLTAGE_ALM);
    LvCurrentCh1TripLevelSet(Q4_INPUT_VOLTAGE_ITLK);

    /* Pt-100 Configuration Limits */
    Pt100SetCh1AlarmLevel(Q4_HS_TEMP_ALM);
    Pt100SetCh1TripLevel(Q4_HS_TEMP_ITLK);
    Pt100SetCh2AlarmLevel(Q4_INDUC_TEMP_ALM);
    Pt100SetCh2TripLevel(Q4_INDUC_TEMP_ITLK);

    /* Pt-100 channel enable */
    Pt100Ch1Enable();
    Pt100Ch2Enable();

    /* RH configuration limits */
    TempBoardAlarmLimitSet(80);
    TempBoardTripLimitSet(90);

    /* Driver Error Enable */
    Driver1ErrEnable();
    Driver2ErrEnable();

    /* Variables */
    q4_module.Iin                   = 0;
    q4_module.IinAlarmSts           = 0;
    q4_module.IinItlkSts            = 0;

    q4_module.Iout                  = 0;
    q4_module.IoutAlarmSts          = 0;
    q4_module.IoutItlkSts           = 0;

    q4_module.VdcLink               = 0;
    q4_module.VdcLinkAlarmSts       = 0;
    q4_module.VdcLinkItlkSts        = 0;

    q4_module.TempIGBT1             = 0;
    q4_module.TempIGBT1AlarmSts     = 0;
    q4_module.TempIGBT1ItlkSts      = 0;
    q4_module.TempIGBT1HwrItlk      = 0;
    q4_module.TempIGBT1HwrItlkSts   = 0;

    q4_module.TempIGBT2             = 0;
    q4_module.TempIGBT2AlarmSts     = 0;
    q4_module.TempIGBT2ItlkSts      = 0;
    q4_module.TempIGBT2HwrItlk      = 0;
    q4_module.TempIGBT2HwrItlkSts   = 0;

    q4_module.TempL                 = 0;
    q4_module.TempLAlarmSts         = 0;
    q4_module.TempLItlkSts          = 0;

    q4_module.TempHeatSink          = 0;
    q4_module.TempHeatSinkAlarmSts  = 0;
    q4_module.TempHeatSinkItlkSts   = 0;

    q4_module.Driver1Error          = 0;
    q4_module.Driver1ErrorItlk      = 0;

    q4_module.Driver2Error          = 0;
    q4_module.Driver2ErrorItlk      = 0;
}

void clear_q4_interlocks()
{
    q4_module.IinItlkSts              = 0;
    q4_module.IoutItlkSts             = 0;
    q4_module.VdcLinkItlkSts          = 0;
    q4_module.TempIGBT1ItlkSts        = 0;
    q4_module.TempIGBT1HwrItlkSts     = 0;
    q4_module.TempIGBT2ItlkSts        = 0;
    q4_module.TempIGBT2HwrItlkSts     = 0;
    q4_module.TempLItlkSts            = 0;
    q4_module.TempHeatSinkItlkSts     = 0;
    q4_module.Driver1ErrorItlk        = 0;
    q4_module.Driver2ErrorItlk        = 0;
}

uint8_t check_q4_interlocks()
{
    uint8_t test = 0;

    test |= q4_module.IinItlkSts;
    test |= q4_module.IoutItlkSts;
    test |= q4_module.VdcLinkItlkSts;
    test |= q4_module.TempIGBT1ItlkSts;
    test |= q4_module.TempIGBT1HwrItlkSts;
    test |= q4_module.TempIGBT2ItlkSts;
    test |= q4_module.TempIGBT2HwrItlkSts;
    test |= q4_module.TempLItlkSts;
    test |= q4_module.TempHeatSinkItlkSts;
    test |= q4_module.Driver1ErrorItlk;
    test |= q4_module.Driver2ErrorItlk;

    return test;
}

void clear_q4_alarms(void)
{
    q4_module.IinAlarmSts           = 0;
    q4_module.IoutAlarmSts          = 0;
    q4_module.VdcLinkAlarmSts       = 0;
    q4_module.TempIGBT1AlarmSts     = 0;
    q4_module.TempIGBT2AlarmSts     = 0;
    q4_module.TempLAlarmSts         = 0;
    q4_module.TempHeatSinkAlarmSts  = 0;
}

uint8_t check_q4_alarms(void)
{
    uint8_t test = 0;

    test |= q4_module.IinAlarmSts;
    test |= q4_module.IoutAlarmSts;
    test |= q4_module.VdcLinkAlarmSts;
    test |= q4_module.TempIGBT1AlarmSts;
    test |= q4_module.TempIGBT2AlarmSts;
    test |= q4_module.TempLAlarmSts;
    test |= q4_module.TempHeatSinkAlarmSts;

    return test;
}

void check_q4_indications_leds()
{
    // Input over voltage
    if(q4_module.VdcLinkItlkSts) Led2TurnOn();
    else if(q4_module.VdcLinkAlarmSts) Led2Toggle();
    else Led2TurnOff();

    // Input over current
    if(q4_module.IinItlkSts) Led3TurnOn();
    else if(q4_module.IinAlarmSts) Led3Toggle();
    else Led3TurnOff();

    // Output over current
    if(q4_module.IoutItlkSts) Led4TurnOn();
    else if(q4_module.IoutAlarmSts) Led4Toggle();
    else Led4TurnOff();

    // Output over current
    if(q4_module.Driver1ErrorItlk || q4_module.Driver2ErrorItlk) Led5TurnOn();
    else Led5TurnOff();

    // Heatsink Over temperature
    if(q4_module.TempHeatSinkItlkSts) Led6TurnOn();
    else if(q4_module.TempHeatSinkAlarmSts) Led6Toggle();
    else Led6TurnOff();

    // Inductor Over temperature
    if(q4_module.TempLItlkSts) Led7TurnOn();
    else if(q4_module.TempLAlarmSts) Led7Toggle();
    else Led7TurnOff();
}

void q4_application_readings()
{
    q4_module.Iin = CurrentCh1Read();
    q4_module.IinAlarmSts = CurrentCh1AlarmStatusRead();
    if(!q4_module.IinItlkSts) q4_module.IinItlkSts = CurrentCh1TripStatusRead();

    q4_module.Iout = CurrentCh2Read();
    q4_module.IoutAlarmSts = CurrentCh2AlarmStatusRead();
    if(!q4_module.IoutItlkSts) q4_module.IoutItlkSts = CurrentCh2TripStatusRead();

    q4_module.VdcLink = LvCurrentCh1Read();
    q4_module.VdcLinkAlarmSts = LvCurrentCh1AlarmStatusRead();
    if(!q4_module.VdcLinkItlkSts) q4_module.VdcLinkItlkSts = LvCurrentCh1TripStatusRead();

    q4_module.TempHeatSink = Pt100ReadCh1();//PT100 CH1
    q4_module.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
    if(!q4_module.TempHeatSinkItlkSts)q4_module.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();

    q4_module.TempL = Pt100ReadCh2();//PT100 CH2
    q4_module.TempLAlarmSts = Pt100ReadCh2AlarmSts();
    if(!q4_module.TempLItlkSts)q4_module.TempLItlkSts = Pt100ReadCh2TripSts();

    q4_map_vars();
}

void q4_map_vars()
{
    g_controller_iib.iib_signals[0].u32 = q4_interlocks_indication;
    g_controller_iib.iib_signals[1].u32 = q4_alarms_indication;
    g_controller_iib.iib_signals[2].f   = q4_module.Iin;
    g_controller_iib.iib_signals[3].f   = q4_module.Iout;
    g_controller_iib.iib_signals[4].f   = q4_module.VdcLink;
    g_controller_iib.iib_signals[5].f   = q4_module.TempHeatSink;
    g_controller_iib.iib_signals[6].f   = q4_module.TempL;
}

float q4_module_iout_read(void)
{
    return q4_module.Iout;
}

unsigned char q4_module_iout_alarm_sts_read(void)
{
    return q4_module.IoutAlarmSts;
}

unsigned char q4_module_iout_itlk_sts_read(void)
{
    return q4_module.IoutItlkSts;
}

//******************************************************************************
unsigned char q4_module_temp_igbt1_read(void)
{
    return q4_module.TempIGBT1;
}

unsigned char q4_module_temp_igbt1_alarm_sts_read(void)
{
    return q4_module.TempIGBT1AlarmSts;
}

unsigned char q4_module_temp_igbt1_itlk_sts_read(void)
{
    return q4_module.TempIGBT1ItlkSts;
}

//******************************************************************************
unsigned char q4_module_temp_igbt2_read(void)
{
    return q4_module.TempIGBT2;
}

unsigned char q4_module_temp_igbt2_alarm_sts_read(void)
{
    return q4_module.TempIGBT2AlarmSts;
}

unsigned char q4_module_temp_igbt2_itlk_sts_read(void)
{
    return q4_module.TempIGBT2ItlkSts;
}

