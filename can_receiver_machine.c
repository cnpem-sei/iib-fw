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
 * @file can_receiver_machine.c
 * @brief Brief description of module
 * 
 * Detailed description
 *
 * @author allef.silva
 * @date 22 de jun de 2018
 *
 */

#include "iib_data_types.h"

/**
 * TODO: Put here your includes
 */

/**
 * TODO: Put here your defines. Just what is local. If you don't
 * need to access it from other module, consider use a constant (const)
 */


/**
 * TODO: Put here your constants and variables. Always use static for 
 * private members.
 */

/**
 * TODO: Put here your function prototypes for private functions. Use
 * static in declaration.
 */


/**
 * TODO: Put here the implementation for your public functions.
 */

void can_process_message(can_rx_cmd_t message)
{
    switch (message)
    {
        case ClearInterlock:
            break;
        case ClearAlarm:
            break;
        case Pt100Ch1ItlkLowLimit:
            break;
        case Pt100Ch1ItlkHighLimit:
            break;
        case Pt100Ch1AlarmLowLimit:
            break;
        case Pt100Ch1AlarmHighLimit:
            break;
        case Pt100Ch2ItlkLowLimit:
            break;
        case Pt100Ch2ItlkHighLimit:
            break;
        case Pt100Ch2AlarmLowLimit:
            break;
        case Pt100Ch2AlarmHighLimit:
            break;
        case Pt100Ch3ItlkLowLimit:
            break;
        case Pt100Ch3ItlkHighLimit:
            break;
        case Pt100Ch3AlarmLowLimit:
            break;
        case Pt100Ch3AlarmHighLimit:
            break;
        case Pt100Ch4ItlkLowLimit:
            break;
        case Pt100Ch4ItlkHighLimit:
            break;
        case Pt100Ch4AlarmLowLimit:
            break;
        case Pt100Ch4AlarmHighLimit:
            break;
        case LeakageVoltCh1ItlkLowLimit:
            break;
        case LeakageVoltCh1ItlkHighLimit:
            break;
        case LeakageVoltCh1AlarmLowLimit:
            break;
        case LeakageVoltCh1AlarmHighLimit:
            break;
        case LeakageVoltCh2ItlkLowLimit:
            break;
        case LeakageVoltCh2ItlkHighLimit:
            break;
        case LeakageVoltCh2AlarmLowLimit:
            break;
        case LeakageVoltCh2AlarmHighLimit:
            break;
        case LeakageVoltCh3ItlkLowLimit:
            break;
        case LeakageVoltCh3ItlkHighLimit:
            break;
        case LeakageVoltCh3AlarmLowLimit:
            break;
        case LeakageVoltCh3AlarmHighLimit:
            break;
        case HallCurrentCh1ItlkLowLimit:
            break;
        case HallCurrentCh1ItlkHighLimit:
            break;
        case HallCurrentCh1AlarmLowLimit:
            break;
        case HallCurrentCh1AlarmHighLimit:
            break;
        case HallCurrentCh2ItlkLowLimit:
            break;
        case HallCurrentCh2ItlkHighLimit:
            break;
        case HallCurrentCh2AlarmLowLimit:
            break;
        case HallCurrentCh2AlarmHighLimit:
            break;
        case HallCurrentCh3ItlkLowLimit:
            break;
        case HallCurrentCh3ItlkHighLimit:
            break;
        case HallCurrentCh3AlarmLowLimit:
            break;
        case HallCurrentCh3AlarmHighLimit:
            break;
        case HallCurrentCh4ItlkLowLimit:
            break;
        case HallCurrentCh4ItlkHighLimit:
            break;
        case HallCurrentCh4AlarmLowLimit:
            break;
        case HallCurrentCh4AlarmHighLimit:
            break;
        case InVoltCh1ItlkLowLimit:
            break;
        case InVoltCh1ItlkHighLimit:
            break;
        case InVoltCh1AlarmLowLimit:
            break;
        case InVoltCh1AlarmHighLimit:
            break;
        case InVoltCh2ItlkLowLimit:
            break;
        case InVoltCh2ItlkHighLimit:
            break;
        case InVoltCh2AlarmLowLimit:
            break;
        case InVoltCh2AlarmHighLimit:
            break;
        case InVoltCh3ItlkLowLimit:
            break;
        case InVoltCh3ItlkHighLimit:
            break;
        case InVoltCh3AlarmLowLimit:
            break;
        case InVoltCh3AlarmHighLimit:
            break;
        case InVoltCh4ItlkLowLimit:
            break;
        case InVoltCh4ItlkHighLimit:
            break;
        case InVoltCh4AlarmLowLimit:
            break;
        case InVoltCh4AlarmHighLimit:
            break;
        default:
            break;
    }
}

/**
 * TODO: Put here the implementation for your private functions.
 */
