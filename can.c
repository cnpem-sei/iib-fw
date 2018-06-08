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
 * @file can.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 8 de jun de 2018
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"


#include "can_bus.h"

#include "BoardTempHum.h"
#include "input.h"
#include "application.h"
#include "adc_internal.h"
#include "leds.h"

#include "board_drivers/hardware_def.h"
#include "peripheral_drivers/gpio/gpio_driver.h"

/**
 * TODO: Put here your defines. Just what is local. If you don't
 * need to access it from other module, consider use a constant (const)
 */
#define INTERLOCK_MESSAGE_ID    0
#define ALARM_MESSAGE_ID        1

/******************************************************************************
 * A flag to indicate that some transmission error occurred.
 *****************************************************************************/

volatile bool g_bErrFlag = 0;

/*******************************************************************************
 * Can Messages
 ******************************************************************************/
tCANMsgObject can_message_rx;
uint8_t message_data_rx[8];

tCANMsgObject can_message_tx;
uint8_t message_data_tx[8];

/**
 * TODO: Put here your constants and variables. Always use static for 
 * private members.
 */

/**
 * TODO: Put here your function prototypes for private functions. Use
 * static in declaration.
 */


/**
 * TODO: Put here the implementation for your public functions.
 */

/**
 * TODO: Put here the implementation for your private functions.
 */
