
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

//*****************************************************************************
//
// A flag to indicate that some transmission error occurred.
//
//*****************************************************************************
volatile bool g_bErrFlag = 0;

//*****************************************************************************
//
// A flag for the interrupt handler to indicate that a message was received.
//
//*****************************************************************************
volatile bool g_bRXFlag = 0;

//Rx
tCANMsgObject sCANMessage;
uint8_t pui8MsgData[8];

//Tx
tCANMsgObject sCANMessageTx;
uint8_t pui8MsgDataTx[8];

//-------------------------------------------------------------------------
// variables
//-------------------------------------------------------------------------

uint16_t SecCount = 0;

uint16_t CanId = 0;

uint8_t CanScheduleVar = 0;

// Partir o float em bytes
static union
{
   float f;
   char c[4];
} floatNchars;


//*****************************************************************************
//
// This function is the interrupt handler for the CAN peripheral.  It checks
// for the cause of the interrupt, and maintains a count of all messages that
// have been transmitted.
//
//*****************************************************************************
void
can_handler(void)
{
    uint32_t ui32Status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    //
    // If the cause is a controller status interrupt, then get the status
    //
    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.  If the
        // CAN peripheral is not connected to a CAN bus with other CAN devices
        // present, then errors will occur and will be indicated in the
        // controller status.
        //
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        //
        // Set a flag to indicate some errors may have occurred.
        //
        g_bErrFlag = 1;
    }

    //
    // Check if the cause is message object 1, which what we are using for
    // sending messages.
    //
    else if(ui32Status == 1)
    {
        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 1, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 1);

        //
        // Increment a counter to keep track of how many messages have been
        // sent.  In a real application this could be used to set flags to
        // indicate when a message is sent.
        //
        //g_ui32MsgCount++;

        //
        // Set flag to indicate received message is pending.
        //
        g_bRXFlag = 1;

        //
        // Since the message was sent, clear any error flags.
        //
        g_bErrFlag = 0;
    }

    //
    // Otherwise, something unexpected caused the interrupt.  This should
    // never happen.
    //
    else
    {
        CANIntClear(CAN0_BASE, 1);
        //
        // Spurious interrupt handling can go here.
        //
    }
}

void SendCanSchedule(void)
{

    if(SecCount >= 10)
    {
        SecCount = 0;
    }


    switch(CanScheduleVar)
    {
    case 0:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:
                SendCan(Q1_I_ARMS);
                break;
            case OUTPUT_Q4_MODULE:

                break;
            case RECTIFIER_MODULE:

                break;
            case INPUT_MODULE:

                break;
        }

        CanScheduleVar = 1;
        break;

    case 1:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:
                SendCan(Q1_V_IN_OUT);
                break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:

               break;
        }

        CanScheduleVar = 2;
        break;

    case 2:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:

               break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:

               break;
        }

        CanScheduleVar = 3;
        break;

    case 3:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:

               break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:

               break;
        }

        CanScheduleVar = 4;
        break;

    case 4:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:

               break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:

               break;
        }

        CanScheduleVar = 5;
        break;

    case 5:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:

               break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:

               break;
        }

        CanScheduleVar = 6;
        break;

    case 6:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:

               break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:

               break;
        }

        CanScheduleVar = 7;
        break;

    // 1s message
    case 7:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:
               if(SecCount == 7)
               {
                   toggle_pin(TP_1_BASE, TP_1_PIN);
                   SendCan(Q1_SLOW_STS);
                   toggle_pin(TP_1_BASE, TP_1_PIN);
               }
               break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:

               break;
        }

        CanScheduleVar = 8;
        break;

    // 1s message
    case 8:
        switch(AppType())
        {
            case OUTPUT_Q1_MODULE:

                if(SecCount == 8)
               {
                   toggle_pin(TP_1_BASE, TP_1_PIN);
                   SendCan(Q1_ALARM_ITLK_STS);
                   toggle_pin(TP_1_BASE, TP_1_PIN);

               }

               break;
            case OUTPUT_Q4_MODULE:

               break;
            case RECTIFIER_MODULE:

               break;
            case INPUT_MODULE:


               break;
        }

        CanScheduleVar = 9;
        break;

    case 9:
        if(InterlockRead())
        {
            SendCan(ITLK_MESS);
        }

        CanScheduleVar = 0;

        // Increase 1s CAN message counter
        SecCount++;
        break;

    default:
        CanScheduleVar = 0;
        break;

    }

}

