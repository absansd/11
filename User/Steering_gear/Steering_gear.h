#ifndef __STEERING_GEAR_H
#define __STEERING_GEAR_H

#include "usart.h"
#include "SCS.h"
#include "SMS_STS.h"
#include "SCSerail.h"



void Steering_gear_Test(void);
void PosEx_Delay(int16_t P1, int16_t P2, uint16_t Speed, uint8_t ACC);



#endif
