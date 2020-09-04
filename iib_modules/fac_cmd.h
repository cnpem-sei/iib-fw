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
 * @file command_drawer.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FAC_CMD_H_
#define FAC_CMD_H_

/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>
#include "application.h"

/////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    union {
        float       f;
        uint8_t     u8[4];
    } VcapBank;

    bool VcapBankAlarmSts;
    bool VcapBankItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } Vout;

    bool VoutAlarmSts;
    bool VoutItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } AuxIdbVoltage;

    bool AuxIdbVoltageAlarmSts;
    bool AuxIdbVoltageItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } AuxCurrent;

    bool AuxCurrentAlarmSts;
    bool AuxCurrentItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } IdbCurrent;

    bool IdbCurrentAlarmSts;
    bool IdbCurrentItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } TempL;

    bool TempLAlarmSts;
    bool TempLItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } TempHeatSink;

    bool TempHeatSinkAlarmSts;
    bool TempHeatSinkItlkSts;

    bool MainOverCurrentItlk;
    bool MainOverCurrentItlkSts;

    bool EmergencyButtonItlk;
    bool EmergencyButtonItlkSts;

    bool MainUnderVoltageItlk;
    bool MainUnderVoltageItlkSts;

    bool MainOverVoltageItlk;
    bool MainOverVoltageItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } GroundLeakage;

    bool GroundLeakageAlarmSts;
    bool GroundLeakageItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } BoardTemperature;

    bool BoardTemperatureAlarmSts;
    bool BoardTemperatureItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } RelativeHumidity;

    bool RelativeHumidityAlarmSts;
    bool RelativeHumidityItlkSts;

} fac_cmd_t;

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ITLK                0x00000001
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ITLK                 0x00000002
#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ITLK     0x00000004
#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ITLK             0x00000008
#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ITLK             0x00000010
#define FAC_CMD_INDUC_OVERTEMP_ITLK                     0x00000020
#define FAC_CMD_HS_OVERTEMP_ITLK                        0x00000040
#define FAC_CMD_MAIN_OVER_CURRENT_ITLK                  0x00000080
#define FAC_CMD_EMERGENCY_BUTTON_ITLK                   0x00000100
#define FAC_CMD_MAIN_UNDER_VOLTAGE_ITLK                 0x00000200
#define FAC_CMD_MAIN_OVER_VOLTAGE_ITLK                  0x00000400
#define FAC_CMD_GROUND_LKG_ITLK                         0x00000800
#define FAC_CMD_BOARD_IIB_OVERTEMP_ITLK                 0x00001000
#define FAC_CMD_BOARD_IIB_OVERHUMIDITY_ITLK             0x00002000

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ALM                 0x00000001
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ALM                  0x00000002
#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ALM      0x00000004
#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ALM              0x00000008
#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ALM              0x00000010
#define FAC_CMD_INDUC_OVERTEMP_ALM                      0x00000020
#define FAC_CMD_HS_OVERTEMP_ALM                         0x00000040
#define FAC_CMD_GROUND_LKG_ALM                          0x00000080
#define FAC_CMD_BOARD_IIB_OVERTEMP_ALM                  0x00000100
#define FAC_CMD_BOARD_IIB_OVERHUMIDITY_ALM              0x00000200

/////////////////////////////////////////////////////////////////////////////////////////////

extern void clear_fac_cmd_interlocks(void);
extern uint8_t check_fac_cmd_interlocks(void);
extern void clear_fac_cmd_alarms(void);
extern uint8_t check_fac_cmd_alarms(void);
extern void check_fac_cmd_indication_leds(void);
extern void fac_cmd_application_readings(void);
extern void config_module_fac_cmd(void);

extern fac_cmd_t fac_cmd;

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC01 / PA-RaPSC02

//BO-FAM:PS-QF

#ifdef BO_FAM_PS_QF__CMD

#define FAC_CMD

#define ON                                                  1
#define OFF                                                 0

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ALM_LIM                 330.0
#define FAC_CMD_CAPBANK_OVERVOLTAGE_ITLK_LIM                350.0

#define FAC_CMD_OUTPUT_OVERVOLTAGE_ALM_LIM                  260.0
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ITLK_LIM                 270.0

#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ALM_LIM      16.0
#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ITLK_LIM     17.0

