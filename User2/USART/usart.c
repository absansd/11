#include "usart.h"

/******************************************************************************************/
/* 加入以下代码, 支持printf函数, 而不需要选择use MicroLIB */

#if 1
#if (__ARMCC_VERSION >= 6010050)                    /* 使用AC6编译器时 */
__asm(".global __use_no_semihosting\n\t");          /* 声明不使用半主机模式 */
__asm(".global __ARM_use_no_argv \n\t");            /* AC6下需要声明main函数为无参数格式，否则部分例程可能出现半主机模式 */

#else
/* 使用AC5编译器时, 要在这里定义__FILE 和 不使用半主机模式 */
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

#endif

/* 不使用半主机模式，至少需要重定义_ttywrch\_sys_exit\_sys_command_string函数,以同时兼容AC6和AC5模式 */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* 定义_sys_exit()以避免使用半主机模式 */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

/* FILE 在 stdio.h里面定义. */
FILE __stdout;

/* 重定义fputc函数, printf函数最终会通过调用fputc输出字符串到串口 */
int fputc(int ch, FILE *f)
{
    while ((Printf_UART->SR & 0X40) == 0);               /* 等待上一个字符发送完成 */

    Printf_UART->DR = (uint8_t)ch;                       /* 将要发送的字符 ch 写入到DR寄存器 */
    return ch;
}
#endif
/***********************************************END*******************************************/


/* 接收缓冲, 最大USART_REC_LEN个字节. */
uint8_t USART1_g_usart_rx_buf[USART1_REC_LEN];
uint8_t USART2_g_usart_rx_buf[USART2_REC_LEN];
uint8_t USART3_g_usart_rx_buf[USART3_REC_LEN];
uint8_t UART4_g_usart_rx_buf[UART4_REC_LEN];
uint8_t UART5_g_usart_rx_buf[UART5_REC_LEN];

/* 接收缓冲, 最大USART_REC_LEN个字节. */
uint8_t USART1_g_usart_rx_buf[USART1_REC_LEN];
uint8_t USART2_g_usart_rx_buf[USART2_REC_LEN];
uint8_t USART3_g_usart_rx_buf[USART3_REC_LEN];
uint8_t UART4_g_usart_rx_buf[UART4_REC_LEN];
uint8_t UART5_g_usart_rx_buf[UART5_REC_LEN];

/*  接收状态
 *  bit15，      接收完成标志
 *  bit14，      接收到0x0d
 *  bit13~0，    接收到的有效字节数目
*/
uint16_t USART1_g_usart_rx_sta = 0;
uint16_t USART2_g_usart_rx_sta = 0;
uint16_t USART3_g_usart_rx_sta = 0;
uint16_t UART4_g_usart_rx_sta = 0;
uint16_t UART5_g_usart_rx_sta = 0;

/* HAL库使用的串口接收缓冲 */
uint8_t USART1_g_rx_buffer[USART1_RXBUFFERSIZE];
uint8_t USART2_g_rx_buffer[USART2_RXBUFFERSIZE];
uint8_t USART3_g_rx_buffer[USART3_RXBUFFERSIZE];
uint8_t UART4_g_rx_buffer[UART4_RXBUFFERSIZE];
uint8_t UART5_g_rx_buffer[UART5_RXBUFFERSIZE];

/* UART句柄 */
UART_HandleTypeDef g_uart1_handle;
UART_HandleTypeDef g_uart2_handle;
UART_HandleTypeDef g_uart3_handle;
UART_HandleTypeDef g_uart4_handle;
UART_HandleTypeDef g_uart5_handle;



/**
 * @brief       串口1初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 *              这里的USART的时钟源在sys_stm32_clock_init()函数中已经设置过了.
 * @retval      无
 */
void usart1_init(uint32_t baudrate)
{
    g_uart1_handle.Instance = USART1;                           /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;                    /* 波特率 */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
    HAL_UART_Init(&g_uart1_handle);                             /* HAL_UART_Init()会使能UART1 */
    
    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)USART1_g_rx_buffer, USART1_RXBUFFERSIZE);
}

/**
 * @brief       串口2初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 *              这里的USART的时钟源在sys_stm32_clock_init()函数中已经设置过了.
 * @retval      无
 */
