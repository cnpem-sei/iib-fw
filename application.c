
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
    // Each Model has a diferent variable list that need to be check
    
    //PowerModuleModel = OUTPUT_Q1_MODULE;
    //PowerModuleModel = OUTPUT_Q4_MODULE;
    //PowerModuleModel = RECTIFIER_MODULE;
    //PowerModuleModel = INPUT_MODULE;
    PowerModuleModel = COMMAND_DRAWER_MODULE;
    
    switch(PowerModuleModel)
    {
    case OUTPUT_Q1_MODULE:
         //Set current range
         CurrentCh1Init(130.0, 0.130, 50.0, 3); // Corrente braço1: Sensor Hall
         CurrentCh2Init(130.0, 0.130, 50.0, 3); // Corrente braço2: LEM LA 130-P

         //Set protection limits
         CurrentCh1AlarmLevelSet(115.0); // Corrente braço1
         CurrentCh1TripLevelSet(120.0);  // Corrente braço1
         CurrentCh2AlarmLevelSet(115.0); // Corrente braço2
         CurrentCh2TripLevelSet(120.0);  // Corrente braço2
         
         // NTC contiguration type
         //ConfigNtcType(SEMIX);
         
         //Leitura de tensão isolada
         LvCurrentCh1Init(450.0, 0.025, 120.0, 3); // Tensão de entrada
         LvCurrentCh2Init(250.0, 0.025, 120.0, 3); // Tensão de saída

         LvCurrentCh1AlarmLevelSet(415.0); // Tensão de entrada Alarme
         LvCurrentCh1TripLevelSet(420.0);  // Tensão de entrada Interlock
         LvCurrentCh2AlarmLevelSet(230.0); // Tensão de saída Alarme
         LvCurrentCh2TripLevelSet(235.0);  // Tensão de saída Interlock

         
         // PT100 configuration limits
         Pt100SetCh1AlarmLevel(70); // Temperatura Dissipador
         Pt100SetCh1TripLevel(80);  // Temperatura Dissipador
         Pt100SetCh2AlarmLevel(45); // Temperatura L
         Pt100SetCh2TripLevel(50);  // Temperatura L
         
         // Delay 4 seconds
         Pt100SetCh1Delay(4);
         // Delay 4 seconds
         Pt100SetCh2Delay(4);

         // PT100 channel enable
         Pt100Ch1Enable(); // Temperatura Dissipador
         Pt100Ch2Enable(); // Temperatura L
         Pt100Ch3Disable();
         Pt100Ch4Disable();

         // Rh configuration limits
         RhAlarmLimitSet(80);
         RhTripLimitSet(90);
         
         // Temp board configuration limits
         TempBoardAlarmLimitSet(80);
         TempBoardTripLimitSet(90);

         Driver1ErrEnable();
         Driver2ErrEnable();
         
         // Init Variables
         Q1Module.Vin = 0.0;
         Q1Module.VinAlarmSts = 0;
         Q1Module.VinItlkSts = 0;
         Q1Module.Vout = 0.0;
         Q1Module.VoutAlarmSts = 0;
         Q1Module.VoutItlkSts = 0;
         Q1Module.IoutA1 = 0.0;
         Q1Module.IoutA1AlarmSts = 0;
         Q1Module.IoutA1ItlkSts = 0;
         Q1Module.IoutA2 = 0.0;
         Q1Module.IoutA2AlarmSts = 0;
         Q1Module.IoutA2ItlkSts = 0;
         Q1Module.TempIGBT1 = 0.0;
         Q1Module.TempIGBT1AlarmSts = 0;
         Q1Module.TempIGBT1ItlkSts = 0;
         Q1Module.TempIGBT1HwrItlk = 0;
         Q1Module.TempIGBT1HwrItlkSts = 0;
         Q1Module.TempIGBT2 = 0.0;
         Q1Module.TempIGBT2AlarmSts = 0;
         Q1Module.TempIGBT2ItlkSts = 0;
         Q1Module.TempIGBT2HwrItlk = 0;
         Q1Module.TempIGBT2HwrItlkSts = 0;
         Q1Module.DriveVoltage  = 0.0;
         Q1Module.Drive1Current = 0.0;
         Q1Module.Drive2Current = 0.0;
         Q1Module.Driver1Error  = 0;
         Q1Module.Driver1ErrorItlk = 0;
         Q1Module.Driver2Error = 0;
         Q1Module.Driver2ErrorItlk = 0;
         Q1Module.TempL = 0;
         Q1Module.TempLAlarmSts = 0;
         Q1Module.TempLItlkSts = 0;
         Q1Module.TempHeatSink = 0;
         Q1Module.TempHeatSinkAlarmSts = 0;
         Q1Module.TempHeatSinkItlkSts = 0;
         Q1Module.Relay = 0;
         Q1Module.ExternalItlk = 0;
         Q1Module.ExternalItlkSts = 0;
         Q1Module.LeakageCurrent = 0;
         Q1Module.LeakageCurrentSts = 0;
         Q1Module.Rack = 0;
         Q1Module.RackSts = 0;

         break;
    case OUTPUT_Q4_MODULE:

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

         //Set current range
         CurrentCh1Init(300.0, 0.150, 50.0, 0); //Corrente de entrada
         CurrentCh2Init(500.0, 0.100, 50.0, 0); //Corrente de saida
         
         //Set protection limits
         CurrentCh1AlarmLevelSet(240); //Corrente de entrada
         CurrentCh1TripLevelSet(250);  //Corrente de entrada
         CurrentCh2AlarmLevelSet(550); //Corrente de saida
         CurrentCh2TripLevelSet(560);  //Corrente de saida

         
         // NTC contiguration type
         //ConfigNtcType(PRIMEPACK);

         //Leitura de tensão isolada
         LvCurrentCh1Init(330.0, 0.025, 120.0, 3); // Tensão de entrada

         LvCurrentCh1AlarmLevelSet(295.0); // Tensão de entrada Alarme
         LvCurrentCh1TripLevelSet(300.0);  // Tensão de entrada Interlock

         // PT100 configuration limits
         Pt100SetCh1AlarmLevel(35);  // Temperatura do dissipador
         Pt100SetCh1TripLevel(40);   // Temperatura do dissipador
         Pt100SetCh2AlarmLevel(55);  // Temperatura do indutor
         Pt100SetCh2TripLevel(60);   // Temperatura do indutor

         // PT100 channel enable
         Pt100Ch1Enable();            // Temperatura do dissipador
         Pt100Ch2Enable();            // Temperatura do indutor

         // Rh configuration limits
         TempBoardAlarmLimitSet(80);
         TempBoardTripLimitSet(90);

         // Driver Error monitoring
         Driver1ErrEnable();
         Driver2ErrEnable();
    
         // Init Variables

         Q4Module.Iin = 0;
         Q4Module.IinAlarmSts = 0;
         Q4Module.IinItlkSts = 0;

         Q4Module.Iout = 0;
         Q4Module.IoutAlarmSts = 0;
         Q4Module.IoutItlkSts = 0;

         Q4Module.VdcLink = 0;
         Q4Module.VdcLinkAlarmSts = 0;
         Q4Module.VdcLinkItlkSts = 0;

         Q4Module.TempIGBT1 = 0;
         Q4Module.TempIGBT1AlarmSts = 0;
         Q4Module.TempIGBT1ItlkSts = 0;
         Q4Module.TempIGBT1HwrItlk = 0;
         Q4Module.TempIGBT1HwrItlkSts = 0;

         Q4Module.TempIGBT2 = 0;
         Q4Module.TempIGBT2AlarmSts = 0;
         Q4Module.TempIGBT2ItlkSts = 0;
         Q4Module.TempIGBT2HwrItlk = 0;
         Q4Module.TempIGBT2HwrItlkSts = 0;

         Q4Module.TempL = 0;
         Q4Module.TempLAlarmSts = 0;
         Q4Module.TempLItlkSts = 0;

         Q4Module.TempHeatSink = 0;
         Q4Module.TempHeatSinkAlarmSts = 0;
         Q4Module.TempHeatSinkItlkSts = 0;

         Q4Module.Driver1Error = 0;
         Q4Module.Driver1ErrorItlk = 0;

         Q4Module.Driver2Error = 0;
         Q4Module.Driver2ErrorItlk = 0;

         break;
    case RECTIFIER_MODULE:
         //Set current range
         CurrentCh1Init(300.0, 0.150, 50.0, 3);    // Rectifier1 Output Current Sensor Configuration: Hall Sensor
         CurrentCh2Init(300.0, 0.150, 50.0, 3);    // Rectifier2 Output Current Sensor Configuration: LEM LF 310-S
         CurrentCh3Init(1.0, 0.0125, 300.0, 0);     // Leakage Current
         CurrentCh4Init(125.0, 0.125, 50.0, 0);
         //Set protection limits
         CurrentCh1AlarmLevelSet(230.0);          // Rectifier1 Output Current Alarm
         CurrentCh1TripLevelSet(235.0);           // Rectifier1 Output Current Trip
         CurrentCh2AlarmLevelSet(230.0);          // Rectifier2 Output Current Alarm
         CurrentCh2TripLevelSet(235.0);           // Rectifier2 Output Current Trip
         CurrentCh3AlarmLevelSet(0.09);          // Leakage Current Alarm Level
         CurrentCh3TripLevelSet(0.1);           // Leakage Current Trip Level
         CurrentCh4AlarmLevelSet(100.0);
         CurrentCh4TripLevelSet(100.0);

         //Setar ranges de entrada
         VoltageCh1Init(61.21, 3);                 // Rectifier1 Output Voltage Configuration.
         VoltageCh2Init(61.21, 3);                 // Rectifier2 Output Voltage Configuration.
         VoltageCh3Init(10.0, 3);                  // NTC SW1
         VoltageCh4Init(10.0, 3);                  // NTC SW2
         
         ConfigPolVoltCh2(1);                   // Change the voltage polarity of the channel 2 (rectifier 2 voltage)
         
         ConfigVoltCh1AsNtc(0);                 // Config Voltage Ch2 as a voltage input
         ConfigVoltCh2AsNtc(0);                 // Config Voltage Ch2 as a voltage input
         ConfigVoltCh3AsNtc(1);                 // Config Voltage Ch3 as a NTC input
         ConfigVoltCh4AsNtc(1);                 // Config Voltage Ch4 as a NTC input

         //Setar limites
         VoltageCh1AlarmLevelSet(55.0);           // Rectifier1 Voltage Alarm
         VoltageCh1TripLevelSet(58.0);            // Rectifier1 Voltage Trip
         VoltageCh2AlarmLevelSet(55.0);           // Rectifier2 Voltage Alarm
         VoltageCh2TripLevelSet(58.0);            // Rectifier2 Voltage Trip
         VoltageCh3AlarmLevelSet(115.0);          // Rectifier1 NTC Temperature Alarm
         VoltageCh3TripLevelSet(125.0);           // Rectifier1 NTC Temperature Trip
         VoltageCh4AlarmLevelSet(115.0);          // Rectifier2 NTC Temperature Alarm
         VoltageCh4TripLevelSet(125.0);           // Rectifier2 NTC Temperature Tip

         // PT100 configuration limits
         Pt100SetCh1AlarmLevel(70);             // Heat Sink Temperature Alarm
         Pt100SetCh1TripLevel(80);              // Heat Sink Temperature Trip
         Pt100SetCh2AlarmLevel(55);             // L1 Temperature Alarm
         Pt100SetCh2TripLevel(60);              // L1 Temperature Trip
         Pt100SetCh3AlarmLevel(55);             // L2 Temperature Alarm
         Pt100SetCh3TripLevel(60);              // L2 Temperature Trip
         Pt100SetCh4AlarmLevel(55);             // Water Temperature Alarm
         Pt100SetCh4TripLevel(60);              // Water Temperature Trip
         
         // Delay 4 seconds
         Pt100SetCh1Delay(4);
         // Delay 4 seconds
         Pt100SetCh2Delay(4);
         // Delay 4 seconds
         Pt100SetCh3Delay(4);
         // Delay 4 seconds
         Pt100SetCh4Delay(4);

         // PT100 channel enable
         Pt100Ch1Enable();                      // Enable PT100 channel 1
         Pt100Ch2Enable();                      // Enable PT100 channel 2
         Pt100Ch3Enable();                      // Enable PT100 channel 3
         Pt100Ch4Disable();                      // Enable PT100 channel 4
         
         // Rh configuration limits
         RhAlarmLimitSet(80);
         RhTripLimitSet(90);

         // Temp board configuration limits
         TempBoardAlarmLimitSet(80);
         TempBoardTripLimitSet(90);

         Driver1ErrDisable();                   // Driver1 Error Signal Disable
         Driver2ErrDisable();                   // Driver1 Error Signal Disable

         // Init variables
         Rectifier.IoutRectf1 = 0;
         Rectifier.IoutRectf1AlarmSts = 0;
         Rectifier.IoutRectf1ItlkSts = 0;

         Rectifier.IoutRectf2 = 0;
         Rectifier.IoutRectf2AlarmSts = 0;
         Rectifier.IoutRectf2ItlkSts = 0;

         Rectifier.VoutRectf1 = 0;
         Rectifier.VoutRectf1AlarmSts = 0;
         Rectifier.VoutRectf1ItlkSts = 0;

         Rectifier.VoutRectf2 = 0;
         Rectifier.VoutRectf2AlarmSts = 0;
         Rectifier.VoutRectf2ItlkSts = 0;

         Rectifier.LeakageCurrent = 0;
         Rectifier.LeakageCurrentAlarmSts = 0;
         Rectifier.LeakageCurrentItlkSts = 0;

         Rectifier.TempHeatSink = 0;
         Rectifier.TempHeatSinkAlarmSts = 0;
         Rectifier.TempHeatSinkItlkSts = 0;

         Rectifier.TempWater = 0;
         Rectifier.TempWaterAlarmSts = 0;
         Rectifier.TempWaterItlkSts = 0;

         Rectifier.TempModule1 = 0;
         Rectifier.TempModule1AlarmSts = 0;
         Rectifier.TempModule1ItlkSts = 0;

         Rectifier.TempModule2 = 0;
         Rectifier.TempModule2AlarmSts = 0;
         Rectifier.TempModule2ItlkSts = 0;

         Rectifier.TempL1 = 0;
         Rectifier.TempL1AlarmSts = 0;
         Rectifier.TempL1ItlkSts = 0;

         Rectifier.TempL2 = 0;
         Rectifier.TempL2AlarmSts = 0;
         Rectifier.TempL2ItlkSts = 0;

         Rectifier.AcPhaseFault = 0;
         Rectifier.AcPhaseFaultSts = 0;

         Rectifier.AcOverCurrent = 0;
         Rectifier.AcOverCurrentSts = 0;

         Rectifier.AcTransformerOverTemp = 0;
         Rectifier.AcTransformerOverTempSts = 0;

         Rectifier.WaterFluxInterlock = 0;
         Rectifier.WaterFluxInterlockSts = 0;
    
         break;
    case INPUT_MODULE:
         //Set Current Range
         CurrentCh1Init(300.0, 0.150, 50.0, 10);    // INPUT CURRENT

         //Set Protection Limits
         CurrentCh1AlarmLevelSet(160);          // INPUT CURRENT ALARM LEVEL
         CurrentCh1TripLevelSet(170);           // INPUT CURRENT TRIP LEVEL

         //LV20-P INPUTS
         LvCurrentCh1Init(550.0, 0.025, 120.0, 10); // CONFIG CHANNEL FOR DC_LINK MEASURE

         //LV20-P LIMITS
         CurrentCh1AlarmLevelSet(535);         // INPUT DC_LINK VOLTAGE ALARM LEVEL
         CurrentCh1TripLevelSet(540);          // INPUT DC_LINK VOLTAGE TRIP LEVEL

         // PT100 configuration limits
         Pt100SetCh1AlarmLevel(45);            // HEATSINK TEMPERATURE ALARM LEVEL
         Pt100SetCh1TripLevel(50);             // HEATSINK TEMPERATURE TRIP LEVEL
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

         // Rh configuration limits
         RhAlarmLimitSet(80);
         RhTripLimitSet(90);

         // Temp board configuration limits
         TempBoardAlarmLimitSet(80);
         TempBoardTripLimitSet(90);

         // Disable all Driver Error Monitoring
         Driver1ErrDisable();
         Driver2ErrDisable();
         
         // Init Variables
         InputModule.Iin = 0.0;
         InputModule.IinAlarmSts = 0;
         InputModule.IinItlkSts = 0;

         InputModule.VdcLink = 0.0;
         InputModule.VdcLinkAlarmSts = 0;
         InputModule.VdcLinkItlkSts = 0;

         InputModule.TempHeatsink = 0.0;
         InputModule.TempHeatsinkAlarmSts = 0;
         InputModule.TempHeatsinkItlkSts = 0;

         InputModule.TempL = 0.0;
         InputModule.TempLAlarmSts = 0;
         InputModule.TempLItlkSts = 0;
         
         InputModule.Driver1Error = 0;
         InputModule.Driver1ErrorItlk = 0;

         InputModule.Driver2Error = 0;
         InputModule.Driver2ErrorItlk = 0;

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

         CommandDrawer.VcapBank             = 0.0;
         CommandDrawer.VcapBankAlarmSts     = 0;
         CommandDrawer.VcapBankItlkSts      = 0;

         CommandDrawer.Vout                 = 0.0;
         CommandDrawer.VoutAlarmSts         = 0;
         CommandDrawer.VoutItlkSts          = 0;

         CommandDrawer.TempHeatSink         = 0;
         CommandDrawer.TempHeatSinkAlarmSts = 0;
         CommandDrawer.TempHeatSinkItlkSts  = 0;

         CommandDrawer.TempL                = 0;
         CommandDrawer.TempLAlarmSts        = 0;
         CommandDrawer.TempLItlkSts         = 0;

         CommandDrawer.ExtItlkSts           = 0;

         CommandDrawer.ExtItlk2Sts          = 0;
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

                Q1Module.VinItlkSts = 0;
                Q1Module.VoutItlkSts = 0;
                Q1Module.IoutA1ItlkSts = 0;
                Q1Module.IoutA2ItlkSts = 0;
                Q1Module.TempIGBT1ItlkSts = 0;
                Q1Module.TempIGBT1HwrItlkSts = 0;
                Q1Module.TempIGBT2ItlkSts = 0;
                Q1Module.TempIGBT2HwrItlkSts = 0;
                Q1Module.Driver1ErrorItlk = 0;
                Q1Module.Driver2ErrorItlk = 0;
                Q1Module.TempLItlkSts = 0;
                Q1Module.TempHeatSinkItlkSts = 0;
                Q1Module.ExternalItlkSts = 0;
                Q1Module.LeakageCurrentSts = 0;
                Q1Module.RackSts = 0;
                break;

          case OUTPUT_Q4_MODULE:

               Q4Module.IinItlkSts = 0;
               Q4Module.IoutItlkSts = 0;
               Q4Module.VdcLinkItlkSts = 0;
               Q4Module.TempIGBT1ItlkSts = 0;
               Q4Module.TempIGBT1HwrItlkSts = 0;
               Q4Module.TempIGBT2ItlkSts = 0;
               Q4Module.TempIGBT2HwrItlkSts = 0;
               Q4Module.TempLItlkSts = 0;
               Q4Module.TempHeatSinkItlkSts = 0;
               Q4Module.Driver1ErrorItlk = 0;
               Q4Module.Driver2ErrorItlk = 0;
               break;
               
          case RECTIFIER_MODULE:
               Rectifier.IoutRectf1AlarmSts = 0;
               Rectifier.IoutRectf1ItlkSts = 0;
               Rectifier.IoutRectf2AlarmSts = 0;
               Rectifier.IoutRectf2ItlkSts = 0;
               Rectifier.VoutRectf1AlarmSts = 0;
               Rectifier.VoutRectf1ItlkSts = 0;
               Rectifier.VoutRectf2AlarmSts = 0;
               Rectifier.VoutRectf2ItlkSts = 0;
               Rectifier.LeakageCurrentAlarmSts = 0;
               Rectifier.LeakageCurrentItlkSts = 0;
               Rectifier.TempHeatSinkAlarmSts = 0;
               Rectifier.TempHeatSinkItlkSts = 0;
               Rectifier.TempWaterAlarmSts = 0;
               Rectifier.TempWaterItlkSts = 0;
               Rectifier.TempModule1AlarmSts = 0;
               Rectifier.TempModule1ItlkSts = 0;
               Rectifier.TempModule2AlarmSts = 0;
               Rectifier.TempModule2ItlkSts = 0;
               Rectifier.TempL1AlarmSts = 0;
               Rectifier.TempL1ItlkSts = 0;
               Rectifier.TempL2AlarmSts = 0;
               Rectifier.TempL2ItlkSts = 0;
               Rectifier.AcPhaseFaultSts = 0;
               Rectifier.AcOverCurrentSts = 0;
               Rectifier.AcTransformerOverTempSts = 0;
               Rectifier.WaterFluxInterlockSts = 0;
               break;
               
          case INPUT_MODULE:
              InputModule.IinAlarmSts = 0;
              InputModule.IinItlkSts = 0;
              InputModule.VdcLinkAlarmSts = 0;
              InputModule.VdcLinkItlkSts = 0;
              InputModule.TempHeatsinkAlarmSts = 0;
              InputModule.TempHeatsinkItlkSts = 0;
              InputModule.TempLAlarmSts = 0;
              InputModule.TempLItlkSts = 0;
              InputModule.Driver1ErrorItlk = 0;
              InputModule.Driver2ErrorItlk = 0;
              break;
          case COMMAND_DRAWER_MODULE:
              CommandDrawer.VcapBankAlarmSts     = 0;
              CommandDrawer.VcapBankItlkSts      = 0;
              CommandDrawer.VoutAlarmSts         = 0;
              CommandDrawer.VoutItlkSts          = 0;
              CommandDrawer.TempHeatSinkAlarmSts = 0;
              CommandDrawer.TempHeatSinkItlkSts  = 0;
              CommandDrawer.TempLAlarmSts        = 0;
              CommandDrawer.TempLItlkSts         = 0;
              CommandDrawer.ExtItlkSts           = 0;
              CommandDrawer.ExtItlk2Sts          = 0;
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
   unsigned char Test = 0;

   switch(PowerModuleModel)
   {
       case OUTPUT_Q1_MODULE:
           Test |= Q1Module.VinItlkSts;
           Test |= Q1Module.VoutItlkSts;
           Test |= Q1Module.IoutA1ItlkSts;
           Test |= Q1Module.IoutA2ItlkSts;
           Test |= Q1Module.TempIGBT1ItlkSts;
           Test |= Q1Module.TempIGBT1HwrItlkSts;
           Test |= Q1Module.TempIGBT2ItlkSts;
           Test |= Q1Module.TempIGBT2HwrItlkSts;
           Test |= Q1Module.Driver1ErrorItlk;
           Test |= Q1Module.Driver2ErrorItlk;
           Test |= Q1Module.TempLItlkSts;
           Test |= Q1Module.TempHeatSinkItlkSts;
           Test |= Q1Module.ExternalItlkSts;
           Test |= Q1Module.LeakageCurrentSts;
           Test |= Q1Module.RackSts;
           break;
       
       case OUTPUT_Q4_MODULE:
            Test |= Q4Module.IinItlkSts;
            Test |= Q4Module.IoutItlkSts;
            Test |= Q4Module.VdcLinkItlkSts;
            Test |= Q4Module.TempIGBT1ItlkSts;
            Test |= Q4Module.TempIGBT1HwrItlkSts;
            Test |= Q4Module.TempIGBT2ItlkSts;
            Test |= Q4Module.TempIGBT2HwrItlkSts;
            Test |= Q4Module.TempLItlkSts;
            Test |= Q4Module.TempHeatSinkItlkSts;
            Test |= Q4Module.Driver1ErrorItlk;
            Test |= Q4Module.Driver2ErrorItlk;
            break;
       
       case RECTIFIER_MODULE:
            Test |= Rectifier.IoutRectf1ItlkSts;
            Test |= Rectifier.IoutRectf2ItlkSts;
            Test |= Rectifier.VoutRectf1ItlkSts;
            Test |= Rectifier.VoutRectf2ItlkSts;
            Test |= Rectifier.LeakageCurrentItlkSts;
            Test |= Rectifier.TempHeatSinkItlkSts;
            Test |= Rectifier.TempWaterItlkSts;
            Test |= Rectifier.TempModule1ItlkSts;
            Test |= Rectifier.TempModule2ItlkSts;
            Test |= Rectifier.TempL1ItlkSts;
            Test |= Rectifier.TempL2ItlkSts;
            Test |= Rectifier.AcPhaseFaultSts;
            Test |= Rectifier.AcOverCurrentSts;
            Test |= Rectifier.AcTransformerOverTempSts;
            Test |= Rectifier.WaterFluxInterlockSts;
            break;
       
       case INPUT_MODULE:
            Test |= InputModule.IinItlkSts;
            Test |= InputModule.VdcLinkItlkSts;
            Test |= InputModule.TempHeatsinkItlkSts;
            Test |= InputModule.TempLItlkSts;
            Test |= InputModule.Driver1ErrorItlk;
            Test |= InputModule.Driver2ErrorItlk;
            break;

       case COMMAND_DRAWER_MODULE:

           Test |= CommandDrawer.TempHeatSinkItlkSts;
           Test |= CommandDrawer.TempLItlkSts;
           Test |= CommandDrawer.VcapBankItlkSts;
           Test |= CommandDrawer.VoutItlkSts;
           Test |= CommandDrawer.ExtItlkSts;
           Test |= CommandDrawer.ExtItlk2Sts;
           break;
   }

   Test |= RhTripStatusRead();

   Test |= DriverVolatgeTripStatusRead();
   Test |= Driver1CurrentTripStatusRead();
   Test |= Driver2CurrentTripStatusRead();

   if(Test)InterlockSet();

}

