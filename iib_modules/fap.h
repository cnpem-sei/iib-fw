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
 * @file fap.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_H_
#define FAP_H_

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
    } Vin;

    bool VinAlarmSts;
    bool VinItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } Vout;

    bool VoutAlarmSts;
    bool VoutItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } IoutA1;

    bool IoutA1AlarmSts;
    bool IoutA1ItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } IoutA2;

    bool IoutA2AlarmSts;
    bool IoutA2ItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } GroundLeakage;

    bool GroundLeakageItlkSts;
    bool GroundLeakageAlarmSts;

    union {
        float       f;
        uint8_t     u8[4];
    } TempIGBT1;

    bool TempIGBT1AlarmSts;
    bool TempIGBT1ItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } TempIGBT2;

    bool TempIGBT2AlarmSts;
    bool TempIGBT2ItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } DriveVoltage;

    bool DriveVoltageAlarmSts;
    bool DriveVoltageItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } Drive1Current;

    bool Drive1CurrentAlarmSts;
    bool Drive1CurrentItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } Drive2Current;

    bool Drive2CurrentAlarmSts;
    bool Drive2CurrentItlkSts;

    bool Driver1Error;
    bool Driver1ErrorItlkSts;
    bool Driver2Error;
    bool Driver2ErrorItlkSts;

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

    bool Relay;
    bool ExternalItlk;
    bool ExternalItlkSts;
    bool Rack;
    bool RackItlkSts;

    bool ReleAuxItlkSts;
    bool ReleExtItlkSts;
    bool RelayOpenItlkSts;
    bool RelayContactStickingItlkSts;

} fap_t;

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAP_INPUT_OVERVOLTAGE_ITLK          0x00000001
#define FAP_OUTPUT_OVERVOLTAGE_ITLK         0x00000002
#define FAP_OUTPUT_OVERCURRENT_1_ITLK       0x00000004
#define FAP_OUTPUT_OVERCURRENT_2_ITLK       0x00000008
#define FAP_IGBT1_OVERTEMP_ITLK             0x00000010
#define FAP_IGBT2_OVERTEMP_ITLK             0x00000020
#define FAP_DRIVER_OVERVOLTAGE_ITLK         0x00000040
#define FAP_DRIVER1_OVERCURRENT_ITLK        0x00000080
#define FAP_DRIVER2_OVERCURRENT_ITLK        0x00000100
#define FAP_DRIVER1_ERROR_ITLK              0x00000200
#define FAP_DRIVER2_ERROR_ITLK              0x00000400
#define FAP_INDUC_OVERTEMP_ITLK             0x00000800
#define FAP_HS_OVERTEMP_ITLK                0x00001000
#define FAP_RELAY_ITLK                      0x00002000
#define FAP_RELAY_CONTACT_STICKING_ITLK     0x00004000
#define FAP_EXTERNAL_ITLK                   0x00008000
#define FAP_RACK_ITLK                       0x00010000
#define FAP_GROUND_LKG_ITLK                 0x00020000
#define FAP_BOARD_IIB_OVERTEMP_ITLK         0x00040000
#define FAP_BOARD_IIB_OVERHUMIDITY_ITLK     0x00080000

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAP_INPUT_OVERVOLTAGE_ALM           0x00000001
#define FAP_OUTPUT_OVERVOLTAGE_ALM          0x00000002
#define FAP_OUTPUT_OVERCURRENT_1_ALM        0x00000004
#define FAP_OUTPUT_OVERCURRENT_2_ALM        0x00000008
#define FAP_IGBT1_OVERTEMP_ALM              0x00000010
#define FAP_IGBT2_OVERTEMP_ALM              0x00000020
#define FAP_DRIVER_OVERVOLTAGE_ALM          0x00000040
#define FAP_DRIVER1_OVERCURRENT_ALM         0x00000080
#define FAP_DRIVER2_OVERCURRENT_ALM         0x00000100
#define FAP_INDUC_OVERTEMP_ALM              0x00000200
#define FAP_HS_OVERTEMP_ALM                 0x00000400
#define FAP_GROUND_LKG_ALM                  0x00000800
#define FAP_BOARD_IIB_OVERTEMP_ALM          0x00001000
#define FAP_BOARD_IIB_OVERHUMIDITY_ALM      0x00002000

/////////////////////////////////////////////////////////////////////////////////////////////

extern void clear_fap_interlocks(void);
extern uint8_t check_fap_interlocks(void);
extern void clear_fap_alarms(void);
extern uint8_t check_fap_alarms(void);
extern void check_fap_indication_leds(void);
extern void fap_application_readings(void);
extern void config_module_fap(void);

