#ifndef ___USART_H
#define	___USART_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

#define Printf_UART             USART1

#define USART1_REC_LEN          200              /* 定义最大接收字节数 200 */
#define USART1_RXBUFFERSIZE     1                /* 缓存大小 */

#define USART2_REC_LEN          200              /* 定义最大接收字节数 200 */
#define USART2_RXBUFFERSIZE     1                /* 缓存大小 */

#define USART3_REC_LEN          200              /* 定义最大接收字节数 200 */
#define USART3_RXBUFFERSIZE     1                /* 缓存大小 */

#define UART4_REC_LEN           200              /* 定义最大接收字节数 200 */
#define UART4_RXBUFFERSIZE      1                /* 缓存大小 */

#define UART5_REC_LEN           200              /* 定义最大接收字节数 200 */
#define UART5_RXBUFFERSIZE      1                /* 缓存大小 */

#define Send_OK 1

extern UART_HandleTypeDef g_uart1_handle;        /* UART句柄 */
extern UART_HandleTypeDef g_uart2_handle;        /* UART句柄 */
extern UART_HandleTypeDef g_uart3_handle;        /* UART句柄 */
extern UART_HandleTypeDef g_uart4_handle;        /* UART句柄 */
extern UART_HandleTypeDef g_uart5_handle;        /* UART句柄 */

extern uint8_t  USART1_g_usart_rx_buf[USART1_REC_LEN];         /* 接收缓冲,最大USART1_REC_LEN个字节.末字节为换行符 */
extern uint16_t USART1_g_usart_rx_sta;                         /* 接收状态标记 */
extern uint8_t  USART1_g_rx_buffer[USART1_RXBUFFERSIZE];       /* HAL库USART1接收Buffer */

extern uint8_t  USART2_g_usart_rx_buf[USART2_REC_LEN];         /* 接收缓冲,最大USART2_REC_LEN个字节.末字节为换行符 */
extern uint16_t USART2_g_usart_rx_sta;                         /* 接收状态标记 */
extern uint8_t  USART2_g_rx_buffer[USART2_RXBUFFERSIZE];       /* HAL库USART2接收Buffer */

extern uint8_t  USART3_g_usart_rx_buf[USART3_REC_LEN];         /* 接收缓冲,最大USART3_REC_LEN个字节.末字节为换行符 */
extern uint16_t USART3_g_usart_rx_sta;                         /* 接收状态标记 */
extern uint8_t  USART3_g_rx_buffer[USART3_RXBUFFERSIZE];       /* HAL库USART3接收Buffer */

extern uint8_t  UART4_g_usart_rx_buf[UART4_REC_LEN];           /* 接收缓冲,最大UART4_REC_LEN个字节.末字节为换行符 */
extern uint16_t UART4_g_usart_rx_sta;                          /* 接收状态标记 */
extern uint8_t  UART4_g_rx_buffer[UART4_RXBUFFERSIZE];         /* HAL库UART4接收Buffer */

extern uint8_t  UART5_g_usart_rx_buf[UART5_REC_LEN];           /* 接收缓冲,最大UART5_REC_LEN个字节.末字节为换行符 */
extern uint16_t UART5_g_usart_rx_sta;                          /* 接收状态标记 */
extern uint8_t  UART5_g_rx_buffer[UART5_RXBUFFERSIZE];         /* HAL库UART5接收Buffer */

void usart1_init(uint32_t baudrate);             /* 串口1初始化函数 */
void usart2_init(uint32_t baudrate);             /* 串口2初始化函数 */
void usart3_init(uint32_t baudrate);             /* 串口3初始化函数 */
void uart4_init(uint32_t baudrate);              /* 串口4初始化函数 */
void uart5_init(uint32_t baudrate);              /* 串口5初始化函数 */

int16_t Uart5_Read(uint8_t *buf , uint16_t len, uint32_t timeout);
void Uart5_Send(uint8_t *buf , uint16_t len);


#endif