void AlarmAppCheck(void)
{
   unsigned char Test = 0;
   
      switch(PowerModuleModel)
   {
       case OUTPUT_Q1_MODULE:
            Test |= Q1Module.VinAlarmSts;
            Test |= Q1Module.VoutAlarmSts;
            Test |= Q1Module.IoutA1AlarmSts;
            Test |= Q1Module.IoutA2AlarmSts;
            Test |= Q1Module.TempIGBT1AlarmSts;
            Test |= Q1Module.TempIGBT2AlarmSts;
            Test |= Q1Module.TempLAlarmSts;
            Test |= Q1Module.TempHeatSinkAlarmSts;
           break;

       case OUTPUT_Q4_MODULE:
            Test |= Q4Module.IinAlarmSts;
            Test |= Q4Module.IoutAlarmSts;
            Test |= Q4Module.VdcLinkAlarmSts;
            Test |= Q4Module.TempIGBT1AlarmSts;
            Test |= Q4Module.TempIGBT2AlarmSts;
            Test |= Q4Module.TempLAlarmSts;
            Test |= Q4Module.TempHeatSinkAlarmSts;
            break;

       case RECTIFIER_MODULE:
            Test |= Rectifier.IoutRectf1AlarmSts;
            Test |= Rectifier.IoutRectf2AlarmSts;
            Test |= Rectifier.VoutRectf1AlarmSts;
            Test |= Rectifier.VoutRectf2AlarmSts;
            Test |= Rectifier.LeakageCurrentAlarmSts;
            Test |= Rectifier.TempHeatSinkAlarmSts;
            Test |= Rectifier.TempWaterAlarmSts;
            Test |= Rectifier.TempModule1AlarmSts;
            Test |= Rectifier.TempModule2AlarmSts;
            Test |= Rectifier.TempL1AlarmSts;
            Test |= Rectifier.TempL2AlarmSts;
            break;

       case INPUT_MODULE:
            Test |= InputModule.IinAlarmSts;
            Test |= InputModule.TempHeatsinkAlarmSts;
            Test |= InputModule.TempLAlarmSts;
            Test |= InputModule.VdcLinkAlarmSts;
            break;

       case COMMAND_DRAWER_MODULE:
           Test |= CommandDrawer.TempHeatSinkAlarmSts;
           Test |= CommandDrawer.TempLAlarmSts;
           Test |= CommandDrawer.VcapBankAlarmSts;
           Test |= CommandDrawer.VoutAlarmSts;
   }

   Test |= RhAlarmStatusRead();


   if(Test)AlarmSet();
}



