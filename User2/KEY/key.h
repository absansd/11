#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx_hal.h"

#define KEY1_GPIO_PORT                  GPIOE
#define KEY1_GPIO_PIN                   GPIO_PIN_14
#define KEY1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define KEY2_GPIO_PORT                  GPIOE
#define KEY2_GPIO_PIN                   GPIO_PIN_13
#define KEY2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define KEY3_GPIO_PORT                  GPIOE
#define KEY3_GPIO_PIN                   GPIO_PIN_12
#define KEY3_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */

#define KEY4_GPIO_PORT                  GPIOE
#define KEY4_GPIO_PIN                   GPIO_PIN_11
#define KEY4_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define KEY5_GPIO_PORT                  GPIOE
#define KEY5_GPIO_PIN                   GPIO_PIN_10
#define KEY5_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define KEY6_GPIO_PORT                  GPIOE
#define KEY6_GPIO_PIN                   GPIO_PIN_9
#define KEY6_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */

#define KEY7_GPIO_PORT                  GPIOE
#define KEY7_GPIO_PIN                   GPIO_PIN_8
#define KEY7_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOE_CLK_ENABLE(); }while(0)   /* PE��ʱ��ʹ�� */
/******************************************************************************************/

#define KEY1        HAL_GPIO_ReadPin(KEY1_GPIO_PORT, KEY1_GPIO_PIN)     /* ��ȡKEY1���� */
#define KEY2        HAL_GPIO_ReadPin(KEY2_GPIO_PORT, KEY2_GPIO_PIN)     /* ��ȡKEY2���� */
#define KEY3        HAL_GPIO_ReadPin(KEY3_GPIO_PORT, KEY3_GPIO_PIN)     /* ��ȡKEY3���� */
#define KEY4        HAL_GPIO_ReadPin(KEY4_GPIO_PORT, KEY4_GPIO_PIN)     /* ��ȡKEY4���� */
#define KEY5        HAL_GPIO_ReadPin(KEY5_GPIO_PORT, KEY5_GPIO_PIN)     /* ��ȡKEY5���� */
#define KEY6        HAL_GPIO_ReadPin(KEY6_GPIO_PORT, KEY6_GPIO_PIN)     /* ��ȡKEY6���� */
#define KEY7        HAL_GPIO_ReadPin(KEY7_GPIO_PORT, KEY7_GPIO_PIN)     /* ��ȡKEY7���� */

#define KEY1_PRES    1              /* KEY1���� */
#define KEY2_PRES    2              /* KEY2���� */
#define KEY3_PRES    3              /* KEY3���� */
#define KEY4_PRES    4              /* KEY4���� */
#define KEY5_PRES    5              /* KEY5���� */
#define KEY6_PRES    6              /* KEY6���� */
#define KEY7_PRES    7              /* KEY7���� */


void KEY_Init(void);
uint8_t key_scan(uint8_t mode);		//����ɨ��


#endif
