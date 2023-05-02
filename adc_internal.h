
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ADC_INTERNAL_H__
#define __ADC_INTERNAL_H__

/////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    unsigned char Ch;
    float Gain;
    float Value;
    unsigned int Offset;
    float AlarmLimit;
    float TripLimit;
    unsigned char Alarm;
    unsigned char Trip;
    unsigned char InvertPol;
    unsigned int  Alarm_Delay_us;  // microsecond
    unsigned int  Alarm_Delay_ms;  // milisecond
    unsigned int  Alarm_DelayCount;
    unsigned int  Itlk_Delay_us;   // microsecond
    unsigned int  Itlk_Delay_ms;   // milisecond
    unsigned int  Itlk_DelayCount;
}adc_t;

/////////////////////////////////////////////////////////////////////////////////////////////

extern adc_t VoltageCh1;
extern adc_t VoltageCh2;
extern adc_t VoltageCh3;
extern adc_t VoltageCh4;

extern adc_t CurrentCh1;
extern adc_t CurrentCh2;
extern adc_t CurrentCh3;
extern adc_t CurrentCh4;

extern adc_t LvCurrentCh1;
extern adc_t LvCurrentCh2;
extern adc_t LvCurrentCh3;

extern adc_t DriverVolt;
extern adc_t Driver1Curr;
extern adc_t Driver2Curr;

/////////////////////////////////////////////////////////////////////////////////////////////