void LedIndicationStatus(void)
{
      switch(PowerModuleModel)
      {
       case OUTPUT_Q1_MODULE:

            // Output over voltage
            if(Q1Module.VoutItlkSts) Led2TurnOn();
            else if(Q1Module.VoutAlarmSts) Led2Toggle();
            else Led2TurnOff();

            // Input over voltage
            if(Q1Module.VinItlkSts) Led3TurnOn();
            else if(Q1Module.VinAlarmSts) Led3Toggle();
            else Led3TurnOff();

            // Output over current
            if (Q1Module.IoutA1ItlkSts || Q1Module.IoutA2ItlkSts) Led4TurnOn();
            else if(Q1Module.IoutA1AlarmSts || Q1Module.IoutA2AlarmSts) Led4Toggle();
            else Led4TurnOff();

            // Over temperature
            if(Q1Module.TempIGBT1ItlkSts || Q1Module.TempIGBT2ItlkSts ||  Q1Module.TempLItlkSts || Q1Module.TempHeatSinkItlkSts || Q1Module.TempIGBT1HwrItlkSts || Q1Module.TempIGBT2HwrItlkSts) Led5TurnOn();
            else if(Q1Module.TempIGBT1AlarmSts || Q1Module.TempIGBT2AlarmSts ||  Q1Module.TempLAlarmSts || Q1Module.TempHeatSinkAlarmSts) Led5Toggle();
            else Led5TurnOff();

            if(Q1Module.ExternalItlkSts) Led6TurnOn();
            else Led6TurnOff();

            if(Q1Module.LeakageCurrentSts) Led7TurnOn();
            else Led7TurnOff();

            if(Q1Module.RackSts) Led8TurnOn();
            else Led8TurnOff();

            if(Q1Module.Driver1ErrorItlk || Q1Module.Driver2ErrorItlk) Led9TurnOn();
            else if(!InterlockRead()) Led9TurnOff();

            if(InterlockRead()) Led10TurnOn();
            else Led10TurnOff();

            break;

       case OUTPUT_Q4_MODULE:
            // Input over voltage
            if(Q4Module.VdcLinkItlkSts) Led2TurnOn();
            else if(Q4Module.VdcLinkAlarmSts) Led2Toggle();
            else Led2TurnOff();

            // Input over current
            if(Q4Module.IinItlkSts) Led3TurnOn();
            else if(Q4Module.IinAlarmSts) Led3Toggle();
            else Led3TurnOff();

            // Output over current
            if(Q4Module.IoutItlkSts) Led4TurnOn();
            else if(Q4Module.IoutAlarmSts) Led4Toggle();
            else Led4TurnOff();

            // Output over current
            if(Q4Module.Driver1ErrorItlk || Q4Module.Driver2ErrorItlk) Led5TurnOn();
            else Led5TurnOff();

            // Heatsink Over temperature
            if(Q4Module.TempHeatSinkItlkSts) Led6TurnOn();
            else if(Q4Module.TempHeatSinkAlarmSts) Led6Toggle();
            else Led6TurnOff();

            // Inductor Over temperature
            if(Q4Module.TempLItlkSts) Led7TurnOn();
            else if(Q4Module.TempLAlarmSts) Led7Toggle();
            else Led7TurnOff();

            /*
            // IGBT Over temperature
            if(Q4Module.TempIGBT1ItlkSts || Q4Module.TempIGBT2ItlkSts) Led8TurnOn();
            else if(Q4Module.TempIGBT1AlarmSts || Q4Module.TempIGBT2AlarmSts) Led8Toggle();
            else Led7TurnOff();
            */

            break;

       case RECTIFIER_MODULE:

            // Rectifier Output Over Voltage
            if(Rectifier.VoutRectf1ItlkSts || Rectifier.VoutRectf2ItlkSts) Led2TurnOn();
            else if(Rectifier.VoutRectf1AlarmSts || Rectifier.VoutRectf2AlarmSts) Led2Toggle();
            else Led2TurnOff();

            // Rectifier Output Over Current
            if(Rectifier.IoutRectf1ItlkSts || Rectifier.IoutRectf1ItlkSts) Led3TurnOn();
            else if(Rectifier.IoutRectf1AlarmSts || Rectifier.IoutRectf1AlarmSts) Led3Toggle();
            else Led3TurnOff();

            // Rectifier Over Temperature
            if(Rectifier.TempHeatSinkItlkSts || Rectifier.TempWaterItlkSts || Rectifier.TempModule1ItlkSts || Rectifier.TempModule2ItlkSts || Rectifier.TempL1ItlkSts || Rectifier.TempL2ItlkSts) Led4TurnOn();
            else if(Rectifier.TempHeatSinkAlarmSts || Rectifier.TempWaterAlarmSts || Rectifier.TempModule1AlarmSts || Rectifier.TempModule2AlarmSts || Rectifier.TempL1AlarmSts || Rectifier.TempL2AlarmSts) Led4Toggle();
            else Led4TurnOff();

            // External interlock or Driver error
            if(Rectifier.AcPhaseFaultSts || Rectifier.AcOverCurrentSts || Rectifier.AcTransformerOverTempSts || Rectifier.WaterFluxInterlockSts) Led5TurnOn();
            else if(!InterlockRead())Led5TurnOff();
            
            break;

       case INPUT_MODULE:

            // Input Over Current
            if(InputModule.IinItlkSts) Led2TurnOn();
            else if(InputModule.IinAlarmSts) Led2Toggle();
            else Led2TurnOff();

            // Dc-Link Overvoltage
            if(InputModule.VdcLinkItlkSts) Led3TurnOn();
            else if(InputModule.VdcLinkAlarmSts) Led3Toggle();
            else Led3TurnOff();

            // Heatsink Over Temperature
            if(InputModule.TempHeatsinkItlkSts) Led4TurnOn();
            else if(InputModule.TempHeatsinkAlarmSts) Led4Toggle();
            else Led4TurnOff();
            
            // Inductor Over Temperature
            if(InputModule.TempLItlkSts) Led5TurnOn();
            else if(InputModule.TempLAlarmSts) Led5Toggle();
            else Led5TurnOff();

            // Driver Error
            if(InputModule.Driver1ErrorItlk || InputModule.Driver2ErrorItlk) Led6TurnOn();
            else Led6TurnOff();

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

           Q1Module.TempHeatSink = Pt100ReadCh1();//PT100 CH1
           Q1Module.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
           if(!Q1Module.TempHeatSinkItlkSts)Q1Module.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();

           Q1Module.TempL = Pt100ReadCh2();//PT100 CH2
           Q1Module.TempLAlarmSts = Pt100ReadCh2AlarmSts();
           if(!Q1Module.TempLItlkSts)Q1Module.TempLItlkSts = Pt100ReadCh2TripSts();

           Q1Module.TempIGBT1 = 0.0;
           Q1Module.TempIGBT1AlarmSts = 0;
           Q1Module.TempIGBT1ItlkSts = 0;

           if(!Q1Module.TempIGBT1HwrItlkSts) Q1Module.TempIGBT1HwrItlkSts = Driver1OverTempRead();

           Q1Module.TempIGBT2 = 0.0;
           Q1Module.TempIGBT2AlarmSts = 0;
           Q1Module.TempIGBT2ItlkSts = 0;

           if(!Q1Module.TempIGBT2HwrItlkSts) Q1Module.TempIGBT2HwrItlkSts = Driver2OverTempRead();

           Q1Module.IoutA1 = CurrentCh1Read();//HALL CH1
           Q1Module.IoutA1AlarmSts = CurrentCh1AlarmStatusRead();
           if(!Q1Module.IoutA1ItlkSts)Q1Module.IoutA1ItlkSts = CurrentCh1TripStatusRead();

           Q1Module.IoutA2 = CurrentCh2Read();//HALL CH2
           Q1Module.IoutA2AlarmSts = CurrentCh2AlarmStatusRead();
           if(!Q1Module.IoutA2ItlkSts)Q1Module.IoutA2ItlkSts = CurrentCh2TripStatusRead();

           Q1Module.Vin = LvCurrentCh1Read();
           Q1Module.VinAlarmSts = LvCurrentCh1AlarmStatusRead();
           if(!Q1Module.VinItlkSts)Q1Module.VinItlkSts = LvCurrentCh1TripStatusRead();

           Q1Module.Vout = LvCurrentCh2Read();
           Q1Module.VoutAlarmSts = LvCurrentCh2AlarmStatusRead();
           if(!Q1Module.VoutItlkSts)Q1Module.VoutItlkSts = LvCurrentCh2TripStatusRead();

           Q1Module.ExternalItlk = !Gpdi1Read();
           if(!Q1Module.ExternalItlkSts) Q1Module.ExternalItlkSts = !Gpdi1Read();

           Q1Module.LeakageCurrent = !Gpdi2Read();
           if(!Q1Module.LeakageCurrentSts) Q1Module.LeakageCurrentSts = !Gpdi2Read();

           Q1Module.Rack = !Gpdi3Read();
           if(!Q1Module.RackSts) Q1Module.RackSts = !Gpdi3Read();

           Q1Module.Relay = !Gpdi4Read();

           Q1Module.Driver1Error = Driver1TopErrRead();
           if(!Q1Module.Driver1ErrorItlk) Q1Module.Driver1ErrorItlk = Driver1TopErrRead();

           Q1Module.Driver2Error = Driver2TopErrRead();
           if(!Q1Module.Driver2ErrorItlk) Q1Module.Driver2ErrorItlk = Driver2TopErrRead();
            
            
           if(Q1Module.ExternalItlkSts || Q1Module.Driver2ErrorItlk || Q1Module.Driver2ErrorItlk) InterlockSet(); // If no signal over the port, then set Interlock action
           break;
       
       case OUTPUT_Q4_MODULE:
            Q4Module.Iin = CurrentCh1Read();
            Q4Module.IinAlarmSts = CurrentCh1AlarmStatusRead();
            if(!Q4Module.IinItlkSts) Q4Module.IinItlkSts = CurrentCh1TripStatusRead();

            Q4Module.Iout = CurrentCh2Read();
            Q4Module.IoutAlarmSts = CurrentCh2AlarmStatusRead();
            if(!Q4Module.IoutItlkSts) Q4Module.IoutItlkSts = CurrentCh2TripStatusRead();

            Q4Module.VdcLink = LvCurrentCh1Read();
            Q4Module.VdcLinkAlarmSts = LvCurrentCh1AlarmStatusRead();
            if(!Q4Module.VdcLinkItlkSts)Q4Module.VdcLinkItlkSts = LvCurrentCh1TripStatusRead();

            Q4Module.TempHeatSink = Pt100ReadCh1();//PT100 CH1
            Q4Module.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
            if(!Q4Module.TempHeatSinkItlkSts)Q4Module.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();

            Q4Module.TempL = Pt100ReadCh2();//PT100 CH2
            Q4Module.TempLAlarmSts = Pt100ReadCh2AlarmSts();
            if(!Q4Module.TempLItlkSts)Q4Module.TempLItlkSts = Pt100ReadCh2TripSts();

            /*
            Q4Module.TempIGBT1 = 0;
            Q4Module.TempIGBT1AlarmSts = 0;
            if(!Q4Module.TempIGBT1ItlkSts) Q4Module.TempIGBT1ItlkSts = 0;
            
            Q4Module.TempIGBT2 = VoltageCh2Read();
            Q4Module.TempIGBT2AlarmSts = VoltageCh2AlarmStatusRead();
            if(!Q4Module.TempIGBT2ItlkSts) Q4Module.TempIGBT2ItlkSts = 0;

            Driver1TopErrRead();
            Driver2TopErrRead();

            Driver1OverTempRead();
            Driver2OverTempRead();
            */


            break;
            
       case RECTIFIER_MODULE:
            Rectifier.IoutRectf1 = CurrentCh1Read();
            Rectifier.IoutRectf1AlarmSts = CurrentCh1AlarmStatusRead();
            if(!Rectifier.IoutRectf1ItlkSts) Rectifier.IoutRectf1ItlkSts = CurrentCh1TripStatusRead();
            
            Rectifier.IoutRectf2 = CurrentCh2Read();
            Rectifier.IoutRectf2AlarmSts = CurrentCh2AlarmStatusRead();
            if(!Rectifier.IoutRectf2ItlkSts) Rectifier.IoutRectf2ItlkSts = CurrentCh2TripStatusRead();
            
            Rectifier.VoutRectf1 = VoltageCh1Read();
            Rectifier.VoutRectf1AlarmSts = VoltageCh1AlarmStatusRead();
            if(!Rectifier.VoutRectf1ItlkSts) Rectifier.VoutRectf1ItlkSts = VoltageCh1TripStatusRead();
            
            Rectifier.VoutRectf2 = VoltageCh2Read();
            Rectifier.VoutRectf2AlarmSts = VoltageCh2AlarmStatusRead();
            if(!Rectifier.VoutRectf2ItlkSts) Rectifier.VoutRectf2ItlkSts = VoltageCh2TripStatusRead();
            
            Rectifier.LeakageCurrent = CurrentCh3Read();
            Rectifier.LeakageCurrentAlarmSts = CurrentCh3AlarmStatusRead();
            if(!Rectifier.LeakageCurrentItlkSts) Rectifier.LeakageCurrentItlkSts = CurrentCh3TripStatusRead();
            
            Rectifier.TempHeatSink = Pt100ReadCh1();
            Rectifier.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
            if(!Rectifier.TempHeatSinkItlkSts) Rectifier.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();
            
            Rectifier.TempWater = Pt100ReadCh4();
            Rectifier.TempWaterAlarmSts = Pt100ReadCh4AlarmSts();
            if(!Rectifier.TempWaterItlkSts) Rectifier.TempWaterItlkSts = Pt100ReadCh4TripSts();
            
            Rectifier.TempModule1 = VoltageCh3Read();
            Rectifier.TempModule1AlarmSts = VoltageCh3AlarmStatusRead();
            if(!Rectifier.TempModule1ItlkSts) Rectifier.TempModule1ItlkSts = VoltageCh3TripStatusRead();
            
            Rectifier.TempModule2 = VoltageCh4Read();
            Rectifier.TempModule2AlarmSts = VoltageCh4AlarmStatusRead();
            if(!Rectifier.TempModule2ItlkSts) Rectifier.TempModule2ItlkSts = VoltageCh4TripStatusRead();
            
            Rectifier.TempL1 = Pt100ReadCh2();
            Rectifier.TempL1AlarmSts = Pt100ReadCh2AlarmSts();
            if(!Rectifier.TempL1ItlkSts) Rectifier.TempL1ItlkSts = Pt100ReadCh2TripSts();
            
            Rectifier.TempL2 = Pt100ReadCh3();
            Rectifier.TempL2AlarmSts = Pt100ReadCh3AlarmSts();
            if(!Rectifier.TempL2ItlkSts) Rectifier.TempL2ItlkSts = Pt100ReadCh3TripSts();
            
            Rectifier.AcPhaseFault = !Gpdi1Read();
            if(!Rectifier.AcPhaseFaultSts) Rectifier.AcPhaseFaultSts = !Gpdi1Read();
            
            Rectifier.AcOverCurrent = !Gpdi2Read();
            if(!Rectifier.AcOverCurrentSts) Rectifier.AcOverCurrentSts = !Gpdi2Read();
            
            Rectifier.AcTransformerOverTemp = !Gpdi3Read();
            if(!Rectifier.AcTransformerOverTempSts) Rectifier.AcTransformerOverTempSts = !Gpdi3Read();
            
            Rectifier.WaterFluxInterlock = !Gpdi4Read();
            if(!Rectifier.WaterFluxInterlockSts) Rectifier.WaterFluxInterlockSts = !Gpdi4Read();
            
            if(Rectifier.AcPhaseFault || Rectifier.AcOverCurrent || Rectifier.AcTransformerOverTemp || Rectifier.WaterFluxInterlock) InterlockSet();
            
            break;
            
       case INPUT_MODULE:
            InputModule.Iin = CurrentCh1Read();
            InputModule.IinAlarmSts = CurrentCh1AlarmStatusRead();
            if(!InputModule.IinItlkSts) InputModule.IinItlkSts = CurrentCh1TripStatusRead();
            
            InputModule.VdcLink = LvCurrentCh1Read();
            InputModule.VdcLinkAlarmSts = CurrentCh1AlarmStatusRead();
            if(!InputModule.VdcLinkItlkSts) InputModule.VdcLinkItlkSts = CurrentCh1TripStatusRead();
            
            InputModule.TempHeatsink = Pt100ReadCh1();
            InputModule.TempHeatsinkAlarmSts = Pt100ReadCh1AlarmSts();
            if(!InputModule.TempHeatsinkItlkSts) InputModule.TempHeatsinkItlkSts = Pt100ReadCh1TripSts();

            InputModule.TempL = Pt100ReadCh2();
            InputModule.TempLAlarmSts = Pt100ReadCh2AlarmSts();
            if(!InputModule.TempLItlkSts) InputModule.TempLItlkSts = Pt100ReadCh2TripSts();

            /*
            InputModule.Driver1Error = Driver1TopErrRead();
            if(!InputModule.Driver1ErrorItlk) InputModule.Driver1ErrorItlk = Driver1TopErrRead();

            InputModule.Driver2Error = Driver2TopErrRead();
            if(!InputModule.Driver2ErrorItlk) InputModule.Driver2ErrorItlk = Driver2TopErrRead();
            */
            break;

       case COMMAND_DRAWER_MODULE:
           CommandDrawer.TempHeatSink = Pt100ReadCh1();
           CommandDrawer.TempHeatSinkAlarmSts = Pt100ReadCh1AlarmSts();
           if (!CommandDrawer.TempHeatSinkItlkSts) CommandDrawer.TempHeatSinkItlkSts = Pt100ReadCh1TripSts();

           CommandDrawer.TempL = Pt100ReadCh2();
           CommandDrawer.TempLAlarmSts = Pt100ReadCh2AlarmSts();
           if (!CommandDrawer.TempLItlkSts) CommandDrawer.TempLItlkSts = Pt100ReadCh2TripSts();

           CommandDrawer.VcapBank = VoltageCh1Read();
           CommandDrawer.VcapBankAlarmSts = VoltageCh1AlarmStatusRead();
           if (!CommandDrawer.VcapBankItlkSts) CommandDrawer.VcapBankItlkSts = VoltageCh1TripStatusRead();

           CommandDrawer.Vout = VoltageCh2Read();
           CommandDrawer.VoutAlarmSts = VoltageCh2AlarmStatusRead();
           if (!CommandDrawer.VoutItlkSts) CommandDrawer.VoutItlkSts = VoltageCh2TripStatusRead();

           if(!CommandDrawer.ExtItlkSts) CommandDrawer.ExtItlkSts = !Gpdi1Read();

           if(!CommandDrawer.ExtItlk2Sts) CommandDrawer.ExtItlk2Sts = !Gpdi5Read();

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
            }
      }

      CheckCan();

}

