/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "moving_ctrl.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define WIFI_UART huart2 //定义通信端口（ESP8266端口�?
#define WIFI_BUFFERSIZE 32

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint8_t press_flag; 
extern uint8_t ctrl_flag; 
extern void excute_special_order(void);
extern void stop_normal_order(void);
extern void excute_normal_order(void);

//uint8_t write_pos = 0;
//uint8_t read_pos = 0;
//uint8_t data_len = 0;
//uint8_t Rx_Data[16] = {0};
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim2;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles RCC global interrupt.
  */
void RCC_IRQHandler(void)
{
  /* USER CODE BEGIN RCC_IRQn 0 */

  /* USER CODE END RCC_IRQn 0 */
  /* USER CODE BEGIN RCC_IRQn 1 */

  /* USER CODE END RCC_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */
//	uint8_t temp_flag=__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE);
//	if(temp_flag!=RESET)
//	{
//		uint8_t i=0 ;
//		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
//		HAL_UART_DMAStop(&huart2);
//		
//		write_pos = WIFI_BUFFERSIZE-__HAL_DMA_GET_COUNTER(&hdma_usart2_rx);
//		
//		
//		if(write_pos >= read_pos)//情况1，没有溢凿
//		{
//			data_len = write_pos - read_pos;
//			for(i=0 ; i<data_len ; i++)//顺序获取数据存放在Rx_Data丿
//			{
//				Rx_Data[i]=Rx_Buffer[read_pos+i];
//			}
//			read_pos = write_pos;
////				if(read_pos>WIFI_BUFFERSIZE)
////				{
////					read_pos-=WIFI_BUFFERSIZE;
////				}
//		}
//		
//		else if(write_pos < read_pos)//情况2，溢凿
//		{
//			uint8_t data1_len=0;
//			uint8_t data2_len=0;
//			data1_len =WIFI_BUFFERSIZE - read_pos;
//			for(i=0;i<data1_len;i++) //获取第一殿
//			{
//				Rx_Data[i]=Rx_Buffer[read_pos+i];	
//			}
//			for(;i<data1_len+data2_len;i++) //获取第二殿
//			{
//				Rx_Data[i]=Rx_Buffer[i-data1_len];	
//			}
//			read_pos = write_pos;
//		}
//			
//		
//		if(Rx_Data[0]=='_')
//		{
//			if(press_flag==0 && Rx_Data[1]!='c' && ctrl_flag==0) //非按键状态，进判斿
//			{
//				excute_normal_order();
//			}
//			else if(ctrl_flag==1 && Rx_Data[2]=='i' && Rx_Data[6]=='d') //在ctrl位，按下两个特殊操作，进判断
//			{
//				excute_special_order();
//			}

//			else if(ctrl_flag==0 && Rx_Buffer[1]=='c') //不在ctrl位，按下ctrl，置ctrl使
//			{
//				ctrl_flag=1;
//				excute_special_order();
//			}
//			else if((press_flag==1 || ctrl_flag==1) && Rx_Data[6]=='u')//棿测到按键抬起，判断，停止普鿚指令并清除按下标志或清除ctrl标志
//			{
//				if(Rx_Data[1]=='c')//抬起的是ctrl
//				{
//					ctrl_flag=0; //清除ctrl标志
//				}
//				else if(Rx_Data[2]!='i')
//				{
//					stop_normal_order(); //停止、清陿
//			}			
//		}
//	}

//}
//	HAL_UART_Receive_DMA(&huart2,Rx_Buffer,WIFI_BUFFERSIZE);

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream6 global interrupt.
  */
void DMA1_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream6_IRQn 0 */

  /* USER CODE END DMA1_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
  /* USER CODE BEGIN DMA1_Stream6_IRQn 1 */

  /* USER CODE END DMA1_Stream6_IRQn 1 */
}

/**
  * @brief This function handles CAN1 RX1 interrupt.
  */