#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_GROUND_LEAKAGE_ALM_LIM                      1.3
#define FAC_CMD_GROUND_LEAKAGE_ITLK_LIM                     1.5

#define FAC_CMD_INDUC_OVERTEMP_ALM_LIM                      50.0
#define FAC_CMD_INDUC_OVERTEMP_ITLK_LIM                     60.0

#define FAC_CMD_HS_OVERTEMP_ALM_LIM                         50.0
#define FAC_CMD_HS_OVERTEMP_ITLK_LIM                        60.0

#define FAC_CMD_RH_OVERHUMIDITY_ALM_LIM                     50.0
#define FAC_CMD_RH_OVERHUMIDITY_ITLK_LIM                    90.0

#define FAC_CMD_BOARD_OVERTEMP_ALM_LIM                      50.0
#define FAC_CMD_BOARD_OVERTEMP_ITLK_LIM                     60.0

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range

//Sensor Hall

//CurrentCh1Init and CurrentCh2Init and CurrentCh3Init and CurrentCh4Init

#define Hall_Primary_Current                                000.0

#define Hall_Secondary_Current                              0.000

#define Hall_Burden_Resistor                                00.0

//Debouncing delay_ms
#define Hall_Delay                                          0

#define CurrentCh1Enable                                    OFF
#define CurrentCh2Enable                                    OFF
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Cap_Bank                         600.0

#define LV_Primary_Voltage_Vout                             300.0

#define LV_Primary_Voltage_GND_Leakage                      4.86

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_ms
#define Delay_Voltage_Cap_Bank                              3

//Debouncing delay_ms
#define Delay_Vout                                          3

//Debouncing delay_ms
#define Delay_GND_Leakage                                   3

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  ON
#define LvCurrentCh3Enable                                  ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                                      4
#define Delay_PT100CH2                                      4

#define Pt100Ch1Enable                                      ON
#define Pt100Ch2Enable                                      ON
#define Pt100Ch3Enable                                      OFF
#define Pt100Ch4Enable                                      OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                                         0
#define Delay_IGBT2                                         0

#define TempIgbt1Enable                                     OFF
#define TempIgbt2Enable                                     OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                                     3
#define Delay_BoardRh                                       3

#define BoardTempEnable                                     ON
#define RhEnable                                            ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                                 3
#define Delay_DriverCurrent                                 3

#define DriverVoltageEnable                                 ON  //Voltage Aux and Idb enable
#define Driver1CurrentEnable                                ON  //Current Aux enable
#define Driver2CurrentEnable                                ON  //Current Idb enable

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                               OFF
#define Driver1BotErrorEnable                               OFF
#define Driver1OverTempEnable                               OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                               OFF
#define Driver2BotErrorEnable                               OFF
#define Driver2OverTempEnable                               OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                                    OFF
#define VoltageCh2Enable                                    OFF
#define VoltageCh3Enable                                    OFF
#define VoltageCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define Gpdi1Enable                                         OFF
#define Gpdi2Enable                                         OFF
#define Gpdi3Enable                                         OFF
#define Gpdi4Enable                                         OFF
#define Gpdi5Enable                                         ON  // Main Over Current
#define Gpdi6Enable                                         ON  // Emergency Button
#define Gpdi7Enable                                         OFF // Main Under Voltage
#define Gpdi8Enable                                         OFF // Main Over Voltage
#define Gpdi9Enable                                         OFF
#define Gpdi10Enable                                        OFF
#define Gpdi11Enable                                        OFF
#define Gpdi12Enable                                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                                         OFF
#define Gpdo2Enable                                         OFF
#define Gpdo3Enable                                         OFF
#define Gpdo4Enable                                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                                       ON
#define ReleExtItlkEnable                                   ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* BO_FAM_PS_QF__CMD */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack BO-FAM:PS-B-1 --> PA-RaPSE01 / PA-RaPSE02 / PA-RaPSE03 / PA-RaPSE04 / PA-RaPSE06 / PA-RaPSE07 / PA-RaPSE08 / PA-RaPSE09

//Rack BO-FAM:PS-B-2 --> PA-RaPSF01 / PA-RaPSF02 / PA-RaPSF03 / PA-RaPSF04 / PA-RaPSF06 / PA-RaPSF07 / PA-RaPSF08 / PA-RaPSF09

