/*
 * bo_fam_ps_qf__cmd.h
 *
 *  Created on: 20 de jun de 2022
 *      Author: rogerio.marcondeli
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BO_FAM_PS_QF__CMD_H_
#define BO_FAM_PS_QF__CMD_H_

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC01 / PA-RaPSC02

//BO-FAM:PS-QF

#define FAC_CMD

#define ON                                                  1
#define OFF                                                 0

#define FAC_CMD_CAPBANK_OVERVOLTAGE_ALM_LIM                 370.0
#define FAC_CMD_CAPBANK_OVERVOLTAGE_ITLK_LIM                380.0

#define FAC_CMD_OUTPUT_OVERVOLTAGE_ALM_LIM                  260.0
#define FAC_CMD_OUTPUT_OVERVOLTAGE_ITLK_LIM                 270.0

#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ALM_LIM      16.0
#define FAC_CMD_AUX_AND_IDB_SUPPLY_OVERVOLTAGE_ITLK_LIM     17.0

#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_AUX_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ALM_LIM              2.0
#define FAC_CMD_IDB_SUPPLY_OVERCURRENT_ITLK_LIM             2.4

#define FAC_CMD_GROUND_LEAKAGE_ALM_LIM                      0.600
#define FAC_CMD_GROUND_LEAKAGE_ITLK_LIM                     0.650

#define FAC_CMD_INDUC_OVERTEMP_ALM_LIM                      50.0
#define FAC_CMD_INDUC_OVERTEMP_ITLK_LIM                     60.0

#define FAC_CMD_HS_OVERTEMP_ALM_LIM                         50.0
#define FAC_CMD_HS_OVERTEMP_ITLK_LIM                        60.0

#define FAC_CMD_RH_OVERHUMIDITY_ALM_LIM                     80.0
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

//Debouncing delay_us
#define Hall_Delay                                          0

#define CurrentCh1Enable                                    OFF
#define CurrentCh2Enable                                    OFF
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Cap_Bank                         602.5 // resistores mais 250 ohms do LV 20P

#define LV_Primary_Voltage_Vout                             302.5 // resistores mais 250 ohms do LV 20P

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_us
#define Delay_Voltage_Cap_Bank                              3

//Debouncing delay_us
#define Delay_Vout                                          3

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  ON
#define LvCurrentCh3Enable                                  OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing delay_ms

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

#define ItlkBoardTempEnable                                 OFF
#define ItlkRhEnable                                        OFF

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

//VoltageCh1 convert to Current

#define Gain_LDC_Transducer 4.0 //Gain Transducer CTSR 0.3-P

//#define Gain_LDC_Transducer 1.2 //Gain Transducer CTSR 1-P

#define Gain_LDC_Amplifier 4.99

#define Current_GND_Leakage 10.0 / (Gain_LDC_Transducer * Gain_LDC_Amplifier)

//Debouncing delay_us
#define Delay_GND_Leakage                       			100

#define VoltageCh1Enable                                    ON
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

#endif /* BO_FAM_PS_QF__CMD_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////




