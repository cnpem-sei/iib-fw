/*
 * timer.h
 *
 *  Created on: 6 de set de 2017
 *      Author: allef.silva
 */

#ifndef DRIVERS_PERIPHERAL_DRIVERS_TIMER_TIMER_H_
#define DRIVERS_PERIPHERAL_DRIVERS_TIMER_TIMER_H_

extern void timer_init(void);
extern void timer_task_init(void);
extern void delay_ms(uint32_t time);

#endif /* DRIVERS_PERIPHERAL_DRIVERS_TIMER_TIMER_H_ */