// Application type
//******************************************************************************

unsigned char AppType(void)
{
      return PowerModuleModel;
}


// 1Q Module
//******************************************************************************
float Q1ModuleVoutRead(void)
{
      return Q1Module.Vout;
}

unsigned char Q1ModuleVoutAlarmStsRead(void)
{
      return Q1Module.VoutAlarmSts;
}

unsigned char Q1ModuleVoutItlkStsRead(void)
{
       return Q1Module.VoutItlkSts;
}

//**********************************************

float Q1ModuleVinRead(void)
{
      return Q1Module.Vin;
}

unsigned char Q1ModuleVinAlarmStsRead(void)
{
      return Q1Module.VinAlarmSts;
}

unsigned char Q1ModuleVinItlkStsRead(void)
{
      return Q1Module.VinItlkSts;
}

//**********************************************

float Q1ModuleIoutA1Read(void)
{
      return Q1Module.IoutA1;
}

unsigned char Q1ModuleIoutA1AlarmStsRead(void)
{
      return Q1Module.IoutA1AlarmSts;
}

unsigned char Q1ModuleIoutA1ItlkStsRead(void)
{
      return Q1Module.IoutA1ItlkSts;
}

//**********************************************

float Q1ModuleIoutA2Read(void)
{
      return Q1Module.IoutA2;
}

