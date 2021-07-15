
/////////////////////////////////////////////////////////////////////////////////////////////

/*
 * can_bus.h
 *
 *  Created on: 30 de abr de 2021
 *      Author: rogerio.marcondeli
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAN_BUS_H__
#define CAN_BUS_H__

/////////////////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>

/////////////////////////////////////////////////////////////////////////////////////////////

#define MESSAGE_DATA_OBJ			1
#define MESSAGE_DATA_LEN			8

/////////////////////////////////////////////////////////////////////////////////////////////

#define MESSAGE_RESET_OBJ      		2
#define MESSAGE_RESET_LEN         	1

/////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {
    MESSAGE_DATA_ID = 1,
    MESSAGE_RESET_ID
}can_message_id_t;

/////////////////////////////////////////////////////////////////////////////////////////////

typedef enum {
	ID_MODULE_1 = 0x000A, // 10
	ID_MODULE_2 = 0x0014, // 20
	ID_MODULE_3 = 0x001E, // 30
	ID_MODULE_4 = 0x0028, // 40
	ID_MODULE_5 = 0x0032, // 50
	ID_MODULE_6 = 0x003C, // 60
	ID_MODULE_7 = 0x0046, // 70
	ID_MODULE_8 = 0x0050  // 80
}id_module_t;

/////////////////////////////////////////////////////////////////////////////////////////////

extern void can_isr(void);
extern void InitCan(uint32_t ui32SysClock);
extern void handle_reset_message(void);
extern void send_data_message(uint8_t var);
extern void can_error_handler(void);
extern uint16_t get_can_address(void);

/////////////////////////////////////////////////////////////////////////////////////////////

#endif

/////////////////////////////////////////////////////////////////////////////////////////////





