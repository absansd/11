#ifndef __MAIXCAM_H
#define __MAIXCAM_H

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "usart.h"
#include "led.h"

#define PAN_ENABLE        11	//����ƽ�Ƴ����µ���ɫʶ��
#define GROUND_ENABLE     12	//�������泡���µ���ɫʶ��
#define CIRCLE_ENABLE     13	//����Բ��ʶ��

#define PAN_DISABLE       01	//�ر�ƽ�Ƴ����µ���ɫʶ��
#define GROUND_DISABLE    02	//�رյ��泡���µ���ɫʶ��
#define CIRCLE_DISABLE    03	//�ر�Բ��ʶ��

#define Red      1
#define Grean    2
#define Blue     3


typedef struct
{
  char color;
  int  col_x;
  int  col_y;
} Cam_Data;

extern Cam_Data cam_data;

void Maixcam_Test(void);
void Maixcam_Mode(uint8_t mode);
void Maixcam_Data(void);
#endif

