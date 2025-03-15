#include "include.h"




int main(void)
{
/*****************************定义变量*****************************/
//    int key;

/******************************初始化******************************/
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    CAN1_Init();
    KEY_Init();
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
//    Chassis_Initialize_response(); 
    /*等待舵机库初始化完毕*/
//    setup();

/***************************** *预设******************************/
//    Chasssis_Test();			//底盘测试
//    Steering_gear_Test();		//舵机测试
//    QR_code_Get();			//扫码测试
    LED1_TOGGLE();

/******************************主循环******************************/
    while(1)
    {
		//判断按键1按下
		if(KEY1_PRES)
		{
		//================出发扫码区================
			Chassis_Left(100,20,3200);
			Chassis_Forward(100,20,3200);
		//===============识别二维码===============
			QR_code_Get();
		//==============前进到原料区==============
			Chassis_Forward(100,20,3200);
													//识别物块?????/???????????????????
			//机械臂动作,调整位置,开始抓取
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
		//===============一号转角区===============
			 Chassis_Forward(100,20,3200);
			 Chassis_Left(100,20,3200);
		//===============二号转角区===============
			Chassis_Forward(100,20,3200);
			Chassis_Left(100,20,3200);
		//=============移动到粗加工区=============
			Chassis_Forward(100,20,3200);
			//识别色环位置,机械臂动作,放置物块
													//摄像头识别!!!!!!未写
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//重新抓取物块
													//摄像头识别!!!!!!未写
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			
			//原地左转90度
			Chassis_Left(100,20,3200);
			Chassis_Forward(100,20,3200);	//前进到地图中央
			
			//继续原地左转90度,前往暂存区
			Chassis_Left(100,20,3200);
			Chassis_Forward(100,20,3200);
				//识别色环位置放置物块
													//摄像头识别!!!!!!未写
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//===============右转经一号转角区回到原料区======
				Chassis_Right(100,20,3200);	//原地右转90度
			Chassis_Forward(100,20,3200);
			Chassis_Right(100,20,3200);
			//机械臂动作,调整位置,开始抓取
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
				//前进至原料区与二维码板之间中心位置原地右转
			Chassis_Forward(100,20,3200);
			Chassis_Right(100,20,3200);
			//直行至粗加工区放置
			Chassis_Forward(100,20,3200);
			//识别色环位置,机械臂动作,放置物块
													//摄像头识别!!!!!!未写
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//重新抓取物块
													//摄像头识别!!!!!!未写
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//原地右转90度
			Chassis_Right(100,20,3200);
			Chassis_Forward(100,20,3200);
			Chassis_Right(100,20,3200);
			//移动到暂存区放置
			//识别色环位置放置物块
													//摄像头识别!!!!!!未写
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//===============直行至一号转角处============
			Chassis_Forward(100,20,3200);
			//右转直行至启停区
			Chassis_Right(100,20,3200);
			Chassis_Forward(100,20,3200);
			break;
		}
		break;

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
