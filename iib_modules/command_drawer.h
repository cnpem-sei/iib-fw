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
 * @file command_drawer.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

#ifndef COMMAND_DRAWER_H_
#define COMMAND_DRAWER_H_

#include <stdint.h>

#define CAPBANK_OVERVOLTAGE_ITLK    0x00000001
#define OUTPUT_OVERVOLTAGE_ITLK     0x00000002
#define HS_OVERTEMP_ITLK            0x00000004
#define INDUC_OVERTEMP_ITLK         0x00000008
#define EXTERNAL_ITLK               0x00000010

#define CAPBANK_OVERVOLTAGE_ALM     0x00000001
#define OUTPUT_OVERVOLTAGE_ALM      0x00000002
#define HS_OVERTEMP_ALM             0x00000004
#define INDUC_OVERTEMP_ALM          0x00000008

extern void init_command_module(void);
extern void clear_command_module_interlocks(void);
extern uint8_t check_command_module_interlocks(void);
extern void clear_command_module_alarms(void);
extern uint8_t check_command_module_alarms(void);
extern void check_command_module_indication_leds(void);
extern void command_module_application_readings(void);

#endif /* COMMAND_DRAWER_H_ */
