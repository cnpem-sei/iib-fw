/******************************************************************************
 * Copyright (C) 2017 by LNLS - Brazilian Synchrotron Light Laboratory
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. LNLS and
 * the Brazilian Center for Research in Energy and Materials (CNPEM) are not
 * liable for any misuse of this material.
 *
 *****************************************************************************/

/**
 * @file iib_data_types.h
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 22 de jun de 2018
 *
 */

#ifndef IIB_DATA_TYPES_H_
#define IIB_DATA_TYPES_H_

#include <stdint.h>

/**
 * TODO: Put here your defines. Just what need 
 * to be accessed by other modules.
 */


/**
 * TODO: Put here your functions prototypes. Just what need 
 * to be accessed by other modules.
 */
typedef enum
{
    ClearInterlock,
    ClearAlarm,
    Pt100Ch1ItlkLowLimit,
    Pt100Ch1ItlkHighLimit,
    Pt100Ch1AlarmLowLimit,
    Pt100Ch1AlarmHighLimit,
    Pt100Ch2ItlkLowLimit,
    Pt100Ch2ItlkHighLimit,
    Pt100Ch2AlarmLowLimit,
    Pt100Ch2AlarmHighLimit,
    Pt100Ch3ItlkLowLimit,
    Pt100Ch3ItlkHighLimit,
    Pt100Ch3AlarmLowLimit,
    Pt100Ch3AlarmHighLimit,
    Pt100Ch4ItlkLowLimit,
    Pt100Ch4ItlkHighLimit,
    Pt100Ch4AlarmLowLimit,
    Pt100Ch4AlarmHighLimit,
    LeakageVoltCh1ItlkLowLimit,
    LeakageVoltCh1ItlkHighLimit,
    LeakageVoltCh1AlarmLowLimit,
    LeakageVoltCh1AlarmHighLimit,
    LeakageVoltCh2ItlkLowLimit,
    LeakageVoltCh2ItlkHighLimit,
    LeakageVoltCh2AlarmLowLimit,
    LeakageVoltCh2AlarmHighLimit,
    LeakageVoltCh3ItlkLowLimit,
    LeakageVoltCh3ItlkHighLimit,
    LeakageVoltCh3AlarmLowLimit,
    LeakageVoltCh3AlarmHighLimit,
    HallCurrentCh1ItlkLowLimit,
    HallCurrentCh1ItlkHighLimit,
    HallCurrentCh1AlarmLowLimit,
    HallCurrentCh1AlarmHighLimit,
    HallCurrentCh2ItlkLowLimit,
    HallCurrentCh2ItlkHighLimit,
    HallCurrentCh2AlarmLowLimit,
    HallCurrentCh2AlarmHighLimit,
    HallCurrentCh3ItlkLowLimit,
    HallCurrentCh3ItlkHighLimit,
    HallCurrentCh3AlarmLowLimit,
    HallCurrentCh3AlarmHighLimit,
    HallCurrentCh4ItlkLowLimit,
    HallCurrentCh4ItlkHighLimit,
    HallCurrentCh4AlarmLowLimit,
    HallCurrentCh4AlarmHighLimit,
    InVoltCh1ItlkLowLimit,
    InVoltCh1ItlkHighLimit,
    InVoltCh1AlarmLowLimit,
    InVoltCh1AlarmHighLimit,
    InVoltCh2ItlkLowLimit,
    InVoltCh2ItlkHighLimit,
    InVoltCh2AlarmLowLimit,
    InVoltCh2AlarmHighLimit,
    InVoltCh3ItlkLowLimit,
    InVoltCh3ItlkHighLimit,
    InVoltCh3AlarmLowLimit,
    InVoltCh3AlarmHighLimit,
    InVoltCh4ItlkLowLimit,
    InVoltCh4ItlkHighLimit,
    InVoltCh4AlarmLowLimit,
    InVoltCh4AlarmHighLimit
} can_rx_cmd_t;

typedef enum
{

} can_tx_cmd_t;

typedef union {
    uint32_t    u32;
    uint8_t     u8[4];
    float       f;
} u_uint32_t;

#endif /* IIB_DATA_TYPES_H_ */
