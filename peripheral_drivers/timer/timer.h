/*
 * timer.h
 *
 *  Created on: 16 de abr de 2021
 *      Author: rogerio.marcondeli
 */

/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DRIVERS_PERIPHERAL_DRIVERS_TIMER_TIMER_H_
#define DRIVERS_PERIPHERAL_DRIVERS_TIMER_TIMER_H_

/////////////////////////////////////////////////////////////////////////////////////////////

extern void delay_us(uint32_t time);
extern void delay_ms(uint32_t time);
extern void IntTimer1usHandler(void);
extern void IntTimer100usHandler(void);
extern void IntTimer1msHandler(void);
extern void IntTimer100msHandler(void);
extern void Timer_1us_Init(void);
extern void Timer_100us_Init(void);
extern void Timer_1ms_Init(void);
extern void Timer_100ms_Init(void);
extern uint32_t SysCtlClockGetTM4C129(void);

/////////////////////////////////////////////////////////////////////////////////////////////

#endif /* DRIVERS_PERIPHERAL_DRIVERS_TIMER_TIMER_H_ */

/////////////////////////////////////////////////////////////////////////////////////////////





