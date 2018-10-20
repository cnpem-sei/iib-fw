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
 * @file rectifier_module.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

#ifndef RECTIFIER_MODULE_H_
#define RECTIFIER_MODULE_H_

#include<stdint.h>

#define OUTPUT_OVERCURRENT_RECT1_ITLK       0x00000001
#define OUTPUT_OVERCURRENT_RECT2_ITLK       0x00000002
#define OUTPUT_OVERVOLTAGE_RECT1_ITLK       0x00000004
#define OUTPUT_OVERVOLTAGE_RECT2_ITLK       0x00000008
#define LEAKAGE_OVERCURRENT_ITLK            0x00000010
#define HS_OVERTEMP_ITLK                    0x00000020
#define WATER_OVERTEMP_ITLK                 0x00000040
#define MODULE1_OVERTEMP_ITLK               0x00000080
#define MODULE2_OVERTEMP_ITLK               0x00000100
#define INDUCTOR1_OVERTEMP_ITLK             0x00000200
#define INDUCTOR2_OVERTEMP_ITLK             0x00000400
#define PHASE_FAULT_ITLK                    0x00000800
#define AC_OVERCURRENT_ITLK                 0x00001000
#define AC_TRANSF_OVERTEMP_ITLK             0x00002000
#define WATER_FLOW_ITLK                     0x00004000

#define OUTPUT_OVERCURRENT_RECT1_ALM        0x00000001
#define OUTPUT_OVERCURRENT_RECT2_ALM        0x00000002
#define OUTPUT_OVERVOLTAGE_RECT1_ALM        0x00000004
#define OUTPUT_OVERVOLTAGE_RECT2_ALM        0x00000008
#define LEAKAGE_OVERCURRENT_ALM             0x00000010
#define HS_OVERTEMP_ALM                     0x00000020
#define WATER_OVERTEMP_ALM                  0x00000040
#define MODULE1_OVERTEMP_ALM                0x00000080
#define MODULE2_OVERTEMP_ALM                0x00000100
#define INDUCTOR1_OVERTEMP_ALM              0x00000200
#define INDUCTOR2_OVERTEMP_ALM              0x00000400
#define PHASE_FAULT_ALM                     0x00000800
#define AC_OVERCURRENT_ALM                  0x00001000
#define AC_TRANSF_OVERTEMP_ALM              0x00002000
#define WATER_FLOW_ALM                      0x00004000

extern void init_rectifier_module(void);
extern void clear_rectifier_interlocks(void);
extern uint8_t check_rectifier_interlocks(void);
extern void clear_rectifier_alarms(void);
extern uint8_t check_rectifier_alarms(void);
extern void check_rectifier_indication_leds(void);
extern void rectifier_application_readings(void);
extern void rectifier_map_vars(void);

#endif /* RECTIFIER_MODULE_H_ */
