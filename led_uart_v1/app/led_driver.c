/******************************************************************************
 * led_driver.c - LED 控制模块
 ******************************************************************************/
#include "led_driver.h"
#include "gpio.h"

static uint8_t s_u8LedState = 0;    /* 0 = 熄灭, 1 = 点亮 */

void Led_Init(void)
{
    stc_gpio_cfg_t stcGpioCfg;

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    DDL_ZERO_STRUCT(stcGpioCfg);
    stcGpioCfg.enDir = GpioDirOut;
    stcGpioCfg.enPu  = GpioPuDisable;
    stcGpioCfg.enPd  = GpioPdEnable;

    Led_Off();
    Gpio_Init(LED_PORT, LED_PIN, &stcGpioCfg);
}

void Led_On(void)
{
    Gpio_WriteOutputIO(LED_PORT, LED_PIN, FALSE);   /* 低电平点亮 */
    s_u8LedState = 1;
}

void Led_Off(void)
{
    Gpio_WriteOutputIO(LED_PORT, LED_PIN, TRUE);
    s_u8LedState = 0;
}

void Led_Toggle(void)
{
    if (s_u8LedState)
    {
        Led_Off();
    }
    else
    {
        Led_On();
    }
}
