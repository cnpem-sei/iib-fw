



#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#define  OUTPUT_Q1_MODULE       0
#define  OUTPUT_Q4_MODULE       1
#define  RECTIFIER_MODULE       2
#define  INPUT_MODULE           3
#define  COMMAND_DRAWER_MODULE  4

void LedIndicationStatus(void);
void AppConfiguration(void);

void InterlockClear(void);
void InterlockSet(void);
void InterlockClearCheck(void);
unsigned char InterlockRead(void);
void AppInterlock(void);

void AlarmSet(void);
void AlarmClear(void);
unsigned char AlarmRead(void);
void AppAlarm(void);

void InterlockAppCheck(void);
void AlarmAppCheck(void);

void Application(void);
unsigned char AppType(void);


// 1Q Module
extern float Q1ModuleVoutRead(void);
extern unsigned char Q1ModuleVoutAlarmStsRead(void);
extern unsigned char Q1ModuleVoutItlkStsRead(void);

extern float Q1ModuleVinRead(void);
extern unsigned char Q1ModuleVinAlarmStsRead(void);
extern unsigned char Q1ModuleVinItlkStsRead(void);

extern float Q1ModuleIoutA1Read(void);
extern unsigned char Q1ModuleIoutA1AlarmStsRead(void);
extern unsigned char Q1ModuleIoutA1ItlkStsRead(void);

extern float Q1ModuleIoutA2Read(void);
extern unsigned char Q1ModuleIoutA2AlarmStsRead(void);
extern unsigned char Q1ModuleIoutA2ItlkStsRead(void);

extern float Q1ModuleIinRead(void);
extern unsigned char Q1ModuleIinAlarmStsRead(void);
extern unsigned char Q1ModuleIinItlkStsRead(void);

extern unsigned char Q1ModuleTempIGBT1Read(void);
extern unsigned char Q1ModuleTempIGBT1AlarmStsRead(void);
extern unsigned char Q1ModuleTempIGBT1ItlkStsRead(void);
extern unsigned char Q1ModuleTempIGBT1HwrItlkRead(void);
extern unsigned char Q1ModuleTempIGBT1HwrItlkStsRead(void);

extern unsigned char Q1ModuleTempIGBT2Read(void);
extern unsigned char Q1ModuleTempIGBT2AlarmStsRead(void);
extern unsigned char Q1ModuleTempIGBT2ItlkStsRead(void);
extern unsigned char Q1ModuleTempIGBT2HwrItlkRead(void);
extern unsigned char Q1ModuleTempIGBT2HwrItlkStsRead(void);

extern unsigned char Q1ModuleTempHeatSinkRead(void);
extern unsigned char Q1ModuleTempHeatSinkAlarmStsRead(void);
extern unsigned char Q1ModuleTempHeatSinkItlkStsRead(void);

extern unsigned char Q1ModuleTempLRead(void);
extern unsigned char Q1ModuleTempLAlarmStsRead(void);
extern unsigned char Q1ModuleTempLItlkStsRead(void);

extern unsigned char Q1ModuleRelayRead(void);

extern unsigned char Q1ModuleDriver1ErrorRead(void);
extern unsigned char Q1ModuleDriver1ErrorItlkRead(void);

extern unsigned char Q1ModuleDriver2ErrorRead(void);
extern unsigned char Q1ModuleDriver2ErrorItlkRead(void);

extern unsigned char Q1ModuleExternalItlkRead(void);
extern unsigned char Q1ModuleExternalItlkStsRead(void);

extern unsigned char Q1ModuleLeakageCurrentRead(void);
extern unsigned char Q1ModuleLeakageCurrentStsRead(void);

extern unsigned char Q1ModuleRackRead(void);
extern unsigned char Q1ModuleRackStsRead(void);



// 4Q Module
float Q4ModuleIoutRead(void);
unsigned char Q4ModuleIoutAlarmStsRead(void);
unsigned char Q4ModuleIoutItlkStsRead(void);

unsigned char Q4ModuleTempIGBT1Read(void);
unsigned char Q4ModuleTempIGBT1AlarmStsRead(void);
unsigned char Q4ModuleTempIGBT1ItlkStsRead(void);

unsigned char Q4ModuleTempIGBT2Read(void);
unsigned char Q4ModuleTempIGBT2AlarmStsRead(void);
unsigned char Q4ModuleTempIGBT2ItlkStsRead(void);

