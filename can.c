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

/*******************************************************************************
 * A flag to indicate that some transmission error occurred.
 ******************************************************************************/

volatile bool g_bErrFlag = 0;

/*******************************************************************************
 * A flag for the interrupt handler to indicate that a message was received.
 ******************************************************************************/

volatile bool g_bRXFlag = 0;

/*******************************************************************************
 * Can Messages
 ******************************************************************************/
tCANMsgObject can_message_rx;   // Receive data from network
uint8_t message_data_rx[8];

tCANMsgObject can_message_tx;   // Send data in network
uint8_t message_data_tx[8];

tCANMsgObject can_message_rx_remote; // Receive data request from network
uint8_t message_data_rx_remote[8];

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
void init_can(uint32_t sysclock)
{
    /* Configure the GPIO pin muxing to select CAN0 functions for these pins*/
    GPIOPinConfigure(GPIO_PA0_CAN0RX);
    GPIOPinConfigure(GPIO_PA0_CAN0TX);

    /* Enable the alternate function on the GPIO pins. The above step selects*/
    GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Enable CAN peripheral*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

    /* Wait for the CAN0 module to be ready. */
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0)) {}

    /* Initialize CAN controller */
    CANInit(CAN0_BASE);

    /* Set bit rate to 1Mbps */
    CANBitRateSet(CAN0_BASE, sysclock, 1000000);

    /* Enable CAN interrupts */
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    /* ISR for CAN */
    CANIntRegister(CAN0_BASE, isr_can);

    /* Priority */
    IntPrioritySet(INT_CAN0, 1);

    /* Enable CAN interrupt on the processor */
    IntEnable(INT_CAN0);

    /* Enable CAN for operation*/
    CANEnable(CAN0_BASE);

}

/**
 * TODO: Put here the implementation for your private functions.
 */
