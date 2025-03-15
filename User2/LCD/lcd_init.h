#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>


#define USE_HORIZONTAL 1  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 128

#else
#define LCD_W 128
#define LCD_H 128
#endif



//-----------------LCD�˿ڶ���---------------- 

#define LCD_SCLK_Clr() do{ HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);}while(0)  //SCL=SCLK
#define LCD_SCLK_Set() do{ HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);}while(0)

#define LCD_MOSI_Clr() do{ HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);}while(0)  //SDA=MOSI
#define LCD_MOSI_Set() do{ HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);}while(0)

#define LCD_RES_Clr()  do{ HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);}while(0)  //RES
#define LCD_RES_Set()  do{ HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);}while(0)

#define LCD_DC_Clr()   do{ HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);}while(0)  //DC
#define LCD_DC_Set()   do{ HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);}while(0)
 		     
#define LCD_CS_Clr()   do{ HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);}while(0)  //CS
#define LCD_CS_Set()   do{ HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);}while(0)

#define LCD_BLK_Clr()  do{ HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);}while(0)  //BLK
#define LCD_BLK_Set()  do{ HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);}while(0)


void LCD_GPIO_Init(void);//��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);//ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��
#endif




