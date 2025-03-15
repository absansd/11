#include "led.h"



void LED_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO配置参数存储变量 */
    LED1_GPIO_CLK_ENABLE();                                     /* LED1时钟使能 */
    LED2_GPIO_CLK_ENABLE();                                     /* LED2时钟使能 */
    LED3_GPIO_CLK_ENABLE();                                     /* LED3时钟使能 */

    gpio_init_struct.Pin = LED1_GPIO_PIN;                       /* LED1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);           /* 初始化LED1引脚 */	

    gpio_init_struct.Pin = LED2_GPIO_PIN;                       /* LED2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(LED2_GPIO_PORT, &gpio_init_struct);           /* 初始化LED1引脚 */

    gpio_init_struct.Pin = LED3_GPIO_PIN;                       /* LED3引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(LED3_GPIO_PORT, &gpio_init_struct);           /* 初始化LED1引脚 */
	
    LED1(1);                                                /* 关闭 LED1 */
    LED2(1);                                                /* 关闭 LED2 */
    LED3(1);                                                /* 关闭 LED3 */
}



