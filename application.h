
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Modules iib FACs                                        //
/////////////////////////////////////////////////////////////////////////////////////////////

/*************************************/
//Racks PA-RaPSC01 / PA-RaPSC02
/*************************************/

//#define BO_FAM_PS_QF__OS
//#define BO_FAM_PS_QF__IS
//#define BO_FAM_PS_QF__CMD

/***********************/
//Rack PA-RaPSC04
/***********************/

//#define BO_FAM_PS_SF__OS
//#define BO_FAM_PS_SD__OS
//#define BO_FAM_PS_QD__OS

/***********************/
//Rack EMA:B:PS01
/***********************/

//#define FAC_DCDC_EMA__OS

/******************************************************************************************************************/
//Rack PA-RaPSE01 / PA-RaPSE02 / PA-RaPSE03 / PA-RaPSE04 / PA-RaPSE06 / PA-RaPSE07 / PA-RaPSE08 / PA-RaPSE09
/******************************************************************************************************************/

//#define BO_FAM_PS_B1__OS
//#define BO_FAM_PS_B1__IS
//#define BO_FAM_PS_B1__CMD

/******************************************************************************************************************/
//Rack PA-RaPSF01 / PA-RaPSF02 / PA-RaPSF03 / PA-RaPSF04 / PA-RaPSF06 / PA-RaPSF07 / PA-RaPSF08 / PA-RaPSF09
/******************************************************************************************************************/

//#define BO_FAM_PS_B2__OS
//#define BO_FAM_PS_B2__IS
//#define BO_FAM_PS_B2__CMD

/***********************/
//Development FAC
/***********************/

//#define FAC_GIGA_TESTE__OS
//#define FAC_GIGA_TESTE__IS
//#define FAC_GIGA_TESTE__CMD
//#define FAC_GIGA_TESTE_NOVO__CMD

/////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Modules iib FAPs                                        //
/////////////////////////////////////////////////////////////////////////////////////////////

/***********************/
//Rack PA-RaPSA01
/***********************/

//#define SI_FAM_PS_QFA
//#define SI_FAM_PS_QFP
//#define SI_FAM_PS_QFB

/***********************/
//Rack PA-RaPSA03
/***********************/

//#define SI_FAM_PS_QDA
//#define SI_FAM_PS_QDP1
//#define SI_FAM_PS_QDP2

/***********************/
//Rack PA-RaPSA04
/***********************/

//#define SI_FAM_PS_QDB1
//#define SI_FAM_PS_QDB2

/***********************/
//Rack PA-RaPSA06
/***********************/

//#define SI_FAM_PS_Q1
//#define SI_FAM_PS_Q3

/***********************/
//Rack PA-RaPSA07
/***********************/

//#define SI_FAM_PS_Q2
//#define SI_FAM_PS_Q4

/***********************/
//Rack PA-RaPSB01
/***********************/

//#define SI_FAM_PS_SDA0
//#define SI_FAM_PS_SDP0
//#define SI_FAM_PS_SDB0

/***********************/
//Rack PA-RaPSB03
/***********************/

//#define SI_FAM_PS_SFA0
//#define SI_FAM_PS_SFP0
//#define SI_FAM_PS_SFB0

/***********************/
//Rack PA-RaPSB04
/***********************/

//#define SI_FAM_PS_SDA1
//#define SI_FAM_PS_SDA2
//#define SI_FAM_PS_SDB1

/***********************/
//Rack PA-RaPSB05
/***********************/

//#define SI_FAM_PS_SDA3
//#define SI_FAM_PS_SFA1
//#define SI_FAM_PS_SDB2

/***********************/
//Rack PA-RaPSB07
/***********************/

//#define SI_FAM_PS_SFA2
//#define SI_FAM_PS_SDP1
//#define SI_FAM_PS_SDB3

/***********************/
//Rack PA-RaPSB08
/***********************/

//#define SI_FAM_PS_SDP2
//#define SI_FAM_PS_SDP3
//#define SI_FAM_PS_SFB1

/***********************/
//Rack PA-RaPSB10
/***********************/

//#define SI_FAM_PS_SFP1
//#define SI_FAM_PS_SFP2
//#define SI_FAM_PS_SFB2

/***********************/
//Rack PA-RaPSD02
/***********************/

//#define SI_FAM_PS_B1B2_1

/***********************/
//Rack PA-RaPSD06
/***********************/

//#define SI_FAM_PS_B1B2_2

/***********************/
//Rack LA-RaPS01
/***********************/

//#define TS_FAM_PS_B

/***********************/
//Rack LA-RaPS03
/***********************/

//#define TB_FAM_PS_B
//#define TS_01_PS_QF1A
//#define TS_01_PS_QF1B
//#define TS_02_PS_QF2
//#define TS_02_PS_QD2

/***********************/
//Rack LA-RaPS05
/***********************/

//#define TS_03_PS_QF3
//#define TS_04_PS_QF4
//#define TS_04_PS_QD4A
//#define TS_04_PS_QD4B

/***********************/
//Development FAP
/***********************/

//#define FAP_GIGA_TESTE_IGBT_1200V
//#define GIGA_TESTES_IIBs
//#define FAP_GIGA_TESTE_IGBT_1200V_DCLINK_400V
//#define FAP_GIGA_TESTE_IGBT_600V_DCLINK_400V

/*********************************/
//Development RESONANT_SWLS
/*********************************/

#define RESONANT_SWLS

/////////////////////////////////////////////////////////////////////////////////////////////

extern volatile unsigned char Interlock;
extern volatile unsigned char Alarm;

/////////////////////////////////////////////////////////////////////////////////////////////

void AppConfiguration(void);
void LedIndicationStatus(void);

/////////////////////////////////////////////////////////////////////////////////////////////

void InterlockClear(void);
void InterlockSet(void);
void InterlockClearCheck(void);
void AppInterlock(void);

/////////////////////////////////////////////////////////////////////////////////////////////

void AlarmClear(void);
void AlarmSet(void);

/////////////////////////////////////////////////////////////////////////////////////////////

void InterlockAppCheck(void);
void AlarmAppCheck(void);

/////////////////////////////////////////////////////////////////////////////////////////////

void Application(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void send_data_schedule();
extern void power_on_check();

/////////////////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////////////////
