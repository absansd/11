#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f4xx_hal.h"


/******************************************************************************************/
/* 引脚 定义 */

#define BEEP_GPIO_PORT                  GPIOB
#define BEEP_GPIO_PIN                   GPIO_PIN_14
#define BEEP_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)         /* PF口时钟使能 */

/******************************************************************************************/

/* 蜂鸣器控制 */
#define BEEP(x)         do{ x ? \
                            HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_SET) : \
                            HAL_GPIO_WritePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN, GPIO_PIN_RESET); \
                        }while(0)

/* BEEP状态翻转 */
#define BEEP_TOGGLE()   do{ HAL_GPIO_TogglePin(BEEP_GPIO_PORT, BEEP_GPIO_PIN); }while(0)    /* BEEP = !BEEP */

void beep_init(void);   /* 初始化蜂鸣器 */

#endif

















