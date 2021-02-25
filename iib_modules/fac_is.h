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
 * @file fac_is.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 20 de out de 2018
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FAC_IS_H_
#define FAC_IS_H_

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
    } Iin;

    bool IinAlarmSts;
    bool IinItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } VdcLink;

    bool VdcLinkAlarmSts;
    bool VdcLinkItlkSts;

    union {
        float       f;
        uint8_t     u8[4];
    } TempIGBT1;

    bool TempIGBT1AlarmSts;
    bool TempIGBT1ItlkSts;
    bool TempIGBT1HwrItlk;
    bool TempIGBT1HwrItlkSts;

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

    bool Driver1ErrorTop;
    bool Driver1ErrorTopItlkSts;

    bool Driver1ErrorBot;
    bool Driver1ErrorBotItlkSts;

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

} fac_is_t;

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_IS_DCLINK_OVERVOLTAGE_ITLK         0x00000001
#define FAC_IS_INPUT_OVERCURRENT_ITLK          0x00000002
#define FAC_IS_IGBT1_OVERTEMP_ITLK             0x00000004
#define FAC_IS_IGBT1_HWR_OVERTEMP_ITLK         0x00000008
#define FAC_IS_DRIVER_OVERVOLTAGE_ITLK         0x00000010
#define FAC_IS_DRIVER1_OVERCURRENT_ITLK        0x00000020
#define FAC_IS_DRIVER1_ERROR_TOP_ITLK          0x00000040
#define FAC_IS_DRIVER1_ERROR_BOT_ITLK          0x00000080
#define FAC_IS_INDUC_OVERTEMP_ITLK             0x00000100
#define FAC_IS_HS_OVERTEMP_ITLK                0x00000200
#define FAC_IS_BOARD_IIB_OVERTEMP_ITLK         0x00000400
#define FAC_IS_BOARD_IIB_OVERHUMIDITY_ITLK     0x00000800

/////////////////////////////////////////////////////////////////////////////////////////////

#define FAC_IS_DCLINK_OVERVOLTAGE_ALM          0x00000001
#define FAC_IS_INPUT_OVERCURRENT_ALM           0x00000002
#define FAC_IS_IGBT1_OVERTEMP_ALM              0x00000004
#define FAC_IS_DRIVER_OVERVOLTAGE_ALM          0x00000008
#define FAC_IS_DRIVER1_OVERCURRENT_ALM         0x00000010
#define FAC_IS_INDUC_OVERTEMP_ALM              0x00000020
#define FAC_IS_HS_OVERTEMP_ALM                 0x00000040
#define FAC_IS_BOARD_IIB_OVERTEMP_ALM          0x00000080
#define FAC_IS_BOARD_IIB_OVERHUMIDITY_ALM      0x00000100

/////////////////////////////////////////////////////////////////////////////////////////////

extern void clear_fac_is_interlocks(void);
extern uint8_t check_fac_is_interlocks(void);
extern void clear_fac_is_alarms(void);
extern uint8_t check_fac_is_alarms(void);
extern void check_fac_is_indication_leds(void);
extern void fac_is_application_readings(void);
extern void config_module_fac_is(void);

extern fac_is_t fac_is;

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSC01 / PA-RaPSC02

//BO-FAM:PS-QF

#ifdef BO_FAM_PS_QF__IS

#define FAC_IS

#define ON                                                  1
#define OFF                                                 0

#define FAC_IS_DCLINK_OVERVOLTAGE_ALM_LIM                   560.0
#define FAC_IS_DCLINK_OVERVOLTAGE_ITLK_LIM                  580.0

#define FAC_IS_INPUT_OVERCURRENT_ALM_LIM                    130.0
#define FAC_IS_INPUT_OVERCURRENT_ITLK_LIM                   140.0

#define FAC_IS_IGBT1_OVERTEMP_ALM_LIM                       60.0
#define FAC_IS_IGBT1_OVERTEMP_ITLK_LIM                      80.0

#define FAC_IS_DRIVER_OVERVOLTAGE_ALM_LIM                   16.0
#define FAC_IS_DRIVER_OVERVOLTAGE_ITLK_LIM                  17.0