unsigned char Q1ModuleIoutA2AlarmStsRead(void)
{
      return Q1Module.IoutA2AlarmSts;
}

unsigned char Q1ModuleIoutA2ItlkStsRead(void)
{
      return Q1Module.IoutA2ItlkSts;
}

//**********************************************

unsigned char Q1ModuleTempIGBT1Read(void)
{
      return Q1Module.TempIGBT1;
}

unsigned char Q1ModuleTempIGBT1AlarmStsRead(void)
{
      return Q1Module.TempIGBT1AlarmSts;
}

unsigned char Q1ModuleTempIGBT1ItlkStsRead(void)
{
      return Q1Module.TempIGBT1ItlkSts;
}

unsigned char Q1ModuleTempIGBT1HwrItlkRead(void)
{
      return Q1Module.TempIGBT1HwrItlk;
}

unsigned char Q1ModuleTempIGBT1HwrItlkStsRead(void)
{
      return Q1Module.TempIGBT1HwrItlkSts;
}
      
//**********************************************

unsigned char Q1ModuleTempIGBT2Read(void)
{
      return Q1Module.TempIGBT2;
}

unsigned char Q1ModuleTempIGBT2AlarmStsRead(void)
{
      return Q1Module.TempIGBT2AlarmSts;
}

unsigned char Q1ModuleTempIGBT2ItlkStsRead(void)
{
      return Q1Module.TempIGBT2ItlkSts;
}

