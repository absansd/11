#ifndef __can_H
#define __can_H

#include "main.h"
#include "stdbool.h"

#define CAN1_CLK_ENABLE() 	__HAL_RCC_GPIOD_CLK_ENABLE()
#define CAN1_GPIO 			GPIOD
#define CAN1_RX_PIN 		GPIO_PIN_0
#define CAN1_TX_PIN 		GPIO_PIN_1

//#define CAN2_CLK_ENABLE() 	__HAL_RCC_GPIOB_CLK_ENABLE()
//#define CAN2_GPIO 		GPIOB
//#define CAN2_RX_PIN 	GPIO_PIN_12
//#define CAN2_TX_PIN 	GPIO_PIN_13

typedef struct {
	__IO CAN_RxHeaderTypeDef CAN_RxMsg;
	__IO uint8_t rxData[32];
	
	__IO CAN_TxHeaderTypeDef CAN_TxMsg;
	__IO uint8_t txData[32];

	__IO bool rxFrameFlag;
}CAN_t;

extern CAN_HandleTypeDef hcan1;
extern __IO CAN_t can;

void CAN1_Init(void);
void USER_CAN1_Filter_Init(void);
void CAN1_SendCmd(__IO uint8_t *cmd, uint8_t len);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif
