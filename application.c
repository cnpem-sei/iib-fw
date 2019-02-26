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

    //PowerModuleModel = OUTPUT_FAP_MODULE;
    //PowerModuleModel = FAP_300A;
    //PowerModuleModel = OUTPUT_Q4_MODULE;
    //PowerModuleModel = RECTIFIER_MODULE;
    //PowerModuleModel = INPUT_MODULE;
    PowerModuleModel = FAC_CMD_MODULE;
    
    switch(PowerModuleModel)
    {
        case OUTPUT_FAP_MODULE:

            init_fap();

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

        case FAC_CMD_MODULE:

            init_fac_cmd();

            break;

        case OUTPUT_FAP_300A_MODULE:

            init_fap_300A();

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
              case OUTPUT_FAP_MODULE:

                  clear_fap_interlocks();
                  clear_fap_alarms();

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

              case FAC_CMD_MODULE:

                  clear_fac_cmd_interlocks();
                  clear_fac_cmd_alarms();

                  break;

              case OUTPUT_FAP_300A_MODULE:

                  clear_fap_300A_interlocks();
                  clear_fap_300A_alarms();

                  break;

              default:
                  break;
          }
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
       case OUTPUT_FAP_MODULE:

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

       case FAC_CMD_MODULE:

           ReleAuxTurnOff();
           ReleItlkTurnOff();

           break;

       case OUTPUT_FAP_300A_MODULE:

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
       case OUTPUT_FAP_MODULE:

           test = check_fap_interlocks();

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

       case FAC_CMD_MODULE:

           test = check_fac_cmd_interlocks();

           break;

       case OUTPUT_FAP_300A_MODULE:

           test = check_fap_300A_interlocks();

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

       switch (PowerModuleModel)
       {
           case OUTPUT_FAP_MODULE:
               send_output_fap_itlk_msg();
               break;

           case OUTPUT_Q4_MODULE:
               send_output_q4_itlk_msg();
               break;

           case RECTIFIER_MODULE:
               send_rectf_itlk_msg();
               break;

           case INPUT_MODULE:
               send_input_itlk_msg();
               break;

           case FAC_CMD_MODULE:
               send_fac_cmd_itlk_msg();
               break;

           case OUTPUT_FAP_300A_MODULE:
               send_output_fap_300A_itlk_msg();
               break;

           default:
               break;
       }
   }

}

void AlarmAppCheck(void)
{
   unsigned char test = 0;
   
   switch(PowerModuleModel)
   {
       case OUTPUT_FAP_MODULE:

           test = check_fap_alarms();

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

       case FAC_CMD_MODULE:

           test = check_fac_cmd_alarms();

           break;

       case OUTPUT_FAP_300A_MODULE:

           test = check_fap_300A_alarms();

           break;

       default:
           break;
   }

   test |= RhAlarmStatusRead();


   if(test) {
       AlarmSet();
       send_data_message(1);
   }
}



void LedIndicationStatus(void)
{
    switch(PowerModuleModel)
    {
        case OUTPUT_FAP_MODULE:

           check_fap_indication_leds();

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

        case FAC_CMD_MODULE:

            check_fac_cmd_indication_leds();

            break;

        case OUTPUT_FAP_300A_MODULE:

            check_fap_300A_indication_leds();

            break;

        default:
            break;
      }
      
}

void Application(void)
{

    switch(PowerModuleModel)
    {
        case OUTPUT_FAP_MODULE:

            fap_application_readings();

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

       case FAC_CMD_MODULE:

           fac_cmd_application_readings();

           break;

       case OUTPUT_FAP_300A_MODULE:

           fap_300A_application_readings();

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
             case OUTPUT_FAP_MODULE:
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

             case FAC_CMD_MODULE:
                 ReleAuxTurnOn();
                 ReleItlkTurnOn();
                 break;

             case OUTPUT_FAP_300A_MODULE:
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
        case OUTPUT_FAP_MODULE:
            send_fap_data();
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

        case FAC_CMD_MODULE:
            send_fac_cmd_data();
            break;

        case OUTPUT_FAP_300A_MODULE:
            send_fap_300A_data();
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
