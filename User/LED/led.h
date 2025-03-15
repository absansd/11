#ifndef __LED_H
#define __LED_H

#include "stm32f4xx_hal.h"

#define LED1_GPIO_PORT                  GPIOD
#define LED1_GPIO_PIN                   GPIO_PIN_3
#define LED1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define LED2_GPIO_PORT                  GPIOD
#define LED2_GPIO_PIN                   GPIO_PIN_4
#define LED2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define LED3_GPIO_PORT                  GPIOD
#define LED3_GPIO_PIN                   GPIO_PIN_5
#define LED3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

/* LED端口定义 */
#define LED1(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)

#define LED2(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)

#define LED3(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)

/* LED取反定义 */
#define LED1_TOGGLE()    do{ HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_GPIO_PIN); }while(0)       /* LED1 = !LED1 */
#define LED2_TOGGLE()    do{ HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_GPIO_PIN); }while(0)       /* LED2 = !LED2 */
#define LED3_TOGGLE()    do{ HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_GPIO_PIN); }while(0)       /* LED3 = !LED3 */


void LED_Init(void);


#endif
