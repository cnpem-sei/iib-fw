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
 * @file task.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author joao.rosa
 * @date 6 de nov de 2017
 *
 */


/////////////////////////////////////////////////////////////////////////////////////////////

/**
 * TODO: Put here your includes
 */

#include <stdbool.h>
#include <stdint.h>
#include <adc_internal.h>
#include "leds.h"
#include "output.h"
#include "input.h"
#include "BoardTempHum.h"
#include "pt100.h"
#include "ntc_isolated_i2c.h"
#include "application.h"

#include <iib_modules/fap.h>
#include <iib_modules/fac_os.h>
#include <iib_modules/fac_is.h>
#include <iib_modules/fac_cmd.h>

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned int mSecond = 0;
unsigned int uSecond = 0;
unsigned int _8Hz = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

bool TempPt100Ch1ReadTask    = 0;
bool TempPt100Ch2ReadTask    = 0;
bool TempPt100Ch3ReadTask    = 0;
bool TempPt100Ch4ReadTask    = 0;
bool StartBoardTempTask      = 0;
bool BoardTempReadTask       = 0;
bool StartRhTask             = 0;
bool RhReadTask              = 0;
bool ErrorCheckTask          = 0;
bool LedUpdateTask           = 0;
bool InterlockAlarmCheckTask = 0;
bool DriverVoltReadTask      = 0;
bool Driver1CurrtReadTask    = 0;
bool Driver2CurrtReadTask    = 0;
bool SendCanDataTask         = 0;
bool StartNtcTask            = 0;
bool NtcReadTask             = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

