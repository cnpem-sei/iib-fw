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

typedef volatile struct
{
    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } Vin;

    volatile bool VinAlarmSts;
    volatile bool VinItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } Vout;

    volatile bool VoutAlarmSts;
    volatile bool VoutItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } IoutA1;

    volatile bool IoutA1AlarmSts;
    volatile bool IoutA1ItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } IoutA2;

    volatile bool IoutA2AlarmSts;
    volatile bool IoutA2ItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } GroundLeakage;

    volatile bool GroundLeakageItlkSts;
    volatile bool GroundLeakageAlarmSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } TempIGBT1;

    volatile bool TempIGBT1AlarmSts;
    volatile bool TempIGBT1ItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } TempIGBT2;

    volatile bool TempIGBT2AlarmSts;
    volatile bool TempIGBT2ItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } DriverVoltage;

    volatile bool DriverVoltageAlarmSts;
    volatile bool DriverVoltageItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } Driver1Current;

    volatile bool Driver1CurrentAlarmSts;
    volatile bool Driver1CurrentItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } Driver2Current;

    volatile bool Driver2CurrentAlarmSts;
    volatile bool Driver2CurrentItlkSts;

    volatile bool Driver1Error;
    volatile bool Driver1ErrorItlkSts;
    volatile bool Driver2Error;
    volatile bool Driver2ErrorItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } TempL;

    volatile bool TempLAlarmSts;
    volatile bool TempLItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } TempHeatSink;

    volatile bool TempHeatSinkAlarmSts;
    volatile bool TempHeatSinkItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } BoardTemperature;

    volatile bool BoardTemperatureAlarmSts;
    volatile bool BoardTemperatureItlkSts;

    union {
    	volatile float       f;
    	volatile uint8_t     u8[4];
    } RelativeHumidity;

    volatile bool RelativeHumidityAlarmSts;
    volatile bool RelativeHumidityItlkSts;

    union {
        volatile uint8_t     u8[4];
        volatile uint32_t    u32;
    } InterlocksRegister;

    union {
        volatile uint8_t     u8[4];
        volatile uint32_t    u32;
    } AlarmsRegister;

    volatile bool Relay;
    volatile bool ExternalItlk;
    volatile bool ExternalItlkSts;
    volatile bool Rack;
    volatile bool RackItlkSts;

    volatile bool ReleAuxItlkSts;
    volatile bool ReleExtItlkSts;
    volatile bool RelayOpenItlkSts;
    volatile bool RelayContactStickingItlkSts;

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

extern volatile fap_t fap;

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA01

//SI-FAM:PS-QFA

#ifdef SI_FAM_PS_QFA

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qfa.h>

#endif /* SI-FAM:PS-QFA */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA01

//SI-FAM:PS-QFP

#ifdef SI_FAM_PS_QFP

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qfp.h>

#endif /* SI-FAM:PS-QFP */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA01

//SI-FAM:PS-QFB

#ifdef SI_FAM_PS_QFB

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qfb.h>

#endif /* SI-FAM:PS-QFB */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA03

//SI-FAM:PS-QDA

#ifdef SI_FAM_PS_QDA

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qda.h>

#endif /* SI-FAM:PS-QDA */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA03

//SI-FAM:PS-QDP1

#ifdef SI_FAM_PS_QDP1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qdp1.h>

#endif /* SI-FAM:PS-QDP1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA03

//SI-FAM:PS-QDP2

#ifdef SI_FAM_PS_QDP2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qdp2.h>

#endif /* SI-FAM:PS-QDP2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA04

//SI-FAM:PS-QDB1

#ifdef SI_FAM_PS_QDB1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qdb1.h>

#endif /* SI-FAM:PS-QDB1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA04

//SI-FAM:PS-QDB2

#ifdef SI_FAM_PS_QDB2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_qdb2.h>

#endif /* SI-FAM:PS-QDB2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA06

//SI-FAM:PS-Q1

#ifdef SI_FAM_PS_Q1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_q1.h>

#endif /* SI-FAM:PS-Q1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA06

//SI-FAM:PS-Q3

