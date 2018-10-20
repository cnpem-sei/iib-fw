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
 * @file rectifier_module.c
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

#define RECTF_OUTPUT_OVERCURRENT_RECT1_ITLK     235.0
#define RECTF_OUTPUT_OVERCURRENT_RECT1_ALM      230.0
#define RECTF_OUTPUT_OVERCURRENT_RECT2_ITLK     235.0
#define RECTF_OUTPUT_OVERCURRENT_RECT2_ALM      230.0
#define RECTF_OUTPUT_OVERVOLTAGE_RECT1_ITLK     58.0
#define RECTF_OUTPUT_OVERVOLTAGE_RECT1_ALM      55.0
#define RECTF_OUTPUT_OVERVOLTAGE_RECT2_ITLK     58.0
#define RECTF_OUTPUT_OVERVOLTAGE_RECT2_ALM      55.0
#define RECTF_LEAKAGE_OVERCURRENT_ITLK          0.1
#define RECTF_LEAKAGE_OVERCURRENT_ALM           0.09
#define RECTF_HS_OVERTEMP_ITLK                  80.0
#define RECTF_HS_OVERTEMP_ALM                   70.0
#define RECTF_WATER_OVERTEMP_ITLK               60.0
#define RECTF_WATER_OVERTEMP_ALM                55.0
#define RECTF_MODULE1_OVERTEMP_ITLK             115.0
#define RECTF_MODULE1_OVERTEMP_ALM              125.0
#define RECTF_MODULE2_OVERTEMP_ITLK             125.0
#define RECTF_MODULE2_OVERTEMP_ALM              115.0
#define RECTF_INDUCTOR1_OVERTEMP_ITLK           60.0
#define RECTF_INDUCTOR1_OVERTEMP_ALM            55.0
#define RECTF_INDUCTOR2_OVERTEMP_ITLK           60.0
#define RECTF_INDUCTOR2_OVERTEMP_ALM            55.0
#define RECTF_AC_OVERCURRENT_ITLK               100.0
#define RECTF_AC_OVERCURRENT_ALM                100.0
#define RECTF_RH_ITLK                           90.0
#define RECTF_RH_ALM                            80.0
#define RECTF_BOARD_TEMP_ITLK                   90.0
#define RECTF_BOARD_TEMP_ALM                    80.0

typedef struct
{
    float IoutRectf1;
    bool IoutRectf1AlarmSts;
    bool IoutRectf1ItlkSts;
    float IoutRectf2;
    bool IoutRectf2AlarmSts;
    bool IoutRectf2ItlkSts;
    float VoutRectf1;
    bool VoutRectf1AlarmSts;
    bool VoutRectf1ItlkSts;
    float VoutRectf2;
    bool VoutRectf2AlarmSts;
    bool VoutRectf2ItlkSts;
    float LeakageCurrent;
    bool LeakageCurrentAlarmSts;
    bool LeakageCurrentItlkSts;
    uint8_t TempHeatSink;
    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    uint8_t TempWater;
    bool TempWaterAlarmSts;
    bool TempWaterItlkSts;
    uint8_t TempModule1;
    bool TempModule1AlarmSts;
    bool TempModule1ItlkSts;
    uint8_t TempModule2;
    bool TempModule2AlarmSts;
    bool TempModule2ItlkSts;
    uint8_t TempL1;
    bool TempL1AlarmSts;
    bool TempL1ItlkSts;
    uint8_t TempL2;
    bool TempL2AlarmSts;
    bool TempL2ItlkSts;
    bool AcPhaseFault;
    bool AcPhaseFaultSts;
    bool AcOverCurrent;
    bool AcOverCurrentSts;
    bool AcTransformerOverTemp;
    bool AcTransformerOverTempSts;
    bool WaterFluxInterlock;
    bool WaterFluxInterlockSts;

} rectifier_module_t;

rectifier_module_t rectf_module;
uint32_t rectf_module_interlocks_indication = 0;
uint32_t rectf_module_alarms_indication     = 0;