extern fap_t fap;

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA01

//SI-FAM:PS-QFA

#ifdef SI_FAM_PS_QFA

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           170.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          180.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          80.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         85.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       90.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       90.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-QFA */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA01

//SI-FAM:PS-QFP

#ifdef SI_FAM_PS_QFP

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           170.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          180.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          110.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         120.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       90.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       90.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-QFP */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA01

//SI-FAM:PS-QFB

#ifdef SI_FAM_PS_QFB

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           350.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          360.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          190.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         200.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       90.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       90.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-QFB */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA03

//SI-FAM:PS-QDA / QDP1 / QDP2

#ifdef SI_FAM_PS_QDA_QDP1_QDP2

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           110.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          120.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          60.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         65.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       90.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       90.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-QDA / QDP1 / QDP2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA04

//SI-FAM:PS-QDB1 / QDB2

#ifdef SI_FAM_PS_QDB1_QDB2

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           210.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          220.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          110.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         115.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       90.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        85.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       90.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-QDB1 / QDB2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA06 / PA-RaPSA07

//SI-FAM:PS-Q1 / Q2 / Q3 / Q4

#ifdef SI_FAM_PS_Q1_Q2_Q3_Q4

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           430.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          440.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          255.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         260.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        90.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       95.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        90.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       95.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              65
#define FAP_INDUC_OVERTEMP_ITLK_LIM             70

#define FAP_HS_OVERTEMP_ALM_LIM                 45
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 335.833333

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-Q1 / Q2 / Q3 / Q4 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB01 / PA-RaPSB03 / PA-RaPSB04 / PA-RaPSB05 / PA-RaPSB07 / PA-RaPSB08 / PA-RaPSB10

// DCLink 130V

//SI-FAM:PS-SDA0 / SDP0 / SFA0 / SFP0 / SDA1 / SDA2 / SDA3 / SFA1 / SFA2 / SDP1 / SDP2 / SDP3 / SFP1 / SFP2

#ifdef SI_FAM_PS_SDA0_SDP0_SFA0_SFP0_SDA1_SDA2_SDA3_SFA1_SFA2_SDP1_SDP2_SDP3_SFP1_SFP2

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           140.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          145.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          80.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         85.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        90.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       100.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        90.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       100.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-SDA0 / SDP0 / SFA0 / SFP0 / SDA1 / SDA2 / SDA3 / SFA1 / SFA2 / SDP1 / SDP2 / SDP3 / SFP1 / SFP2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB01 / PA-RaPSB03 / PA-RaPSB04 / PA-RaPSB05 / PA-RaPSB07 / PA-RaPSB08 / PA-RaPSB10

// DCLink 200V

//SI-FAM:PS-SDB0 / SDB1 / SDB2 / SDB3 / SFB0 / SFB1 / SFB2

#ifdef SI_FAM_PS_SDB0_SDB1_SDB2_SDB3_SFB0_SFB1_SFB2

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           210.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          215.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          135.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         140.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        90.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       100.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        90.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       100.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-SDB0 / SDB1 / SDB2 / SDB3 / SFB0 / SFB1 / SFB2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSD02 / PA-RaPSD06

//SI-FAM:PS-B1B2-1 / B1B2-2 / 4 MÓDULOS

#ifdef SI_FAM_PS_B1B2_1_and_B1B2_2

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           400.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          420.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          300.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         310.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        115.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       130.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        115.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       130.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              65
#define FAP_INDUC_OVERTEMP_ITLK_LIM             70

#define FAP_HS_OVERTEMP_ALM_LIM                 45
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             70
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 335.833333

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               500

//Debouncing delay_ms
#define Delay_Vout                              500

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_SALA_FONTES

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             ON  // RackITLK
#define Gpdi8Enable                             ON  // RelayStatus
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* SI-FAM:PS-B1B2-1 / B1B2-2 / 4 MÓDULOS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS01

//Source 750A

//TS-FAM:PS-B / 4 MÓDULOS

#ifdef TS_FAM_PS_B

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           55.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          60.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          40.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         45.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        100.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       105.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        100.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       105.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_LT

#define Gpdi1Enable                             ON  // ExternalITLK
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             ON  // RackITLK
#define Gpdi4Enable                             ON  // RelayStatus
#define Gpdi5Enable                             OFF
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             OFF
#define Gpdi8Enable                             OFF
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* TS-FAM:PS-B / 4 MÓDULOS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS03

//Source 300A

//TB-FAM:PS-B

#ifdef TB_FAM_PS_B

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           55.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          60.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          17.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         20.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        151.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       152.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        151.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       152.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              50
#define FAP_INDUC_OVERTEMP_ITLK_LIM             60

