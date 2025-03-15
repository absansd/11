#include "QR_code.h"


uint8_t QR_Code_Num1;
uint8_t QR_Code_Num2;
uint8_t QR_Code_Num3;
uint8_t QR_Code_Num4;
uint8_t QR_Code_Num5;
uint8_t QR_Code_Num6;


int QR_code_Get(void)
{
    uint8_t err=1;
    uint8_t times;
//    uint8_t len;
    while(err)
    {
        if (UART4_g_usart_rx_sta != 0)         /* 接收到了数据? */
        {
            if( QR_Num1+QR_Num2+QR_Num3==6 || QR_Num1+QR_Num2+QR_Num3==6 )
            {
                if(QR_Num1!=QR_Num2 && QR_Num2!=QR_Num3 && QR_Num3!=QR_Num1 && 
                   QR_Num4!=QR_Num5 && QR_Num5!=QR_Num6 && QR_Num6!=QR_Num4)
                {
                    /*通过TFT显示扫码结果*/
                    LCD_ShowString(10,64-16,UART4_g_usart_rx_buf,RED,WHITE,32,0);
                    /*通过串口1发送扫码结果*/
//                    len = UART4_g_usart_rx_sta & 0x3fff;  /* 得到此次接收到的数据长度 */
//                    HAL_UART_Transmit_IT(&g_uart1_handle,(uint8_t*)UART4_g_usart_rx_buf,len);    /* 发送接收到的数据 */
//                    while(__HAL_UART_GET_FLAG(&g_uart1_handle,UART_FLAG_TC)!=SET);           /* 等待发送结束 */
//                    printf("\r\n\r\n");             /* 插入换行 */
                    QR_Code_Num1 = QR_Num1;		QR_Code_Num2 = QR_Num2;		QR_Code_Num3 = QR_Num3;
                    QR_Code_Num4 = QR_Num4;		QR_Code_Num5 = QR_Num5;		QR_Code_Num6 = QR_Num6;
                    UART4_g_usart_rx_sta = 0;
                    err=0;
                }
            }
        }
        else
        {
            times++;
            if (times % 30  == 0) LED2_TOGGLE(); /* 闪烁LED,提示系统正在运行. */
            HAL_Delay(10);
        }
    }
    return err;
}

