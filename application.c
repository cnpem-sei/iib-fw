
#include "adc_internal.h"
#include "application.h"

#include "BoardTempHum.h"
#include "pt100.h"
#include "output.h"
//#include "rs485.h"
#include "leds.h"
#include "can_bus.h"
#include "input.h"

#include "stdbool.h"
#include "stdint.h"


typedef struct
{
    float Vin;
    bool VinAlarmSts;
    bool VinItlkSts;
    float Vout;
    bool VoutAlarmSts;
    bool VoutItlkSts;
    float IoutA1;
    bool IoutA1AlarmSts;
    bool IoutA1ItlkSts;
    float IoutA2;
    bool IoutA2AlarmSts;
    bool IoutA2ItlkSts;
    uint8_t TempIGBT1;
    bool TempIGBT1AlarmSts;
    bool TempIGBT1ItlkSts;
    bool TempIGBT1HwrItlk;
    bool TempIGBT1HwrItlkSts;
    uint8_t TempIGBT2;
    bool TempIGBT2AlarmSts;
    bool TempIGBT2ItlkSts;
    bool TempIGBT2HwrItlk;
    bool TempIGBT2HwrItlkSts;
    float DriveVoltage;
    float Drive1Current;
    float Drive2Current;
    bool Driver1Error;
    bool Driver1ErrorItlk;
    bool Driver2Error;
    bool Driver2ErrorItlk;
    uint8_t TempL;
    bool TempLAlarmSts;
    bool TempLItlkSts;
    uint8_t TempHeatSink;
    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    bool Relay;
    bool ExternalItlk;
    bool ExternalItlkSts;
    bool LeakageCurrent;
    bool LeakageCurrentSts;
    bool Rack;
    bool RackSts;
} Q1Module_t;


/*
*PT100
- PT100CH1: Temperatura do dissipador, interlocar em 50ºC;
- PT100CH2: Temperatura do indutor, interlocar em 60ºC;

*Leitura de Tensão via LV20-P
- LCH1: Tensão do DC-link, relação 330V/25mA, interlocar em 300V;

*Leitura de corrente por sensor hall
- ICH1: Corrente de entrada, relação 300A/150mA, interlocar em 250A;
- ICH2: Corrente de saída, relação 500A/100mA, interlocar em 510A;
*/


typedef struct
{
    float Iin;
    bool IinAlarmSts;
    bool IinItlkSts;
    float Iout;
    bool IoutAlarmSts;
    bool IoutItlkSts;
    float VdcLink;
    bool VdcLinkAlarmSts;
    bool VdcLinkItlkSts;
    uint8_t TempIGBT1;
    bool TempIGBT1AlarmSts;
    bool TempIGBT1ItlkSts;
    bool TempIGBT1HwrItlk;
    bool TempIGBT1HwrItlkSts;
    uint8_t TempIGBT2;
    bool TempIGBT2AlarmSts;
    bool TempIGBT2ItlkSts;
    bool TempIGBT2HwrItlk;
    bool TempIGBT2HwrItlkSts;
    uint8_t TempL;
    bool TempLAlarmSts;
    bool TempLItlkSts;
    uint8_t TempHeatSink;
    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    bool Driver1Error;
    bool Driver1ErrorItlk;
    bool Driver2Error;
    bool Driver2ErrorItlk;

} Q4Module_t;


//- PT100 CH1: interlockar ao passar de 100ºC                                                                Indutor 1
//- PT100 CH2: interlockar ao passar de 100ºC                                                                Indutor 2
//- Hall Sensor 1: Sensor hall de 300A/150mA, interlockar em 170A                                            Corrente de Entrada 1
//- Hall Sensor 2: Sensor hall de 300A/150mA, interlockar em 170A                                            Corrente de Entrada 2
//- Hall Sensor 3: Sensor hall de 300A/150mA, interlockar em 200A                                            Corrente de Saída 1
//- Hall Sensor 4: Sensor hall de 300A/150mA, interlockar em 200A                                            Corrente de Saída 2
//- Voltage Input CH1: Interlockar acima de 5V                                                               Tensão de Saída 1
//- Voltage Input CH2: Interlockar acima de 5V                                                               Tensão de Saída 2
//- Digital Input CH1: Acionar interlock quando em nível lógico baixo                                        Interlock Externo

