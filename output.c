
/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "output.h"
#include "board_drivers/hardware_def.h"
#include "peripheral_drivers/gpio/gpio_driver.h"

#include <iib_modules/fap.h>
#include <iib_modules/fac_os.h>
#include <iib_modules/fac_is.h>
#include <iib_modules/fac_cmd.h>

#include "application.h"

/////////////////////////////////////////////////////////////////////////////////////////////

void OutputInit(void)
{
    
    set_gpio_as_output(RELAY_1_BASE, RELAY_1_PIN);
    set_gpio_as_output(RELAY_2_BASE, RELAY_2_PIN);

    set_gpio_as_output(GPDO_1_BASE, GPDO_1_PIN);
    set_gpio_as_output(GPDO_2_BASE, GPDO_2_PIN);
    set_gpio_as_output(GPDO_3_BASE, GPDO_3_PIN);
    set_gpio_as_output(GPDO_4_BASE, GPDO_4_PIN);

    set_gpio_as_output(TP_1_BASE, TP_1_PIN);
    set_gpio_as_output(TP_2_BASE, TP_2_PIN);
    set_gpio_as_output(TP_3_BASE, TP_3_PIN);

    set_gpio_as_output(STATUS_LED_BASE, STATUS_LED_PIN);

    clear_pin(RELAY_1_BASE, RELAY_1_PIN);
    clear_pin(RELAY_2_BASE, RELAY_2_PIN);
    
    clear_pin(GPDO_1_BASE, GPDO_1_PIN);
    clear_pin(GPDO_2_BASE, GPDO_2_PIN);
    clear_pin(GPDO_3_BASE, GPDO_3_PIN);
    clear_pin(GPDO_4_BASE, GPDO_4_PIN);
    
    clear_pin(TP_1_BASE, TP_1_PIN);
    clear_pin(TP_2_BASE, TP_2_PIN);
    clear_pin(TP_3_BASE, TP_3_PIN);

    clear_pin(STATUS_LED_BASE, STATUS_LED_PIN);

}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo1TurnOn(void)
{
#if (Gpdo1Enable == 1)

    set_pin(GPDO_1_BASE, GPDO_1_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo1TurnOff(void)
{
#if (Gpdo1Enable == 1)

    clear_pin(GPDO_1_BASE, GPDO_1_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char Gpdo1Sts(void)
{
#if (Gpdo1Enable == 1)

    return read_pin(GPDO_1_BASE, GPDO_1_PIN);

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo2TurnOn(void)
{
#if (Gpdo2Enable == 1)

    set_pin(GPDO_2_BASE, GPDO_2_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo2TurnOff(void)
{
#if (Gpdo2Enable == 1)

    clear_pin(GPDO_2_BASE, GPDO_2_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char Gpdo2Sts(void)
{
#if (Gpdo2Enable == 1)

    return read_pin(GPDO_2_BASE, GPDO_2_PIN);

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo3TurnOn(void)
{
#if (Gpdo3Enable == 1)

    set_pin(GPDO_3_BASE, GPDO_3_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo3TurnOff(void)
{
#if (Gpdo3Enable == 1)

    clear_pin(GPDO_3_BASE, GPDO_3_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char Gpdo3Sts(void)
{
#if (Gpdo3Enable == 1)

    return read_pin(GPDO_3_BASE, GPDO_3_PIN);

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo4TurnOn(void)
{
#if (Gpdo4Enable == 1)

    set_pin(GPDO_4_BASE, GPDO_4_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void Gpdo4TurnOff(void)
{
#if (Gpdo4Enable == 1)

    clear_pin(GPDO_4_BASE, GPDO_4_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char Gpdo4Sts(void)
{
#if (Gpdo4Enable == 1)

    return read_pin(GPDO_4_BASE, GPDO_4_PIN);

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void ReleAuxTurnOn(void)
{
#if (ReleAuxEnable == 1)

    set_pin(RELAY_1_BASE, RELAY_1_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void ReleAuxTurnOff(void)
{
#if (ReleAuxEnable == 1)

    clear_pin(RELAY_1_BASE, RELAY_1_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char ReleAuxSts(void)
{
#if (ReleAuxEnable == 1)

    return read_pin(RELAY_1_BASE, RELAY_1_PIN);

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void ReleExtItlkTurnOn(void)
{
#if (ReleExtItlkEnable == 1)

    set_pin(RELAY_2_BASE, RELAY_2_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void ReleExtItlkTurnOff(void)
{
#if (ReleExtItlkEnable == 1)

    clear_pin(RELAY_2_BASE, RELAY_2_PIN);

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char ReleExtItlkSts(void)
{
#if (ReleExtItlkEnable == 1)

    return read_pin(RELAY_2_BASE, RELAY_2_PIN);

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////


