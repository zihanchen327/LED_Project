/******************************************************************************
 * led_driver.h - LED 控制模块
 *
 * 板载 LED（共 3 个，低电平点亮）：
 *   绿色 LED4 -> P24
 *   蓝色 LED2 -> P25
 *   黄色 LED3 -> P26
 *   红色 LED1 -> 直接接 GND，上电常亮，不可控
 ******************************************************************************/
#ifndef __LED_DRIVER_H__
#define __LED_DRIVER_H__

#include "ddl.h"

#define LED_GREEN_PORT    GpioPort2
#define LED_GREEN_PIN     GpioPin4
#define LED_BLUE_PORT     GpioPort2
#define LED_BLUE_PIN      GpioPin5
#define LED_YELLOW_PORT   GpioPort2
#define LED_YELLOW_PIN    GpioPin6

#define LED_GREEN         0u
#define LED_BLUE          1u
#define LED_YELLOW        2u

void Led_Init(void);
void Led_On(uint8_t u8Led);
void Led_Off(uint8_t u8Led);
void Led_AllOff(void);

#endif /* __LED_DRIVER_H__ */
