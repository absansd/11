#include "include.h"




int main(void)
{
/*****************************�������*****************************/
//    int key;

/******************************��ʼ��******************************/
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    CAN1_Init();
    KEY_Init();
    LED_Init();
    LCD_Init();//LCD��ʼ��
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
    usart1_init(115200);
    usart2_init(115200);
    usart3_init(115200);
    uart4_init(9600);
    uart5_init(1000000);
    USER_CAN1_Filter_Init();	// ��ʼ��CAN�˲���
    if(HAL_CAN_Start(&hcan1) != HAL_OK) { Error_Handler(); }	// ����CAN������
    if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) { Error_Handler(); }	// ʹ��CAN�����������ж�

    /*�ȴ����̳�ʼ�����*/
//    Chassis_Initialize_response(); 
    /*�ȴ�������ʼ�����*/
//    setup();

/***************************** *Ԥ��******************************/
//    Chasssis_Test();			//���̲���
//    Steering_gear_Test();		//�������
//    QR_code_Get();			//ɨ�����
    LED1_TOGGLE();

/******************************��ѭ��******************************/
    while(1)
    {
		//�жϰ���1����
		if(KEY1_PRES)
		{
		//================����ɨ����================
			Chassis_Left(100,20,3200);
			Chassis_Forward(100,20,3200);
		//===============ʶ���ά��===============
			QR_code_Get();
		//==============ǰ����ԭ����==============
			Chassis_Forward(100,20,3200);
													//ʶ�����?????/???????????????????
			//��е�۶���,����λ��,��ʼץȡ
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
		//===============һ��ת����===============
			 Chassis_Forward(100,20,3200);
			 Chassis_Left(100,20,3200);
		//===============����ת����===============
			Chassis_Forward(100,20,3200);
			Chassis_Left(100,20,3200);
		//=============�ƶ����ּӹ���=============
			Chassis_Forward(100,20,3200);
			//ʶ��ɫ��λ��,��е�۶���,�������
													//����ͷʶ��!!!!!!δд
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//����ץȡ���
													//����ͷʶ��!!!!!!δд
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			
			//ԭ����ת90��
			Chassis_Left(100,20,3200);
			Chassis_Forward(100,20,3200);	//ǰ������ͼ����
			
			//����ԭ����ת90��,ǰ���ݴ���
			Chassis_Left(100,20,3200);
			Chassis_Forward(100,20,3200);
				//ʶ��ɫ��λ�÷������
													//����ͷʶ��!!!!!!δд
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//===============��ת��һ��ת�����ص�ԭ����======
				Chassis_Right(100,20,3200);	//ԭ����ת90��
			Chassis_Forward(100,20,3200);
			Chassis_Right(100,20,3200);
			//��е�۶���,����λ��,��ʼץȡ
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
				//ǰ����ԭ�������ά���֮������λ��ԭ����ת
			Chassis_Forward(100,20,3200);
			Chassis_Right(100,20,3200);
			//ֱ�����ּӹ�������
			Chassis_Forward(100,20,3200);
			//ʶ��ɫ��λ��,��е�۶���,�������
													//����ͷʶ��!!!!!!δд
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//����ץȡ���
													//����ͷʶ��!!!!!!δд
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//ԭ����ת90��
			Chassis_Right(100,20,3200);
			Chassis_Forward(100,20,3200);
			Chassis_Right(100,20,3200);
			//�ƶ����ݴ�������
			//ʶ��ɫ��λ�÷������
													//����ͷʶ��!!!!!!δд
		    RegWritePosEx(1, 3072, 2250, 100);
			RegWritePosEx(2, 2048, 1500, 80);
			RegWritePosEx(3, 1024, 1000, 50);
			RegWritePosEx(4, 1, 1000, 30);
			RegWriteAction();
			//===============ֱ����һ��ת�Ǵ�============
			Chassis_Forward(100,20,3200);
			//��תֱ������ͣ��
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
