// Header:__VISION_H__
// File Name: 视觉数据处理
// Author:Xiayuan（GTY）
// Date: 8.16.2023 v0.1 添加了基础的串口收发功能，进行数据通讯测试

/*-----------------------INCLUDING BEGIN--------------------*/
#include "main.h"//根据需要引用head
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "can_bsp.h"
#include "RM3508.h"
#include "moving_motor.h"
#include "vision.h"

/*------------------------Define Begin---------------------*/

#define v_UART huart2 //数据接收口
#define CRC_LED() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8) //校验灯，如有需要可更改

/*------------------------Define Over---------------------*/

/*------------------------Variables Begin---------------------*/

uint8_t Rx_Data[10]={0};

/*------------------------Variables Over---------------------*/

void vision_get_data()
{
	CRC_LED();
	HAL_UART_Receive_IT(&v_UART,Rx_Data,10);
	CRC_LED();
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if(huart->Instance==v_UART.Instance)
//	{
//		CRC_LED();

//		HAL_UART_Transmit(&v_UART,Rx_Data,10,100);
//		
//		CRC_LED();

//	}
//}