void init_rectifier_module()
{
    //Set current range
    CurrentCh1Init(300.0, 0.150, 50.0, 3);  // Rectifier1 Output Current Sensor Configuration: Hall Sensor
    CurrentCh2Init(300.0, 0.150, 50.0, 3);  // Rectifier2 Output Current Sensor Configuration: LEM LF 310-S
    CurrentCh3Init(1.0, 0.0125, 300.0, 0);  // Leakage Current
    CurrentCh4Init(125.0, 0.125, 50.0, 0);
    //Set protection limits
    CurrentCh1AlarmLevelSet(RECTF_OUTPUT_OVERCURRENT_RECT1_ALM); // Rectifier1 Output Current Alarm
    CurrentCh1TripLevelSet(RECTF_OUTPUT_OVERCURRENT_RECT1_ITLK); // Rectifier1 Output Current Trip
    CurrentCh2AlarmLevelSet(RECTF_OUTPUT_OVERCURRENT_RECT2_ALM); // Rectifier2 Output Current Alarm
    CurrentCh2TripLevelSet(RECTF_OUTPUT_OVERCURRENT_RECT2_ITLK); // Rectifier2 Output Current Trip
    CurrentCh3AlarmLevelSet(RECTF_LEAKAGE_OVERCURRENT_ALM); // Leakage Current Alarm Level
    CurrentCh3TripLevelSet(RECTF_LEAKAGE_OVERCURRENT_ITLK); // Leakage Current Trip Level
    CurrentCh4AlarmLevelSet(RECTF_AC_OVERCURRENT_ALM);
    CurrentCh4TripLevelSet(RECTF_AC_OVERCURRENT_ITLK);

    //Setar ranges de entrada
    VoltageCh1Init(61.21, 3);              // Rectifier1 Output Voltage Configuration.
    VoltageCh2Init(61.21, 3);              // Rectifier2 Output Voltage Configuration.
    VoltageCh3Init(10.0, 3);               // NTC SW1
    VoltageCh4Init(10.0, 3);               // NTC SW2

    ConfigPolVoltCh2(1);                   // Change the voltage polarity of the channel 2 (rectifier 2 voltage)

    ConfigVoltCh1AsNtc(0);                 // Config Voltage Ch2 as a voltage input
    ConfigVoltCh2AsNtc(0);                 // Config Voltage Ch2 as a voltage input
    ConfigVoltCh3AsNtc(1);                 // Config Voltage Ch3 as a NTC input
    ConfigVoltCh4AsNtc(1);                 // Config Voltage Ch4 as a NTC input

    //Setar limites
    VoltageCh1AlarmLevelSet(RECTF_OUTPUT_OVERVOLTAGE_RECT1_ALM);  // Rectifier1 Voltage Alarm
    VoltageCh1TripLevelSet(RECTF_OUTPUT_OVERVOLTAGE_RECT1_ITLK);  // Rectifier1 Voltage Trip
    VoltageCh2AlarmLevelSet(RECTF_OUTPUT_OVERVOLTAGE_RECT2_ALM);  // Rectifier2 Voltage Alarm
    VoltageCh2TripLevelSet(RECTF_OUTPUT_OVERVOLTAGE_RECT2_ITLK);  // Rectifier2 Voltage Trip
    VoltageCh3AlarmLevelSet(RECTF_MODULE1_OVERTEMP_ALM);          // Rectifier1 NTC Temperature Alarm
    VoltageCh3TripLevelSet(RECTF_MODULE1_OVERTEMP_ITLK);          // Rectifier1 NTC Temperature Trip
    VoltageCh4AlarmLevelSet(RECTF_MODULE2_OVERTEMP_ALM);          // Rectifier2 NTC Temperature Alarm
    VoltageCh4TripLevelSet(RECTF_MODULE2_OVERTEMP_ITLK);          // Rectifier2 NTC Temperature Tip

    // PT100 configuration limits
    Pt100SetCh1AlarmLevel(RECTF_HS_OVERTEMP_ALM); // Heat Sink Temperature Alarm
    Pt100SetCh1TripLevel(RECTF_HS_OVERTEMP_ITLK); // Heat Sink Temperature Trip
    Pt100SetCh2AlarmLevel(RECTF_INDUCTOR1_OVERTEMP_ALM); // L1 Temperature Alarm
    Pt100SetCh2TripLevel(RECTF_INDUCTOR1_OVERTEMP_ITLK); // L1 Temperature Trip
    Pt100SetCh3AlarmLevel(RECTF_INDUCTOR2_OVERTEMP_ALM); // L2 Temperature Alarm
    Pt100SetCh3TripLevel(RECTF_INDUCTOR2_OVERTEMP_ITLK); // L2 Temperature Trip
    Pt100SetCh4AlarmLevel(RECTF_WATER_OVERTEMP_ALM);     // Water Temperature Alarm
    Pt100SetCh4TripLevel(RECTF_WATER_OVERTEMP_ITLK);     // Water Temperature Trip

    // Delay 4 seconds
    Pt100SetCh1Delay(4);
    // Delay 4 seconds
    Pt100SetCh2Delay(4);
    // Delay 4 seconds
    Pt100SetCh3Delay(4);
    // Delay 4 seconds
    Pt100SetCh4Delay(4);

    // PT100 channel enable
    Pt100Ch1Enable();            // Enable PT100 channel 1
    Pt100Ch2Enable();            // Enable PT100 channel 2
    Pt100Ch3Enable();            // Enable PT100 channel 3
    Pt100Ch4Disable();           // Enable PT100 channel 4

    // Rh configuration limits
    RhAlarmLimitSet(RECTF_RH_ALM);
    RhTripLimitSet(RECTF_RH_ITLK);

    // Temp board configuration limits
    TempBoardAlarmLimitSet(RECTF_BOARD_TEMP_ALM);
    TempBoardTripLimitSet(RECTF_BOARD_TEMP_ITLK);

    Driver1ErrDisable();         // Driver1 Error Signal Disable
    Driver2ErrDisable();         // Driver1 Error Signal Disable

    // Init variables
    rectf_module.IoutRectf1               = 0;
    rectf_module.IoutRectf1AlarmSts       = 0;
    rectf_module.IoutRectf1ItlkSts        = 0;

    rectf_module.IoutRectf2               = 0;
    rectf_module.IoutRectf2AlarmSts       = 0;
    rectf_module.IoutRectf2ItlkSts        = 0;

    rectf_module.VoutRectf1               = 0;
    rectf_module.VoutRectf1AlarmSts       = 0;
    rectf_module.VoutRectf1ItlkSts        = 0;

    rectf_module.VoutRectf2               = 0;
    rectf_module.VoutRectf2AlarmSts       = 0;
    rectf_module.VoutRectf2ItlkSts        = 0;

    rectf_module.LeakageCurrent           = 0;
    rectf_module.LeakageCurrentAlarmSts   = 0;
    rectf_module.LeakageCurrentItlkSts    = 0;

    rectf_module.TempHeatSink             = 0;
    rectf_module.TempHeatSinkAlarmSts     = 0;
    rectf_module.TempHeatSinkItlkSts      = 0;

    rectf_module.TempWater                = 0;
    rectf_module.TempWaterAlarmSts        = 0;
    rectf_module.TempWaterItlkSts         = 0;

    rectf_module.TempModule1              = 0;
    rectf_module.TempModule1AlarmSts      = 0;
    rectf_module.TempModule1ItlkSts       = 0;

    rectf_module.TempModule2              = 0;
    rectf_module.TempModule2AlarmSts      = 0;
    rectf_module.TempModule2ItlkSts       = 0;

    rectf_module.TempL1                   = 0;
    rectf_module.TempL1AlarmSts           = 0;
    rectf_module.TempL1ItlkSts            = 0;

    rectf_module.TempL2                   = 0;
    rectf_module.TempL2AlarmSts           = 0;
    rectf_module.TempL2ItlkSts            = 0;

    rectf_module.AcPhaseFault             = 0;
    rectf_module.AcPhaseFaultSts          = 0;

    rectf_module.AcOverCurrent            = 0;
    rectf_module.AcOverCurrentSts         = 0;

    rectf_module.AcTransformerOverTemp    = 0;
    rectf_module.AcTransformerOverTempSts = 0;

    rectf_module.WaterFluxInterlock       = 0;
    rectf_module.WaterFluxInterlockSts    = 0;
}

