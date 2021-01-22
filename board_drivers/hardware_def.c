/******************************************************************************
 * Copyright (C) 2017 by LNLS - Power Electronics Group (ELP)
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it without restrictions. LNLS is not
 * liable for any misuse of this material.
 *
 *****************************************************************************/
/**
 * @file hardware_def.c
 * @brief Hardware configurations for Interlock board.
 *
 * @author Allef Araujo
 * @date 11/08/2017
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_can.h"
#include "inc/hw_epi.h"
#include "inc/hw_ssi.h"
#include "inc/hw_udma.h"
#include "inc/hw_i2c.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/can.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/epi.h"
#include "driverlib/ssi.h"
#include "driverlib/uart.h"
#include "driverlib/usb.h"
#include "driverlib/udma.h"
#include "driverlib/pin_map.h"
#include "hardware_def.h"

/////////////////////////////////////////////////////////////////////////////////////////////

void pinout_config(void)
{
    // Disable WDOG0 and WDOG1
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG0);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG1);

    // Disable all GPIO.
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOP);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOQ);

    // Reset all GPIO.
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOH);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOK);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOL);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOM);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOP);
    SysCtlPeripheralReset(SYSCTL_PERIPH_GPIOQ);

	// Enable all GPIO.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);

	// Wait for the Peripheral to be ready for programming
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)
    || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)
    || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)
	|| !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG)
	|| !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOH));

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)
	|| !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOK));

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)
    || !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM));

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)
	|| !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOP));

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOQ));

}

/////////////////////////////////////////////////////////////////////////////////////////////


