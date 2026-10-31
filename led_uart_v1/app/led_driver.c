/******************************************************************************
 * led_driver.c - LED 控制模块
 ******************************************************************************/
#include "led_driver.h"
#include "gpio.h"

static const en_gpio_port_t s_enLedPort[3] = { LED_GREEN_PORT, LED_BLUE_PORT, LED_YELLOW_PORT };
static const en_gpio_pin_t  s_enLedPin[3]  = { LED_GREEN_PIN,  LED_BLUE_PIN,  LED_YELLOW_PIN  };

void Led_Init(void)
{
    stc_gpio_cfg_t stcGpioCfg;
    uint8_t i;

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    DDL_ZERO_STRUCT(stcGpioCfg);
    stcGpioCfg.enDir = GpioDirOut;
    stcGpioCfg.enPu  = GpioPuDisable;
    stcGpioCfg.enPd  = GpioPdDisable;

    for (i = 0u; i < 3u; i++)
    {
        Gpio_WriteOutputIO(s_enLedPort[i], s_enLedPin[i], TRUE);
        Gpio_Init(s_enLedPort[i], s_enLedPin[i], &stcGpioCfg);
    }
}

void Led_On(uint8_t u8Led)
{
    if (u8Led < 3u)
    {
        Gpio_WriteOutputIO(s_enLedPort[u8Led], s_enLedPin[u8Led], FALSE);
    }
}

void Led_Off(uint8_t u8Led)
{
    if (u8Led < 3u)
    {
        Gpio_WriteOutputIO(s_enLedPort[u8Led], s_enLedPin[u8Led], TRUE);
    }
}

void Led_AllOff(void)
{
    uint8_t i;
    for (i = 0u; i < 3u; i++)
    {
        Gpio_WriteOutputIO(s_enLedPort[i], s_enLedPin[i], TRUE);
    }
}
