
/////////////////////////////////////////////////////////////////////////////////////////////

// Sensor: Si7005-B-FM1
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "BoardTempHum.h"
#include "peripheral_drivers/timer/timer.h"
#include "peripheral_drivers/gpio/gpio_driver.h"
#include "peripheral_drivers/i2c/i2c_driver.h"
#include "board_drivers/hardware_def.h"

#include <iib_modules/fap.h>
#include <iib_modules/fac_os.h>
#include <iib_modules/fac_is.h>
#include <iib_modules/fac_cmd.h>

#include "application.h"

/////////////////////////////////////////////////////////////////////////////////////////////

#define SlaveAddress      0x40
#define RegisterAddress0  0x00
#define RegisterAddress1  0x01
#define RegisterAddress2  0x02
#define RegisterAddress3  0x03

/////////////////////////////////////////////////////////////////////////////////////////////

#define a0 (-4.7844)
#define a1  0.4008
#define a2 (-0.00393)
#define q0  0.1973
#define q1  0.00237

/////////////////////////////////////////////////////////////////////////////////////////////

rh_tempboard_t TemperatureBoard;
rh_tempboard_t RelativeHumidity;

/////////////////////////////////////////////////////////////////////////////////////////////

static unsigned char Start1 = 0x01;
static unsigned char Start2 = 0x11;

static unsigned char Size_8_Bits 	= 0;
static unsigned char Size_16_Bits 	= 1;

static unsigned char RegisterReady       		= 0;
static unsigned char RegisterTemperature 		= 1;
static unsigned char RegisterRelativeHumidity 	= 2;

/////////////////////////////////////////////////////////////////////////////////////////////

