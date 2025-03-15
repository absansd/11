#ifndef __QR_code_H
#define __QR_code_H

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "led.h"
#include "lcd_init.h"
#include "lcd.h"

#define QR_Num1 (UART4_g_usart_rx_buf[0]-'0')
#define QR_Num2 (UART4_g_usart_rx_buf[1]-'0')
#define QR_Num3 (UART4_g_usart_rx_buf[2]-'0')
#define QR_Num4 (UART4_g_usart_rx_buf[4]-'0')
#define QR_Num5 (UART4_g_usart_rx_buf[5]-'0')
#define QR_Num6 (UART4_g_usart_rx_buf[6]-'0')

extern uint8_t QR_Code_Num1;
extern uint8_t QR_Code_Num2;
extern uint8_t QR_Code_Num3;
extern uint8_t QR_Code_Num4;
extern uint8_t QR_Code_Num5;
extern uint8_t QR_Code_Num6;

int QR_code_Get(void);

#endif