typedef struct
{

    float Iin;
    bool IinAlarmSts;
    bool IinItlkSts;
    float VdcLink;
    bool VdcLinkAlarmSts;
    bool VdcLinkItlkSts;
    uint8_t TempHeatsink;
    bool TempHeatsinkAlarmSts;
    bool TempHeatsinkItlkSts;
    uint8_t TempL;
    bool TempLAlarmSts;
    bool TempLItlkSts;
    bool Driver1Error;
    bool Driver1ErrorItlk;
    bool Driver2Error;
    bool Driver2ErrorItlk;

} InputModule_t;

typedef struct
{
    float IoutRectf1;
    bool IoutRectf1AlarmSts;
    bool IoutRectf1ItlkSts;
    float IoutRectf2;
    bool IoutRectf2AlarmSts;
    bool IoutRectf2ItlkSts;
    float VoutRectf1;
    bool VoutRectf1AlarmSts;
    bool VoutRectf1ItlkSts;
    float VoutRectf2;
    bool VoutRectf2AlarmSts;
    bool VoutRectf2ItlkSts;
    float LeakageCurrent;
    bool LeakageCurrentAlarmSts;
    bool LeakageCurrentItlkSts;
    uint8_t TempHeatSink;
    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    uint8_t TempWater;
    bool TempWaterAlarmSts;
    bool TempWaterItlkSts;
    uint8_t TempModule1;
    bool TempModule1AlarmSts;
    bool TempModule1ItlkSts;
    uint8_t TempModule2;
    bool TempModule2AlarmSts;
    bool TempModule2ItlkSts;
    uint8_t TempL1;
    bool TempL1AlarmSts;
    bool TempL1ItlkSts;
    uint8_t TempL2;
    bool TempL2AlarmSts;
    bool TempL2ItlkSts;
    bool AcPhaseFault;
    bool AcPhaseFaultSts;
    bool AcOverCurrent;
    bool AcOverCurrentSts;
    bool AcTransformerOverTemp;
    bool AcTransformerOverTempSts;
    bool WaterFluxInterlock;
    bool WaterFluxInterlockSts;

} RectifierModule_t;

typedef struct
{
    /* PT100CH1 */
    uint8_t TempHeatSink;
    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;
    /* PT100CH2 */
    uint8_t TempL;
    bool TempLAlarmSts;
    bool TempLItlkSts;
    /* LCH1 */
    float VcapBank;
    bool VcapBankAlarmSts;
    bool VcapBankItlkSts;
    /* LCH2 */
    float Vout;
    bool VoutAlarmSts;
    bool VoutItlkSts;
    /* GPDIO1 */
    bool ExtItlkSts;
    /* GPDI05*/
    bool ExtItlk2Sts;

} CommandDrawerModule_t;

