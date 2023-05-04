
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
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"
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
#include <iib_modules/resonant_swls.h>

/////////////////////////////////////////////////////////////////////////////////////////////

static uint32_t ui32SysClock;

/////////////////////////////////////////////////////////////////////////////////////////////

uint32_t SysCtlClockGetTM4C129(void)
{
    return ui32SysClock;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/**
 * main.c
 *
 */
int main(void)
{

    ui32SysClock = SysCtlClockFreqSet((SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                       SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480), 120000000);

    pinout_config();

    init_control_framwork(&g_controller_iib);

    AdcsInit();

    //LEDs initialization
    LedsInit();

    //Digital Input initialization
    InputInit();

    //Digital Output initialization
    OutputInit();

    InitCan(ui32SysClock);

    Timer_1us_Init();

    Timer_100us_Init();

    Timer_1ms_Init();

    Timer_Can_Bus_Init();

/////////////////////////////////////////////////////////////////////////////////////////////

    //PT100 channels initialization
    Pt100Init();

    //Rh & Board Temp sensors initialization
#if ((RhEnable && BoardTempEnable) == 1)

    RhBoardTempSenseInit();

#endif

    //ADS1014 with NTC 5K Igbt1 and Igbt2 initialization
#if ((TempIgbt1Enable || TempIgbt2Enable) == 1)

    NtcInit();

#endif

    //Led test
    LedPong();

/////////////////////////////////////////////////////////////////////////////////////////////

    //Block application to sign that CAN Address is out of range
    while(get_can_address() == 0 || get_can_address() >= 496)
    {
        //Blink bar
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

/////////////////////////////////////////////////////////////////////////////////////////////