void clear_rectifier_interlocks()
{
    rectf_module.IoutRectf1ItlkSts           = 0;
    rectf_module.IoutRectf2ItlkSts           = 0;
    rectf_module.VoutRectf1ItlkSts           = 0;
    rectf_module.VoutRectf2ItlkSts           = 0;
    rectf_module.LeakageCurrentItlkSts       = 0;
    rectf_module.TempHeatSinkItlkSts         = 0;
    rectf_module.TempWaterItlkSts            = 0;
    rectf_module.TempModule1ItlkSts          = 0;
    rectf_module.TempModule2ItlkSts          = 0;
    rectf_module.TempL1ItlkSts               = 0;
    rectf_module.TempL2ItlkSts               = 0;
    rectf_module.AcPhaseFaultSts             = 0;
    rectf_module.AcOverCurrentSts            = 0;
    rectf_module.AcTransformerOverTempSts    = 0;
    rectf_module.WaterFluxInterlockSts       = 0;
}

uint8_t check_rectifier_interlocks()
{
    uint8_t test = 0;

    test |= rectf_module.IoutRectf1ItlkSts;
    test |= rectf_module.IoutRectf2ItlkSts;
    test |= rectf_module.VoutRectf1ItlkSts;
    test |= rectf_module.VoutRectf2ItlkSts;
    test |= rectf_module.LeakageCurrentItlkSts;
    test |= rectf_module.TempHeatSinkItlkSts;
    test |= rectf_module.TempWaterItlkSts;
    test |= rectf_module.TempModule1ItlkSts;
    test |= rectf_module.TempModule2ItlkSts;
    test |= rectf_module.TempL1ItlkSts;
    test |= rectf_module.TempL2ItlkSts;
    test |= rectf_module.AcPhaseFaultSts;
    test |= rectf_module.AcOverCurrentSts;
    test |= rectf_module.AcTransformerOverTempSts;
    test |= rectf_module.WaterFluxInterlockSts;

    return test;
}

