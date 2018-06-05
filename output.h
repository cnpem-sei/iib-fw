




#ifndef __OUTPUT_H__
#define __OUTPUT_H__

void OutputInit(void);

void Gpdo1TurnOn(void);
void Gpdo1TurnOff(void);
unsigned char Gpdo1Sts(void);
void Gpdo2TurnOn(void);
void Gpdo2TurnOff(void);
unsigned char Gpdo2Sts(void);
void Gpdo3TurnOn(void);
void Gpdo3TurnOff(void);
unsigned char Gpdo3Sts(void);
void Gpdo4TurnOn(void);
void Gpdo4TurnOff(void);
unsigned char Gpdo4Sts(void);

void ReleAuxTurnOn(void);
void ReleAuxTurnOff(void);
unsigned char ReleAuxSts(void);

void ReleItlkTurnOn(void);
void ReleItlkTurnOff(void);
unsigned char ReleItlkSts(void);

#endif