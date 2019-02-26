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
 * @file fap_module.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

#ifndef FAP_H_
#define FAP_H_

#include <stdint.h>

#define INPUT_OVERVOLTAGE_ITLK          0x00000001
#define OUTPUT_OVERVOLTAGE_ITLK         0x00000002
#define OUTPUT_OVERCURRENT_1_ITLK       0x00000004
#define OUTPUT_OVERCURRENT_2_ITLK       0x00000008
#define IGBT1_OVERTEMP_ITLK             0x00000010
#define IGBT2_OVERTEMP_ITLK             0x00000020
#define DRIVER_OVERVOLTAGE_ITLK         0x00000040
#define DRIVER1_OVERCURRENT_ITLK        0x00000080
#define DRIVER2_OVERCURRENT_ITLK        0x00000100
#define DRIVER1_ERROR_ITLK              0x00000200
#define DRIVER2_ERROR_ITLK              0x00000400
#define INDUC_OVERTEMP_ITLK             0x00000800
#define HS_OVERTEMP_ITLK                0x00001000
#define RELAY_ITLK                      0x00002000
#define EXTERNAL_ITLK                   0x00004000
#define LEAKAGE_CURRENT_ITLK            0x00008000
#define RACK_ITLK                       0x00010000

#define INPUT_OVERVOLTAGE_ALM           0x00000001
#define OUTPUT_OVERVOLTAGE_ALM          0x00000002
#define OUTPUT_OVERCURRENT_1_ALM        0x00000004
#define OUTPUT_OVERCURRENT_2_ALM        0x00000008
#define IGBT1_OVERTEMP_ALM              0x00000010
#define IGBT2_OVERTEMP_ALM              0x00000020
#define DRIVER_OVERVOLTAGE_ALM          0x00000040
#define DRIVER1_OVERCURRENT_ALM         0x00000080
#define DRIVER2_OVERCURRENT_ALM         0x00000100
#define INDUC_OVERTEMP_ALM              0x00000800
#define HS_OVERTEMP_ALM                 0x00001000

/**
 * TODO: Put here your functions prototypes. Just what need 
 * to be accessed by other modules.
 */

extern void init_fap(void);
extern void clear_fap_interlocks(void);
extern uint8_t check_fap_interlocks(void);
extern void clear_fap_alarms(void);
extern uint8_t check_fap_alarms(void);
extern void check_fap_indication_leds(void);
extern void fap_application_readings(void);
extern void send_output_fap_itlk_msg(void);
extern void fap_power_on_check(void);

#endif /* FAP_H_ */