#define FAP_HS_OVERTEMP_ALM_LIM                 60
#define FAP_HS_OVERTEMP_ITLK_LIM                70

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 150 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      150.0

#define LA_Secondary_Current                    0.150

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               3

//Debouncing delay_ms
#define Delay_Vout                              3

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_LT

#define Gpdi1Enable                             ON  // ExternalITLK
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             ON  // RackITLK
#define Gpdi4Enable                             ON  // RelayStatus
#define Gpdi5Enable                             OFF
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             OFF
#define Gpdi8Enable                             OFF
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* TB-FAM:PS-B */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS03 / LA-RaPS05

//TS-01:PS-QF1A / TS-01:PS-QF1B / TS-02:PS-QF2 / TS-02:PS-QD2 / TS-03:PS-QF3 / TS-04:PS-QF4 / TS-04:PS-QD4A / TS-04:PS-QD4B

#ifdef TS_01_PS_QF1A_TS_01_PS_QF1B_TS_02_PS_QF2_TS_02_PS_QD2_TS_03_PS_QF3_TS_04_PS_QF4_TS_04_PS_QD4A_TS_04_PS_QD4B

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           30.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          35.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          15.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         20.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        80.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       85.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        80.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       85.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              45.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             50.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              40
#define FAP_INDUC_OVERTEMP_ITLK_LIM             50

#define FAP_HS_OVERTEMP_ALM_LIM                 40
#define FAP_HS_OVERTEMP_ITLK_LIM                50

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  452.5

#define LV_Primary_Voltage_Vout                 252.5

#define LV_Primary_Voltage_GND_Leakage          50.0

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define SIRIUS_LT

#define Gpdi1Enable                             ON  // ExternalITLK
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             ON  // RackITLK
#define Gpdi4Enable                             ON  // RelayStatus
#define Gpdi5Enable                             OFF
#define Gpdi6Enable                             OFF
#define Gpdi7Enable                             OFF
#define Gpdi8Enable                             OFF
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* TS-01:PS-QF1A / TS-01:PS-QF1B / TS-02:PS-QF2 / TS-02:PS-QD2 / TS-03:PS-QF3 / TS-04:PS-QF4 / TS-04:PS-QD4A / TS-04:PS-QD4B */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAP Giga de Testes IGBT 1200V

#ifdef FAP_GIGA_TESTE_IGBT_1200V

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           555.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          560.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          260.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         270.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        115.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       120.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        115.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       120.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              40.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             45.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              70
#define FAP_INDUC_OVERTEMP_ITLK_LIM             80

#define FAP_HS_OVERTEMP_ALM_LIM                 50
#define FAP_HS_OVERTEMP_ITLK_LIM                60

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  722.5

#define LV_Primary_Voltage_Vout                 302.5

#define LV_Primary_Voltage_GND_Leakage          52.5

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         ON
#define TempIgbt2Enable                         ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define GIGA

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             ON  // RackITLK
#define Gpdi7Enable                             ON  // RelayStatus
#define Gpdi8Enable                             OFF
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAP Giga de Testes IGBT 1200V */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Giga de Testes 4 IIBs

#ifdef GIGA_TESTES_IIBs

#define FAP

#define ON                                      1
#define OFF                                     0

#define FAP_INPUT_OVERVOLTAGE_ALM_LIM           555.0
#define FAP_INPUT_OVERVOLTAGE_ITLK_LIM          560.0

#define FAP_OUTPUT_OVERVOLTAGE_ALM_LIM          260.0
#define FAP_OUTPUT_OVERVOLTAGE_ITLK_LIM         270.0

#define FAP_OUTPUT_OVERCURRENT_1_ALM_LIM        115.0
#define FAP_OUTPUT_OVERCURRENT_1_ITLK_LIM       120.0

#define FAP_OUTPUT_OVERCURRENT_2_ALM_LIM        115.0
#define FAP_OUTPUT_OVERCURRENT_2_ITLK_LIM       120.0

#define FAP_GROUND_LEAKAGE_ALM_LIM              40.0
#define FAP_GROUND_LEAKAGE_ITLK_LIM             45.0

#define FAP_IGBT1_OVERTEMP_ALM_LIM              60
#define FAP_IGBT1_OVERTEMP_ITLK_LIM             80

#define FAP_IGBT2_OVERTEMP_ALM_LIM              60
#define FAP_IGBT2_OVERTEMP_ITLK_LIM             80

#define FAP_DRIVER_OVERVOLTAGE_ALM_LIM          16.0
#define FAP_DRIVER_OVERVOLTAGE_ITLK_LIM         17.0

