#include "Maixcam.h"


Cam_Data cam_data;

void Maixcam_Test(void)
{
    Maixcam_Data();
    printf("color %c  ",cam_data.color);
    printf("col_x %d  ",cam_data.col_x);
    printf("col_y %d  ",cam_data.col_y);
    HAL_UART_Transmit_IT(&g_uart1_handle,(uint8_t*)USART3_g_usart_rx_buf,8);    /* ���ͽ��յ������� */
    printf("\n");
}

void Maixcam_Mode(uint8_t mode)
{
    char Num[2];
    // ������ת��Ϊ�ַ���
    sprintf(Num, "%d", mode);
    HAL_UART_Transmit(&g_uart3_handle, (uint8_t*)Num, 2, HAL_MAX_DELAY);
}

void Maixcam_Data(void)
{
    if (USART3_g_usart_rx_sta != 0)         /* ���յ�������? */
    {
        cam_data.color = USART3_g_usart_rx_buf[0];
        if(USART3_g_usart_rx_buf[1]=='-')
        {
            cam_data.col_x=-((USART3_g_usart_rx_buf[2]-'0')*10+(USART3_g_usart_rx_buf[3]-'0'));
            if(USART3_g_usart_rx_buf[5]=='-')
            {
                cam_data.col_y=-((USART3_g_usart_rx_buf[6]-'0')*10+(USART3_g_usart_rx_buf[7]-'0'));
            }
            else cam_data.col_y=((USART3_g_usart_rx_buf[5]-'0')*10+(USART3_g_usart_rx_buf[6]-'0'));
        }
        else
        {
            cam_data.col_x=((USART3_g_usart_rx_buf[1]-'0')*10+(USART3_g_usart_rx_buf[2]-'0'));
            if(USART3_g_usart_rx_buf[4]=='-')
            {
                cam_data.col_y=-((USART3_g_usart_rx_buf[5]-'0')*10+(USART3_g_usart_rx_buf[6]-'0'));
            }
            else cam_data.col_y=((USART3_g_usart_rx_buf[4]-'0')*10+(USART3_g_usart_rx_buf[5]-'0'));
        }
        USART3_g_usart_rx_sta = 0;
    }
}

