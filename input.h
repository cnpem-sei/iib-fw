




#ifndef __INPUT_H__
#define __INPUT_H__

void InputInit(void);

extern unsigned char Gpdi1Read(void);
extern unsigned char Gpdi2Read(void);
extern unsigned char Gpdi3Read(void);
extern unsigned char Gpdi4Read(void);
extern unsigned char Gpdi5Read(void);
extern unsigned char Gpdi6Read(void);
extern unsigned char Gpdi7Read(void);
extern unsigned char Gpdi8Read(void);
extern unsigned char Gpdi9Read(void);
extern unsigned char Gpdi10Read(void);
extern unsigned char Gpdi11Read(void);
extern unsigned char Gpdi12Read(void);

extern void Driver1ErrEnable(void);
extern void Driver1ErrDisable(void);
extern void Driver2ErrEnable(void);
extern void Driver2ErrDisable(void);

extern unsigned char Driver1TopErrRead(void);
extern unsigned char Driver1BotErrRead(void);
extern unsigned char Driver1OverTempRead(void);
extern unsigned char Driver2TopErrRead(void);
extern unsigned char Driver2BotErrRead(void);
extern unsigned char Driver2OverTempRead(void);

extern unsigned char BoardAddressRead(void);

#endif