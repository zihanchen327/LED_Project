/******************************************************************************
 * main.c - HC32F005 LED 闪烁 + UART1 printf
 *
 * UART1: TX = P35, RX = P36, 115200-8-N-1
 ******************************************************************************/
#include "ddl.h"
#include "uart.h"
#include "bt.h"
#include "gpio.h"
#include "led_driver.h"
#include <stdio.h>

/* printf 重定向到 UART1 */
int fputc(int ch, FILE *f)
{
    (void)f;
    if (ch == '\n')
    {
        Uart_SendDataPoll(M0P_UART1, '\r');
    }
    Uart_SendDataPoll(M0P_UART1, (uint8_t)ch);
    return ch;
}

static void App_UartInit(void)
{
    stc_gpio_cfg_t      stcGpioCfg;
    stc_uart_cfg_t      stcUartCfg;
    stc_uart_baud_cfg_t stcBaud;
    stc_bt_cfg_t        stcBtCfg;
    uint16_t            u16Timer;

    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1, TRUE);
    Sysctrl_SetPeripheralGate(SysctrlPeripheralBt, TRUE);

    /* TX: P35 -> UART1_TX (AF1) */
    DDL_ZERO_STRUCT(stcGpioCfg);
    stcGpioCfg.enDir = GpioDirOut;
    Gpio_Init(GpioPort3, GpioPin5, &stcGpioCfg);
    Gpio_SetAfMode(GpioPort3, GpioPin5, GpioAf1);

    /* RX: P36 -> UART1_RX (AF1) */
    stcGpioCfg.enDir = GpioDirIn;
    Gpio_Init(GpioPort3, GpioPin6, &stcGpioCfg);
    Gpio_SetAfMode(GpioPort3, GpioPin6, GpioAf1);

    /* 波特率重装值 + BT1 生成波特率 */
    DDL_ZERO_STRUCT(stcBaud);
    stcBaud.bDbaud  = 0u;
    stcBaud.u32Baud = 115200u;
    stcBaud.enMode  = UartMode3;
    stcBaud.u32Pclk = Sysctrl_GetPClkFreq();
    u16Timer = Uart_SetBaudRate(M0P_UART1, &stcBaud);

    DDL_ZERO_STRUCT(stcBtCfg);
    stcBtCfg.enMD = BtMode2;
    stcBtCfg.enCT = BtTimer;
    Bt_Init(TIM1, &stcBtCfg);
    Bt_ARRSet(TIM1, u16Timer);
    Bt_Cnt16Set(TIM1, u16Timer);
    Bt_Run(TIM1);

    /* UART1 模式3 */
    DDL_ZERO_STRUCT(stcUartCfg);
    stcUartCfg.enRunMode = UartMode3;
    Uart_Init(M0P_UART1, &stcUartCfg);
}

int32_t main(void)
{
    uint32_t u32Tick = 0;

    Led_Init();
    App_UartInit();

    printf("HC32F005 LED + UART demo start\n");

    while (1)
    {
        u32Tick++;
        Led_Toggle();
        printf("[%u] LED toggle\n", (unsigned)u32Tick);
        delay1ms(1000);
    }
}

/******************************************************************************
 * EOF
 ******************************************************************************/
