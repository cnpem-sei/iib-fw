#include "adc_internal.h"
#include "application.h"

#include "BoardTempHum.h"
#include "pt100.h"
#include "output.h"
//#include "rs485.h"
#include "leds.h"
#include "can_bus.h"
#include "input.h"
#include "can_bus.h"

#include "stdbool.h"
#include "stdint.h"

static unsigned char PowerModuleModel = 0;
static unsigned char Interlock = 0;
static unsigned char InterlockOld = 0;
static unsigned char ItlkClrCmd = 0;
static unsigned char InitApp = 0;
static unsigned char InitAppOld = 0;
static unsigned char Alarm = 0;

void AppConfiguration(void)
{

    // Set Power Module Model
    // This parameter guide the firmware behavior
    // Each Model has a different variable list that need to be check

    PowerModuleModel = OUTPUT_Q1_MODULE;
    //PowerModuleModel = OUTPUT_Q1_300A_MODULE;
    //PowerModuleModel = OUTPUT_Q4_MODULE;
    //PowerModuleModel = RECTIFIER_MODULE;
    //PowerModuleModel = INPUT_MODULE;
    //PowerModuleModel = COMMAND_DRAWER_MODULE;
    
    switch(PowerModuleModel)
    {
        case OUTPUT_Q1_MODULE:

            init_q1_module();

            break;

        case OUTPUT_Q4_MODULE:

            init_q4_module();

            break;
         
        case RECTIFIER_MODULE:

            init_rectifier_module();

            break;

        case INPUT_MODULE:

            init_input_module();

            break;

        case COMMAND_DRAWER_MODULE:

            init_command_module();

            break;

        case OUTPUT_Q1_300A_MODULE:

            init_q1_300A_module();

            break;

        default:
            break;

    }
    // End of configuration
    // Turn on Led1 (board started)
    Led1TurnOn();

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
          InitAppOld = 0;

          AdcClearAlarmTrip();
          Pt100ClearAlarmTrip();
          RhTempClearAlarmTrip();
          
          ItlkClrCmd = 0;
          
          switch(PowerModuleModel)
          {
              case OUTPUT_Q1_MODULE:

                  clear_q1_interlocks();
                  clear_q1_alarms();

                  break;

              case OUTPUT_Q4_MODULE:

                  clear_q4_interlocks();
                  clear_q4_alarms();

                  break;

              case RECTIFIER_MODULE:

                  clear_rectifier_interlocks();
                  clear_rectifier_alarms();

                  break;
               
              case INPUT_MODULE:

                  clear_input_module_interlocks();
                  clear_input_module_alarms();

                  break;

              case COMMAND_DRAWER_MODULE:

                  clear_command_module_interlocks();
                  clear_command_module_alarms();

                  break;

              case OUTPUT_Q1_300A_MODULE:

                  clear_q1_300A_interlocks();
                  clear_q1_300A_alarms();

                  break;

              default:
                  break;
          }
          
          g_itlk_id = 0;
          g_alarm_id = 0;
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
       case OUTPUT_Q1_MODULE:

            ReleAuxTurnOff();
            ReleItlkTurnOff();

            break;

       case OUTPUT_Q4_MODULE:

            ReleAuxTurnOff();
            ReleItlkTurnOff();
            Gpdo1TurnOff();
            Gpdo2TurnOff();

            break;

       case RECTIFIER_MODULE:

            ReleAuxTurnOff();
            ReleItlkTurnOff();

            break;

       case INPUT_MODULE:

            ReleAuxTurnOff();
            ReleItlkTurnOff();

            break;

       case COMMAND_DRAWER_MODULE:

           ReleAuxTurnOff();
           ReleItlkTurnOff();

           break;

       case OUTPUT_Q1_300A_MODULE:

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

   switch(PowerModuleModel)
   {
       case OUTPUT_Q1_MODULE:

           test = check_q1_interlocks();

           break;
       
       case OUTPUT_Q4_MODULE:

           test = check_q4_interlocks();

           break;
       
       case RECTIFIER_MODULE:

           test = check_rectifier_interlocks();

           break;
       
       case INPUT_MODULE:

           test = check_input_module_interlocks();

           break;

       case COMMAND_DRAWER_MODULE:

           test = check_command_module_interlocks();

           break;

       case OUTPUT_Q1_300A_MODULE:

           test = check_q1_300A_interlocks();

           break;

       default:
           break;
   }

   test |= RhTripStatusRead();

   test |= DriverVolatgeTripStatusRead();
   test |= Driver1CurrentTripStatusRead();
   test |= Driver2CurrentTripStatusRead();

   if(test) {

       InterlockSet();
       send_interlock_message();
   }

}