#ifdef SI_FAM_PS_Q3

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_q3.h>

#endif /* SI-FAM:PS-Q3 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA07

//SI-FAM:PS-Q2

#ifdef SI_FAM_PS_Q2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_q2.h>

#endif /* SI-FAM:PS-Q2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSA07

//SI-FAM:PS-Q4

#ifdef SI_FAM_PS_Q4

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_q4.h>

#endif /* SI-FAM:PS-Q4 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB01

//SI-FAM:PS-SDA0

#ifdef SI_FAM_PS_SDA0

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sda0.h>

#endif /* SI-FAM:PS-SDA0 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB01

//SI-FAM:PS-SDP0

#ifdef SI_FAM_PS_SDP0

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdp0.h>

#endif /* SI-FAM:PS-SDP0 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB01

//SI-FAM:PS-SDB0

#ifdef SI_FAM_PS_SDB0

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdb0.h>

#endif /* SI-FAM:PS-SDB0 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB03

//SI-FAM:PS-SFA0

#ifdef SI_FAM_PS_SFA0

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfa0.h>

#endif /* SI-FAM:PS-SFA0 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB03

//SI-FAM:PS-SFP0

#ifdef SI_FAM_PS_SFP0

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfp0.h>

#endif /* SI-FAM:PS-SFP0 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB03

//SI-FAM:PS-SFB0

#ifdef SI_FAM_PS_SFB0

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfb0.h>

#endif /* SI-FAM:PS-SFB0 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB04

//SI-FAM:PS-SDA1

#ifdef SI_FAM_PS_SDA1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sda1.h>

#endif /* SI-FAM:PS-SDA1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB04

//SI-FAM:PS-SDA2

#ifdef SI_FAM_PS_SDA2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sda2.h>

#endif /* SI-FAM:PS-SDA2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB04

//SI-FAM:PS-SDB1

#ifdef SI_FAM_PS_SDB1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdb1.h>

#endif /* SI-FAM:PS-SDB1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB05

//SI-FAM:PS-SDA3

#ifdef SI_FAM_PS_SDA3

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sda3.h>

#endif /* SI-FAM:PS-SDA3 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB05

//SI-FAM:PS-SFA1

#ifdef SI_FAM_PS_SFA1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfa1.h>

#endif /* SI-FAM:PS-SFA1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB05

//SI-FAM:PS-SDB2

#ifdef SI_FAM_PS_SDB2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdb2.h>

#endif /* SI-FAM:PS-SDB2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB07

//SI-FAM:PS-SFA2

#ifdef SI_FAM_PS_SFA2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfa2.h>

#endif /* SI-FAM:PS-SFA2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB07

//SI-FAM:PS-SDP1

#ifdef SI_FAM_PS_SDP1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdp1.h>

#endif /* SI-FAM:PS-SDP1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB07

//SI-FAM:PS-SDB3

#ifdef SI_FAM_PS_SDB3

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdb3.h>

#endif /* SI-FAM:PS-SDB3 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB08

//SI-FAM:PS-SDP2

#ifdef SI_FAM_PS_SDP2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdp2.h>

#endif /* SI-FAM:PS-SDP2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB08

//SI-FAM:PS-SDP3

#ifdef SI_FAM_PS_SDP3

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sdp3.h>

#endif /* SI-FAM:PS-SDP3 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB08

//SI-FAM:PS-SFB1

#ifdef SI_FAM_PS_SFB1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfb1.h>

#endif /* SI-FAM:PS-SFB1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB10

//SI-FAM:PS-SFP1

#ifdef SI_FAM_PS_SFP1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfp1.h>

#endif /* SI-FAM:PS-SFP1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB10

//SI-FAM:PS-SFP2

#ifdef SI_FAM_PS_SFP2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfp2.h>

#endif /* SI-FAM:PS-SFP2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSB10

//SI-FAM:PS-SFB2

#ifdef SI_FAM_PS_SFB2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_sfb2.h>

#endif /* SI-FAM:PS-SFB2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSD02

//SI-FAM:PS-B1B2-1 --> 4 MÓDULOS