#define FAP_DRIVER1_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER1_OVERCURRENT_ITLK_LIM        2.4

#define FAP_DRIVER2_OVERCURRENT_ALM_LIM         2.0
#define FAP_DRIVER2_OVERCURRENT_ITLK_LIM        2.4

#define FAP_INDUC_OVERTEMP_ALM_LIM              70
#define FAP_INDUC_OVERTEMP_ITLK_LIM             80

#define FAP_HS_OVERTEMP_ALM_LIM                 50
#define FAP_HS_OVERTEMP_ITLK_LIM                60

#define FAP_RH_OVERHUMIDITY_ALM_LIM             60
#define FAP_RH_OVERHUMIDITY_ITLK_LIM            90

#define FAP_BOARD_OVERTEMP_ALM_LIM              50
#define FAP_BOARD_OVERTEMP_ITLK_LIM             60

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range FAP 130 A

//Sensor Hall LEM LA 130-P

//CurrentCh1Init and CurrentCh2Init

#define LA_Primary_Current                      130.0

#define LA_Secondary_Current                    0.130

#define LA_Burden_Resistor                      50.0

//Debouncing delay_ms
#define LA_Delay                                3

#define CurrentCh1Enable                        ON
#define CurrentCh2Enable                        ON
#define CurrentCh3Enable                        OFF
#define CurrentCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                  34.5

#define LV_Primary_Voltage_Vout                 34.5

#define LV_Primary_Voltage_GND_Leakage          34.5

#define LV_Secondary_Current_Vin                0.025

#define LV_Burden_Resistor                      120.0

//Debouncing delay_ms
#define Delay_Vin                               100

//Debouncing delay_ms
#define Delay_Vout                              100

//Debouncing delay_ms
#define Delay_GND_Leakage                       3

#define LvCurrentCh1Enable                      ON
#define LvCurrentCh2Enable                      ON
#define LvCurrentCh3Enable                      ON

/////////////////////////////////////////////////////////////////////////////////////////////

//PT100 CH1 and CH2 configuration
//Debouncing Delay seconds

#define Delay_PT100CH1                          4
#define Delay_PT100CH2                          4

#define Pt100Ch1Enable                          ON
#define Pt100Ch2Enable                          ON
#define Pt100Ch3Enable                          OFF
#define Pt100Ch4Enable                          OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature igbt1 and igbt2 configuration
//Debouncing delay_ms

#define Delay_IGBT1                             3
#define Delay_IGBT2                             3

#define TempIgbt1Enable                         OFF
#define TempIgbt2Enable                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Temperature Board and Humidity Board configuration
//Debouncing delay_ms

#define Delay_BoardTemp                         3
#define Delay_BoardRh                           3

#define BoardTempEnable                         ON
#define RhEnable                                ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver Voltage and Driver Current configuration
//Debouncing delay_ms

#define Delay_DriverVoltage                     3
#define Delay_DriverCurrent                     3

#define DriverVoltageEnable                     ON
#define Driver1CurrentEnable                    ON
#define Driver2CurrentEnable                    ON

/////////////////////////////////////////////////////////////////////////////////////////////

//Driver1 error configuration

#define Driver1TopErrorEnable                   ON
#define Driver1BotErrorEnable                   OFF
#define Driver1OverTempEnable                   OFF

//Driver2 error configuration

#define Driver2TopErrorEnable                   ON
#define Driver2BotErrorEnable                   OFF
#define Driver2OverTempEnable                   OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Voltage configuration

#define VoltageCh1Enable                        OFF
#define VoltageCh2Enable                        OFF
#define VoltageCh3Enable                        OFF
#define VoltageCh4Enable                        OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdi configuration

#define GIGA

#define Gpdi1Enable                             OFF
#define Gpdi2Enable                             OFF
#define Gpdi3Enable                             OFF
#define Gpdi4Enable                             OFF
#define Gpdi5Enable                             ON  // ExternalITLK
#define Gpdi6Enable                             ON  // RackITLK
#define Gpdi7Enable                             ON  // RelayStatus
#define Gpdi8Enable                             OFF
#define Gpdi9Enable                             OFF
#define Gpdi10Enable                            OFF
#define Gpdi11Enable                            OFF
#define Gpdi12Enable                            OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Gpdo configuration

#define Gpdo1Enable                             OFF
#define Gpdo2Enable                             OFF
#define Gpdo3Enable                             OFF
#define Gpdo4Enable                             OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                           ON
#define ReleExtItlkEnable                       ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* GIGA_TESTES_IIBs */

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAP_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////