void clear_rectifier_alarms()
{
    rectf_module.IoutRectf1AlarmSts          = 0;
    rectf_module.IoutRectf2AlarmSts          = 0;
    rectf_module.VoutRectf1AlarmSts          = 0;
    rectf_module.VoutRectf2AlarmSts          = 0;
    rectf_module.LeakageCurrentAlarmSts      = 0;
    rectf_module.TempHeatSinkAlarmSts        = 0;
    rectf_module.TempWaterAlarmSts           = 0;
    rectf_module.TempModule1AlarmSts         = 0;
    rectf_module.TempModule2AlarmSts         = 0;
    rectf_module.TempL1AlarmSts              = 0;
    rectf_module.TempL2AlarmSts              = 0;
}

uint8_t check_rectifier_alarms()
{
    uint8_t test = 0;

    test |= rectf_module.IoutRectf1AlarmSts;
    test |= rectf_module.IoutRectf2AlarmSts;
    test |= rectf_module.VoutRectf1AlarmSts;
    test |= rectf_module.VoutRectf2AlarmSts;
    test |= rectf_module.LeakageCurrentAlarmSts;
    test |= rectf_module.TempHeatSinkAlarmSts;
    test |= rectf_module.TempWaterAlarmSts;
    test |= rectf_module.TempModule1AlarmSts;
    test |= rectf_module.TempModule2AlarmSts;
    test |= rectf_module.TempL1AlarmSts;
    test |= rectf_module.TempL2AlarmSts;

    return test;
}

