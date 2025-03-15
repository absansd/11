#include "key.h"

void KEY_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct;                          /* GPIO���ò����洢���� */
    KEY1_GPIO_CLK_ENABLE();                                     /* KEY1ʱ��ʹ�� */
    KEY2_GPIO_CLK_ENABLE();                                     /* KEY2ʱ��ʹ�� */
    KEY3_GPIO_CLK_ENABLE();                                     /* KEY3ʱ��ʹ�� */
    KEY4_GPIO_CLK_ENABLE();                                     /* KEY4ʱ��ʹ�� */
    KEY5_GPIO_CLK_ENABLE();                                     /* KEY5ʱ��ʹ�� */
    KEY6_GPIO_CLK_ENABLE();                                     /* KEY6ʱ��ʹ�� */
    KEY7_GPIO_CLK_ENABLE();                                     /* KEY7ʱ��ʹ�� */

    gpio_init_struct.Pin = KEY1_GPIO_PIN;                       /* KEY1���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY1_GPIO_PORT, &gpio_init_struct);           /* KEY1����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY2_GPIO_PIN;                       /* KEY2���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY2_GPIO_PORT, &gpio_init_struct);           /* KEY2����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY3_GPIO_PIN;                       /* KEY3���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY3_GPIO_PORT, &gpio_init_struct);           /* KEY3����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY4_GPIO_PIN;                       /* KEY4���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY4_GPIO_PORT, &gpio_init_struct);           /* KEY4����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY5_GPIO_PIN;                       /* KEY5���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY5_GPIO_PORT, &gpio_init_struct);           /* KEY5����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY6_GPIO_PIN;                       /* KEY6���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY6_GPIO_PORT, &gpio_init_struct);           /* KEY5����ģʽ����,�������� */

    gpio_init_struct.Pin = KEY7_GPIO_PIN;                       /* KEY7���� */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* ���� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                        /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* ���� */
    HAL_GPIO_Init(KEY7_GPIO_PORT, &gpio_init_struct);           /* KEY5����ģʽ����,�������� */
}



/**
 * @brief       ����ɨ�躯��
 * @note        �ú�������Ӧ���ȼ�(ͬʱ���¶������):KEY7 > KEY6 > KEY5 > KEY4 > KEY3 > KEY2 > KEY1!!
 * @param       mode:0 / 1, ���庬������:
 *   @arg       0,  ��֧��������(���������²���ʱ, ֻ�е�һ�ε��û᷵�ؼ�ֵ,
 *                  �����ɿ��Ժ�, �ٴΰ��²Ż᷵��������ֵ)
 *   @arg       1,  ֧��������(���������²���ʱ, ÿ�ε��øú������᷵�ؼ�ֵ)
 * @retval      ��ֵ, ��������:
 *              KEY1_PRES, 1, KEY1����
 *              KEY2_PRES, 2, KEY2����
 *              KEY3_PRES, 3, KEY3����
 *              KEY3_PRES, 4, KEY3����
 *              KEY3_PRES, 5, KEY3����
 *              KEY3_PRES, 6, KEY3����
 *              KEY3_PRES, 7, KEY3����
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* �������ɿ���־ */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* ֧������ */

    if (key_up && (KEY1 == 1 || KEY2 == 1 || KEY3 == 1 || KEY4 == 1 || KEY5 == 1 || KEY6 == 1 || KEY7 == 1))/* �����ɿ���־Ϊ0, ��������һ������������ */
    {
        HAL_Delay(10);           /* ȥ���� */
        key_up = 0;
        if (KEY1 == 1)  keyval = KEY1_PRES;
        if (KEY2 == 1)  keyval = KEY2_PRES;
        if (KEY3 == 1)  keyval = KEY3_PRES;
        if (KEY4 == 1)  keyval = KEY4_PRES;
        if (KEY5 == 1)  keyval = KEY5_PRES;
        if (KEY6 == 1)  keyval = KEY6_PRES;
        if (KEY7 == 1)  keyval = KEY7_PRES;
    }
    else if (KEY1 == 0 && KEY2 == 0 && KEY3 == 0 && KEY4 == 0 && KEY5 == 0 && KEY6 == 0 && KEY7 == 0) /* û���κΰ�������, ��ǰ����ɿ� */
    {
        key_up = 1;
    }
    return keyval;              /* ���ؼ�ֵ */
}

