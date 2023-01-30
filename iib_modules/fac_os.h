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
 * @file fac_os.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 28 de ago de 2018
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FAC_OS_H_
#define FAC_OS_H_

/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>
#include "application.h"

/////////////////////////////////////////////////////////////////////////////////////////////

typedef volatile struct
{
    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } Iin;

    volatile bool IinAlarmSts;
    volatile bool IinItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } Iout;

    volatile bool IoutAlarmSts;
    volatile bool IoutItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } VdcLink;

    volatile bool VdcLinkAlarmSts;
    volatile bool VdcLinkItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } TempIGBT1;

    volatile bool TempIGBT1AlarmSts;
    volatile bool TempIGBT1ItlkSts;
    volatile bool TempIGBT1HwrItlk;
    volatile bool TempIGBT1HwrItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } TempIGBT2;

    volatile bool TempIGBT2AlarmSts;
    volatile bool TempIGBT2ItlkSts;
    volatile bool TempIGBT2HwrItlk;
    volatile bool TempIGBT2HwrItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } DriverVoltage;

    volatile bool DriverVoltageAlarmSts;
    volatile bool DriverVoltageItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } Driver1Current;

    volatile bool Driver1CurrentAlarmSts;
    volatile bool Driver1CurrentItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } Driver2Current;

    volatile bool Driver2CurrentAlarmSts;
    volatile bool Driver2CurrentItlkSts;

    volatile bool Driver1ErrorTop;
    volatile bool Driver1ErrorTopItlkSts;

    volatile bool Driver1ErrorBot;
    volatile bool Driver1ErrorBotItlkSts;

    volatile bool Driver2ErrorTop;
    volatile bool Driver2ErrorTopItlkSts;

    volatile bool Driver2ErrorBot;
    volatile bool Driver2ErrorBotItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } TempL;

    volatile bool TempLAlarmSts;
    volatile bool TempLItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } TempHeatSink;

    volatile bool TempHeatSinkAlarmSts;
    volatile bool TempHeatSinkItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } GroundLeakage;

    volatile bool GroundLeakageAlarmSts;
    volatile bool GroundLeakageItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } BoardTemperature;

    volatile bool BoardTemperatureAlarmSts;
    volatile bool BoardTemperatureItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } RelativeHumidity;

    volatile bool RelativeHumidityAlarmSts;
    volatile bool RelativeHumidityItlkSts;

    union {
    	volatile uint8_t     u8[4];
    	volatile uint32_t    u32;
    } InterlocksRegister;

    union {
    	volatile uint8_t     u8[4];
    	volatile uint32_t    u32;
    } AlarmsRegister;

} fac_os_t;

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_OS_INPUT_OVERVOLTAGE_ITLK       0x00000001
#define FAC_OS_INPUT_OVERCURRENT_ITLK       0x00000002
#define FAC_OS_OUTPUT_OVERCURRENT_ITLK      0x00000004
#define FAC_OS_IGBT1_OVERTEMP_ITLK          0x00000008
#define FAC_OS_IGBT1_HWR_OVERTEMP_ITLK      0x00000010
#define FAC_OS_IGBT2_OVERTEMP_ITLK          0x00000020
#define FAC_OS_IGBT2_HWR_OVERTEMP_ITLK      0x00000040
#define FAC_OS_DRIVER_OVERVOLTAGE_ITLK      0x00000080
#define FAC_OS_DRIVER1_OVERCURRENT_ITLK     0x00000100
#define FAC_OS_DRIVER2_OVERCURRENT_ITLK     0x00000200
#define FAC_OS_DRIVER1_ERROR_TOP_ITLK       0x00000400
#define FAC_OS_DRIVER1_ERROR_BOT_ITLK       0x00000800
#define FAC_OS_DRIVER2_ERROR_TOP_ITLK       0x00001000
#define FAC_OS_DRIVER2_ERROR_BOT_ITLK       0x00002000
#define FAC_OS_INDUC_OVERTEMP_ITLK          0x00004000
#define FAC_OS_HS_OVERTEMP_ITLK             0x00008000
#define FAC_OS_GROUND_LKG_ITLK              0x00010000
#define FAC_OS_BOARD_IIB_OVERTEMP_ITLK      0x00020000
#define FAC_OS_BOARD_IIB_OVERHUMIDITY_ITLK  0x00040000

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_OS_INPUT_OVERVOLTAGE_ALM        0x00000001
#define FAC_OS_INPUT_OVERCURRENT_ALM        0x00000002
#define FAC_OS_OUTPUT_OVERCURRENT_ALM       0x00000004
#define FAC_OS_IGBT1_OVERTEMP_ALM           0x00000008
#define FAC_OS_IGBT2_OVERTEMP_ALM           0x00000010
#define FAC_OS_DRIVER_OVERVOLTAGE_ALM       0x00000020
#define FAC_OS_DRIVER1_OVERCURRENT_ALM      0x00000040
#define FAC_OS_DRIVER2_OVERCURRENT_ALM      0x00000080
#define FAC_OS_INDUC_OVERTEMP_ALM           0x00000100
#define FAC_OS_HS_OVERTEMP_ALM              0x00000200
#define FAC_OS_GROUND_LKG_ALM               0x00000400
#define FAC_OS_BOARD_IIB_OVERTEMP_ALM       0x00000800
#define FAC_OS_BOARD_IIB_OVERHUMIDITY_ALM   0x00001000