#define FAC_IS_DRIVER1_OVERCURRENT_ALM_LIM                  2.0
#define FAC_IS_DRIVER1_OVERCURRENT_ITLK_LIM                 2.4

#define FAC_IS_INDUC_OVERTEMP_ALM_LIM                       50.0
#define FAC_IS_INDUC_OVERTEMP_ITLK_LIM                      60.0

#define FAC_IS_HS_OVERTEMP_ALM_LIM                          50.0
#define FAC_IS_HS_OVERTEMP_ITLK_LIM                         60.0

#define FAC_IS_RH_OVERHUMIDITY_ALM_LIM                      80.0
#define FAC_IS_RH_OVERHUMIDITY_ITLK_LIM                     90.0

#define FAC_IS_BOARD_OVERTEMP_ALM_LIM                       50.0
#define FAC_IS_BOARD_OVERTEMP_ITLK_LIM                      60.0

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range

//Sensor Hall

//CurrentCh1Init and CurrentCh2Init and CurrentCh3Init and CurrentCh4Init

#define Hall_Primary_Current                                300.0

#define Hall_Secondary_Current                              0.150

#define Hall_Burden_Resistor                                50.0

//Debouncing delay_ms
#define Hall_Delay                                          10

#define CurrentCh1Enable                                    ON
#define CurrentCh2Enable                                    OFF
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                              600.0

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_ms
#define Delay_Voltage_Vin                                   10

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  OFF
#define LvCurrentCh3Enable                                  OFF

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

#define Delay_IGBT1                                         3
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

#define Gpdo1Enable                                         OFF
#define Gpdo2Enable                                         OFF
#define Gpdo3Enable                                         OFF
#define Gpdo4Enable                                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                                       ON
#define ReleExtItlkEnable                                   ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* BO_FAM_PS_QF__IS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack BO-FAM:PS-B-1 --> PA-RaPSE01 / PA-RaPSE02 / PA-RaPSE03 / PA-RaPSE04 / PA-RaPSE06 / PA-RaPSE07 / PA-RaPSE08 / PA-RaPSE09

//Rack BO-FAM:PS-B-2 --> PA-RaPSF01 / PA-RaPSF02 / PA-RaPSF03 / PA-RaPSF04 / PA-RaPSF06 / PA-RaPSF07 / PA-RaPSF08 / PA-RaPSF09

//BO-FAM:PS-B-1 / B-2

#ifdef BO_FAM_PS_B1_and_B2__IS

#define FAC_IS

#define ON                                                  1
#define OFF                                                 0

#define FAC_IS_DCLINK_OVERVOLTAGE_ALM_LIM                   590.0
#define FAC_IS_DCLINK_OVERVOLTAGE_ITLK_LIM                  600.0

#define FAC_IS_INPUT_OVERCURRENT_ALM_LIM                    160.0
#define FAC_IS_INPUT_OVERCURRENT_ITLK_LIM                   170.0

#define FAC_IS_IGBT1_OVERTEMP_ALM_LIM                       60.0
#define FAC_IS_IGBT1_OVERTEMP_ITLK_LIM                      80.0

#define FAC_IS_DRIVER_OVERVOLTAGE_ALM_LIM                   16.0
#define FAC_IS_DRIVER_OVERVOLTAGE_ITLK_LIM                  17.0

#define FAC_IS_DRIVER1_OVERCURRENT_ALM_LIM                  2.0
#define FAC_IS_DRIVER1_OVERCURRENT_ITLK_LIM                 2.4

#define FAC_IS_INDUC_OVERTEMP_ALM_LIM                       50.0
#define FAC_IS_INDUC_OVERTEMP_ITLK_LIM                      60.0

#define FAC_IS_HS_OVERTEMP_ALM_LIM                          50.0
#define FAC_IS_HS_OVERTEMP_ITLK_LIM                         60.0

#define FAC_IS_RH_OVERHUMIDITY_ALM_LIM                      80.0
#define FAC_IS_RH_OVERHUMIDITY_ITLK_LIM                     90.0

#define FAC_IS_BOARD_OVERTEMP_ALM_LIM                       50.0
#define FAC_IS_BOARD_OVERTEMP_ITLK_LIM                      60.0

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range

//Sensor Hall

//CurrentCh1Init and CurrentCh2Init and CurrentCh3Init and CurrentCh4Init