void usart2_init(uint32_t baudrate)
{
    g_uart2_handle.Instance = USART2;                           /* USART2 */
    g_uart2_handle.Init.BaudRate = baudrate;                    /* 波特率 */
    g_uart2_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
    g_uart2_handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
    g_uart2_handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
    g_uart2_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
    g_uart2_handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
    HAL_UART_Init(&g_uart2_handle);                             /* HAL_UART_Init()会使能UART2 */
    
    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
    HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)USART2_g_rx_buffer,USART2_RXBUFFERSIZE);
}

/**
 * @brief       串口3初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 *              这里的USART的时钟源在sys_stm32_clock_init()函数中已经设置过了.
 * @retval      无
 */
void usart3_init(uint32_t baudrate)
{
    g_uart3_handle.Instance = USART3;                           /* USART3 */
    g_uart3_handle.Init.BaudRate = baudrate;                    /* 波特率 */
    g_uart3_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
    g_uart3_handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
    g_uart3_handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
    g_uart3_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
    g_uart3_handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
    HAL_UART_Init(&g_uart3_handle);                             /* HAL_UART_Init()会使能UART3 */
    
    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
    HAL_UART_Receive_IT(&g_uart3_handle, (uint8_t *)USART3_g_rx_buffer,USART3_RXBUFFERSIZE);
}

/**
 * @brief       串口4初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 *              这里的USART的时钟源在sys_stm32_clock_init()函数中已经设置过了.
 * @retval      无
 */
void uart4_init(uint32_t baudrate)
{
    g_uart4_handle.Instance = UART4;                            /* UART4 */
    g_uart4_handle.Init.BaudRate = baudrate;                    /* 波特率 */
    g_uart4_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
    g_uart4_handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
    g_uart4_handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
    g_uart4_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
    g_uart4_handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
    HAL_UART_Init(&g_uart4_handle);                             /* HAL_UART_Init()会使能UART4 */
    
    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
    HAL_UART_Receive_IT(&g_uart4_handle, (uint8_t *)UART4_g_rx_buffer,UART4_RXBUFFERSIZE);
}

/**
 * @brief       串口5初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 *              这里的USART的时钟源在sys_stm32_clock_init()函数中已经设置过了.
 * @retval      无
 */
void uart5_init(uint32_t baudrate)
{
    g_uart5_handle.Instance = UART5;                            /* UART5 */
    g_uart5_handle.Init.BaudRate = baudrate;                    /* 波特率 */
    g_uart5_handle.Init.WordLength = UART_WORDLENGTH_8B;        /* 字长为8位数据格式 */
    g_uart5_handle.Init.StopBits = UART_STOPBITS_1;             /* 一个停止位 */
    g_uart5_handle.Init.Parity = UART_PARITY_NONE;              /* 无奇偶校验位 */
    g_uart5_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;        /* 无硬件流控 */
    g_uart5_handle.Init.Mode = UART_MODE_TX_RX;                 /* 收发模式 */
    g_uart5_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&g_uart5_handle);                             /* HAL_UART_Init()会使能UART5 */

//    /* 该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量 */
//    HAL_UART_Receive_IT(&g_uart5_handle, (uint8_t *)UART5_g_rx_buffer,UART5_RXBUFFERSIZE);
}