//BO-FAM:PS-B-1 / B-2

#ifdef BO_FAM_PS_B1_and_B2__CMD

#define FAC_CMD

#define ON                                                  1
#define OFF                                                 0

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ALM_LIM                 290.0
#define FAC_CMD_CAPBANK_OVERVOLTAGE_ITLK_LIM                300.0

#define FAC_CMD_OUTPUT_OVERVOLTAGE_ALM_LIM                  260.0
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ITLK_LIM                 270.0

#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ALM_LIM      16.0
#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ITLK_LIM     17.0

#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_GROUND_LEAKAGE_ALM_LIM                      1.3
#define FAC_CMD_GROUND_LEAKAGE_ITLK_LIM                     1.5

#define FAC_CMD_INDUC_OVERTEMP_ALM_LIM                      50.0
#define FAC_CMD_INDUC_OVERTEMP_ITLK_LIM                     60.0

#define FAC_CMD_HS_OVERTEMP_ALM_LIM                         50.0
#define FAC_CMD_HS_OVERTEMP_ITLK_LIM                        60.0

#define FAC_CMD_RH_OVERHUMIDITY_ALM_LIM                     50.0
#define FAC_CMD_RH_OVERHUMIDITY_ITLK_LIM                    90.0

#define FAC_CMD_BOARD_OVERTEMP_ALM_LIM                      50.0
#define FAC_CMD_BOARD_OVERTEMP_ITLK_LIM                     60.0

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range

//Sensor Hall

//CurrentCh1Init and CurrentCh2Init and CurrentCh3Init and CurrentCh4Init

#define Hall_Primary_Current                                000.0

#define Hall_Secondary_Current                              0.000

#define Hall_Burden_Resistor                                00.0

//Debouncing delay_ms
#define Hall_Delay                                          0

#define CurrentCh1Enable                                    OFF
#define CurrentCh2Enable                                    OFF
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Cap_Bank                         600.0

#define LV_Primary_Voltage_Vout                             300.0

#define LV_Primary_Voltage_GND_Leakage                      4.86

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_ms
#define Delay_Voltage_Cap_Bank                              3

//Debouncing delay_ms
#define Delay_Vout                                          3

//Debouncing delay_ms
#define Delay_GND_Leakage                                   3

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  ON
#define LvCurrentCh3Enable                                  ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                                      4
#define Delay_PT100CH2                                      4

#define Pt100Ch1Enable                                      ON
#define Pt100Ch2Enable                                      ON
#define Pt100Ch3Enable                                      OFF
#define Pt100Ch4Enable                                      OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                                         0
#define Delay_IGBT2                                         0

#define TempIgbt1Enable                                     OFF
#define TempIgbt2Enable                                     OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                                     3
#define Delay_BoardRh                                       3

#define BoardTempEnable                                     ON
#define RhEnable                                            ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                                 3
#define Delay_DriverCurrent                                 3

#define DriverVoltageEnable                                 ON  //Voltage Aux and Idb enable
#define Driver1CurrentEnable                                ON  //Current Aux enable
#define Driver2CurrentEnable                                ON  //Current Idb enable

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                               OFF
#define Driver1BotErrorEnable                               OFF
#define Driver1OverTempEnable                               OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                               OFF
#define Driver2BotErrorEnable                               OFF
#define Driver2OverTempEnable                               OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                                    OFF
#define VoltageCh2Enable                                    OFF
#define VoltageCh3Enable                                    OFF
#define VoltageCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define Gpdi1Enable                                         OFF
#define Gpdi2Enable                                         OFF
#define Gpdi3Enable                                         OFF
#define Gpdi4Enable                                         OFF
#define Gpdi5Enable                                         ON  // Main Over Current
#define Gpdi6Enable                                         ON  // Emergency Button
#define Gpdi7Enable                                         OFF // Main Under Voltage
#define Gpdi8Enable                                         OFF // Main Over Voltage
#define Gpdi9Enable                                         OFF
#define Gpdi10Enable                                        OFF
#define Gpdi11Enable                                        OFF
#define Gpdi12Enable                                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                                         OFF
#define Gpdo2Enable                                         OFF
#define Gpdo3Enable                                         OFF
#define Gpdo4Enable                                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                                       ON
#define ReleExtItlkEnable                                   ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* BO_FAM_PS_B1_and_B2__CMD */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAC Giga de Testes CMD