unsigned char Q1ModuleTempIGBT2HwrItlkRead(void)
{
      return Q1Module.TempIGBT2HwrItlk;
}

unsigned char Q1ModuleTempIGBT2HwrItlkStsRead(void)
{
      return Q1Module.TempIGBT2HwrItlkSts;
}

//**********************************************

unsigned char Q1ModuleTempHeatSinkRead(void)
{
      return Q1Module.TempHeatSink;
}

unsigned char Q1ModuleTempHeatSinkAlarmStsRead(void)
{
      return Q1Module.TempHeatSinkAlarmSts;
}

unsigned char Q1ModuleTempHeatSinkItlkStsRead(void)
{
      return Q1Module.TempHeatSinkItlkSts;
}

//**********************************************

unsigned char Q1ModuleTempLRead(void)
{
      return Q1Module.TempL;
}

unsigned char Q1ModuleTempLAlarmStsRead(void)
{
      return Q1Module.TempLAlarmSts;
}

unsigned char Q1ModuleTempLItlkStsRead(void)
{
      return Q1Module.TempLItlkSts;
}

//**********************************************

unsigned char Q1ModuleRelayRead(void)
{
      return Q1Module.Relay;
}

//**********************************************

unsigned char Q1ModuleDriver1ErrorRead(void)
{
      return Q1Module.Driver1Error;
}

