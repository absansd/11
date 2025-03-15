#include "include.h"




int main(void)
{
/*****************************定义变量*****************************/
    int key;

/******************************初始化******************************/
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    CAN1_Init();
    KEY_Init();
    beep_init();
    LED_Init();
    LCD_Init();//LCD初始化
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    usart1_init(115200);
    usart2_init(115200);
    usart3_init(115200);
    uart4_init(9600);
    uart5_init(1000000);
    USER_CAN1_Filter_Init();	// 初始化CAN滤波器
    if(HAL_CAN_Start(&hcan1) != HAL_OK) { Error_Handler(); }	// 启动CAN控制器
    if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) { Error_Handler(); }	// 使能CAN控制器接收中断

    /*等待底盘初始化完毕*/
    /*等待舵机库初始化完毕*/
    setup();

/***************************** *预设******************************/
//    Chasssis_Test();			//底盘测试
//    HAL_Delay(200);
//    Steering_gear_Test();		//舵机测试
//    HAL_Delay(200);
//    QR_code_Get();			//扫码测试
//    HAL_Delay(200);
    LED1_TOGGLE();
    LED2_TOGGLE();
    LED3_TOGGLE();
/******************************主循环******************************/
    while(1)
    {
        key=key_scan(0);
        if(key==1) BEEP_TOGGLE();
        else if(key==2)     Chasssis_Test();			//底盘测试
        else if(key==3)     Steering_gear_Test();		//舵机测试
        else if(key==4)     QR_code_Get();			//扫码测试
        else if(key==5)     LED1_TOGGLE();
        else if(key==6)     LED2_TOGGLE();
        else if(key==7)     LED3_TOGGLE();
    }
}




/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

/*Configure the main internal regulator output voltage*/
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
/*Initializes the CPU, AHB and APB busses clocks*/
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
/*Initializes the CPU, AHB and APB busses clocks*/
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	while(1);

}
