#include "usart.h"

/******************************************************************************************/
/* �������´���, ֧��printf����, ������Ҫѡ��use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");          /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else
/* ʹ��AC5������ʱ, Ҫ�����ﶨ��__FILE �� ��ʹ�ð�����ģʽ */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE �� stdio.h���涨��. */
FILE __stdout;

/* �ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{
    while ((Printf_UART->SR & 0X40) == 0);               /* �ȴ���һ���ַ�������� */

    Printf_UART->DR = (uint8_t)ch;                       /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
    return ch;
}
#endif
/***********************************************END*******************************************/


/* ���ջ���, ���USART_REC_LEN���ֽ�. */
uint8_t USART1_g_usart_rx_buf[USART1_REC_LEN];
uint8_t USART2_g_usart_rx_buf[USART2_REC_LEN];
uint8_t USART3_g_usart_rx_buf[USART3_REC_LEN];
uint8_t UART4_g_usart_rx_buf[UART4_REC_LEN];
uint8_t UART5_g_usart_rx_buf[UART5_REC_LEN];

/* ���ջ���, ���USART_REC_LEN���ֽ�. */
uint8_t USART1_g_usart_rx_buf[USART1_REC_LEN];
uint8_t USART2_g_usart_rx_buf[USART2_REC_LEN];
uint8_t USART3_g_usart_rx_buf[USART3_REC_LEN];
uint8_t UART4_g_usart_rx_buf[UART4_REC_LEN];
uint8_t UART5_g_usart_rx_buf[UART5_REC_LEN];

/*  ����״̬
 *  bit15��      ������ɱ�־
 *  bit14��      ���յ�0x0d
 *  bit13~0��    ���յ�����Ч�ֽ���Ŀ
*/
uint16_t USART1_g_usart_rx_sta = 0;
uint16_t USART2_g_usart_rx_sta = 0;
uint16_t USART3_g_usart_rx_sta = 0;
uint16_t UART4_g_usart_rx_sta = 0;
uint16_t UART5_g_usart_rx_sta = 0;

/* HAL��ʹ�õĴ��ڽ��ջ��� */
uint8_t USART1_g_rx_buffer[USART1_RXBUFFERSIZE];
uint8_t USART2_g_rx_buffer[USART2_RXBUFFERSIZE];
uint8_t USART3_g_rx_buffer[USART3_RXBUFFERSIZE];
uint8_t UART4_g_rx_buffer[UART4_RXBUFFERSIZE];
uint8_t UART5_g_rx_buffer[UART5_RXBUFFERSIZE];

/* UART��� */
UART_HandleTypeDef g_uart1_handle;
UART_HandleTypeDef g_uart2_handle;
UART_HandleTypeDef g_uart3_handle;
UART_HandleTypeDef g_uart4_handle;
UART_HandleTypeDef g_uart5_handle;



/**
 * @brief       ����1��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 *              �����USART��ʱ��Դ��sys_stm32_clock_init()�������Ѿ����ù���.
 * @retval      ��
 */
void usart1_init(uint32_t baudrate)
{
    g_uart1_handle.Instance = USART1;                           /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                    /* ������ */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
    HAL_UART_Init(&g_uart1_handle);                             /* HAL_UART_Init()��ʹ��UART1 */
    
    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)USART1_g_rx_buffer, USART1_RXBUFFERSIZE);
}

/**
 * @brief       ����2��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 *              �����USART��ʱ��Դ��sys_stm32_clock_init()�������Ѿ����ù���.
 * @retval      ��
 */
void usart2_init(uint32_t baudrate)
{
    g_uart2_handle.Instance = USART2;                           /* USART2 */
    g_uart2_handle.Init.BaudRate = baudrate;                    /* ������ */
    g_uart2_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart2_handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
    g_uart2_handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
    g_uart2_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
    g_uart2_handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
    HAL_UART_Init(&g_uart2_handle);                             /* HAL_UART_Init()��ʹ��UART2 */
    
    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
    HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)USART2_g_rx_buffer,USART2_RXBUFFERSIZE);
}

