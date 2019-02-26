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

#ifndef FAC_CMD_H_
#define FAC_CMD_H_

#include <stdint.h>

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ITLK    0x00000001
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ITLK     0x00000002
#define FAC_CMD_HS_OVERTEMP_ITLK            0x00000004
#define FAC_CMD_INDUC_OVERTEMP_ITLK         0x00000008
#define FAC_CMD_EXTERNAL1_ITLK              0x00000010
#define FAC_CMD_EXTERNAL2_ITLK              0x00000020

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ALM     0x00000001
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ALM      0x00000002
#define FAC_CMD_HS_OVERTEMP_ALM             0x00000004
#define FAC_CMD_INDUC_OVERTEMP_ALM          0x00000008

extern void init_fac_cmd(void);

#endif /* COMMAND_DRAWER_H_ */
