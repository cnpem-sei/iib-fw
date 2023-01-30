/*
 * fac_giga_teste__os.h
 *
 *  Created on: 20 de jun de 2022
 *      Author: rogerio.marcondeli
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FAC_GIGA_TESTE__OS_H_
#define FAC_GIGA_TESTE__OS_H_

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAC Giga de Testes OS

///////////////////////

#define FAC_OS

#define ON                                                  1
#define OFF                                                 0

#define FAC_OS_INPUT_OVERVOLTAGE_ALM_LIM                    290.0
#define FAC_OS_INPUT_OVERVOLTAGE_ITLK_LIM                   295.0

#define FAC_OS_INPUT_OVERCURRENT_ALM_LIM                    430.0
#define FAC_OS_INPUT_OVERCURRENT_ITLK_LIM                   440.0

#define FAC_OS_OUTPUT_OVERCURRENT_ALM_LIM                   570.0
#define FAC_OS_OUTPUT_OVERCURRENT_ITLK_LIM                  590.0

#define FAC_OS_IGBT1_OVERTEMP_ALM_LIM                       60.0
#define FAC_OS_IGBT1_OVERTEMP_ITLK_LIM                      80.0

#define FAC_OS_IGBT2_OVERTEMP_ALM_LIM                       60.0
#define FAC_OS_IGBT2_OVERTEMP_ITLK_LIM                      80.0

#define FAC_OS_DRIVER_OVERVOLTAGE_ALM_LIM                   16.0
#define FAC_OS_DRIVER_OVERVOLTAGE_ITLK_LIM                  17.0

#define FAC_OS_DRIVER1_OVERCURRENT_ALM_LIM                  2.0
#define FAC_OS_DRIVER1_OVERCURRENT_ITLK_LIM                 2.4

#define FAC_OS_DRIVER2_OVERCURRENT_ALM_LIM                  2.0
#define FAC_OS_DRIVER2_OVERCURRENT_ITLK_LIM                 2.4

#define FAC_OS_GROUND_LEAKAGE_ALM_LIM                       0.450
#define FAC_OS_GROUND_LEAKAGE_ITLK_LIM                      0.650

#define FAC_OS_INDUC_OVERTEMP_ALM_LIM                       40.0
#define FAC_OS_INDUC_OVERTEMP_ITLK_LIM                      45.0

#define FAC_OS_HS_OVERTEMP_ALM_LIM                          40.0
#define FAC_OS_HS_OVERTEMP_ITLK_LIM                         45.0

#define FAC_OS_RH_OVERHUMIDITY_ALM_LIM                      60.0
#define FAC_OS_RH_OVERHUMIDITY_ITLK_LIM                     90.0

#define FAC_OS_BOARD_OVERTEMP_ALM_LIM                       50.0
#define FAC_OS_BOARD_OVERTEMP_ITLK_LIM                      60.0

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range

//Sensor Hall

//CurrentCh1Init and CurrentCh2Init and CurrentCh3Init and CurrentCh4Init

#define Hall_Primary_Current_Iin                            300.0

#define Hall_Primary_Current_Iout                           500.0

#define Hall_Secondary_Current_Iin                          0.150

#define Hall_Secondary_Current_Iout                         0.100

#define Hall_Burden_Resistor                                50.0

//Debouncing delay_us
#define Hall_Delay                                          0

#define CurrentCh1Enable                                    ON
#define CurrentCh2Enable                                    ON
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                              602.5 // resistores mais 250 ohms do LV 20P

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_us
#define Delay_Voltage_Vin                                   3

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  OFF
#define LvCurrentCh3Enable                                  OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing delay_ms

#define Delay_PT100CH1                                      2
#define Delay_PT100CH2                                      2

#define Pt100Ch1Enable                                      ON
#define Pt100Ch2Enable                                      ON
#define Pt100Ch3Enable                                      OFF
#define Pt100Ch4Enable                                      OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                                         3
#define Delay_IGBT2                                         3

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

#define DriverVoltageEnable                                 OFF
#define Driver1CurrentEnable                                OFF
#define Driver2CurrentEnable                                OFF

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
#define Delay_GND_Leakage                                   100

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
#define Gpdi5Enable                                         OFF
#define Gpdi6Enable                                         OFF
#define Gpdi7Enable                                         OFF
#define Gpdi8Enable                                         OFF
#define Gpdi9Enable                                         OFF
#define Gpdi10Enable                                        OFF
#define Gpdi11Enable                                        OFF
#define Gpdi12Enable                                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                                         ON
#define Gpdo2Enable                                         ON
#define Gpdo3Enable                                         OFF
#define Gpdo4Enable                                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                                       ON
#define ReleExtItlkEnable                                   ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAC_GIGA_TESTE__OS_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////