unsigned char Q1ModuleDriver1ErrorItlkRead(void)
{
      return Q1Module.Driver1ErrorItlk;
}

//**********************************************

unsigned char Q1ModuleDriver2ErrorRead(void)
{
      return Q1Module.Driver2Error;
}

unsigned char Q1ModuleDriver2ErrorItlkRead(void)
{
      return Q1Module.Driver2ErrorItlk;
}

//**********************************************

unsigned char Q1ModuleExternalItlkRead(void)
{
      return Q1Module.ExternalItlk;
}

unsigned char Q1ModuleExternalItlkStsRead(void)
{
      return Q1Module.ExternalItlkSts;
}

//**********************************************

unsigned char Q1ModuleLeakageCurrentRead(void)
{
    return Q1Module.LeakageCurrent;

}

unsigned char Q1ModuleLeakageCurrentStsRead(void)
{
    return Q1Module.LeakageCurrentSts;

}

//**********************************************

unsigned char Q1ModuleRackRead(void)
{
    return Q1Module.Rack;

}

unsigned char Q1ModuleRackStsRead(void)
{
    return Q1Module.RackSts;

}




// 4Q Module
//******************************************************************************
float Q4ModuleIoutRead(void)
{
      return Q4Module.Iout;
}

unsigned char Q4ModuleIoutAlarmStsRead(void)
{
      return Q4Module.IoutAlarmSts;
}

unsigned char Q4ModuleIoutItlkStsRead(void)
{
      return Q4Module.IoutItlkSts;
}