void check_rectifier_indication_leds()
{
    // Rectifier Output Over Voltage
    if(rectf_module.VoutRectf1ItlkSts || rectf_module.VoutRectf2ItlkSts) Led2TurnOn();
    else if(rectf_module.VoutRectf1AlarmSts || rectf_module.VoutRectf2AlarmSts) Led2Toggle();
    else Led2TurnOff();

    // Rectifier Output Over Current
    if(rectf_module.IoutRectf1ItlkSts || rectf_module.IoutRectf1ItlkSts) Led3TurnOn();
    else if(rectf_module.IoutRectf1AlarmSts || rectf_module.IoutRectf1AlarmSts) Led3Toggle();
    else Led3TurnOff();

    // Rectifier Over Temperature
    if(rectf_module.TempHeatSinkItlkSts || rectf_module.TempWaterItlkSts || rectf_module.TempModule1ItlkSts || rectf_module.TempModule2ItlkSts || rectf_module.TempL1ItlkSts || rectf_module.TempL2ItlkSts) Led4TurnOn();
    else if(rectf_module.TempHeatSinkAlarmSts || rectf_module.TempWaterAlarmSts || rectf_module.TempModule1AlarmSts || rectf_module.TempModule2AlarmSts || rectf_module.TempL1AlarmSts || rectf_module.TempL2AlarmSts) Led4Toggle();
    else Led4TurnOff();

    // External interlock or Driver error
    if(rectf_module.AcPhaseFaultSts || rectf_module.AcOverCurrentSts || rectf_module.AcTransformerOverTempSts || rectf_module.WaterFluxInterlockSts) Led5TurnOn();
    else if(!InterlockRead())Led5TurnOff();
}

void rectifier_application_readings()
{
    rectf_module.IoutRectf1 = CurrentCh1Read();
    rectf_module.IoutRectf1AlarmSts = CurrentCh1AlarmStatusRead();
    if(!rectf_module.IoutRectf1ItlkSts) rectf_module.IoutRectf1ItlkSts        = CurrentCh1TripStatusRead();

    rectf_module.IoutRectf2 = CurrentCh2Read();
    rectf_module.IoutRectf2AlarmSts = CurrentCh2AlarmStatusRead();
    if(!rectf_module.IoutRectf2ItlkSts) rectf_module.IoutRectf2ItlkSts        = CurrentCh2TripStatusRead();

    rectf_module.VoutRectf1 = VoltageCh1Read();
    rectf_module.VoutRectf1AlarmSts = VoltageCh1AlarmStatusRead();
    if(!rectf_module.VoutRectf1ItlkSts) rectf_module.VoutRectf1ItlkSts        = VoltageCh1TripStatusRead();

    rectf_module.VoutRectf2 = VoltageCh2Read();
    rectf_module.VoutRectf2AlarmSts = VoltageCh2AlarmStatusRead();
    if(!rectf_module.VoutRectf2ItlkSts) rectf_module.VoutRectf2ItlkSts        = VoltageCh2TripStatusRead();

    rectf_module.LeakageCurrent = CurrentCh3Read();
    rectf_module.LeakageCurrentAlarmSts = CurrentCh3AlarmStatusRead();
    if(!rectf_module.LeakageCurrentItlkSts) rectf_module.LeakageCurrentItlkSts = CurrentCh3TripStatusRead();

    rectf_module.TempHeatSink = Pt100ReadCh1();
    rectf_module.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
    if(!rectf_module.TempHeatSinkItlkSts) rectf_module.TempHeatSinkItlkSts    = Pt100ReadCh1TripSts();

    rectf_module.TempWater = Pt100ReadCh4();
    rectf_module.TempWaterAlarmSts = Pt100ReadCh4AlarmSts();
    if(!rectf_module.TempWaterItlkSts) rectf_module.TempWaterItlkSts          = Pt100ReadCh4TripSts();

    rectf_module.TempModule1 = VoltageCh3Read();
    rectf_module.TempModule1AlarmSts = VoltageCh3AlarmStatusRead();
    if(!rectf_module.TempModule1ItlkSts) rectf_module.TempModule1ItlkSts      = VoltageCh3TripStatusRead();

    rectf_module.TempModule2 = VoltageCh4Read();
    rectf_module.TempModule2AlarmSts = VoltageCh4AlarmStatusRead();
    if(!rectf_module.TempModule2ItlkSts) rectf_module.TempModule2ItlkSts      = VoltageCh4TripStatusRead();

    rectf_module.TempL1 = Pt100ReadCh2();
    rectf_module.TempL1AlarmSts = Pt100ReadCh2AlarmSts();
    if(!rectf_module.TempL1ItlkSts) rectf_module.TempL1ItlkSts                = Pt100ReadCh2TripSts();

    rectf_module.TempL2 = Pt100ReadCh3();
    rectf_module.TempL2AlarmSts = Pt100ReadCh3AlarmSts();
    if(!rectf_module.TempL2ItlkSts) rectf_module.TempL2ItlkSts                = Pt100ReadCh3TripSts();

    rectf_module.AcPhaseFault = !Gpdi1Read();
    if(!rectf_module.AcPhaseFaultSts) rectf_module.AcPhaseFaultSts            = !Gpdi1Read();

    rectf_module.AcOverCurrent = !Gpdi2Read();
    if(!rectf_module.AcOverCurrentSts) rectf_module.AcOverCurrentSts          = !Gpdi2Read();

    rectf_module.AcTransformerOverTemp = !Gpdi3Read();
    if(!rectf_module.AcTransformerOverTempSts) rectf_module.AcTransformerOverTempSts = !Gpdi3Read();

    rectf_module.WaterFluxInterlock = !Gpdi4Read();
    if(!rectf_module.WaterFluxInterlockSts) rectf_module.WaterFluxInterlockSts = !Gpdi4Read();

    if(rectf_module.AcPhaseFault || rectf_module.AcOverCurrent || rectf_module.AcTransformerOverTemp || rectf_module.WaterFluxInterlock) InterlockSet();

    rectifier_map_vars();
}

