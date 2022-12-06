
/////////////////////////////////////////////////////////////////////////////////////////////

#include "application.h"
#include "adc_internal.h"
#include "BoardTempHum.h"
#include "ntc_isolated_i2c.h"
#include "pt100.h"
#include "output.h"
#include "leds.h"
#include "can_bus.h"
#include "input.h"
#include <stdbool.h>
#include <stdint.h>
#include "fac_cmd.h"
#include "fac_is.h"
#include "fac_os.h"
#include "fap.h"

/////////////////////////////////////////////////////////////////////////////////////////////

volatile unsigned char Interlock = 0;
volatile unsigned char Alarm = 0;

static unsigned char ItlkClrCmd = 0;
static unsigned char InterlockOld = 0;
static unsigned char InitApp = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

void AppConfiguration(void)
{

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    config_module_fap();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    config_module_fac_os();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    config_module_fac_is();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

    config_module_fac_cmd();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    // End of configuration
    // Turn on Led1 (board started)
    Led1TurnOff();
    Led2TurnOn();
    Led3TurnOn();
    Led4TurnOn();
    Led5TurnOn();
    Led6TurnOn();
    Led7TurnOn();
    Led8TurnOn();
    Led9TurnOn();
    Led10TurnOn();

}

/////////////////////////////////////////////////////////////////////////////////////////////

void InterlockClear(void)
{
    ItlkClrCmd = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void InterlockSet(void)
{
    Interlock = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void InterlockClearCheck(void)
{
    if(ItlkClrCmd)
    {
        Interlock = 0;

        Alarm = 0;

        InterlockOld = 0;

        InitApp = 0;

        AdcClearAlarmTrip();
        Pt100ClearAlarmTrip();
        RhBoardTempClearAlarmTrip();
        TempIgbt1TempIgbt2ClearAlarmTrip();

        ItlkClrCmd = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

        clear_fap_interlocks();
        clear_fap_alarms();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

        clear_fac_os_interlocks();
        clear_fac_os_alarms();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

        clear_fac_is_interlocks();
        clear_fac_is_alarms();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

        clear_fac_cmd_interlocks();
        clear_fac_cmd_alarms();

#endif

    }

}

/////////////////////////////////////////////////////////////////////////////////////////////

void AppInterlock(void)
{
    // caso haja algum Interlock, o rele auxiliar deve ser desligado e as opera��es cabiveis de Interlock devem ser executadas
    // Analisar se todos os interlocks foram apagados para poder liberar o rele auxiliar
    // caso n�o haja mais Interlock, fechar o rele auxiliar

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    ReleAuxTurnOff();
    ReleExtItlkTurnOff();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    ReleAuxTurnOff();
    ReleExtItlkTurnOff();
    Gpdo1TurnOff();
    Gpdo2TurnOff();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    ReleAuxTurnOff();
    ReleExtItlkTurnOff();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

    ReleAuxTurnOff();
    ReleExtItlkTurnOff();

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////

void AlarmClear(void)
{
    Alarm = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void AlarmSet(void)
{
    Alarm = 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////

void InterlockAppCheck(void)
{
    unsigned char test = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    test = check_fap_interlocks();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    test = check_fac_os_interlocks();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    test = check_fac_is_interlocks();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

    test = check_fac_cmd_interlocks();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    if(test)
    {
        InterlockSet();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

void AlarmAppCheck(void)
{
    unsigned char test = 0;

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    test = check_fap_alarms();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    test = check_fac_os_alarms();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    test = check_fac_is_alarms();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

    test = check_fac_cmd_alarms();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    if(test)
    {
        AlarmSet();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////

void LedIndicationStatus(void)
{

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    check_fap_indication_leds();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    check_fac_os_indication_leds();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    check_fac_is_indication_leds();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

    check_fac_cmd_indication_leds();

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////

void Application(void)
{

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    fap_application_readings();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    fac_os_application_readings();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    fac_is_application_readings();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

    fac_cmd_application_readings();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    InterlockAppCheck();

    AlarmAppCheck();

    // Interlock Test
    if(Interlock == 1 && InterlockOld == 0)
    {
        InterlockOld = 1;
        AppInterlock();
        //Gpdo1TurnOn(); // Para teste de interlock
    }

    // Actions that needs to be taken during the Application initialization
    if(InitApp == 0 && Interlock == 0)
    {
        InitApp = 1;

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

        ReleAuxTurnOn();
        ReleExtItlkTurnOff();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

        ReleAuxTurnOn();
        ReleExtItlkTurnOn();
        Gpdo1TurnOn();
        Gpdo2TurnOn();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

        ReleAuxTurnOn();
        ReleExtItlkTurnOn();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

        ReleAuxTurnOn();
        ReleExtItlkTurnOn();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

    }

    InterlockClearCheck();
}

/////////////////////////////////////////////////////////////////////////////////////////////

void send_data_schedule()
{

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    static uint8_t i = 0;

    send_data_message(i);

    i++;

    if (i > 7) i = 0;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    static uint8_t i = 0;

    send_data_message(i);

    i++;

    if (i > 7) i = 0;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    static uint8_t i = 0;

    send_data_message(i);

    i++;

    if (i > 5) i = 0;

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

    static uint8_t i = 0;

    send_data_message(i);

    i++;

    if (i > 5) i = 0;

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////

void power_on_check()
{

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAP

    if(fap.Relay) {

        Led1TurnOff();
        ReleExtItlkTurnOff();
    }

    else {

        Led1TurnOn();
        ReleExtItlkTurnOn();
    }

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_OS

    Led1TurnOn();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_IS

    Led1TurnOn();

#endif

/////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FAC_CMD

#if !defined (FAC_NOVO_CMD)

    Led1TurnOn();

#endif /* FAC_NOVO_CMD */

#endif

}

/////////////////////////////////////////////////////////////////////////////////////////////