//******************************************************************************

unsigned char Q4ModuleTempIGBT1Read(void)
{
      return Q4Module.TempIGBT1;
}

unsigned char Q4ModuleTempIGBT1AlarmStsRead(void)
{
      return Q4Module.TempIGBT1AlarmSts;
}

unsigned char Q4ModuleTempIGBT1ItlkStsRead(void)
{
      return Q4Module.TempIGBT1ItlkSts;
}

//******************************************************************************

unsigned char Q4ModuleTempIGBT2Read(void)
{
      return Q4Module.TempIGBT2;
}

unsigned char Q4ModuleTempIGBT2AlarmStsRead(void)
{
      return Q4Module.TempIGBT2AlarmSts;
}

unsigned char Q4ModuleTempIGBT2ItlkStsRead(void)
{
      return Q4Module.TempIGBT2ItlkSts;
}


// Rectifier
//******************************************************************************
float RectifierIoutRectf1Read(void)
{
      return Rectifier.IoutRectf1;
}
            
unsigned char RectifierIoutRectf1AlarmStsRead(void)
{
      return Rectifier.IoutRectf1AlarmSts;
}

unsigned char RectifierIoutRectf1ItlkStsRead(void)
{
      return Rectifier.IoutRectf1ItlkSts;
}

//******************************************************************************

float RectifierIoutRectf2Read(void)
{
      return Rectifier.IoutRectf2;
}

unsigned char RectifierIoutRectf2AlarmStsRead(void)
{
      return Rectifier.IoutRectf2AlarmSts;
}

unsigned char RectifierIoutRectf2ItlkStsRead(void)
{
      return Rectifier.IoutRectf2ItlkSts;
}

//******************************************************************************

float RectifierVoutRectf1Read(void)
{
      return Rectifier.VoutRectf1;
}

unsigned char RectifierVoutRectf1AlarmStsRead(void)
{
      return Rectifier.VoutRectf1AlarmSts;
}

unsigned char RectifierVoutRectf1ItlkStsRead(void)
{
      return Rectifier.VoutRectf1ItlkSts;
}

//******************************************************************************
            
float RectifierVoutRectf2Read(void)
{
      return Rectifier.VoutRectf2;
}

unsigned char RectifierVoutRectf2AlarmStsRead(void)
{
      return Rectifier.VoutRectf2AlarmSts;
}

unsigned char RectifierVoutRectf2ItlkStsRead(void)
{
      return Rectifier.VoutRectf2ItlkSts;
}

//******************************************************************************

float RectifierLeakageCurrentRead(void)
{
      return Rectifier.LeakageCurrent;
}

unsigned char RectifierLeakageCurrentAlarmStsread(void)
{
      return Rectifier.LeakageCurrentAlarmSts;
}

unsigned char RectifierLeakageCurrentItlkStsRead(void)
{
      return Rectifier.LeakageCurrentItlkSts;
}

//******************************************************************************

unsigned char RectifierTempHeatSinkRead(void)
{
      return Rectifier.TempHeatSink;
}

unsigned char RectifierTempHeatSinkAlarmStsRead(void)
{
      return Rectifier.TempHeatSinkAlarmSts;
}

unsigned char RectifierTempHeatSinkItlkStsRead(void)
{
      return Rectifier.TempHeatSinkItlkSts;
}

//******************************************************************************

unsigned char RectifierTempWaterRead(void)
{
      return Rectifier.TempWater;
}

unsigned char RectifierTempWaterAlarmStsRead(void)
{
      return Rectifier.TempWaterAlarmSts;
}

unsigned char RectifierTempWaterItlkStsRead(void)
{
      return Rectifier.TempWaterItlkSts;
}

//******************************************************************************

unsigned char RectifierTempModule1Read(void)
{
      return Rectifier.TempModule1;
}

unsigned char RectifierTempModule1AlarmStsRead(void)
{
      return Rectifier.TempModule1AlarmSts;
}

unsigned char RectifierTempModule1ItlkStsRead(void)
{
      return Rectifier.TempModule1ItlkSts;
}

//******************************************************************************

unsigned char RectifierTempModule2Read(void)
{
      return Rectifier.TempModule2;
}

unsigned char RectifierTempModule2AlarmStsRead(void)
{
      return Rectifier.TempModule2AlarmSts;
}

unsigned char RectifierTempModule2ItlkStsRead(void)
{
      return Rectifier.TempModule2ItlkSts;
}

//******************************************************************************

unsigned char RectifierTempL1Read(void)
{
      return Rectifier.TempL1;
}

unsigned char RectifierTempL1AlarmStsRead(void)
{
      return Rectifier.TempL1AlarmSts;
}

unsigned char RectifierTempL1ItlkStsRead(void)
{
      return Rectifier.TempL1ItlkSts;
}

//******************************************************************************

unsigned char RectifierTempL2Read(void)
{
      return Rectifier.TempL2;
}

unsigned char RectifierTempL2AlarmStsRead(void)
{
      return Rectifier.TempL2AlarmSts;
}

unsigned char RectifierTempL2ItlkStsRead(void)
{
      return Rectifier.TempL2ItlkSts;
}

//******************************************************************************

unsigned char RectifierAcPhaseFaultRead(void)
{
      return Rectifier.AcPhaseFault;
}

unsigned char RectifierAcPhaseFaultStsRead(void)
{
      return Rectifier.AcPhaseFaultSts;
}

//******************************************************************************

unsigned char RectifierAcOverCurrentRead(void)
{
      return Rectifier.AcOverCurrent;
}

unsigned char RectifierAcOverCurrentStsRead(void)
{
      return Rectifier.AcOverCurrentSts;
}

//******************************************************************************

unsigned char RectifierAcTransformerOverTempRead(void)
{
      return Rectifier.AcTransformerOverTemp;
}

unsigned char RectifierAcTransformerOverTempStsRead(void)
{
      return Rectifier.AcTransformerOverTempSts;
}

//******************************************************************************

unsigned char RectifierWaterFluxInterlockRead(void)
{
      return Rectifier.WaterFluxInterlock;
}

unsigned char RectifierWaterFluxInterlockStsRead(void)
{
      return Rectifier.WaterFluxInterlockSts;
}

// Input Module
//******************************************************************************
float InputModuleIinRead(void)
{
      return InputModule.Iin;
}

unsigned char InputModuleIinAlarmStsRead(void)
{
      return InputModule.IinAlarmSts;
}

unsigned char InputModuleIinItlkStsRead(void)
{
      return InputModule.IinItlkSts;
}

//******************************************************************************

float InputModuleVdcLinkRead(void)
{
      return InputModule.VdcLink;
}

unsigned char InputModuleVdcLinkAlarmStsRead(void)
{
      return InputModule.VdcLinkAlarmSts;
}

unsigned char InputModuleVdcLinkItlkStsRead(void)
{
      return InputModule.VdcLinkItlkSts;
}

//******************************************************************************

unsigned char InputModuleTempHeatsinkRead(void)
{
      return InputModule.TempHeatsink;
}

unsigned char InputModuleTempHeatsinkAlarmStsRead(void)
{
      return InputModule.TempHeatsinkAlarmSts;
}

unsigned char InputModuleTempHeatsinkItlkStsRead(void)
{
      return InputModule.TempHeatsinkItlkSts;
}

//******************************************************************************

unsigned char InputModuleTempLRead(void)
{
      return InputModule.TempL;
}

unsigned char InputModuleTempLAlarmStsRead(void)
{
      return InputModule.TempLAlarmSts;
}

unsigned char InputModuleTempLItlkStsRead(void)
{
      return InputModule.TempLItlkSts;
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