/**
 * @brief       ����3��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 *              �����USART��ʱ��Դ��sys_stm32_clock_init()�������Ѿ����ù���.
 * @retval      ��
 */
void usart3_init(uint32_t baudrate)
{
    g_uart3_handle.Instance = USART3;                           /* USART3 */
    g_uart3_handle.Init.BaudRate = baudrate;                    /* ������ */
    g_uart3_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart3_handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
    g_uart3_handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
    g_uart3_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
    g_uart3_handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
    HAL_UART_Init(&g_uart3_handle);                             /* HAL_UART_Init()��ʹ��UART3 */
    
    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
    HAL_UART_Receive_IT(&g_uart3_handle, (uint8_t *)USART3_g_rx_buffer,USART3_RXBUFFERSIZE);
}

/**
 * @brief       ����4��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 *              �����USART��ʱ��Դ��sys_stm32_clock_init()�������Ѿ����ù���.
 * @retval      ��
 */
void uart4_init(uint32_t baudrate)
{
    g_uart4_handle.Instance = UART4;                            /* UART4 */
    g_uart4_handle.Init.BaudRate = baudrate;                    /* ������ */
    g_uart4_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart4_handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
    g_uart4_handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
    g_uart4_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
    g_uart4_handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
    HAL_UART_Init(&g_uart4_handle);                             /* HAL_UART_Init()��ʹ��UART4 */
    
    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
    HAL_UART_Receive_IT(&g_uart4_handle, (uint8_t *)UART4_g_rx_buffer,UART4_RXBUFFERSIZE);
}

/**
 * @brief       ����5��ʼ������
 * @param       baudrate: ������, �����Լ���Ҫ���ò�����ֵ
 * @note        ע��: ����������ȷ��ʱ��Դ, ���򴮿ڲ����ʾͻ������쳣.
 *              �����USART��ʱ��Դ��sys_stm32_clock_init()�������Ѿ����ù���.
 * @retval      ��
 */
void uart5_init(uint32_t baudrate)
{
    g_uart5_handle.Instance = UART5;                            /* UART5 */
    g_uart5_handle.Init.BaudRate = baudrate;                    /* ������ */
    g_uart5_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* �ֳ�Ϊ8λ���ݸ�ʽ */
    g_uart5_handle.Init.StopBits = UART_STOPBITS_1;             /* һ��ֹͣλ */
    g_uart5_handle.Init.Parity = UART_PARITY_NONE;              /* ����żУ��λ */
    g_uart5_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* ��Ӳ������ */
    g_uart5_handle.Init.Mode = UART_MODE_TX_RX;                 /* �շ�ģʽ */
    g_uart5_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&g_uart5_handle);                             /* HAL_UART_Init()��ʹ��UART5 */

//    /* �ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ��������������� */
//    HAL_UART_Receive_IT(&g_uart5_handle, (uint8_t *)UART5_g_rx_buffer,UART5_RXBUFFERSIZE);
}

