#include <stdint.h>

#ifndef CAN_BUS_H__
#define CAN_BUS_H__

#define Q1_I_ARMS               0
#define Q1_V_IN_OUT             1
#define Q1_SLOW_STS             2
#define Q1_ALARM_ITLK_STS       3

#define Q4_I_OUT                4
#define Q4_TEMP                 5

#define BUCK_I_IN               7
#define BUCK_I_OUT              8
#define BUCK_V_IN               9
#define BUCK_TEMP               10

#define RECTF_I_OUT             11
#define RECTF_V_OUT             12
#define RECTF_I_LEAK            13
#define RECTF_TEMP              14
#define RECTF_ALARM_ITLK_STS    15

#define DRAWER_TEMP             16
#define DRAWER_V                17
#define DRAWER_ALARM_ITLK_STS   20

#define ITLK_MESS               255

#define EVENT_MESSAGE_LEN           8
#define EVENT_MESSAGE_OBJ_ID        1

#define PARAMS_MESSAGE_LEN          8
#define PARAMS_MESSAGE_OBJ_ID       2

#define RESET_MESSAGE_LEN           1
#define RESET_MESSAGE_OBJ_ID        3

#define DATA_REQUEST_MESSAGE_LEN    4
#define DATA_REQUEST_OBJ_ID         4

#define DATA_SEND_MESSAGE_LEN       8
#define DATA_SEND_OBJ_ID            5

typedef enum {
    ItlkMsgId = 1,
    AlmMsgId,
    ResetMsgId,
    DataRequestMsgId,
    DataSendMsgId,
    ParamsSetMsgId,
    HeartBeatMsgId
}can_message_id_t;

typedef enum {
    TempHeatSink,
    TempL,
    VcapBank,
    Vout,
    Gpdi
} command_drawer_field_t;

extern void SendCanSchedule(void);
extern void SendCan(unsigned char Message);
extern void InitCan(uint32_t ui32SysClock);
extern void CheckCan(void);
extern uint16_t CanIdRead(void);
extern void test_bus();
extern void send_board_readings();

#endif
