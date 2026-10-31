/******************************************************************************
 * led_driver.h - LED 控制模块
 ******************************************************************************/
#ifndef __LED_DRIVER_H__
#define __LED_DRIVER_H__

#include "ddl.h"

/* LED 引脚(小华 SK TSSOP20 开发板: P03, 低电平点亮) */
#define LED_PORT    GpioPort0
#define LED_PIN     GpioPin3

void Led_Init(void);
void Led_On(void);
void Led_Off(void);
void Led_Toggle(void);

#endif /* __LED_DRIVER_H__ */
