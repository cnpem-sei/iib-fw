
/////////////////////////////////////////////////////////////////////////////////////////////

/*
 * timer.c
 *
 *  Created on: 16 de abr de 2021
 *      Author: rogerio.marcondeli
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/systick.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"
#include "can_bus.h"
#include "adc_internal.h"
#include "application.h"
#include "board_drivers/hardware_def.h"
#include "peripheral_drivers/gpio/gpio_driver.h"
#include "peripheral_drivers/timer/timer.h"
#include "leds.h"
#include "output.h"
#include "input.h"
#include "BoardTempHum.h"
#include "ntc_isolated_i2c.h"
#include "pt100.h"
#include "task.h"
#include "iib_data.h"

#include <iib_modules/fap.h>
#include <iib_modules/fac_os.h>
#include <iib_modules/fac_is.h>
#include <iib_modules/fac_cmd.h>

/////////////////////////////////////////////////////////////////////////////////////////////

volatile static uint32_t micros = 0;

volatile static uint32_t millis = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

void delay_us(uint32_t time)
{
    volatile uint32_t temp = micros;
    while ((micros - temp) < time);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void delay_ms(uint32_t time)
{
    volatile uint32_t temp = millis;
    while ((millis - temp) < time);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void IntTimer1usHandler(void)
{
	// Clear the timer 2 interrupt.
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

	micros++;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void IntTimer100usHandler(void)
{
    // Clear the timer 0 interrupt.
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    RunToggle();

    task_100_us();

    RunToggle();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void IntTimer1msHandler(void)
{
    // Clear the timer 1 interrupt.
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    millis++;

    RunToggle();

    sample_adc();

    RunToggle();

    task_1_ms();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void IntTimer100msHandler(void)
{
    // Clear the timer 3 interrupt.
    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

    send_data_schedule();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Timer_1us_Init(void)
{
    // Disable timer 2 peripheral
    SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER2);

    // Reset timer 2 peripheral
    SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER2);

    // Enable timer 2 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

    // Wait for the timer 2 peripheral to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2));

    // Disable the timer 2 module.
    TimerDisable(TIMER2_BASE, TIMER_A);

    // Configure the two 32-bit periodic timers.
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER2_BASE, TIMER_A, (SYSCLOCK / 1000000) - 1);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER2A);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER2_BASE, TIMER_A, IntTimer1usHandler);
    IntPrioritySet(INT_TIMER2A, 2);

    // Enable the timer 2.
    TimerEnable(TIMER2_BASE, TIMER_A);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Timer_100us_Init(void)
{
    // Disable timer 0 peripheral
    SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER0);

    // Reset timer 0 peripheral
    SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER0);

    // Enable timer 0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Wait for the timer 0 peripheral to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));

    // Disable the timer 0 module.
    TimerDisable(TIMER0_BASE, TIMER_A);

    // Configure the two 32-bit periodic timers.
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (SYSCLOCK / 10000) - 1);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, IntTimer100usHandler);
    IntPrioritySet(INT_TIMER0A, 0);

    // Enable the timer 0.
    TimerEnable(TIMER0_BASE, TIMER_A);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Timer_1ms_Init(void)
{
    // Disable timer 1 peripheral
    SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER1);

    // Reset timer 1 peripheral
    SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER1);

    // Enable timer 1 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    // Wait for the timer 1 peripheral to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1));

    // Disable the timer 1 module.
    TimerDisable(TIMER1_BASE, TIMER_A);

    // Configure the two 32-bit periodic timers.
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, (SYSCLOCK / 1000) - 1);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER1_BASE, TIMER_A, IntTimer1msHandler);
    IntPrioritySet(INT_TIMER1A, 1);

    // Enable the timer 1.
    TimerEnable(TIMER1_BASE, TIMER_A);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Timer_100ms_Init(void)
{
    // Disable timer 3 peripheral
    SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER3);

    // Reset timer 3 peripheral
    SysCtlPeripheralReset(SYSCTL_PERIPH_TIMER3);

    // Enable timer 3 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);

    // Wait for the timer 3 peripheral to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3));

    // Disable the timer 3 module.
    TimerDisable(TIMER3_BASE, TIMER_A);

    // Configure the two 32-bit periodic timers.
    TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER3_BASE, TIMER_A, (SYSCLOCK / 10) - 1);

    // Setup the interrupts for the timer timeouts.
    IntEnable(INT_TIMER3A);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER3_BASE, TIMER_A, IntTimer100msHandler);
    IntPrioritySet(INT_TIMER3A, 3);

    // Enable the timer 3.
    TimerEnable(TIMER3_BASE, TIMER_A);
}

/////////////////////////////////////////////////////////////////////////////////////////////