static Q1Module_t               Q1Module;
static Q4Module_t               Q4Module;
static InputModule_t            InputModule;
static RectifierModule_t        Rectifier;
static CommandDrawerModule_t    CommandDrawer;

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

    //PowerModuleModel = OUTPUT_Q1_MODULE;
    PowerModuleModel = OUTPUT_Q4_MODULE;
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
            //Setar ranges de entrada
            VoltageCh1Init(330.0, 3);                 // Capacitors Voltage Configuration.
            VoltageCh2Init(250.0, 3);                 // Output Voltage Configuration.

            ConfigVoltCh1AsNtc(0);                 // Config Voltage Ch1 as a voltage input
            ConfigVoltCh2AsNtc(0);                 // Config Voltage Ch2 as a voltage input

            //Setar limites
            VoltageCh1AlarmLevelSet(250.0);           // Rectifier1 Voltage Alarm
            VoltageCh1TripLevelSet(300.0);            // Rectifier1 Voltage Trip
            VoltageCh2AlarmLevelSet(180.0);           // Rectifier2 Voltage Alarm
            VoltageCh2TripLevelSet(210.0);            // Rectifier2 Voltage Trip

            // PT100 configuration limits
            Pt100SetCh1AlarmLevel(55);            // HEATSINK TEMPERATURE ALARM LEVEL
            Pt100SetCh1TripLevel(60);             // HEATSINK TEMPERATURE TRIP LEVEL
            Pt100SetCh2AlarmLevel(55);            // INDUCTOR TEMPERATURE ALARM LEVEL
            Pt100SetCh2TripLevel(60);             // INDUCTOR TEMPERATURE TRIP LEVEL
            // PT100 channel enable
            Pt100Ch1Enable();                     // HEATSINK TEMPERATURE CHANNEL ENABLE
            Pt100Ch2Enable();                     // INDUCTOR TEMPERATURE CHANNEL ENABLE
            Pt100Ch3Disable();
            Pt100Ch4Disable();

            // Delay 4 seconds
            Pt100SetCh1Delay(4);
            // Delay 4 seconds
            Pt100SetCh2Delay(4);
            // Delay 4 seconds
            Pt100SetCh3Delay(4);
            // Delay 4 seconds
            Pt100SetCh4Delay(4);

            CommandDrawer.VcapBank                 = 0.0;
            CommandDrawer.VcapBankAlarmSts         = 0;
            CommandDrawer.VcapBankItlkSts          = 0;

            CommandDrawer.Vout                     = 0.0;
            CommandDrawer.VoutAlarmSts             = 0;
            CommandDrawer.VoutItlkSts              = 0;

            CommandDrawer.TempHeatSink             = 0;
            CommandDrawer.TempHeatSinkAlarmSts     = 0;
            CommandDrawer.TempHeatSinkItlkSts      = 0;

            CommandDrawer.TempL                    = 0;
            CommandDrawer.TempLAlarmSts            = 0;
            CommandDrawer.TempLItlkSts             = 0;

            CommandDrawer.ExtItlkSts               = 0;

            CommandDrawer.ExtItlk2Sts              = 0;
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

                  CommandDrawer.VcapBankAlarmSts        = 0;
                  CommandDrawer.VcapBankItlkSts         = 0;
                  CommandDrawer.VoutAlarmSts            = 0;
                  CommandDrawer.VoutItlkSts             = 0;
                  CommandDrawer.TempHeatSinkAlarmSts    = 0;
                  CommandDrawer.TempHeatSinkItlkSts     = 0;
                  CommandDrawer.TempLAlarmSts           = 0;
                  CommandDrawer.TempLItlkSts            = 0;
                  CommandDrawer.ExtItlkSts              = 0;
                  CommandDrawer.ExtItlk2Sts             = 0;

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

           test |= CommandDrawer.TempHeatSinkItlkSts;
           test |= CommandDrawer.TempLItlkSts;
           test |= CommandDrawer.VcapBankItlkSts;
           test |= CommandDrawer.VoutItlkSts;
           test |= CommandDrawer.ExtItlkSts;
           test |= CommandDrawer.ExtItlk2Sts;
           break;
   }

   test |= RhTripStatusRead();

   test |= DriverVolatgeTripStatusRead();
   test |= Driver1CurrentTripStatusRead();
   test |= Driver2CurrentTripStatusRead();

   if(test) InterlockSet();

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
           test |= CommandDrawer.TempHeatSinkAlarmSts;
           test |= CommandDrawer.TempLAlarmSts;
           test |= CommandDrawer.VcapBankAlarmSts;
           test |= CommandDrawer.VoutAlarmSts;
   }

   test |= RhAlarmStatusRead();


   if(test) AlarmSet();
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
            if (CommandDrawer.VcapBankItlkSts) Led2TurnOn();
            else if (CommandDrawer.VcapBankAlarmSts) Led2Toggle();
            else Led2TurnOff();

            if (CommandDrawer.VoutItlkSts) Led3TurnOn();
            else if (CommandDrawer.VoutAlarmSts) Led3Toggle();
            else Led3TurnOff();

            if (CommandDrawer.TempHeatSinkItlkSts) Led4TurnOn();
            else if (CommandDrawer.TempHeatSinkAlarmSts) Led4Toggle();
            else Led4TurnOff();

            if (CommandDrawer.TempLItlkSts) Led5TurnOn();
            else if (CommandDrawer.TempLAlarmSts) Led5TurnOff();
            else Led5TurnOff();

            if (CommandDrawer.ExtItlkSts) Led6TurnOn();
            else Led6TurnOff();

            if (CommandDrawer.ExtItlk2Sts) Led7TurnOn();
            else Led7TurnOff();

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
           CommandDrawer.TempHeatSink = Pt100ReadCh1();
           CommandDrawer.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
           if (!CommandDrawer.TempHeatSinkItlkSts) CommandDrawer.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();

           CommandDrawer.TempL = Pt100ReadCh2();
           CommandDrawer.TempLAlarmSts = Pt100ReadCh2AlarmSts();
           if (!CommandDrawer.TempLItlkSts) CommandDrawer.TempLItlkSts          = Pt100ReadCh2TripSts();

           CommandDrawer.VcapBank = VoltageCh1Read();
           CommandDrawer.VcapBankAlarmSts = VoltageCh1AlarmStatusRead();
           if (!CommandDrawer.VcapBankItlkSts) CommandDrawer.VcapBankItlkSts    = VoltageCh1TripStatusRead();

           CommandDrawer.Vout = VoltageCh2Read();
           CommandDrawer.VoutAlarmSts = VoltageCh2AlarmStatusRead();
           if (!CommandDrawer.VoutItlkSts) CommandDrawer.VoutItlkSts            = VoltageCh2TripStatusRead();

           if(!CommandDrawer.ExtItlkSts) CommandDrawer.ExtItlkSts               = Gpdi1Read();

           if(!CommandDrawer.ExtItlk2Sts) CommandDrawer.ExtItlk2Sts             = Gpdi5Read();

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
            }
      }

      InterlockClearCheck();
      CheckCan();

}