extern void AdcsInit(void);
extern void sample_adc(void);
extern float CurrentRange(float nFstCurr, float nSecCurr, float nBurden, float MaxVoltInput);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void ConfigPolVoltCh1(unsigned char sts);
extern void ConfigPolVoltCh2(unsigned char sts);
extern void ConfigPolVoltCh3(unsigned char sts);
extern void ConfigPolVoltCh4(unsigned char sts);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void VoltageCh1Init(float nValue, unsigned int delay_us);
extern void VoltageCh2Init(float nValue, unsigned int delay_us);
extern void VoltageCh3Init(float nValue, unsigned int delay_us);
extern void VoltageCh4Init(float nValue, unsigned int delay_us);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void ConfigPolCurrCh1(unsigned char sts);
extern void ConfigPolCurrCh2(unsigned char sts);
extern void ConfigPolCurrCh3(unsigned char sts);
extern void ConfigPolCurrCh4(unsigned char sts);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void CurrentCh1Init(float nFstCurr, float nSecCurr, float nBurden, unsigned int delay_us);
extern void CurrentCh2Init(float nFstCurr, float nSecCurr, float nBurden, unsigned int delay_us);
extern void CurrentCh3Init(float nFstCurr, float nSecCurr, float nBurden, unsigned int delay_us);
extern void CurrentCh4Init(float nFstCurr, float nSecCurr, float nBurden, unsigned int delay_us);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void ConfigPolLvCurrCh1(unsigned char sts);
extern void ConfigPolLvCurrCh2(unsigned char sts);
extern void ConfigPolLvCurrCh3(unsigned char sts);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void LvCurrentCh1Init(float nFstCurr, float nSecCurr, float nBurden, unsigned int delay_us);
extern void LvCurrentCh2Init(float nFstCurr, float nSecCurr, float nBurden, unsigned int delay_us);
extern void LvCurrentCh3Init(float nFstCurr, float nSecCurr, float nBurden, unsigned int delay_us);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void DriverVoltageInit(void);
extern void DriverCurrentInit(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void VoltageCh1Sample(void);
extern void VoltageCh2Sample(void);
extern void VoltageCh3Sample(void);
extern void VoltageCh4Sample(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void CurrentCh1Sample(void);
extern void CurrentCh2Sample(void);
extern void CurrentCh3Sample(void);
extern void CurrentCh4Sample(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void LvCurrentCh1Sample(void);
extern void LvCurrentCh2Sample(void);
extern void LvCurrentCh3Sample(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void DriverVoltageSample(void);
extern void Driver1CurrentSample(void);
extern void Driver2CurrentSample(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern float VoltageCh1Read(void);
extern float VoltageCh2Read(void);
extern float VoltageCh3Read(void);
extern float VoltageCh4Read(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern float CurrentCh1Read(void);
extern float CurrentCh2Read(void);
extern float CurrentCh3Read(void);
extern float CurrentCh4Read(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern float LvCurrentCh1Read(void);
extern float LvCurrentCh2Read(void);
extern float LvCurrentCh3Read(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern float DriverVoltageRead(void);
extern float Driver1CurrentRead(void);
extern float Driver2CurrentRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char VoltageCh1AlarmStatusRead(void);
extern unsigned char VoltageCh1TripStatusRead(void);
extern unsigned char VoltageCh2AlarmStatusRead(void);
extern unsigned char VoltageCh2TripStatusRead(void);
extern unsigned char VoltageCh3AlarmStatusRead(void);
extern unsigned char VoltageCh3TripStatusRead(void);
extern unsigned char VoltageCh4AlarmStatusRead(void);
extern unsigned char VoltageCh4TripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void VoltageCh1AlarmLevelSet(float nValue);
extern void VoltageCh1TripLevelSet(float nValue);
extern void VoltageCh2AlarmLevelSet(float nValue);
extern void VoltageCh2TripLevelSet(float nValue);
extern void VoltageCh3AlarmLevelSet(float nValue);
extern void VoltageCh3TripLevelSet(float nValue);
extern void VoltageCh4AlarmLevelSet(float nValue);
extern void VoltageCh4TripLevelSet(float nValue);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char CurrentCh1AlarmStatusRead(void);
extern unsigned char CurrentCh1TripStatusRead(void);
extern unsigned char CurrentCh2AlarmStatusRead(void);
extern unsigned char CurrentCh2TripStatusRead(void);
extern unsigned char CurrentCh3AlarmStatusRead(void);
extern unsigned char CurrentCh3TripStatusRead(void);
extern unsigned char CurrentCh4AlarmStatusRead(void);
extern unsigned char CurrentCh4TripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void CurrentCh1AlarmLevelSet(float nValue);
extern void CurrentCh1TripLevelSet(float nValue);
extern void CurrentCh2AlarmLevelSet(float nValue);
extern void CurrentCh2TripLevelSet(float nValue);
extern void CurrentCh3AlarmLevelSet(float nValue);
extern void CurrentCh3TripLevelSet(float nValue);
extern void CurrentCh4AlarmLevelSet(float nValue);
extern void CurrentCh4TripLevelSet(float nValue);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char LvCurrentCh1AlarmStatusRead(void);
extern unsigned char LvCurrentCh1TripStatusRead(void);
extern unsigned char LvCurrentCh2AlarmStatusRead(void);
extern unsigned char LvCurrentCh2TripStatusRead(void);
extern unsigned char LvCurrentCh3AlarmStatusRead(void);
extern unsigned char LvCurrentCh3TripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void LvCurrentCh1AlarmLevelSet(float nValue);
extern void LvCurrentCh1TripLevelSet(float nValue);
extern void LvCurrentCh2AlarmLevelSet(float nValue);
extern void LvCurrentCh2TripLevelSet(float nValue);
extern void LvCurrentCh3AlarmLevelSet(float nValue);
extern void LvCurrentCh3TripLevelSet(float nValue);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char DriverVoltageAlarmStatusRead(void);
extern unsigned char DriverVoltageTripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void DriverVoltageAlarmLevelSet(float nValue);
extern void DriverVoltageTripLevelSet(float nValue);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void DriverVoltageDelay(unsigned int delay_ms);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Driver1CurrentAlarmStatusRead(void);
extern unsigned char Driver1CurrentTripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Driver1CurrentAlarmLevelSet(float nValue);
extern void Driver1CurrentTripLevelSet(float nValue);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Driver2CurrentAlarmStatusRead(void);
extern unsigned char Driver2CurrentTripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Driver2CurrentAlarmLevelSet(float nValue);
extern void Driver2CurrentTripLevelSet(float nValue);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void DriverCurrentDelay(unsigned int delay_ms);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void AdcClearAlarmTrip(void);

/////////////////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////////////////