void ErrorCheckHandle(void)
{
    if(Pt100Ch1ErrorRead()) Pt100Ch1Clear();
    if(Pt100Ch2ErrorRead()) Pt100Ch2Clear();
    if(Pt100Ch3ErrorRead()) Pt100Ch3Clear();
    if(Pt100Ch4ErrorRead()) Pt100Ch4Clear();

    // Check CanNotCommunicate
    // Indicate channel problem, need a PT100 initialization or a chip verification
    // Reset() -> Reset implemented by software

    // Check RTD Out Of Range
    // send a command to indication layer to signalize the user
    if(Pt100Ch1RtdStatusRead()) Pt100Ch1Reset();
    if(Pt100Ch2RtdStatusRead()) Pt100Ch2Reset();
    if(Pt100Ch3RtdStatusRead()) Pt100Ch3Reset();
    if(Pt100Ch4RtdStatusRead()) Pt100Ch4Reset();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void task_100_us(void)
{
	if(uSecond >= 10)
	{
		uSecond = 0;
	}
	else uSecond++;

	if(uSecond == 0)
	{

#if (VoltageCh1Enable == 1)

        VoltageCh1Sample();

#endif

#if (VoltageCh2Enable == 1)

        VoltageCh2Sample();

#endif

    }

    else if(uSecond == 1)
    {

#if (VoltageCh3Enable == 1)

        VoltageCh3Sample();

#endif

    }

    else if(uSecond == 2)
    {

#if (VoltageCh4Enable == 1)

        VoltageCh4Sample();

#endif

    }

    else if(uSecond == 3)
    {

#if (CurrentCh1Enable == 1)

        CurrentCh1Sample();

#endif

    }

    else if(uSecond == 4)
    {

#if (CurrentCh2Enable == 1)

        CurrentCh2Sample();

#endif

    }

    else if(uSecond == 5)
    {

#if (CurrentCh3Enable == 1)

        CurrentCh3Sample();

#endif

    }

    else if(uSecond == 6)
    {

#if (CurrentCh4Enable == 1)

        CurrentCh4Sample();

#endif

    }

    else if(uSecond == 7)
    {

#if (LvCurrentCh1Enable == 1)

        LvCurrentCh1Sample();

#endif

    }

    else if(uSecond == 8)
    {

#if (LvCurrentCh2Enable == 1)

        LvCurrentCh2Sample();

#endif

    }

    else if(uSecond == 9)
    {

#if (LvCurrentCh3Enable == 1)

        LvCurrentCh3Sample();

#endif

    }

}

/////////////////////////////////////////////////////////////////////////////////////////////

void task_1_ms(void)
{
	// Timestamp for 8Hz tasks (no critical tasks)
    if(_8Hz >= 125)
    {
        _8Hz = 0;
        LedUpdateTask = 1;
    }
    else _8Hz++;

    // Timestamp for 1ms tasks
    if(mSecond >= 1000)
    {
        mSecond = 0;
    }
    else mSecond++;

    // Trigger for 1s period tasks (no critical tasks)
    switch(mSecond)
    {

    case 20:
    	SendCanDataTask = 1;        	// 80ms
    	break;

    case 100:
    	TempPt100Ch1ReadTask = 1;   	// 100ms
    	break;

    case 200:
    	DriverVoltReadTask = 1;			// 30ms
    	break;

    case 230:
    	TempPt100Ch2ReadTask = 1;		// 100ms
    	break;

    case 330:
    	Driver1CurrtReadTask = 1;		// 30ms
    	break;

    case 360:
    	TempPt100Ch3ReadTask = 1;		// 20ms
    	break;

    case 380:
    	Driver2CurrtReadTask = 1;		// 30ms
    	break;

    case 410:
    	TempPt100Ch4ReadTask = 1;		// 20ms
    	break;

    case 430:
    	StartBoardTempTask = 1;			// 40ms
    	break;

    case 470:
    	BoardTempReadTask = 1;			// 100ms
    	break;

    case 570:
    	StartNtcTask  = 1;				// 50ms
    	break;

    case 620:
    	NtcReadTask = 1;				// 100ms
    	break;

    case 720:
    	StartRhTask = 1;           		// 40ms
    	break;

    case 760:
    	RhReadTask = 1;					// 100ms
    	break;

    case 860:
    	ErrorCheckTask = 1;				// 40ms
    	break;

    case 900:
    	InterlockAlarmCheckTask = 1;	// 100ms
    	break;

    case 1000:

    	break;
    default:

    	break;

    }

}

/////////////////////////////////////////////////////////////////////////////////////////////

void BoardTask(void)
{

//*******************************************************************************************

  RunToggle();

//*******************************************************************************************

  if(TempPt100Ch1ReadTask)
  {

#if (Pt100Ch1Enable == 1)

	  Pt100Ch1Sample();

#endif

	  TempPt100Ch1ReadTask = 0;
  }

//*******************************************************************************************

  else if(TempPt100Ch2ReadTask)
  {

#if (Pt100Ch2Enable == 1)

	  Pt100Ch2Sample();

#endif

	  TempPt100Ch2ReadTask = 0;
  }

//*******************************************************************************************

  else if(TempPt100Ch3ReadTask)
  {

#if (Pt100Ch3Enable == 1)

	  Pt100Ch3Sample();

#endif

	  TempPt100Ch3ReadTask = 0;
  }

//*******************************************************************************************

  else if(TempPt100Ch4ReadTask)
  {

#if (Pt100Ch4Enable == 1)

	  Pt100Ch4Sample();

#endif

	  TempPt100Ch4ReadTask = 0;
  }

//*******************************************************************************************

  else if(StartBoardTempTask)
  {

#if (BoardTempEnable == 1)

	  BoardTemperatureStartConversion();

#endif

	  StartBoardTempTask = 0;
  }

//*******************************************************************************************

  else if(BoardTempReadTask)
  {

#if (BoardTempEnable == 1)

	  BoardTemperatureRead();

#endif

	  BoardTempReadTask = 0;
  }

//*******************************************************************************************

  else if(StartRhTask)
  {

#if (RhEnable == 1)

	  RelativeHumidityStartConversion();

#endif

	  StartRhTask = 0;
  }

//*******************************************************************************************

  else if(RhReadTask)
  {

#if (RhEnable == 1)

	  RelativeHumidityRead();

#endif

	  RhReadTask = 0;
  }

//*******************************************************************************************

  else if(StartNtcTask)
  {

#if ((TempIgbt1Enable || TempIgbt2Enable) == 1)

	  NtcStartConversion();

#endif

	  StartNtcTask = 0;
  }

//*******************************************************************************************

  else if(NtcReadTask)
  {

#if ((TempIgbt1Enable || TempIgbt2Enable) == 1)

	  NtcRead();

#endif

	  NtcReadTask = 0;
  }

//*******************************************************************************************

  else if(DriverVoltReadTask)
  {

#if (DriverVoltageEnable == 1)

      DriverVoltageSample();

#endif

      DriverVoltReadTask = 0;
  }

//*******************************************************************************************

  else if(Driver1CurrtReadTask)
  {

#if (Driver1CurrentEnable == 1)

      Driver1CurrentSample();

#endif

      Driver1CurrtReadTask = 0;
  }

//*******************************************************************************************

  else if(Driver2CurrtReadTask)
  {

#if (Driver2CurrentEnable == 1)

      Driver2CurrentSample();

#endif

      Driver2CurrtReadTask = 0;
  }

//*******************************************************************************************

  else if(ErrorCheckTask)
  {
      ErrorCheckHandle();

      ErrorCheckTask = 0;
  }

//*******************************************************************************************

  else if(InterlockAlarmCheckTask)
  {
      InterlockAppCheck();

      AlarmAppCheck();

      InterlockAlarmCheckTask = 0;
  }

//*******************************************************************************************

  else if(LedUpdateTask)
  {
      LedIndicationStatus();

      LedUpdateTask = 0;
  }

//*******************************************************************************************

  else if (SendCanDataTask)
  {
	  // Usado para testes com leituras rapidas, comentar linha ao usar.

	  send_data_schedule();

      SendCanDataTask = 0;
  }

//*******************************************************************************************

  power_on_check();

//*******************************************************************************************

}

/////////////////////////////////////////////////////////////////////////////////////////////


