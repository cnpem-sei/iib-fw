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
 * @file fac_is.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FAC_IS_H_
#define FAC_IS_H_

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
    } DriverVoltage;

    volatile bool DriverVoltageAlarmSts;
    volatile bool DriverVoltageItlkSts;

    union {
        volatile float       f;
        volatile uint8_t     u8[4];
    } Driver1Current;

    volatile bool Driver1CurrentAlarmSts;
    volatile bool Driver1CurrentItlkSts;

    volatile bool Driver1ErrorTop;
    volatile bool Driver1ErrorTopItlkSts;

    volatile bool Driver1ErrorBot;
    volatile bool Driver1ErrorBotItlkSts;

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

} fac_is_t;

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_IS_DCLINK_OVERVOLTAGE_ITLK         0x00000001
#define FAC_IS_INPUT_OVERCURRENT_ITLK          0x00000002
#define FAC_IS_IGBT1_OVERTEMP_ITLK             0x00000004
#define FAC_IS_IGBT1_HWR_OVERTEMP_ITLK         0x00000008
#define FAC_IS_DRIVER_OVERVOLTAGE_ITLK         0x00000010
#define FAC_IS_DRIVER1_OVERCURRENT_ITLK        0x00000020
#define FAC_IS_DRIVER1_ERROR_TOP_ITLK          0x00000040
#define FAC_IS_DRIVER1_ERROR_BOT_ITLK          0x00000080
#define FAC_IS_INDUC_OVERTEMP_ITLK             0x00000100
#define FAC_IS_HS_OVERTEMP_ITLK                0x00000200
#define FAC_IS_BOARD_IIB_OVERTEMP_ITLK         0x00000400
#define FAC_IS_BOARD_IIB_OVERHUMIDITY_ITLK     0x00000800

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_IS_DCLINK_OVERVOLTAGE_ALM          0x00000001
#define FAC_IS_INPUT_OVERCURRENT_ALM           0x00000002
#define FAC_IS_IGBT1_OVERTEMP_ALM              0x00000004
#define FAC_IS_DRIVER_OVERVOLTAGE_ALM          0x00000008
#define FAC_IS_DRIVER1_OVERCURRENT_ALM         0x00000010
#define FAC_IS_INDUC_OVERTEMP_ALM              0x00000020
#define FAC_IS_HS_OVERTEMP_ALM                 0x00000040
#define FAC_IS_BOARD_IIB_OVERTEMP_ALM          0x00000080
#define FAC_IS_BOARD_IIB_OVERHUMIDITY_ALM      0x00000100

/////////////////////////////////////////////////////////////////////////////////////////////

extern void clear_fac_is_interlocks(void);
extern uint8_t check_fac_is_interlocks(void);
extern void clear_fac_is_alarms(void);
extern uint8_t check_fac_is_alarms(void);
extern void check_fac_is_indication_leds(void);
extern void fac_is_application_readings(void);
extern void config_module_fac_is(void);

extern volatile fac_is_t fac_is;

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC01 / PA-RaPSC02

//BO-FAM:PS-QF

#ifdef BO_FAM_PS_QF__IS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_qf__is.h>

#endif /* BO_FAM_PS_QF__IS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSE01 / PA-RaPSE02 / PA-RaPSE03 / PA-RaPSE04 / PA-RaPSE06 / PA-RaPSE07 / PA-RaPSE08 / PA-RaPSE09

//BO-FAM:PS-B-1

#ifdef BO_FAM_PS_B1__IS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_b1__is.h>

#endif /* BO_FAM_PS_B1__IS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSF01 / PA-RaPSF02 / PA-RaPSF03 / PA-RaPSF04 / PA-RaPSF06 / PA-RaPSF07 / PA-RaPSF08 / PA-RaPSF09

//BO-FAM:PS-B-2

#ifdef BO_FAM_PS_B2__IS

#include <iib_ps_parameters/PA/fac/bo_fam_ps_b2__is.h>

#endif /* BO_FAM_PS_B2__IS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAC Giga de Testes IS

#ifdef FAC_GIGA_TESTE__IS

#include <iib_ps_parameters/development/fac/fac_giga_teste__is.h>

#endif /* FAC_GIGA_TESTE__IS */

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAC_IS_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////





