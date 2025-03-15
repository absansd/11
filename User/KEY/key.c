#include "key.h"

void KEY_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO配置参数存储变量 */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1时钟使能 */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2时钟使能 */
    KEY3_GPIO_CLK_ENABLE();                                     /* KEY3时钟使能 */
    KEY4_GPIO_CLK_ENABLE();                                     /* KEY4时钟使能 */
    KEY5_GPIO_CLK_ENABLE();                                     /* KEY5时钟使能 */
    KEY6_GPIO_CLK_ENABLE();                                     /* KEY6时钟使能 */
    KEY7_GPIO_CLK_ENABLE();                                     /* KEY7时钟使能 */

    gpio_init_struct.Pin = KEY1_GPIO_PIN;                       /* KEY1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);           /* KEY1引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY2_GPIO_PIN;                       /* KEY2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &gpio_init_struct);           /* KEY2引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY3_GPIO_PIN;                       /* KEY3引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY3_GPIO_PORT, &gpio_init_struct);           /* KEY3引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY4_GPIO_PIN;                       /* KEY4引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY4_GPIO_PORT, &gpio_init_struct);           /* KEY4引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY5_GPIO_PIN;                       /* KEY5引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY5_GPIO_PORT, &gpio_init_struct);           /* KEY5引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY6_GPIO_PIN;                       /* KEY6引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY6_GPIO_PORT, &gpio_init_struct);           /* KEY5引脚模式设置,上拉输入 */

    gpio_init_struct.Pin = KEY7_GPIO_PIN;                       /* KEY7引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* 下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
    HAL_GPIO_Init(KEY7_GPIO_PORT, &gpio_init_struct);           /* KEY5引脚模式设置,上拉输入 */
}



/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键):KEY7 > KEY6 > KEY5 > KEY4 > KEY3 > KEY2 > KEY1!!
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY1_PRES, 1, KEY1按下
 *              KEY2_PRES, 2, KEY2按下
 *              KEY3_PRES, 3, KEY3按下
 *              KEY3_PRES, 4, KEY3按下
 *              KEY3_PRES, 5, KEY3按下
 *              KEY3_PRES, 6, KEY3按下
 *              KEY3_PRES, 7, KEY3按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && (KEY1 == 1 || KEY2 == 1 || KEY3 == 1 || KEY4 == 1 || KEY5 == 1 || KEY6 == 1 || KEY7 == 1))/* 按键松开标志为0, 且有任意一个按键按下了 */
    {
        HAL_Delay(10);           /* 去抖动 */
        key_up = 0;
        if (KEY1 == 1)  keyval = KEY1_PRES;
        if (KEY2 == 1)  keyval = KEY2_PRES;
        if (KEY3 == 1)  keyval = KEY3_PRES;
        if (KEY4 == 1)  keyval = KEY4_PRES;
        if (KEY5 == 1)  keyval = KEY5_PRES;
        if (KEY6 == 1)  keyval = KEY6_PRES;
        if (KEY7 == 1)  keyval = KEY7_PRES;
    }
    else if (KEY1 == 0 && KEY2 == 0 && KEY3 == 0 && KEY4 == 0 && KEY5 == 0 && KEY6 == 0 && KEY7 == 0) /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }
    return keyval;              /* 返回键值 */
}