// Input Module
extern float InputModuleIinRead(void);
extern unsigned char InputModuleIinAlarmStsRead(void);
extern unsigned char InputModuleIinItlkStsRead(void);

extern float InputModuleVdcLinkRead(void);
extern unsigned char InputModuleVdcLinkAlarmStsRead(void);
extern unsigned char InputModuleVdcLinkItlkStsRead(void);

extern unsigned char InputModuleTempHeatsinkRead(void);
extern unsigned char InputModuleTempHeatsinkAlarmStsRead(void);
extern unsigned char InputModuleTempHeatsinkItlkStsRead(void);

extern unsigned char InputModuleTempLRead(void);
extern unsigned char InputModuleTempLAlarmStsRead(void);
extern unsigned char InputModuleTempLItlkStsRead(void);

// Rectifier
float RectifierIoutRectf1Read(void);
unsigned char RectifierIoutRectf1AlarmStsRead(void);
unsigned char RectifierIoutRectf1ItlkStsRead(void);

float RectifierIoutRectf2Read(void);
unsigned char RectifierIoutRectf2AlarmStsRead(void);
unsigned char RectifierIoutRectf2ItlkStsRead(void);

float RectifierVoutRectf1Read(void);
unsigned char RectifierVoutRectf1AlarmStsRead(void);
unsigned char RectifierVoutRectf1ItlkStsRead(void);

float RectifierVoutRectf2Read(void);
unsigned char RectifierVoutRectf2AlarmStsRead(void);
unsigned char RectifierVoutRectf2ItlkStsRead(void);

float RectifierLeakageCurrentRead(void);
unsigned char RectifierLeakageCurrentAlarmStsread(void);
unsigned char RectifierLeakageCurrentItlkStsRead(void);

unsigned char RectifierTempHeatSinkRead(void);
unsigned char RectifierTempHeatSinkAlarmStsRead(void);
unsigned char RectifierTempHeatSinkItlkStsRead(void);

unsigned char RectifierTempWaterRead(void);
unsigned char RectifierTempWaterAlarmStsRead(void);
unsigned char RectifierTempWaterItlkStsRead(void);

unsigned char RectifierTempModule1Read(void);
unsigned char RectifierTempModule1AlarmStsRead(void);
unsigned char RectifierTempModule1ItlkStsRead(void);

unsigned char RectifierTempModule2Read(void);
unsigned char RectifierTempModule2AlarmStsRead(void);
unsigned char RectifierTempModule2ItlkStsRead(void);

unsigned char RectifierTempL1Read(void);
unsigned char RectifierTempL1AlarmStsRead(void);
unsigned char RectifierTempL1ItlkStsRead(void);

unsigned char RectifierTempL2Read(void);
unsigned char RectifierTempL2AlarmStsRead(void);
unsigned char RectifierTempL2ItlkStsRead(void);

unsigned char RectifierAcPhaseFaultRead(void);
unsigned char RectifierAcPhaseFaultStsRead(void);

unsigned char RectifierAcOverCurrentRead(void);
unsigned char RectifierAcOverCurrentStsRead(void);

unsigned char RectifierAcTransformerOverTempRead(void);
unsigned char RectifierAcTransformerOverTempStsRead(void);

unsigned char RectifierWaterFluxInterlockRead(void);
unsigned char RectifierWaterFluxInterlockStsRead(void);

// Command Drawer
unsigned char CommandDrawerTempHeatSinkRead(void);
unsigned char CommandDrawerTempHeatSinkAlarmStsRead(void);
unsigned char CommandDrawerTempHeatSinkItlkStsRead(void);

unsigned char CommandDrawerTempLRead(void);
unsigned char CommandDrawerTempLAlarmStsRead(void);
unsigned char CommandDrawerTempLItlkStsRead(void);

extern float CommandDrawerVcapBankRead(void);
extern unsigned char CommandDrawerVcapBankAlarmStsRead(void);
extern unsigned char CommandDrawerVcapBankItlkStsRead(void);

extern float CommandDrawerVoutRead(void);
extern unsigned char CommandDrawerVoutAlarmStsRead(void);
extern unsigned char CommandDrawerVoutItlkStsRead(void);

extern unsigned char CommandDrawerExtItlkStsRead();
extern unsigned char CommandDrawerExt2ItlkStsRead();

void ClearDiagnosticCount(void);
void PrintDiagnosticVar(void);


#endif