void CAN1_RX1_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX1_IRQn 0 */

  /* USER CODE END CAN1_RX1_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_RX1_IRQn 1 */

  /* USER CODE END CAN1_RX1_IRQn 1 */
}

/**
  * @brief This function handles CAN1 SCE interrupt.
  */
void CAN1_SCE_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_SCE_IRQn 0 */

  /* USER CODE END CAN1_SCE_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_SCE_IRQn 1 */

  /* USER CODE END CAN1_SCE_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
//	uint16_t temp=0;
		uint8_t temp_flag=__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE);
	if(temp_flag!=RESET)
	{
		uint8_t i=0 ;
		__HAL_UART_CLEAR_IDLEFLAG(&huart2);
		HAL_UART_DMAStop(&huart2);
		
//		write_pos = WIFI_BUFFERSIZE-__HAL_DMA_GET_COUNTER(&hdma_usart2_rx);
		
		
//		if(write_pos >= read_pos)//情况1，没有溢凿
//		{
//			data_len = write_pos - read_pos;
//			for(i=0 ; i<data_len ; i++)//顺序获取数据存放在Rx_Data丿
//			{
//				Rx_Data[i]=Rx_Buffer[read_pos+i];
//			}
//			read_pos = write_pos;
////				if(read_pos>WIFI_BUFFERSIZE)
////				{
////					read_pos-=WIFI_BUFFERSIZE;
////				}
//		}
//		
//		else if(write_pos < read_pos)//情况2，溢凿
//		{
//			uint8_t data1_len=0;
//			uint8_t data2_len=0;
//			data1_len =WIFI_BUFFERSIZE - read_pos;
//			for(i=0;i<data1_len;i++) //获取第一殿
//			{
//				Rx_Data[i]=Rx_Buffer[read_pos+i];	
//			}
//			for(;i<data1_len+data2_len;i++) //获取第二殿
//			{
//				Rx_Data[i]=Rx_Buffer[i-data1_len];	
//			}
//			read_pos = write_pos;
//		}
			
		
		if(Rx_Buffer[0]=='_')
		{
			if(press_flag==0 && Rx_Buffer[1]!='c' && ctrl_flag==0) //非按键状态，进判斿
			{
				excute_normal_order();
			}
			else if(ctrl_flag==1 && Rx_Buffer[2]=='i' && Rx_Buffer[6]=='d') //在ctrl位，按下两个特殊操作，进判断
			{
				excute_special_order();
			}

			else if(ctrl_flag==0 && Rx_Buffer[1]=='c') //不在ctrl位，按下ctrl，置ctrl使
			{
				ctrl_flag=1;
				excute_special_order();
			}
			else if((press_flag==1 || ctrl_flag==1) && Rx_Buffer[6]=='u')//棿测到按键抬起，判断，停止普鿚指令并清除按下标志或清除ctrl标志
			{
				if(Rx_Buffer[1]=='c')//抬起的是ctrl
				{
					ctrl_flag=0; //清除ctrl标志
				}
				else if(Rx_Buffer[2]!='i')
				{
					stop_normal_order(); //停止、清陿
			}			
		}
	}

}
	HAL_UART_Receive_DMA(&huart2,Rx_Buffer,WIFI_BUFFERSIZE);

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles CAN2 RX1 interrupt.
  */
void CAN2_RX1_IRQHandler(void)
{
  /* USER CODE BEGIN CAN2_RX1_IRQn 0 */

  /* USER CODE END CAN2_RX1_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan2);
  /* USER CODE BEGIN CAN2_RX1_IRQn 1 */

  /* USER CODE END CAN2_RX1_IRQn 1 */
}

/**
  * @brief This function handles CAN2 SCE interrupt.
  */
void CAN2_SCE_IRQHandler(void)
{
  /* USER CODE BEGIN CAN2_SCE_IRQn 0 */

  /* USER CODE END CAN2_SCE_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan2);
  /* USER CODE BEGIN CAN2_SCE_IRQn 1 */

  /* USER CODE END CAN2_SCE_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