//Configure the Si7005 temperature sensor initialization.
void BoardTemperatureStartConversion(void)
{
	I2C5Send(SlaveAddress, 2, RegisterAddress3, Start2);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void BoardTemperatureRead(void)
{
	int16_t Status = 1;

    int16_t TempValue;

    //Wait until conversion is finished (typical 35ms)
    while(Status == 1)
    {
    	Status = I2C5Receive(SlaveAddress, RegisterAddress0, Size_8_Bits, RegisterReady);
    }

    TempValue = I2C5Receive(SlaveAddress, RegisterAddress1, Size_16_Bits, RegisterTemperature);

//*******************************************************************************************

    TemperatureBoard.Value = (TempValue/32.0) - 50.0;

//*******************************************************************************************

    if(TemperatureBoard.Value > TemperatureBoard.AlarmLimit)
    {
        if(TemperatureBoard.Alarm_DelayCount < TemperatureBoard.Alarm_Delay_ms) TemperatureBoard.Alarm_DelayCount++;
        else
        {
           TemperatureBoard.Alarm_DelayCount = 0;
           TemperatureBoard.Alarm = 1;
        }
    }
    else TemperatureBoard.Alarm_DelayCount = 0;

    if(TemperatureBoard.Value > TemperatureBoard.TripLimit)
    {
        if(TemperatureBoard.Itlk_DelayCount < TemperatureBoard.Itlk_Delay_ms) TemperatureBoard.Itlk_DelayCount++;
        else
        {
           TemperatureBoard.Itlk_DelayCount = 0;
           TemperatureBoard.Trip = 1;
        }
    }
    else TemperatureBoard.Itlk_DelayCount = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Configure the Si7005 relative humidity sensor initialization
void RelativeHumidityStartConversion(void)
{
	I2C5Send(SlaveAddress, 2, RegisterAddress3, Start1);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void RelativeHumidityRead(void)
{
	int16_t Status = 1;

	int16_t RelHumValue;

	float curve;
	float rawHumidity;
	float linearHumidity;

    //Wait until conversion is finished (typical 35ms)
    while(Status == 1)
    {
    	Status = I2C5Receive(SlaveAddress, RegisterAddress0, Size_8_Bits, RegisterReady);
    }

    RelHumValue = I2C5Receive(SlaveAddress, RegisterAddress1, Size_16_Bits, RegisterRelativeHumidity);

//*******************************************************************************************

    rawHumidity = RelHumValue;

    curve = (rawHumidity/16.0)-24.0;

    linearHumidity = curve - ( (curve * curve) * a2 + curve * a1 + a0);

    linearHumidity = linearHumidity + ( TemperatureBoard.Value - 30.0 ) * ( linearHumidity * q1 + q0 );

    RelativeHumidity.Value = linearHumidity;

//*******************************************************************************************

    if(RelativeHumidity.Value > RelativeHumidity.AlarmLimit)
    {
        if(RelativeHumidity.Alarm_DelayCount < RelativeHumidity.Alarm_Delay_ms) RelativeHumidity.Alarm_DelayCount++;
        else
        {
           RelativeHumidity.Alarm_DelayCount = 0;
           RelativeHumidity.Alarm = 1;
        }
    }
    else RelativeHumidity.Alarm_DelayCount = 0;

    if(RelativeHumidity.Value > RelativeHumidity.TripLimit)
    {
        if(RelativeHumidity.Itlk_DelayCount < RelativeHumidity.Itlk_Delay_ms) RelativeHumidity.Itlk_DelayCount++;
        else
        {
           RelativeHumidity.Itlk_DelayCount = 0;
           RelativeHumidity.Trip = 1;
        }
    }
    else RelativeHumidity.Itlk_DelayCount = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//Initializes the I2C communication of the Si7005-B-FM1 sensor.
void RhBoardTempSenseInit(void)
{
	//I2C5 initialization
	InitI2C5();

	//Configure CS for Si7005-B
	set_gpio_as_output(GPIO_PORTB_BASE, GPIO_PIN_2);

	clear_pin(GPIO_PORTB_BASE, GPIO_PIN_2);

	TemperatureBoard.Value = 0.0;
	TemperatureBoard.AlarmLimit = 90.0;
	TemperatureBoard.TripLimit = 100.0;
	TemperatureBoard.Alarm = 0;
	TemperatureBoard.Trip = 0;
	TemperatureBoard.Alarm_Delay_ms = 0;	// milisecond
	TemperatureBoard.Alarm_DelayCount = 0;
	TemperatureBoard.Itlk_Delay_ms = 0;		// milisecond
	TemperatureBoard.Itlk_DelayCount = 0;

	RelativeHumidity.Value = 0.0;
	RelativeHumidity.AlarmLimit = 90.0;
	RelativeHumidity.TripLimit = 100.0;
	RelativeHumidity.Alarm = 0;
	RelativeHumidity.Trip = 0;
	RelativeHumidity.Alarm_Delay_ms = 0;	// milisecond
	RelativeHumidity.Alarm_DelayCount = 0;
	RelativeHumidity.Itlk_Delay_ms = 0;		// milisecond
	RelativeHumidity.Itlk_DelayCount = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

float BoardTempRead(void)
{
#if (BoardTempEnable == 1)

    return TemperatureBoard.Value;

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

float RhRead(void)
{
#if (RhEnable == 1)

    return RelativeHumidity.Value;

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void BoardTempAlarmLevelSet(float nValue)
{
    TemperatureBoard.AlarmLimit = nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void BoardTempTripLevelSet(float nValue)
{
    TemperatureBoard.TripLimit = nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void BoardTempDelay(unsigned int delay_ms)
{
    TemperatureBoard.Alarm_Delay_ms = delay_ms;
    TemperatureBoard.Itlk_Delay_ms = delay_ms;

}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char BoardTempAlarmStatusRead(void)
{
#if (BoardTempEnable == 1)

    return TemperatureBoard.Alarm;

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char BoardTempTripStatusRead(void)
{
#if (BoardTempEnable == 1)

    return TemperatureBoard.Trip;

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void RhAlarmLevelSet(float nValue)
{
    RelativeHumidity.AlarmLimit = nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void RhTripLevelSet(float nValue)
{
    RelativeHumidity.TripLimit = nValue;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void RhDelay(unsigned int delay_ms)
{
    RelativeHumidity.Alarm_Delay_ms = delay_ms;
    RelativeHumidity.Itlk_Delay_ms = delay_ms;
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char RhAlarmStatusRead(void)
{
#if (RhEnable == 1)

    return RelativeHumidity.Alarm;

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned char RhTripStatusRead(void)
{
#if (RhEnable == 1)

    return RelativeHumidity.Trip;

#else

    return 0;

#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////

void RhBoardTempClearAlarmTrip(void)
{
    TemperatureBoard.Alarm = 0;
    TemperatureBoard.Trip = 0;

    RelativeHumidity.Alarm = 0;
    RelativeHumidity.Trip = 0;
   
}

/////////////////////////////////////////////////////////////////////////////////////////////