// Application type
//******************************************************************************
unsigned char AppType(void)
{
    return PowerModuleModel;
}

//******************************************************************************
/* Command Drawer */
unsigned char CommandDrawerTempHeatSinkRead(void)
{
    return CommandDrawer.TempHeatSink;
}

unsigned char CommandDrawerTempHeatSinkAlarmStsRead(void)
{
    return CommandDrawer.TempHeatSinkAlarmSts;
}

unsigned char CommandDrawerTempHeatSinkItlkStsRead(void)
{
    return CommandDrawer.TempHeatSinkItlkSts;
}

//******************************************************************************
unsigned char CommandDrawerTempLRead(void)
{
    return CommandDrawer.TempL;
}

unsigned char CommandDrawerTempLAlarmStsRead(void)
{
    return CommandDrawer.TempLAlarmSts;
}

unsigned char CommandDrawerTempLItlkStsRead(void)
{
    return CommandDrawer.TempLItlkSts;
}

//******************************************************************************

float CommandDrawerVcapBankRead(void)
{
    return CommandDrawer.VcapBank;
}

unsigned char CommandDrawerVcapBankAlarmStsRead(void)
{
    return CommandDrawer.VcapBankAlarmSts;
}

unsigned char CommandDrawerVcapBankItlkStsRead(void)
{
    return CommandDrawer.VcapBankItlkSts;
}

//******************************************************************************
float CommandDrawerVoutRead(void)
{
    return CommandDrawer.Vout;
}

unsigned char CommandDrawerVoutAlarmStsRead(void)
{
    return CommandDrawer.VoutAlarmSts;
}

unsigned char CommandDrawerVoutItlkStsRead(void)
{
    return CommandDrawer.VoutItlkSts;
}

unsigned char CommandDrawerExtItlkStsRead()
{
    return CommandDrawer.ExtItlkSts;
}

unsigned char CommandDrawerExt2ItlkStsRead()
{
    return CommandDrawer.ExtItlk2Sts;
}