/**
 * @brief       UART底层初始化函数
 * @param       huart: UART句柄类型指针
 * @note        此函数会被HAL_UART_Init()调用
 *              完成时钟使能，引脚配置，中断配置
 * @retval      无
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;
    if(huart->Instance == USART1)                              /* 如果是串口1，进行串口1 MSP初始化 */
    {
        __HAL_RCC_USART1_CLK_ENABLE();                         /* USART1 时钟使能 */
        __HAL_RCC_GPIOA_CLK_ENABLE();                          /* 发送,接收引脚时钟使能 */

        GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;          /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;           /* 复用为USART1 */
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                /* 初始化发送引脚 */
        HAL_NVIC_EnableIRQ(USART1_IRQn);                       /* 使能USART1中断通道 */
        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);               /* 抢占优先级3，子优先级3 */
    }
    else if(huart->Instance == USART2)                         /* 如果是串口2，进行串口2 MSP初始化 */
    {
        __HAL_RCC_USART2_CLK_ENABLE();                         /* USART2 时钟使能 */
        __HAL_RCC_GPIOA_CLK_ENABLE();                          /* 发送,接收引脚时钟使能 */

        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;           /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;           /* 复用为USART2 */
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                /* 初始化发送引脚 */
        HAL_NVIC_EnableIRQ(USART2_IRQn);                       /* 使能USART2中断通道 */
        HAL_NVIC_SetPriority(USART2_IRQn, 3, 3);               /* 抢占优先级3，子优先级3 */
    }
    else if(huart->Instance == USART3)                         /* 如果是串口3，进行串口3 MSP初始化 */
    {
        __HAL_RCC_USART3_CLK_ENABLE();                         /* USART3 时钟使能 */
        __HAL_RCC_GPIOB_CLK_ENABLE();                          /* 发送,接收引脚时钟使能 */

        GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;         /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
        GPIO_InitStruct.Alternate = GPIO_AF7_USART3;           /* 复用为USART3 */
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);                /* 初始化发送引脚 */
        HAL_NVIC_EnableIRQ(USART3_IRQn);                       /* 使能USART3中断通道 */
        HAL_NVIC_SetPriority(USART3_IRQn, 3, 3);               /* 抢占优先级3，子优先级3 */
    }
    else if(huart->Instance == UART4)                          /* 如果是串口4，进行串口4 MSP初始化 */
    {
        __HAL_RCC_UART4_CLK_ENABLE();                          /* UART4 时钟使能 */
        __HAL_RCC_GPIOC_CLK_ENABLE();                          /* 发送,接收引脚时钟使能 */

        GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;         /* TX|RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* 高速 */
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;            /* 复用为UART4 */
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);                /* 初始化发送引脚 */
        HAL_NVIC_EnableIRQ(UART4_IRQn);                        /* 使能UART4中断通道 */
        HAL_NVIC_SetPriority(UART4_IRQn, 3, 3);                /* 抢占优先级3，子优先级3 */
    }
    else if(huart->Instance == UART5)                          /* 如果是串口5，进行串口5 MSP初始化 */
    {
        __HAL_RCC_UART5_CLK_ENABLE();                          /* UART5 时钟使能 */
        __HAL_RCC_GPIOC_CLK_ENABLE();                          /* 发送引脚时钟使能 */
        __HAL_RCC_GPIOD_CLK_ENABLE();                          /* 接收引脚时钟使能 */

        GPIO_InitStruct.Pin = GPIO_PIN_12;                     /* TX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* 高速 */
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;            /* 复用为UART5 */
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);                /* 初始化发送引脚 */

        GPIO_InitStruct.Pin = GPIO_PIN_2;                      /* RX */
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽 */
        GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* 上拉 */
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* 高速 */
        GPIO_InitStruct.Alternate = GPIO_AF8_UART5;            /* 复用为UART5 */
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);                /* 初始化接收引脚 */

        HAL_NVIC_EnableIRQ(UART5_IRQn);                        /* 使能UART5中断通道 */
        HAL_NVIC_SetPriority(UART5_IRQn, 3, 3);                /* 抢占优先级3，子优先级3 */
    } 
}