#ifdef FAC_GIGA_TESTE__CMD

#define FAC_CMD

#define ON                                                  1
#define OFF                                                 0

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ALM_LIM                 270.0
#define FAC_CMD_CAPBANK_OVERVOLTAGE_ITLK_LIM                290.0

#define FAC_CMD_OUTPUT_OVERVOLTAGE_ALM_LIM                  220.0
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ITLK_LIM                 240.0

#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ALM_LIM      16.0
#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ITLK_LIM     17.0

#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_GROUND_LEAKAGE_ALM_LIM                      45.0
#define FAC_CMD_GROUND_LEAKAGE_ITLK_LIM                     50.0

#define FAC_CMD_INDUC_OVERTEMP_ALM_LIM                      55.0
#define FAC_CMD_INDUC_OVERTEMP_ITLK_LIM                     60.0

#define FAC_CMD_HS_OVERTEMP_ALM_LIM                         55.0
#define FAC_CMD_HS_OVERTEMP_ITLK_LIM                        60.0

#define FAC_CMD_RH_OVERHUMIDITY_ALM_LIM                     50.0
#define FAC_CMD_RH_OVERHUMIDITY_ITLK_LIM                    90.0

#define FAC_CMD_BOARD_OVERTEMP_ALM_LIM                      50.0
#define FAC_CMD_BOARD_OVERTEMP_ITLK_LIM                     60.0

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range

//Sensor Hall

//CurrentCh1Init and CurrentCh2Init and CurrentCh3Init and CurrentCh4Init

#define Hall_Primary_Current                                000.0

#define Hall_Secondary_Current                              0.000

#define Hall_Burden_Resistor                                00.0

//Debouncing delay_ms
#define Hall_Delay                                          0

#define CurrentCh1Enable                                    OFF
#define CurrentCh2Enable                                    OFF
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Cap_Bank                         600.0

#define LV_Primary_Voltage_Vout                             300.0

#define LV_Primary_Voltage_GND_Leakage                      50.0

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_ms
#define Delay_Voltage_Cap_Bank                              3

//Debouncing delay_ms
#define Delay_Vout                                          3

//Debouncing delay_ms
#define Delay_GND_Leakage                                   3

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  ON
#define LvCurrentCh3Enable                                  ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                                      4
#define Delay_PT100CH2                                      4

#define Pt100Ch1Enable                                      ON
#define Pt100Ch2Enable                                      ON
#define Pt100Ch3Enable                                      OFF
#define Pt100Ch4Enable                                      OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                                         0
#define Delay_IGBT2                                         0

#define TempIgbt1Enable                                     OFF
#define TempIgbt2Enable                                     OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                                     3
#define Delay_BoardRh                                       3

#define BoardTempEnable                                     ON
#define RhEnable                                            ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                                 3
#define Delay_DriverCurrent                                 3

#define DriverVoltageEnable                                 ON  //Voltage Aux and Idb enable
#define Driver1CurrentEnable                                ON  //Current Aux enable
#define Driver2CurrentEnable                                ON  //Current Idb enable

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                               OFF
#define Driver1BotErrorEnable                               OFF
#define Driver1OverTempEnable                               OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                               OFF
#define Driver2BotErrorEnable                               OFF
#define Driver2OverTempEnable                               OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                                    OFF
#define VoltageCh2Enable                                    OFF
#define VoltageCh3Enable                                    OFF
#define VoltageCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define Gpdi1Enable                                         OFF
#define Gpdi2Enable                                         OFF
#define Gpdi3Enable                                         OFF
#define Gpdi4Enable                                         OFF
#define Gpdi5Enable                                         ON  // Main Over Current
#define Gpdi6Enable                                         ON  // Emergency Button
#define Gpdi7Enable                                         ON  // Main Under Voltage
#define Gpdi8Enable                                         ON  // Main Over Voltage
#define Gpdi9Enable                                         OFF
#define Gpdi10Enable                                        OFF
#define Gpdi11Enable                                        OFF
#define Gpdi12Enable                                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                                         OFF
#define Gpdo2Enable                                         OFF
#define Gpdo3Enable                                         OFF
#define Gpdo4Enable                                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                                       ON
#define ReleExtItlkEnable                                   ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAC_GIGA_TESTE__CMD */

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAC_CMD_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////