#define Hall_Primary_Current                                300.0

#define Hall_Secondary_Current                              0.150

#define Hall_Burden_Resistor                                50.0

//Debouncing delay_ms
#define Hall_Delay                                          10

#define CurrentCh1Enable                                    ON
#define CurrentCh2Enable                                    OFF
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                              600.0

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_ms
#define Delay_Voltage_Vin                                   10

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  OFF
#define LvCurrentCh3Enable                                  OFF

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

#define Delay_IGBT1                                         3
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

#define Gpdo1Enable                                         OFF
#define Gpdo2Enable                                         OFF
#define Gpdo3Enable                                         OFF
#define Gpdo4Enable                                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                                       ON
#define ReleExtItlkEnable                                   ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* BO_FAM_PS_B1_and_B2__IS */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAC Giga de Testes IS

#ifdef FAC_GIGA_TESTE__IS

#define FAC_IS

#define ON                                                  1
#define OFF                                                 0

#define FAC_IS_DCLINK_OVERVOLTAGE_ALM_LIM                   580.0
#define FAC_IS_DCLINK_OVERVOLTAGE_ITLK_LIM                  590.0

#define FAC_IS_INPUT_OVERCURRENT_ALM_LIM                    160.0
#define FAC_IS_INPUT_OVERCURRENT_ITLK_LIM                   170.0

#define FAC_IS_IGBT1_OVERTEMP_ALM_LIM                       60.0
#define FAC_IS_IGBT1_OVERTEMP_ITLK_LIM                      80.0

#define FAC_IS_DRIVER_OVERVOLTAGE_ALM_LIM                   16.0
#define FAC_IS_DRIVER_OVERVOLTAGE_ITLK_LIM                  17.0

#define FAC_IS_DRIVER1_OVERCURRENT_ALM_LIM                  2.0
#define FAC_IS_DRIVER1_OVERCURRENT_ITLK_LIM                 2.4

#define FAC_IS_INDUC_OVERTEMP_ALM_LIM                       55.0
#define FAC_IS_INDUC_OVERTEMP_ITLK_LIM                      60.0

#define FAC_IS_HS_OVERTEMP_ALM_LIM                          50.0
#define FAC_IS_HS_OVERTEMP_ITLK_LIM                         60.0

#define FAC_IS_RH_OVERHUMIDITY_ALM_LIM                      50.0
#define FAC_IS_RH_OVERHUMIDITY_ITLK_LIM                     90.0

#define FAC_IS_BOARD_OVERTEMP_ALM_LIM                       50.0
#define FAC_IS_BOARD_OVERTEMP_ITLK_LIM                      60.0

/////////////////////////////////////////////////////////////////////////////////////////////

//Set current range

//Sensor Hall

//CurrentCh1Init and CurrentCh2Init and CurrentCh3Init and CurrentCh4Init

#define Hall_Primary_Current                                300.0

#define Hall_Secondary_Current                              0.150

#define Hall_Burden_Resistor                                50.0

//Debouncing delay_ms
#define Hall_Delay                                          10

#define CurrentCh1Enable                                    ON
#define CurrentCh2Enable                                    OFF
#define CurrentCh3Enable                                    OFF
#define CurrentCh4Enable                                    OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//Set LV 20P range

//LvCurrentCh1Init and LvCurrentCh2Init and LvCurrentCh3Init

#define LV_Primary_Voltage_Vin                              600.0

#define LV_Secondary_Current_Vin                            0.025

#define LV_Burden_Resistor                                  120.0

//Debouncing delay_ms
#define Delay_Voltage_Vin                                   10

#define LvCurrentCh1Enable                                  ON
#define LvCurrentCh2Enable                                  OFF
#define LvCurrentCh3Enable                                  OFF

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

#define Delay_IGBT1                                         3
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

#define Gpdo1Enable                                         OFF
#define Gpdo2Enable                                         OFF
#define Gpdo3Enable                                         OFF
#define Gpdo4Enable                                         OFF

/////////////////////////////////////////////////////////////////////////////////////////////

//ReleAux and ReleExtItlk configuration

#define ReleAuxEnable                                       ON
#define ReleExtItlkEnable                                   ON

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAC_GIGA_TESTE__IS */

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAC_IS_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////