/**
 * @brief       Rx传输回调函数
 * @param       huart: UART句柄类型指针
 * @retval      无
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)             /* 如果是串口1 */
    {
        if((USART1_g_usart_rx_sta & 0x8000) == 0)      /* 接收未完成 */
        {
            if(USART1_g_usart_rx_sta & 0x4000)         /* 接收到了0x0d */
            {
                if(USART1_g_rx_buffer[0] != 0x0a) 
                {
                    USART1_g_usart_rx_sta = 0;         /* 接收错误,重新开始 */
                }
                else 
                {
                    USART1_g_usart_rx_sta |= 0x8000;   /* 接收完成了 */
                }
            }
            else                                /* 还没收到0X0D */
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
                        USART1_g_usart_rx_sta = 0;     /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)USART1_g_rx_buffer, USART1_RXBUFFERSIZE);
    }

    else if(huart->Instance == USART2)             /* 如果是串口2 */
    {
        if((USART2_g_usart_rx_sta & 0x8000) == 0)      /* 接收未完成 */
        {
            if(USART2_g_usart_rx_sta & 0x4000)         /* 接收到了0x0d */
            {
                if(USART2_g_rx_buffer[0] != 0x0a) 
                {
                    USART2_g_usart_rx_sta = 0;         /* 接收错误,重新开始 */
                }
                else 
                {
                    USART2_g_usart_rx_sta |= 0x8000;   /* 接收完成了 */
                }
            }
            else                                /* 还没收到0X0D */
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
                        USART2_g_usart_rx_sta = 0;     /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart2_handle, (uint8_t *)USART2_g_rx_buffer, USART2_RXBUFFERSIZE);
    }

    else if(huart->Instance == USART3)             /* 如果是串口3 */
    {
        if((USART3_g_usart_rx_sta & 0x8000) == 0)      /* 接收未完成 */
        {
            if(USART3_g_usart_rx_sta & 0x4000)         /* 接收到了0x0d */
            {
                if(USART3_g_rx_buffer[0] != 0x0a) 
                {
                    USART3_g_usart_rx_sta = 0;         /* 接收错误,重新开始 */
                }
                else 
                {
                    USART3_g_usart_rx_sta |= 0x8000;   /* 接收完成了 */
                }
            }
            else                                /* 还没收到0X0D */
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
                        USART3_g_usart_rx_sta = 0;     /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart3_handle, (uint8_t *)USART3_g_rx_buffer, USART3_RXBUFFERSIZE);
    }

    else if(huart->Instance == UART4)             /* 如果是串口4 */
    {
        if((UART4_g_usart_rx_sta & 0x8000) == 0)      /* 接收未完成 */
        {
            if(UART4_g_usart_rx_sta & 0x4000)         /* 接收到了0x0d */
            {
                if(UART4_g_rx_buffer[0] != 0x0a) 
                {
                    UART4_g_usart_rx_sta = 0;         /* 接收错误,重新开始 */
                }
                else 
                {
                    UART4_g_usart_rx_sta |= 0x8000;   /* 接收完成了 */
                }
            }
            else                                /* 还没收到0X0D */
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
                        UART4_g_usart_rx_sta = 0;     /* 接收数据错误,重新开始接收 */
                    }
                }
            }
        }
        
        HAL_UART_Receive_IT(&g_uart4_handle, (uint8_t *)UART4_g_rx_buffer, UART4_RXBUFFERSIZE);
    }

    else if(huart->Instance == UART5)             /* 如果是串口5 */
    {
		
		
		
//        if((UART5_g_usart_rx_sta & 0x8000) == 0)      /* 接收未完成 */
//        {
//            if(UART5_g_usart_rx_sta & 0x4000)         /* 接收到了0x0d */
//            {
//                if(UART5_g_rx_buffer[0] != 0x0a) 
//                {
//                    UART5_g_usart_rx_sta = 0;         /* 接收错误,重新开始 */
//                }
//                else 
//                {
//                    UART5_g_usart_rx_sta |= 0x8000;   /* 接收完成了 */
//                }
//            }
//            else                                /* 还没收到0X0D */
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
//                        UART5_g_usart_rx_sta = 0;     /* 接收数据错误,重新开始接收 */
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
 * @brief       串口1中断服务函数
 * @param       无
 * @retval      无
 */
void USART1_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart1_handle);       /* 调用HAL库中断处理公用函数 */
}

/**
 * @brief       串口2中断服务函数
 * @param       无
 * @retval      无
 */
void USART2_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart2_handle);       /* 调用HAL库中断处理公用函数 */
}

/**
 * @brief       串口3中断服务函数
 * @param       无
 * @retval      无
 */
void USART3_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart3_handle);       /* 调用HAL库中断处理公用函数 */
}

/**
 * @brief       串口4中断服务函数
 * @param       无
 * @retval      无
 */
void UART4_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart4_handle);       /* 调用HAL库中断处理公用函数 */
}
/**
 * @brief       串口5中断服务函数
 * @param       无
 * @retval      无
 */
void UART5_IRQHandler(void)
{ 
    HAL_UART_IRQHandler(&g_uart5_handle);       /* 调用HAL库中断处理公用函数 */
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






