

#include <adc_internal.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"

#include "can_bus.h"
#include "adc_internal.h"
#include "application.h"

#include "board_drivers/hardware_def.h"
#include "peripheral_drivers/gpio/gpio_driver.h"


#include "leds.h"
#include "output.h"
#include "input.h"
#include "BoardTempHum.h"
#include "pt100.h"
//#include "memory.h"
#include "task.h"
//#include "driver_board.h"

/*
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

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
*/

#define ON  ~0
#define OFF 0

#define SYSCLOCK    120000000

volatile static uint32_t millis = 0;

volatile static uint8_t can_timestamp_100ms = 0;

void delay_ms(uint32_t time)
{
    volatile uint32_t temp = millis;
    while ((millis - temp) < time);
}

static void int_timer_1ms_handler(void)
{
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    // var count delay function
    millis++;

    // can time stamp
    if(can_timestamp_100ms >= 10)
    {
        RunToggle();
        SendCanSchedule();
        can_timestamp_100ms = 0;
        RunToggle();
    }
    else can_timestamp_100ms++;

    RunToggle();
    sample_adc();
    RunToggle();

    task_1_ms();
}

static void int_timer_100us_handler(void)
{
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    RunToggle();
    task_100_us();
    RunToggle();

}

void timer_1ms_init(void)
{
    //
    // Enable timer 1.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    //
    // Configure the two 32-bit periodic timers.
    //
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, (SYSCLOCK / 1000) - 1);

    IntPrioritySet(INT_TIMER1A, 1);

    //
    // Setup the interrupts for the timer timeouts.
    //
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    TimerIntRegister(TIMER1_BASE, TIMER_A, int_timer_1ms_handler);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER1_BASE, TIMER_A);
}

void timer_100us_init(void)
{
    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    //
    // Configure the two 32-bit periodic timers.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, (SYSCLOCK / 10000) - 1);

    //
    // Setup the interrupts for the timer timeouts.
    //
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerIntRegister(TIMER0_BASE, TIMER_A, int_timer_100us_handler);

    IntPrioritySet(INT_TIMER0A, 0);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);

}

/**
 * main.c
 */
int main(void)
{

    uint32_t ui32SysClock;

    ui32SysClock = SysCtlClockFreqSet((SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ |
    SYSCTL_CFG_VCO_480), 120000000);

    pinout_config();

    AdcsInit();

    InitCan(ui32SysClock);

    //Driver Voltage channel configuration
    DriverVoltageInit();

    //Driver Current channel configuration
    DriverCurrentInit();

    //LEDs initialization
    LedsInit();

    //Digital Input initialization
    InputInit();

    //Digital Output initialization
    OutputInit();

    timer_1ms_init();
    timer_100us_init();

    // PT100 channels initialization
    Pt100Init();

    //Rh & Board Temp sensors initialization
    //RhTempSenseInit();

    // Led test
    LedPong();

    // Block application to sign that CAN Address is out of range
    while(CanIdRead() == 0 || CanIdRead() >= 496)
    {
        // Blink bar
        LedBarBlink();
        delay_ms(40);
    }

    AppConfiguration();


    while(1)
    {

        Application();

        BoardTask();

    }


    return 0;
}