void SendCan(unsigned char Message)
{

    switch (Message)
    {
      case Q1_I_ARMS:

           floatNchars.f = Q1ModuleIoutA1Read(); //  I Braço 1
           pui8MsgDataTx[0] = floatNchars.c[0];
           pui8MsgDataTx[1] = floatNchars.c[1];
           pui8MsgDataTx[2] = floatNchars.c[2];
           pui8MsgDataTx[3] = floatNchars.c[3];

           floatNchars.f = Q1ModuleIoutA2Read(); //  I Braço 2
           pui8MsgDataTx[4] = floatNchars.c[0];
           pui8MsgDataTx[5] = floatNchars.c[1];
           pui8MsgDataTx[6] = floatNchars.c[2];
           pui8MsgDataTx[7] = floatNchars.c[3];

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 0;
           break;
      case Q1_V_IN_OUT:
           floatNchars.f = Q1ModuleVinRead();  // Vin
           pui8MsgDataTx[0] = floatNchars.c[0];
           pui8MsgDataTx[1] = floatNchars.c[1];
           pui8MsgDataTx[2] = floatNchars.c[2];
           pui8MsgDataTx[3] = floatNchars.c[3];

           floatNchars.f = Q1ModuleVoutRead(); //  Vout
           pui8MsgDataTx[4] = floatNchars.c[0];
           pui8MsgDataTx[5] = floatNchars.c[1];
           pui8MsgDataTx[6] = floatNchars.c[2];
           pui8MsgDataTx[7] = floatNchars.c[3];

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 1;
           break;

      case Q1_SLOW_STS:

           pui8MsgDataTx[0] = Q1ModuleTempHeatSinkRead();
           pui8MsgDataTx[1] = Q1ModuleTempIGBT1Read();
           pui8MsgDataTx[2] = Q1ModuleTempIGBT2Read();
           pui8MsgDataTx[3] = Q1ModuleTempLRead();
           pui8MsgDataTx[4] = BoardTempRead();
           pui8MsgDataTx[5] = RhRead();

           pui8MsgDataTx[6] = 0;
           if(Q1ModuleRelayRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00000001;
           if(Q1ModuleExternalItlkRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00000010;
           if(Q1ModuleDriver1ErrorRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00000100;
           if(Q1ModuleDriver2ErrorRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00001000;
           if(Q1ModuleLeakageCurrentRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00010000;
           if(Q1ModuleRackRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00100000;
           if(Q1ModuleTempIGBT1HwrItlkRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b01000000;
           if(Q1ModuleTempIGBT2HwrItlkRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b10000000;

           pui8MsgDataTx[7] = 0;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 2;
           break;

      case Q1_ALARM_ITLK_STS:

           //Alarm bytes
           pui8MsgDataTx[0] = 0;
           pui8MsgDataTx[1] = 0;

           if(Q1ModuleVoutAlarmStsRead())         pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00000001;
           if(Q1ModuleVinAlarmStsRead())          pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00000010;
           if(Q1ModuleIoutA1AlarmStsRead())       pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00000100;
           if(Q1ModuleIoutA2AlarmStsRead())       pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00001000;
           if(Q1ModuleTempIGBT1AlarmStsRead())    pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00010000;
           if(Q1ModuleTempIGBT2AlarmStsRead())    pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00100000;
           if(Q1ModuleTempLAlarmStsRead())        pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b01000000;
           if(Q1ModuleTempHeatSinkAlarmStsRead()) pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b10000000;

           if(RhAlarmStatusRead())                pui8MsgDataTx[1] = pui8MsgDataTx[1] | 0b00000001;
           if(TempAlarmStatusRead())              pui8MsgDataTx[1] = pui8MsgDataTx[1] | 0b00000010;

           pui8MsgDataTx[2] = 0;
           pui8MsgDataTx[3] = 0;

           //Interlock bytes
           pui8MsgDataTx[4] = 0;
           pui8MsgDataTx[5] = 0;

           if(Q1ModuleVoutItlkStsRead())         pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000001;
           if(Q1ModuleVinItlkStsRead())          pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000010;
           if(Q1ModuleIoutA1ItlkStsRead())       pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000100;
           if(Q1ModuleIoutA2ItlkStsRead())       pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00001000;
           if(Q1ModuleTempIGBT1ItlkStsRead())    pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00010000;
           if(Q1ModuleTempIGBT2ItlkStsRead())    pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00100000;
           if(Q1ModuleTempIGBT1HwrItlkStsRead()) pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b01000000;
           if(Q1ModuleTempIGBT2HwrItlkStsRead()) pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b10000000;

           if(Q1ModuleTempLItlkStsRead())        pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000001;
           if(Q1ModuleTempHeatSinkItlkStsRead()) pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000010;
           if(Q1ModuleExternalItlkStsRead())     pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000100;
           if(Q1ModuleLeakageCurrentStsRead())   pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00001000;
           if(Q1ModuleRackStsRead())             pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00010000;
           if(Q1ModuleDriver1ErrorItlkRead())    pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00100000;
           if(Q1ModuleDriver2ErrorItlkRead())    pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b01000000;
           if(RhTripStatusRead())                pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b10000000;

           pui8MsgDataTx[6] = 0;
           if(TempTripStatusRead())              pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00000001;


           pui8MsgDataTx[7] = 0;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 3;
           break;


      case Q4_I_OUT:

           floatNchars.f = Q4ModuleIoutRead();  // Vin
           pui8MsgDataTx[0] = floatNchars.c[0];
           pui8MsgDataTx[1] = floatNchars.c[1];
           pui8MsgDataTx[2] = floatNchars.c[2];
           pui8MsgDataTx[3] = floatNchars.c[3];

           pui8MsgDataTx[4] = Q4ModuleTempIGBT1Read();
           pui8MsgDataTx[5] = Q4ModuleTempIGBT2Read();
           pui8MsgDataTx[6] = RhRead();
           pui8MsgDataTx[7] = 0;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 0;
           break;

      case Q4_TEMP:

           pui8MsgDataTx[0] = 0;
           pui8MsgDataTx[1] = 0;
           pui8MsgDataTx[2] = 0;
           pui8MsgDataTx[3] = 0;

           pui8MsgDataTx[4] = 0;
           // Alarm
           if(Q4ModuleIoutAlarmStsRead())      pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000001;
           if(Q4ModuleTempIGBT1AlarmStsRead()) pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000010;
           if(Q4ModuleTempIGBT2AlarmStsRead()) pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000100;
           if(RhAlarmStatusRead())             pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00001000;

           pui8MsgDataTx[5] = 0;
           // Interlock
           if(Q4ModuleIoutItlkStsRead())      pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000001;
           if(Q4ModuleTempIGBT1ItlkStsRead()) pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000010;
           if(Q4ModuleTempIGBT2ItlkStsRead()) pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000100;
           if(RhTripStatusRead())             pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00001000;

           pui8MsgDataTx[6] = 0;
           pui8MsgDataTx[7] = 0;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 1;
           break;

      case BUCK_I_IN:

           floatNchars.f = InputModuleIinRead();  // Iin
           pui8MsgDataTx[0] = floatNchars.c[0];
           pui8MsgDataTx[1] = floatNchars.c[1];
           pui8MsgDataTx[2] = floatNchars.c[2];
           pui8MsgDataTx[3] = floatNchars.c[3];

           floatNchars.f = InputModuleVdcLinkRead(); //  Vdc Link
           pui8MsgDataTx[4] = floatNchars.c[0];
           pui8MsgDataTx[5] = floatNchars.c[1];
           pui8MsgDataTx[6] = floatNchars.c[2];
           pui8MsgDataTx[7] = floatNchars.c[3];

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 0;
           break;

      case BUCK_TEMP:

           pui8MsgDataTx[0] = InputModuleTempHeatsinkRead();
           pui8MsgDataTx[1] = InputModuleTempLRead();

           pui8MsgDataTx[2] = 0;
           // Status
           //if(BuckModuleWaterFluxInterlockRead()) pui8MsgDataTx[2] = pui8MsgDataTx[2] | 0b00000001;
           //if(BuckModuleAcOverCurrentRead())      pui8MsgDataTx[2] = pui8MsgDataTx[2] | 0b00000010;

           pui8MsgDataTx[3] = 0;

           pui8MsgDataTx[4] = 0;
           pui8MsgDataTx[5] = 0;
           //Alarm
           if(InputModuleIinAlarmStsRead())           pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000001;
           if(InputModuleVdcLinkAlarmStsRead())       pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000010;
           if(InputModuleTempHeatsinkAlarmStsRead())  pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000100;
           if(InputModuleTempLAlarmStsRead())         pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00001000;
           //if(BuckModuleTempL1AlarmStsRead()) pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00010000;
           //if(BuckModuleTempL2AlarmStsRead()) pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00100000;
           if(RhAlarmStatusRead())            pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b01000000;


           pui8MsgDataTx[6] = 0;
           pui8MsgDataTx[7] = 0;
           //Interlock
           if(InputModuleIinItlkStsRead())            pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00000001;
           if(InputModuleVdcLinkItlkStsRead())        pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00000010;
           if(InputModuleTempHeatsinkItlkStsRead())   pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00000100;
           if(InputModuleTempLItlkStsRead())          pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00001000;
           //if(BuckModuleTempL1ItlkStsRead())         pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00010000;
           //if(BuckModuleTempL2ItlkStsRead())         pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b00100000;
           //if(BuckModuleWaterFluxInterlockStsRead()) pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b01000000;
           //if(BuckModuleAcOverCurrentStsRead())      pui8MsgDataTx[6] = pui8MsgDataTx[6] | 0b10000000;

           if(RhTripStatusRead())                    pui8MsgDataTx[7] = pui8MsgDataTx[7] | 0b00000001;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 3;
           break;

      case RECTF_I_OUT:

           floatNchars.f = RectifierIoutRectf1Read();
           pui8MsgDataTx[0] = floatNchars.c[0];
           pui8MsgDataTx[1] = floatNchars.c[1];
           pui8MsgDataTx[2] = floatNchars.c[2];
           pui8MsgDataTx[3] = floatNchars.c[3];

           floatNchars.f = RectifierIoutRectf2Read();
           pui8MsgDataTx[4] = floatNchars.c[0];
           pui8MsgDataTx[5] = floatNchars.c[1];
           pui8MsgDataTx[6] = floatNchars.c[2];
           pui8MsgDataTx[7] = floatNchars.c[3];

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 0;
           break;

      case RECTF_V_OUT:
           floatNchars.f = RectifierVoutRectf1Read();
           pui8MsgDataTx[0] = floatNchars.c[0];
           pui8MsgDataTx[1] = floatNchars.c[1];
           pui8MsgDataTx[2] = floatNchars.c[2];
           pui8MsgDataTx[3] = floatNchars.c[3];

           floatNchars.f = RectifierVoutRectf2Read();
           pui8MsgDataTx[4] = floatNchars.c[0];
           pui8MsgDataTx[5] = floatNchars.c[1];
           pui8MsgDataTx[6] = floatNchars.c[2];
           pui8MsgDataTx[7] = floatNchars.c[3];

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 1;
           break;

      case RECTF_I_LEAK:
           floatNchars.f = RectifierLeakageCurrentRead();
           pui8MsgDataTx[0] = floatNchars.c[0];
           pui8MsgDataTx[1] = floatNchars.c[1];
           pui8MsgDataTx[2] = floatNchars.c[2];
           pui8MsgDataTx[3] = floatNchars.c[3];

           pui8MsgDataTx[4] = 0;
           if(RectifierAcPhaseFaultRead())          pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000001;
           if(RectifierAcOverCurrentRead())         pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000010;
           if(RectifierAcTransformerOverTempRead()) pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000100;
           if(RectifierWaterFluxInterlockRead())    pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00001000;;

           pui8MsgDataTx[5] = 0;
           pui8MsgDataTx[6] = 0;
           pui8MsgDataTx[7] = 0;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 2;
           break;

      case RECTF_TEMP:

           pui8MsgDataTx[0] = RectifierTempHeatSinkRead();
           pui8MsgDataTx[1] = RectifierTempWaterRead();
           pui8MsgDataTx[2] = RectifierTempModule1Read();
           pui8MsgDataTx[3] = RectifierTempModule2Read();
           pui8MsgDataTx[4] = RectifierTempL1Read();
           pui8MsgDataTx[5] = RectifierTempL2Read();
           pui8MsgDataTx[6] = RhRead();
           pui8MsgDataTx[7] = 0;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 3;
           break;

      case RECTF_ALARM_ITLK_STS:
           //Alarm bytes
           pui8MsgDataTx[0] = 0;
           pui8MsgDataTx[1] = 0;

           if(RectifierIoutRectf1AlarmStsRead())     pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00000001;
           if(RectifierIoutRectf2AlarmStsRead())     pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00000010;
           if(RectifierVoutRectf1AlarmStsRead())     pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00000100;
           if(RectifierVoutRectf2AlarmStsRead())     pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00001000;
           if(RectifierLeakageCurrentAlarmStsread()) pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00010000;
           if(RectifierTempHeatSinkAlarmStsRead())   pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b00100000;
           if(RectifierTempWaterAlarmStsRead())      pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b01000000;
           if(RectifierTempModule1AlarmStsRead())    pui8MsgDataTx[0] = pui8MsgDataTx[0] | 0b10000000;

           if(RectifierTempModule2AlarmStsRead())    pui8MsgDataTx[1] = pui8MsgDataTx[1] | 0b00000001;
           if(RectifierTempL1AlarmStsRead())         pui8MsgDataTx[1] = pui8MsgDataTx[1] | 0b00000010;
           if(RectifierTempL2AlarmStsRead())         pui8MsgDataTx[1] = pui8MsgDataTx[1] | 0b00000100;
           if(RhAlarmStatusRead())                   pui8MsgDataTx[1] = pui8MsgDataTx[1] | 0b00001000;

           pui8MsgDataTx[2] = 0;
           pui8MsgDataTx[3] = 0;

           //Interlock bytes
           pui8MsgDataTx[4] = 0;
           pui8MsgDataTx[5] = 0;

           if(RectifierIoutRectf1ItlkStsRead())        pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000001;
           if(RectifierIoutRectf2ItlkStsRead())        pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000010;
           if(RectifierVoutRectf1ItlkStsRead())        pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00000100;
           if(RectifierVoutRectf2ItlkStsRead())        pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00001000;
           if(RectifierLeakageCurrentItlkStsRead())    pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00010000;
           if(RectifierTempHeatSinkItlkStsRead())      pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b00100000;
           if(RectifierTempWaterItlkStsRead())         pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b01000000;
           if(RectifierTempModule1ItlkStsRead())       pui8MsgDataTx[4] = pui8MsgDataTx[4] | 0b10000000;

           if(RectifierTempModule2ItlkStsRead())       pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000001;
           if(RectifierTempL1ItlkStsRead())            pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000010;
           if(RectifierTempL2ItlkStsRead())            pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00000100;
           if(RectifierAcPhaseFaultStsRead())          pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00001000;
           if(RectifierAcOverCurrentStsRead())         pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00010000;
           if(RectifierAcTransformerOverTempStsRead()) pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b00100000;
           if(RectifierWaterFluxInterlockStsRead())    pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b01000000;
           if(RhTripStatusRead())                      pui8MsgDataTx[5] = pui8MsgDataTx[5] | 0b10000000;

           pui8MsgDataTx[6] = 0;
           pui8MsgDataTx[7] = 0;

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 4;
           break;

      case ITLK_MESS:
           pui8MsgDataTx[0] = InterlockRead();

           sCANMessageTx.ui32MsgLen = 8;
           sCANMessageTx.ui32MsgID = CanId + 15;
           break;

    }

    CANMessageSet(CAN0_BASE, 2, &sCANMessageTx, MSG_OBJ_TYPE_TX);

}

void CheckCan(void)
{

    if(g_bRXFlag)
    {
        //
        // Reuse the same message object that was used earlier to configure
        // the CAN for receiving messages.  A buffer for storing the
        // received data must also be provided, so set the buffer pointer
        // within the message object.
        //
        sCANMessage.pui8MsgData = pui8MsgData;

        //
        // Read the message from the CAN.  Message object number 1 is used
        // (which is not the same thing as CAN ID).  The interrupt clearing
        // flag is not set because this interrupt was already cleared in
        // the interrupt handler.
        //
        CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);

        //
        // Clear the pending message flag so that the interrupt handler can
        // set it again when the next message arrives.
        //
        g_bRXFlag = 0;

        InterlockClear();

    }

}


//--------------------------------------------------------------------------
void InitCan(uint32_t ui32SysClock)
{

    // Configure the GPIO pin muxing to select CAN0 functions for these pins.
    GPIOPinConfigure(GPIO_PA0_CAN0RX);
    GPIOPinConfigure(GPIO_PA1_CAN0TX);

    // Enable the alternate function on the GPIO pins.  The above step selects
    GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // The GPIO port and pins have been set up for CAN.  The CAN peripheral
    // must be enabled.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

    //
    // Initialize the CAN controller
    //
    CANInit(CAN0_BASE);


    // Set up the bit rate for the CAN bus 1Mbps
    CANBitRateSet(CAN0_BASE, ui32SysClock, 1000000);
    //CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 1000000);
    //CANBitRateSet(CAN0_BASE, 8000000, 1000000);

    // Enable interrupts on the CAN peripheral.
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    CANIntRegister(CAN0_BASE, can_handler);

    IntPrioritySet(INT_CAN0, 1);

    //
    // Enable the CAN interrupt on the processor (NVIC).
    //
    IntEnable(INT_CAN0);

    //
    // Enable the CAN for operation.
    //
    CANEnable(CAN0_BASE);

    //
    // Initialize a message object to receive CAN messages with ID 0x200 (Interlock Clear)
    // The expected ID must be set along with the mask to indicate that all
    // bits in the ID must match.
    //
    sCANMessage.ui32MsgID = 0x200;
    sCANMessage.ui32MsgIDMask = 0x7FF;
    sCANMessage.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER | MSG_OBJ_FIFO);
    sCANMessage.ui32MsgLen = 8;

    //
    // Now load the message object into the CAN peripheral message object 1.
    // Once loaded the CAN will receive any messages with this CAN ID into
    // this message object, and an interrupt will occur.
    //
    CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);

    //
    // Initialize message object 2 to be able to send CAN message 1.  This
    // message object is not shared so it only needs to be initialized one
    // time, and can be used for repeatedly sending the same message ID.
    //
    sCANMessageTx.ui32MsgID = 0x000;
    sCANMessageTx.ui32MsgIDMask = 0;
    sCANMessageTx.ui32Flags = (MSG_OBJ_TX_INT_ENABLE | MSG_OBJ_FIFO);
    sCANMessageTx.ui32MsgLen = 8;
    sCANMessageTx.pui8MsgData = pui8MsgDataTx;


    // Module ID
    CanId = BoardAddressRead();
    CanId = 1;
    //CanId = CanId << 4;

}
//---------------------------------------------------------------------------

uint16_t CanIdRead(void)
{
    return CanId;
}