/**
 * @brief       UART�ײ��ʼ������
 * @param       huart: UART�������ָ��
 * @note        �˺����ᱻHAL_UART_Init()����
 *              ���ʱ��ʹ�ܣ��������ã��ж�����
 * @retval      ��
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    if(huart->Instance == USART1)                              /* ����Ǵ���1�����д���1 MSP��ʼ�� */
    {
        __HAL_RCC_USART1_CLK_ENABLE();                         /* USART1 ʱ��ʹ�� */
        __HAL_RCC_GPIOA_CLK_ENABLE();                          /* ����,��������ʱ��ʹ�� */

        GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;          /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* �������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;           /* ����ΪUSART1 */
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                /* ��ʼ���������� */
        HAL_NVIC_EnableIRQ(USART1_IRQn);                       /* ʹ��USART1�ж�ͨ�� */
        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);               /* ��ռ���ȼ�3�������ȼ�3 */
    }
    else if(huart->Instance == USART2)                         /* ����Ǵ���2�����д���2 MSP��ʼ�� */
    {
        __HAL_RCC_USART2_CLK_ENABLE();                         /* USART2 ʱ��ʹ�� */
        __HAL_RCC_GPIOA_CLK_ENABLE();                          /* ����,��������ʱ��ʹ�� */

        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;           /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* �������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;           /* ����ΪUSART2 */
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                /* ��ʼ���������� */
        HAL_NVIC_EnableIRQ(USART2_IRQn);                       /* ʹ��USART2�ж�ͨ�� */
        HAL_NVIC_SetPriority(USART2_IRQn, 3, 3);               /* ��ռ���ȼ�3�������ȼ�3 */
    }
    else if(huart->Instance == USART3)                         /* ����Ǵ���3�����д���3 MSP��ʼ�� */
    {
        __HAL_RCC_USART3_CLK_ENABLE();                         /* USART3 ʱ��ʹ�� */
        __HAL_RCC_GPIOB_CLK_ENABLE();                          /* ����,��������ʱ��ʹ�� */

        GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;         /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* �������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
        GPIO_InitStruct.Alternate = GPIO_AF7_USART3;           /* ����ΪUSART3 */
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);                /* ��ʼ���������� */
        HAL_NVIC_EnableIRQ(USART3_IRQn);                       /* ʹ��USART3�ж�ͨ�� */
        HAL_NVIC_SetPriority(USART3_IRQn, 3, 3);               /* ��ռ���ȼ�3�������ȼ�3 */
    }
    else if(huart->Instance == UART4)                          /* ����Ǵ���4�����д���4 MSP��ʼ�� */
    {
        __HAL_RCC_UART4_CLK_ENABLE();                          /* UART4 ʱ��ʹ�� */
        __HAL_RCC_GPIOC_CLK_ENABLE();                          /* ����,��������ʱ��ʹ�� */

        GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;         /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* �������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* ���� */
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;            /* ����ΪUART4 */
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);                /* ��ʼ���������� */
        HAL_NVIC_EnableIRQ(UART4_IRQn);                        /* ʹ��UART4�ж�ͨ�� */
        HAL_NVIC_SetPriority(UART4_IRQn, 3, 3);                /* ��ռ���ȼ�3�������ȼ�3 */
    }
    else if(huart->Instance == UART5)                          /* ����Ǵ���5�����д���5 MSP��ʼ�� */
    {
        __HAL_RCC_UART5_CLK_ENABLE();                          /* UART5 ʱ��ʹ�� */
        __HAL_RCC_GPIOC_CLK_ENABLE();                          /* ��������ʱ��ʹ�� */
        __HAL_RCC_GPIOD_CLK_ENABLE();                          /* ��������ʱ��ʹ�� */

        GPIO_InitStruct.Pin = GPIO_PIN_12;                     /* TX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* �������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* ���� */
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;            /* ����ΪUART5 */
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);                /* ��ʼ���������� */

        GPIO_InitStruct.Pin = GPIO_PIN_2;                      /* RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* �������� */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* ���� */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* ���� */
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;            /* ����ΪUART5 */
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);                /* ��ʼ���������� */

        HAL_NVIC_EnableIRQ(UART5_IRQn);                        /* ʹ��UART5�ж�ͨ�� */
        HAL_NVIC_SetPriority(UART5_IRQn, 3, 3);                /* ��ռ���ȼ�3�������ȼ�3 */
    } 
}




