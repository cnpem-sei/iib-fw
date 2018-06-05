
#include <stdint.h>

#ifndef __CAN_BUS_H__
#define __CAN_BUS_H__

#define Q1_I_ARMS             0
#define Q1_V_IN_OUT           1
#define Q1_SLOW_STS           2
#define Q1_ALARM_ITLK_STS     3

#define Q4_I_OUT              4
#define Q4_TEMP               5

#define BUCK_I_IN             7
#define BUCK_I_OUT            8
#define BUCK_V_IN             9
#define BUCK_TEMP             10

#define RECTF_I_OUT           11
#define RECTF_V_OUT           12
#define RECTF_I_LEAK          13
#define RECTF_TEMP            14
#define RECTF_ALARM_ITLK_STS  15

#define ITLK_MESS           255

extern void SendCanSchedule(void);
extern void SendCan(unsigned char Message);

extern void InitCan(uint32_t ui32SysClock);

extern void CheckCan(void);

extern uint16_t CanIdRead(void);

#endif
