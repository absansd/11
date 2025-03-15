#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx_hal.h"

#define KEY1_GPIO_PORT                  GPIOE
#define KEY1_GPIO_PIN                   GPIO_PIN_14
#define KEY1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY2_GPIO_PORT                  GPIOE
#define KEY2_GPIO_PIN                   GPIO_PIN_13
#define KEY2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY3_GPIO_PORT                  GPIOE
#define KEY3_GPIO_PIN                   GPIO_PIN_12
#define KEY3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define KEY4_GPIO_PORT                  GPIOE
#define KEY4_GPIO_PIN                   GPIO_PIN_11
#define KEY4_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY5_GPIO_PORT                  GPIOE
#define KEY5_GPIO_PIN                   GPIO_PIN_10
#define KEY5_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY6_GPIO_PORT                  GPIOE
#define KEY6_GPIO_PIN                   GPIO_PIN_9
#define KEY6_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */

#define KEY7_GPIO_PORT                  GPIOE
#define KEY7_GPIO_PIN                   GPIO_PIN_8
#define KEY7_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
/******************************************************************************************/

#define KEY1        HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* 读取KEY1引脚 */
#define KEY2        HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)     /* 读取KEY2引脚 */
#define KEY3        HAL_GPIO_ReadPin(KEY3_GPIO_PORT, KEY3_GPIO_PIN)     /* 读取KEY3引脚 */
#define KEY4        HAL_GPIO_ReadPin(KEY4_GPIO_PORT, KEY4_GPIO_PIN)     /* 读取KEY4引脚 */
#define KEY5        HAL_GPIO_ReadPin(KEY5_GPIO_PORT, KEY5_GPIO_PIN)     /* 读取KEY5引脚 */
#define KEY6        HAL_GPIO_ReadPin(KEY6_GPIO_PORT, KEY6_GPIO_PIN)     /* 读取KEY6引脚 */
#define KEY7        HAL_GPIO_ReadPin(KEY7_GPIO_PORT, KEY7_GPIO_PIN)     /* 读取KEY7引脚 */

#define KEY1_PRES    1              /* KEY1按下 */
#define KEY2_PRES    2              /* KEY2按下 */
#define KEY3_PRES    3              /* KEY3按下 */
#define KEY4_PRES    4              /* KEY4按下 */
#define KEY5_PRES    5              /* KEY5按下 */
#define KEY6_PRES    6              /* KEY6按下 */
#define KEY7_PRES    7              /* KEY7按下 */


void KEY_Init(void);
uint8_t key_scan(uint8_t mode);		//按键扫描


#endif