/////////////////////////////////////////////////////////////////////////////////////////////

extern void clear_fac_os_interlocks(void);
extern uint8_t check_fac_os_interlocks(void);
extern void clear_fac_os_alarms(void);
extern uint8_t check_fac_os_alarms(void);
extern void check_fac_os_indication_leds(void);
extern void fac_os_application_readings(void);
extern void config_module_fac_os(void);

extern volatile fac_os_t fac_os;

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC01 / PA-RaPSC02

//BO-FAM:PS-QF

#ifdef BO_FAM_PS_QF__OS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_qf__os.h>

#endif /* BO_FAM_PS_QF__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC04

//BO-FAM:PS-SF

#ifdef BO_FAM_PS_SF__OS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_sf__os.h>

#endif /* BO_FAM_PS_SF__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC04

//BO-FAM:PS-SD

#ifdef BO_FAM_PS_SD__OS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_sd__os.h>

#endif /* BO_FAM_PS_SD__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC04

//BO-FAM:PS-QD

#ifdef BO_FAM_PS_QD__OS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_qd__os.h>

#endif /* BO_FAM_PS_QD__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack EMA:B:PS01

//FAC_DCDC_EMA

#ifdef FAC_DCDC_EMA__OS

#include <iib_ps_parameters/BL/EMA/fac/fac_dcdc_ema__os.h>

#endif /* FAC_DCDC_EMA__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSE01 / PA-RaPSE02 / PA-RaPSE03 / PA-RaPSE04 / PA-RaPSE06 / PA-RaPSE07 / PA-RaPSE08 / PA-RaPSE09

//BO-FAM:PS-B-1

#ifdef BO_FAM_PS_B1__OS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_b1__os.h>

#endif /* BO_FAM_PS_B1__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSF01 / PA-RaPSF02 / PA-RaPSF03 / PA-RaPSF04 / PA-RaPSF06 / PA-RaPSF07 / PA-RaPSF08 / PA-RaPSF09

//BO-FAM:PS-B-2

#ifdef BO_FAM_PS_B2__OS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_b2__os.h>

#endif /* BO_FAM_PS_B2__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAC Giga de Testes OS

#ifdef FAC_GIGA_TESTE__OS

#include <iib_ps_parameters/development/fac/fac_giga_teste__os.h>

#endif /* FAC_GIGA_TESTE__OS */

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAC_OS_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////






