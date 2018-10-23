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
 * @file q4_module.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 28 de ago de 2018
 *
 */

#ifndef Q4_MODULE_H_
#define Q4_MODULE_H_

#include <stdint.h>

#define INPUT_OVERCURRENT_ITLK      0x00000001
#define OUTPUT_OVERCURRENT_ITLK     0x00000002
#define INPUT_OVERVOLTAGE_ITLK      0x00000004
#define IGBT1_OVERTEMP_ITLK         0x00000008
#define IGBT1_HWR_OVERTEMP_ITLK     0x00000010
#define IGBT2_OVERTEMP_ITLK         0x00000020
#define IGBT2_HWR_OVERTEMP_ITLK     0x00000040
#define INDUC_OVERTEMP_ITLK         0x00000080
#define HS_OVERTEMP_ITLK            0x00000100
#define DRIVER1_ERROR_ITLK          0x00000200
#define DRIVER2_ERROR_ITLK          0x00000400

#define INPUT_OVERCURRENT_ALM       0x00000001
#define OUTPUT_OVERCURRENT_ALM      0x00000002
#define INPUT_OVERVOLTAGE_ALM       0x00000004
#define IGBT1_OVERTEMP_ALM          0x00000008
#define IGBT1_HWR_OVERTEMP_ALM      0x00000010
#define IGBT2_OVERTEMP_ALM          0x00000020
#define IGBT2_HWR_OVERTEMP_ALM      0x00000040
#define INDUC_OVERTEMP_ALM          0x00000080
#define HS_OVERTEMP_ALM             0x00000100

/**
 * TODO: Put here your functions prototypes. Just what need 
 * to be accessed by other modules.
 */

extern void init_q4_module(void);
extern void clear_q4_interlocks(void);
extern uint8_t check_q4_interlocks(void);
extern void clear_q4_alarms(void);
extern uint8_t check_q4_alarms(void);
extern void check_q4_indication_leds(void);
extern void q4_application_readings(void);

#endif /* Q4_MODULE_H_ */
