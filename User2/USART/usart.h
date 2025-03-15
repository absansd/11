#ifndef ___USART_H
#define	___USART_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

#define Printf_UART             USART1

#define USART1_REC_LEN          200              /* �����������ֽ��� 200 */
#define USART1_RXBUFFERSIZE     1                /* �����С */

#define USART2_REC_LEN          200              /* �����������ֽ��� 200 */
#define USART2_RXBUFFERSIZE     1                /* �����С */

#define USART3_REC_LEN          200              /* �����������ֽ��� 200 */
#define USART3_RXBUFFERSIZE     1                /* �����С */

#define UART4_REC_LEN           200              /* �����������ֽ��� 200 */
#define UART4_RXBUFFERSIZE      1                /* �����С */

#define UART5_REC_LEN           200              /* �����������ֽ��� 200 */
#define UART5_RXBUFFERSIZE      1                /* �����С */

#define Send_OK 1

extern UART_HandleTypeDef g_uart1_handle;        /* UART��� */
extern UART_HandleTypeDef g_uart2_handle;        /* UART��� */
extern UART_HandleTypeDef g_uart3_handle;        /* UART��� */
extern UART_HandleTypeDef g_uart4_handle;        /* UART��� */
extern UART_HandleTypeDef g_uart5_handle;        /* UART��� */

extern uint8_t  USART1_g_usart_rx_buf[USART1_REC_LEN];         /* ���ջ���,���USART1_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t USART1_g_usart_rx_sta;                         /* ����״̬��� */
extern uint8_t  USART1_g_rx_buffer[USART1_RXBUFFERSIZE];       /* HAL��USART1����Buffer */

extern uint8_t  USART2_g_usart_rx_buf[USART2_REC_LEN];         /* ���ջ���,���USART2_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t USART2_g_usart_rx_sta;                         /* ����״̬��� */
extern uint8_t  USART2_g_rx_buffer[USART2_RXBUFFERSIZE];       /* HAL��USART2����Buffer */

extern uint8_t  USART3_g_usart_rx_buf[USART3_REC_LEN];         /* ���ջ���,���USART3_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t USART3_g_usart_rx_sta;                         /* ����״̬��� */
extern uint8_t  USART3_g_rx_buffer[USART3_RXBUFFERSIZE];       /* HAL��USART3����Buffer */

extern uint8_t  UART4_g_usart_rx_buf[UART4_REC_LEN];           /* ���ջ���,���UART4_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t UART4_g_usart_rx_sta;                          /* ����״̬��� */
extern uint8_t  UART4_g_rx_buffer[UART4_RXBUFFERSIZE];         /* HAL��UART4����Buffer */

extern uint8_t  UART5_g_usart_rx_buf[UART5_REC_LEN];           /* ���ջ���,���UART5_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� */
extern uint16_t UART5_g_usart_rx_sta;                          /* ����״̬��� */
extern uint8_t  UART5_g_rx_buffer[UART5_RXBUFFERSIZE];         /* HAL��UART5����Buffer */

void usart1_init(uint32_t baudrate);             /* ����1��ʼ������ */
void usart2_init(uint32_t baudrate);             /* ����2��ʼ������ */
void usart3_init(uint32_t baudrate);             /* ����3��ʼ������ */
void uart4_init(uint32_t baudrate);              /* ����4��ʼ������ */
void uart5_init(uint32_t baudrate);              /* ����5��ʼ������ */

int16_t Uart5_Read(uint8_t *buf , uint16_t len, uint32_t timeout);
void Uart5_Send(uint8_t *buf , uint16_t len);


#endif