#ifdef SI_FAM_PS_B1B2_1

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_b1b2_1.h>

#endif /* SI-FAM:PS-B1B2-1 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack PA-RaPSD06

//SI-FAM:PS-B1B2-2 --> 4 MÓDULOS

#ifdef SI_FAM_PS_B1B2_2

#include <iib_ps_parameters/racks_PA/fap/si_fam_ps_b1b2_2.h>

#endif /* SI-FAM:PS-B1B2-2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS01

//TS-FAM:PS-B --> 4 MÓDULOS

#ifdef TS_FAM_PS_B

#include <iib_ps_parameters/racks_LA/fap/ts_fam_ps_b.h>

#endif /* TS-FAM:PS-B */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS03

//TB-FAM:PS-B

#ifdef TB_FAM_PS_B

#include <iib_ps_parameters/racks_LA/fap/tb_fam_ps_b.h>

#endif /* TB-FAM:PS-B */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS03

//TS-01:PS-QF1A

#ifdef TS_01_PS_QF1A

#include <iib_ps_parameters/racks_LA/fap/ts_01_ps_qf1a.h>

#endif /* TS-01:PS-QF1A */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS03

//TS-01:PS-QF1B

#ifdef TS_01_PS_QF1B

#include <iib_ps_parameters/racks_LA/fap/ts_01_ps_qf1b.h>

#endif /* TS-01:PS-QF1B */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS03

//TS-02:PS-QF2

#ifdef TS_02_PS_QF2

#include <iib_ps_parameters/racks_LA/fap/ts_02_ps_qf2.h>

#endif /* TS-02:PS-QF2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS03

//TS-02:PS-QD2

#ifdef TS_02_PS_QD2

#include <iib_ps_parameters/racks_LA/fap/ts_02_ps_qd2.h>

#endif /* TS-02:PS-QD2 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS05

//TS-03:PS-QF3

#ifdef TS_03_PS_QF3

#include <iib_ps_parameters/racks_LA/fap/ts_03_ps_qf3.h>

#endif /* TS-03:PS-QF3 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS05

//TS-04:PS-QF4

#ifdef TS_04_PS_QF4

#include <iib_ps_parameters/racks_LA/fap/ts_04_ps_qf4.h>

#endif /* TS-04:PS-QF4 */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS05

//TS-04:PS-QD4A

#ifdef TS_04_PS_QD4A

#include <iib_ps_parameters/racks_LA/fap/ts_04_ps_qd4a.h>

#endif /* TS-04:PS-QD4A */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Rack LA-RaPS05

//TS-04:PS-QD4B

#ifdef TS_04_PS_QD4B

#include <iib_ps_parameters/racks_LA/fap/ts_04_ps_qd4b.h>

#endif /* TS-04:PS-QD4B */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAP Giga de Testes IGBT 1200V

#ifdef FAP_GIGA_TESTE_IGBT_1200V

#include <iib_ps_parameters/development/fap/fap_giga_teste_igbt_1200v.h>

#endif /* FAP Giga de Testes IGBT 1200V */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//Giga de Testes 4 IIBs

#ifdef GIGA_TESTES_IIBs

#include <iib_ps_parameters/development/fap/giga_testes_iibs.h>

#endif /* GIGA_TESTES_IIBs */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAP Giga de Testes IGBT 1200V Com DCLink 400V

#ifdef FAP_GIGA_TESTE_IGBT_1200V_DCLINK_400V

#include <iib_ps_parameters/development/fap/fap_giga_teste_igbt_1200v_dclink_400v.h>

#endif /* FAP Giga de Testes IGBT 1200V Com DCLink 400V */

/////////////////////////////////////////////////////////////////////////////////////////////

//Set Power Module Alarms And Interlocks

//FAP Giga de Testes IGBT 600V Com DCLink 400V

#ifdef FAP_GIGA_TESTE_IGBT_600V_DCLINK_400V

#include <iib_ps_parameters/development/fap/fap_giga_teste_igbt_600v_dclink_400v.h>

#endif /* FAP Giga de Testes IGBT 600V Com DCLink 400V */

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* FAP_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////