void AlarmAppCheck(void)
{
   unsigned char test = 0;
   
   switch(PowerModuleModel)
   {
       case OUTPUT_Q1_MODULE:

           test = check_q1_alarms();

           break;

       case OUTPUT_Q4_MODULE:

           test = check_q4_alarms();

           break;

       case RECTIFIER_MODULE:

           test = check_rectifier_alarms();

           break;

       case INPUT_MODULE:

           test = check_input_module_alarms();

           break;

       case COMMAND_DRAWER_MODULE:

           test = check_command_module_alarms();

           break;

       case OUTPUT_Q1_300A_MODULE:

           test = check_q1_300A_alarms();

           break;

       default:
           break;
   }

   test |= RhAlarmStatusRead();


   if(test) {
       AlarmSet();
       send_alarm_message();
   }
}



void LedIndicationStatus(void)
{
    switch(PowerModuleModel)
    {
        case OUTPUT_Q1_MODULE:

           check_q1_indication_leds();

           break;

        case OUTPUT_Q4_MODULE:

           check_q4_indications_leds();

           break;

        case RECTIFIER_MODULE:

            check_rectifier_indication_leds();
            
            break;

        case INPUT_MODULE:

            check_input_module_indication_leds();

            break;

        case COMMAND_DRAWER_MODULE:

            check_command_module_indication_leds();

            break;

        case OUTPUT_Q1_300A_MODULE:

            check_q1_300A_indication_leds();

            break;

        default:
            break;
      }
      
}

void Application(void)
{

    switch(PowerModuleModel)
    {
        case OUTPUT_Q1_MODULE:

            q1_application_readings();

            break;
       
        case OUTPUT_Q4_MODULE:

            q4_application_readings();

            break;
            
        case RECTIFIER_MODULE:
            
            rectifier_application_readings();
            
            break;
            
       case INPUT_MODULE:

           input_module_application_readings();

           break;

       case COMMAND_DRAWER_MODULE:

           command_module_application_readings();

           break;

       case OUTPUT_Q1_300A_MODULE:

           q1_300A_application_readings();

           break;

       default:
           break;
      }

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
             case OUTPUT_Q1_MODULE:
                  ReleAuxTurnOn();
                  ReleItlkTurnOn();
                  break;

             case OUTPUT_Q4_MODULE:
                  ReleAuxTurnOn();
                  ReleItlkTurnOn();

                  Gpdo1TurnOn();
                  Gpdo2TurnOn();

                  break;

             case RECTIFIER_MODULE:
                  ReleAuxTurnOn();
                  ReleItlkTurnOn();
                  break;

             case INPUT_MODULE:
                  ReleAuxTurnOn();
                  ReleItlkTurnOn();
                  break;

             case COMMAND_DRAWER_MODULE:
                 ReleAuxTurnOn();
                 ReleItlkTurnOn();
                 break;

             case OUTPUT_Q1_300A_MODULE:
                 ReleAuxTurnOn();
                 ReleItlkTurnOn();
                 break;

             default:
                 break;
            }
      }

      InterlockClearCheck();
}

void send_data_schedule()
{
    switch(AppType())
    {
        case OUTPUT_Q1_MODULE:
            send_q1_module_data();
            break;

        case OUTPUT_Q4_MODULE:
            send_q4_module_data();
            break;

        case RECTIFIER_MODULE:
            send_rectifier_module_data();
            break;

        case INPUT_MODULE:
            send_input_module_data();
            break;

        case COMMAND_DRAWER_MODULE:
            send_command_module_data();
            break;

        case OUTPUT_Q1_300A_MODULE:
            send_q1_300A_module_data();
            break;

        default:
            break;
    }
}

// Application type
//******************************************************************************
unsigned char AppType(void)
{
    return PowerModuleModel;
}
