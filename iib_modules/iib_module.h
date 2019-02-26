/*
 * iib_module.h
 *
 *  Created on: 26 de fev de 2019
 *      Author: allef.silva
 */

#ifndef IIB_MODULE_H_
#define IIB_MODULE_H_

#include<stdint.h>

typedef struct {
    void (*clear_interlocks) (void);
    uint8_t (*check_interlocks) (void);
    void (*clear_alarms) (void);
    uint8_t (*check_alarms) (void);
    void (*check_indication_leds) (void);
    void (*application_readings) (void);
    void (*power_on_check) (void);
    void (*send_data) (void);
    void (*send_itlk_msg) (void);

} iib_module_t;

extern iib_module_t g_iib_module;

extern void init_iib_module(iib_module_t *iib_module,
                     void (*clear_interlocks) (void),
                     uint8_t (*check_interlocks) (void),
                     void (*clear_alarms) (void),
                     uint8_t (*check_alarms) (void),
                     void (*check_indication_leds) (void),
                     void (*application_readings) (void),
                     void (*power_on_check) (void),
                     void (*send_data) (void),
                     void (*send_itlk_msg) (void));

#endif /* IIB_MODULE_H_ */
