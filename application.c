#include "application.h"
#include "adc_internal.h"
#include "BoardTempHum.h"
#include "pt100.h"
#include "output.h"
#include "leds.h"
#include "can_bus.h"
#include "input.h"
#include "can_bus.h"
#include "stdbool.h"
#include "stdint.h"
#include "fac_cmd.h"
#include "fac_is.h"
#include "fac_os.h"
#include "fap.h"
#include "fap_300A.h"
#include "rectifier_module.h"
#include "iib_module.h"


static unsigned char PowerModuleModel = 0;
static unsigned char Interlock = 0;
static unsigned char InterlockOld = 0;
static unsigned char ItlkClrCmd = 0;
static unsigned char InitApp = 0;
static unsigned char Alarm = 0;

void AppConfiguration(void)
{

    // Set Power Module Model
    // This parameter guide the firmware behavior
    // Each Model has a different variable list that need to be check

    PowerModuleModel = FAP;
    //PowerModuleModel = FAP_300A;
    //PowerModuleModel = FAC_OS;
    //PowerModuleModel = RECTIFIER_MODULE;
    //PowerModuleModel = FAC_IS;
    //PowerModuleModel = FAC_CMD_MODULE;
    
    switch(PowerModuleModel)
    {
        case FAP:

            init_fap();

            break;

        case FAC_OS:

            init_fac_os();

            break;
         
        case RECTIFIER_MODULE:

            init_rectifier_module();

            break;

        case FAC_IS:

            init_fac_is();

            break;

        case FAC_CMD_MODULE:

            init_fac_cmd();

            break;

        case FAP_300A:

            init_fap_300A();

            break;

        default:
            break;

    }
    // End of configuration
    // Turn on Led1 (board started)
    Led1TurnOff();
    Led2TurnOn();
    Led3TurnOn();
    Led4TurnOn();
    Led5TurnOn();
    Led6TurnOn();
    Led7TurnOn();
    Led8TurnOn();
    Led9TurnOn();
    Led10TurnOn();
}

// Set Interlock clear command
void InterlockClear(void)
{
    ItlkClrCmd = 1;
}

void InterlockSet(void)
{
    Interlock = 1;
}

void InterlockClearCheck(void)
{
      //if(ItlkClrCmd && Interlock)
      if(ItlkClrCmd)
      {
          Interlock = 0;
          InterlockOld = 0;

          InitApp = 0;

          AdcClearAlarmTrip();
          Pt100ClearAlarmTrip();
          RhTempClearAlarmTrip();
          
          ItlkClrCmd = 0;
          
          g_iib_module.clear_interlocks();
          g_iib_module.clear_alarms();

      }
}

unsigned char InterlockRead(void)
{
      return Interlock;
}

void AppInterlock(void)
{
      
      // caso haja algum Interlock, o rele auxiliar deve ser desligado e as operações cabiveis de Interlock devem ser executadas
      
      // Analisar se todos os interlocks foram apagados para poder liberar o rele auxiliar
      // caso não haja mais Interlock, fechar o rele auxiliar
      
      switch(PowerModuleModel)
      {
       case FAP:

            ReleAuxTurnOff();
            ReleItlkTurnOff();

            break;

       case FAC_OS:

            ReleAuxTurnOff();
            ReleItlkTurnOff();
            Gpdo1TurnOff();
            Gpdo2TurnOff();

            break;

       case RECTIFIER_MODULE:

            ReleAuxTurnOff();
            ReleItlkTurnOff();

            break;

       case FAC_IS:

            ReleAuxTurnOff();
            ReleItlkTurnOff();

            break;

       case FAC_CMD_MODULE:

           ReleAuxTurnOff();
           ReleItlkTurnOff();

           break;

       case FAP_300A:

           ReleAuxTurnOff();
           ReleItlkTurnOff();

           break;

       default:
           break;

      }
      
}


void AlarmSet(void)
{
      Alarm = 1;
}

void AlarmClear(void)
{
      Alarm = 0;
}

unsigned char AlarmRead(void)
{
      return Alarm;
}

void AppAlarm(void)
{

}

void InterlockAppCheck(void)
{
   unsigned char test = 0;

   test = g_iib_module.check_interlocks();

   test |= RhTripStatusRead();

   test |= DriverVolatgeTripStatusRead();
   test |= Driver1CurrentTripStatusRead();
   test |= Driver2CurrentTripStatusRead();

   if(test) {

       InterlockSet();

       g_iib_module.send_itlk_msg();

   }

}

void AlarmAppCheck(void)
{
   unsigned char test = 0;
   
   test = g_iib_module.check_alarms();

   test |= RhAlarmStatusRead();


   if(test) {
       AlarmSet();
       send_data_message(1);
   }
}



void LedIndicationStatus(void)
{
    g_iib_module.check_indication_leds();
}

void Application(void)
{

    g_iib_module.application_readings();

    // Interlock Test
    if(Interlock == 1 && InterlockOld == 0)
    {
          InterlockOld = 1;
          AppInterlock();
    }

    // Actions that needs to be taken during the Application initialization
    if(InitApp == 0 && Interlock == 0)
    {
          InitApp = 1;

          switch(PowerModuleModel)
          {
           case FAP:
                ReleAuxTurnOn();
                ReleItlkTurnOff();
                break;

           case FAC_OS:
                ReleAuxTurnOn();
                ReleItlkTurnOn();

                Gpdo1TurnOn();
                Gpdo2TurnOn();

                break;

           case RECTIFIER_MODULE:
                ReleAuxTurnOn();
                ReleItlkTurnOn();
                break;

           case FAC_IS:
                ReleAuxTurnOn();
                ReleItlkTurnOn();
                break;

           case FAC_CMD_MODULE:
               ReleAuxTurnOn();
               ReleItlkTurnOn();
               break;

           case FAP_300A:
               ReleAuxTurnOn();
               ReleItlkTurnOff();
               break;

           default:
               break;
          }
    }

    InterlockClearCheck();
}

void send_data_schedule()
{
    g_iib_module.send_data();
}

void power_on_check()
{
    g_iib_module.power_on_check();

}

// Application type
//******************************************************************************
unsigned char AppType(void)
{
    return PowerModuleModel;
}