void rectifier_map_vars()
{
    g_controller_iib.iib_signals[0].u32     = rectf_module_interlocks_indication;
    g_controller_iib.iib_signals[1].u32     = rectf_module_alarms_indication;
    g_controller_iib.iib_signals[2].f       = rectf_module.IoutRectf1;
    g_controller_iib.iib_signals[3].f       = rectf_module.IoutRectf2;
    g_controller_iib.iib_signals[4].f       = rectf_module.VoutRectf1;
    g_controller_iib.iib_signals[5].f       = rectf_module.VoutRectf2;
    g_controller_iib.iib_signals[6].f       = rectf_module.LeakageCurrent;
    g_controller_iib.iib_signals[7].u8[0]   = rectf_module.TempHeatSink;
    g_controller_iib.iib_signals[8].u8[0]   = rectf_module.TempWater;
    g_controller_iib.iib_signals[9].u8[0]   = rectf_module.TempModule1;
    g_controller_iib.iib_signals[10].u8[0]  = rectf_module.TempModule2;
    g_controller_iib.iib_signals[11].u8[0]  = rectf_module.TempL1;
    g_controller_iib.iib_signals[12].u8[0]  = rectf_module.TempL2;
}

float rectifier_iout_rectf1_read(void)
{
    return rectf_module.IoutRectf1;
}

unsigned char rectifier_iout_rectf1_alarm_sts_read(void)
{
    return rectf_module.IoutRectf1AlarmSts;
}

unsigned char rectifier_iout_rectf1_itlk_sts_read(void)
{
    return rectf_module.IoutRectf1ItlkSts;
}

//******************************************************************************
float rectifier_iout_rectf2_read(void)
{
    return rectf_module.IoutRectf2;
}

unsigned char rectifier_iout_rectf2_alarm_sts_read(void)
{
    return rectf_module.IoutRectf2AlarmSts;
}

unsigned char rectifier_iout_rectf2_itlk_sts_read(void)
{
    return rectf_module.IoutRectf2ItlkSts;
}

//******************************************************************************
float rectifier_vout_rectf1_read(void)
{
    return rectf_module.VoutRectf1;
}

unsigned char rectifier_vout_rectf1_alarm_sts_read(void)
{
    return rectf_module.VoutRectf1AlarmSts;
}

unsigned char rectifier_vout_rectf1_itlk_sts_read(void)
{
    return rectf_module.VoutRectf1ItlkSts;
}

//******************************************************************************
float rectifier_vout_rectf2_read(void)
{
    return rectf_module.VoutRectf2;
}