/**
 * @brief       Rx����ص�����
 * @param       huart: UART�������ָ��
 * @retval      ��
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)             /* ����Ǵ���1 */
    {
        if((USART1_g_usart_rx_sta & 0x8000) == 0)      /* ����δ��� */
        {
            if(USART1_g_usart_rx_sta & 0x4000)         /* ���յ���0x0d */
            {
                if(USART1_g_rx_buffer[0] != 0x0a) 
                {
                    USART1_g_usart_rx_sta = 0;         /* ���մ���,���¿�ʼ */
                }
                else 
                {
                    USART1_g_usart_rx_sta |= 0x8000;   /* ��������� */
                }
            }
            else                                /* ��û�յ�0X0D */
            {
                if(USART1_g_rx_buffer[0] == 0x0d)
                {
                    USART1_g_usart_rx_sta |= 0x4000;
                }
                else
                {
                    USART1_g_usart_rx_buf[USART1_g_usart_rx_sta & 0X3FFF] = USART1_g_rx_buffer[0] ;
                    USART1_g_usart_rx_sta++;
                    if(USART1_g_usart_rx_sta > (USART1_REC_LEN - 1))
                    {
                        USART1_g_usart_rx_sta = 0;     /* �������ݴ���,���¿�ʼ���� */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)USART1_g_rx_buffer, USART1_RXBUFFERSIZE);
    }

    else if(huart->Instance == USART2)             /* ����Ǵ���2 */
    {
        if((USART2_g_usart_rx_sta & 0x8000) == 0)      /* ����δ��� */
        {
            if(USART2_g_usart_rx_sta & 0x4000)         /* ���յ���0x0d */
            {
                if(USART2_g_rx_buffer[0] != 0x0a) 
                {
                    USART2_g_usart_rx_sta = 0;         /* ���մ���,���¿�ʼ */
                }
                else 
                {
                    USART2_g_usart_rx_sta |= 0x8000;   /* ��������� */
                }
            }
            else                                /* ��û�յ�0X0D */
            {
                if(USART2_g_rx_buffer[0] == 0x0d)
                {
                    USART2_g_usart_rx_sta |= 0x4000;
                }
                else
                {
                    USART2_g_usart_rx_buf[USART2_g_usart_rx_sta & 0X3FFF] = USART2_g_rx_buffer[0] ;
                    USART2_g_usart_rx_sta++;
                    if(USART2_g_usart_rx_sta > (USART2_REC_LEN - 1))
                    {
                        USART2_g_usart_rx_sta = 0;     /* �������ݴ���,���¿�ʼ���� */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)USART2_g_rx_buffer, USART2_RXBUFFERSIZE);
    }

    else if(huart->Instance == USART3)             /* ����Ǵ���3 */
    {
        if((USART3_g_usart_rx_sta & 0x8000) == 0)      /* ����δ��� */
        {
            if(USART3_g_usart_rx_sta & 0x4000)         /* ���յ���0x0d */
            {
                if(USART3_g_rx_buffer[0] != 0x0a) 
                {
                    USART3_g_usart_rx_sta = 0;         /* ���մ���,���¿�ʼ */
                }
                else 
                {
                    USART3_g_usart_rx_sta |= 0x8000;   /* ��������� */
                }
            }
            else                                /* ��û�յ�0X0D */
            {
                if(USART3_g_rx_buffer[0] == 0x0d)
                {
                    USART3_g_usart_rx_sta |= 0x4000;
                }
                else
                {
                    USART3_g_usart_rx_buf[USART3_g_usart_rx_sta & 0X3FFF] = USART3_g_rx_buffer[0] ;
                    USART3_g_usart_rx_sta++;
                    if(USART3_g_usart_rx_sta > (USART3_REC_LEN - 1))
                    {
                        USART3_g_usart_rx_sta = 0;     /* �������ݴ���,���¿�ʼ���� */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart3_handle, (uint8_t *)USART3_g_rx_buffer, USART3_RXBUFFERSIZE);
    }

    else if(huart->Instance == UART4)             /* ����Ǵ���4 */
    {
        if((UART4_g_usart_rx_sta & 0x8000) == 0)      /* ����δ��� */
        {
            if(UART4_g_usart_rx_sta & 0x4000)         /* ���յ���0x0d */
            {
                if(UART4_g_rx_buffer[0] != 0x0a) 
                {
                    UART4_g_usart_rx_sta = 0;         /* ���մ���,���¿�ʼ */
                }
                else 
                {
                    UART4_g_usart_rx_sta |= 0x8000;   /* ��������� */
                }
            }
            else                                /* ��û�յ�0X0D */
            {
                if(UART4_g_rx_buffer[0] == 0x0d)
                {
                    UART4_g_usart_rx_sta |= 0x4000;
                }
                else
                {
                    UART4_g_usart_rx_buf[UART4_g_usart_rx_sta & 0X3FFF] = UART4_g_rx_buffer[0] ;
                    UART4_g_usart_rx_sta++;
                    if(UART4_g_usart_rx_sta > (UART4_REC_LEN - 1))
                    {
                        UART4_g_usart_rx_sta = 0;     /* �������ݴ���,���¿�ʼ���� */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart4_handle, (uint8_t *)UART4_g_rx_buffer, UART4_RXBUFFERSIZE);
    }

    else if(huart->Instance == UART5)             /* ����Ǵ���5 */
    {
		
		
		
//        if((UART5_g_usart_rx_sta & 0x8000) == 0)      /* ����δ��� */
//        {
//            if(UART5_g_usart_rx_sta & 0x4000)         /* ���յ���0x0d */
//            {
//                if(UART5_g_rx_buffer[0] != 0x0a) 
//                {
//                    UART5_g_usart_rx_sta = 0;         /* ���մ���,���¿�ʼ */
//                }
//                else 
//                {
//                    UART5_g_usart_rx_sta |= 0x8000;   /* ��������� */
//                }
//            }
//            else                                /* ��û�յ�0X0D */
//            {
//                if(UART5_g_rx_buffer[0] == 0x0d)
//                {
//                    UART5_g_usart_rx_sta |= 0x4000;
//                }
//                else
//                {
//                    UART5_g_usart_rx_buf[UART5_g_usart_rx_sta & 0X3FFF] = UART5_g_rx_buffer[0] ;
//                    UART5_g_usart_rx_sta++;
//                    if(UART5_g_usart_rx_sta > (UART5_REC_LEN - 1))
//                    {
//                        UART5_g_usart_rx_sta = 0;     /* �������ݴ���,���¿�ʼ���� */
//                    }
//                }
//            }
//        }
//        
//        HAL_UART_Receive_IT(&g_uart5_handle, (uint8_t *)UART5_g_rx_buffer, UART5_RXBUFFERSIZE);
    }
}


void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==UART5)
  {
    __HAL_RCC_UART5_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);
  }
}


/**
 * @brief       ����1�жϷ�����
 * @param       ��
 * @retval      ��
 */
void USART1_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart1_handle);       /* ����HAL���жϴ����ú��� */
}

/**
 * @brief       ����2�жϷ�����
 * @param       ��
 * @retval      ��
 */
void USART2_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart2_handle);       /* ����HAL���жϴ����ú��� */
}

/**
 * @brief       ����3�жϷ�����
 * @param       ��
 * @retval      ��
 */
void USART3_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart3_handle);       /* ����HAL���жϴ����ú��� */
}

/**
 * @brief       ����4�жϷ�����
 * @param       ��
 * @retval      ��
 */
void UART4_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart4_handle);       /* ����HAL���жϴ����ú��� */
}
/**
 * @brief       ����5�жϷ�����
 * @param       ��
 * @retval      ��
 */
void UART5_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart5_handle);       /* ����HAL���жϴ����ú��� */
}
 

 

void Uart5_Send(uint8_t *buf , uint16_t len)
{
	HAL_UART_Transmit(&g_uart5_handle, buf, len, HAL_MAX_DELAY);
}

int16_t Uart5_Read(uint8_t *buf , uint16_t len, uint32_t timeout)
{
	if(HAL_UART_Receive(&g_uart5_handle, buf, len, timeout)==HAL_OK){
		return len;
	}else{
		return 0;
	}
}






