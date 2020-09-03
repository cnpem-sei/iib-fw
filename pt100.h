
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __PT100_H__
#define __PT100_H__

/////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    unsigned char Ch;
    unsigned char Calibration;
    float Temperature;
    float AlarmLimit;
    float TripLimit;
    unsigned char CanNotCommunicate;
    unsigned char Error;
    unsigned char RtdOutOfRange;
    unsigned char Alarm;
    unsigned char Trip;
    unsigned int  Alarm_Delay_s; // second
    unsigned int  Alarm_DelayCount;
    unsigned int  Itlk_Delay_s; // second
    unsigned int  Itlk_DelayCount;
}pt100_t;

/////////////////////////////////////////////////////////////////////////////////////////////

extern pt100_t Pt100Ch1;
extern pt100_t Pt100Ch2;
extern pt100_t Pt100Ch3;
extern pt100_t Pt100Ch4;

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Pt100Init(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Pt100Ch1Sample(void);
extern void Pt100Ch2Sample(void);
extern void Pt100Ch3Sample(void);
extern void Pt100Ch4Sample(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern float Pt100Ch1Read(void);
extern float Pt100Ch2Read(void);
extern float Pt100Ch3Read(void);
extern float Pt100Ch4Read(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Pt100Ch1ErrorRead(void);
extern unsigned char Pt100Ch2ErrorRead(void);
extern unsigned char Pt100Ch3ErrorRead(void);
extern unsigned char Pt100Ch4ErrorRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Pt100Ch1AlarmLevelSet(float alarm);
extern void Pt100Ch1TripLevelSet(float trip);
extern void Pt100Ch2AlarmLevelSet(float alarm);
extern void Pt100Ch2TripLevelSet(float trip);
extern void Pt100Ch3AlarmLevelSet(float alarm);
extern void Pt100Ch3TripLevelSet(float trip);
extern void Pt100Ch4AlarmLevelSet(float alarm);
extern void Pt100Ch4TripLevelSet(float trip);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Pt100Ch1AlarmStatusRead(void);
extern unsigned char Pt100Ch1TripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Pt100Ch2AlarmStatusRead(void);
extern unsigned char Pt100Ch2TripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Pt100Ch3AlarmStatusRead(void);
extern unsigned char Pt100Ch3TripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Pt100Ch4AlarmStatusRead(void);
extern unsigned char Pt100Ch4TripStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Pt100Ch1Delay(unsigned int Delay_Set);
extern void Pt100Ch2Delay(unsigned int Delay_Set);
extern void Pt100Ch3Delay(unsigned int Delay_Set);
extern void Pt100Ch4Delay(unsigned int Delay_Set);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Pt100Ch1CNCRead(void);
extern unsigned char Pt100Ch2CNCRead(void);
extern unsigned char Pt100Ch3CNCRead(void);
extern unsigned char Pt100Ch4CNCRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern unsigned char Pt100Ch1RtdStatusRead(void);
extern unsigned char Pt100Ch2RtdStatusRead(void);
extern unsigned char Pt100Ch3RtdStatusRead(void);
extern unsigned char Pt100Ch4RtdStatusRead(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Pt100Ch1Clear(void);
extern void Pt100Ch2Clear(void);
extern void Pt100Ch3Clear(void);
extern void Pt100Ch4Clear(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Pt100Ch1Reset(void);
extern void Pt100Ch2Reset(void);
extern void Pt100Ch3Reset(void);
extern void Pt100Ch4Reset(void);

/////////////////////////////////////////////////////////////////////////////////////////////

extern void Pt100ClearAlarmTrip(void);

/////////////////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////////////////