unsigned char rectifier_vout_rectf2_alarm_sts_read(void)
{
    return rectf_module.VoutRectf2AlarmSts;
}

unsigned char rectifier_vout_rectf2_itlk_sts_read(void)
{
    return rectf_module.VoutRectf2ItlkSts;
}

//******************************************************************************
float rectifier_leakage_current_read(void)
{
    return rectf_module.LeakageCurrent;
}

unsigned char rectifier_leakage_current_alarm_sts_read(void)
{
    return rectf_module.LeakageCurrentAlarmSts;
}

unsigned char rectifier_leakage_current_itlk_sts_read(void)
{
    return rectf_module.LeakageCurrentItlkSts;
}

//******************************************************************************
unsigned char rectifier_temp_heatsink_read(void)
{
    return rectf_module.TempHeatSink;
}

unsigned char rectifier_temp_heatsink_alarm_sts_read(void)
{
    return rectf_module.TempHeatSinkAlarmSts;
}

unsigned char rectifier_temp_heatsink_itlk_sts_read(void)
{
    return rectf_module.TempHeatSinkItlkSts;
}

//******************************************************************************
unsigned char rectifier_temp_water_read(void)
{
    return rectf_module.TempWater;
}

unsigned char rectifier_temp_water_alarm_sts_read(void)
{
    return rectf_module.TempWaterAlarmSts;
}

unsigned char rectifier_temp_water_itlk_sts_read(void)
{
    return rectf_module.TempWaterItlkSts;
}

//******************************************************************************
unsigned char rectifier_temp_module1_read(void)
{
    return rectf_module.TempModule1;
}

unsigned char rectifier_temp_module1_alarm_sts_read(void)
{
    return rectf_module.TempModule1AlarmSts;
}

unsigned char rectifier_temp_module1_itlk_sts_read(void)
{
    return rectf_module.TempModule1ItlkSts;
}

//******************************************************************************
unsigned char rectifier_temp_module2_read(void)
{
    return rectf_module.TempModule2;
}

unsigned char rectifier_temp_module2_Alarm_sts_read(void)
{
    return rectf_module.TempModule2AlarmSts;
}

unsigned char rectifier_temp_module2_itlk_sts_read(void)
{
    return rectf_module.TempModule2ItlkSts;
}

//******************************************************************************
unsigned char Rectifier_tempL1_read(void)
{
    return rectf_module.TempL1;
}

unsigned char rectifier_tempL1_alarm_sts_read(void)
{
    return rectf_module.TempL1AlarmSts;
}

unsigned char rectifier_tempL1_itlk_sts_read(void)
{
    return rectf_module.TempL1ItlkSts;
}

//******************************************************************************
unsigned char rectifier_tempL2_read(void)
{
    return rectf_module.TempL2;
}

unsigned char rectifier_tempL2_alarm_sts_read(void)
{
    return rectf_module.TempL2AlarmSts;
}

unsigned char rectifier_tempL2_itlk_sts_read(void)
{
    return rectf_module.TempL2ItlkSts;
}

//******************************************************************************
unsigned char rectifier_ac_phase_fault_read(void)
{
    return rectf_module.AcPhaseFault;
}

unsigned char rectifier_ac_phase_fault_sts_read(void)
{
    return rectf_module.AcPhaseFaultSts;
}

//******************************************************************************
unsigned char rectifier_ac_overcurrent_read(void)
{
    return rectf_module.AcOverCurrent;
}

unsigned char rectifier_ac_overcurrent_sts_read(void)
{
    return rectf_module.AcOverCurrentSts;
}

//******************************************************************************
unsigned char rectifier_ac_transformer_overtemp_read(void)
{
    return rectf_module.AcTransformerOverTemp;
}

unsigned char rectifier_ac_transformer_overtemp_sts_read(void)
{
    return rectf_module.AcTransformerOverTempSts;
}

//******************************************************************************
unsigned char rectifier_water_flow_interlock_read(void)
{
    return rectf_module.WaterFluxInterlock;
}

unsigned char rectifier_water_flow_interlock_sts_read(void)
{
    return rectf_module.WaterFluxInterlockSts;
}
