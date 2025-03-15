#ifndef __MAIXCAM_H
#define __MAIXCAM_H

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "usart.h"
#include "led.h"

#define PAN_ENABLE        11	//开启平移场景下的颜色识别
#define GROUND_ENABLE     12	//开启地面场景下的颜色识别
#define CIRCLE_ENABLE     13	//开启圆环识别

#define PAN_DISABLE       01	//关闭平移场景下的颜色识别
#define GROUND_DISABLE    02	//关闭地面场景下的颜色识别
#define CIRCLE_DISABLE    03	//关闭圆环识别

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

