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
 * @file input_module.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

#ifndef INPUT_MODULE_H_
#define INPUT_MODULE_H_

#include <stdint.h>

#define INPUT_OVERCURRENT_ITLK          0x00000001
#define DCLINK_OVERVOLTAGE_ITLK         0x00000002
#define HS_OVERTEMP_ITLK                0x00000004
#define INDUC_OVERTEMP_ITLK             0x00000008
#define DRIVER1_ERROR_ITLK              0x00000010
#define DRIVER2_ERROR_ITLK              0x00000020

#define INPUT_OVERCURRENT_ALM           0x00000001
#define DCLINK_OVERVOLTAGE_ALM          0x00000002
#define HS_OVERTEMP_ALM                 0x00000004
#define INDUC_OVERTEMP_ALM              0x00000008

extern void init_input_module(void);
extern void clear_input_module_interlocks(void);
extern uint8_t check_input_module_interlocks(void);
extern void clear_input_module_alarms(void);
extern uint8_t check_input_module_alarms(void);
extern void check_input_module_indication_leds(void);
extern void input_module_application_readings(void);
extern void send_input_itlk_msg(void);

#endif /* INPUT_MODULE_H_ */
