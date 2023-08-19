// Header:__MOVING_CTRL_H__
// File Name: 基于ESP8266和U-Switch的数据接收处理->控制小车模块
// Author:Xiayuan（GTY）
// Date:8.15.2023 v0.1 *阳炎日快乐！
// Date:8.15.2023 v0.2 *360都摇杆暂时用不到了，相关代码已注释
//										 * ESP8266初始化测试失败，相关代码暂时注释



/*
（编码格式：UTF-8）
简介：该模块基于U-Switch生成摇杆和按钮数据->通过ESP8266发给单片机，处理数据并给电机等外设发送指令，从而实现遥控功能
注意：该模块函数基于keilv5.32和STM32CubeMXv6.9.1开发，请配合RM3508/AM3508库、can_bsp库、moving_motor库使用！
*/

/*------------------------Including Begin---------------------*/
#include "main.h"//根据需要引用head
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "can_bsp.h"
#include "can.h"
#include "RM3508.h"
#include "moving_motor.h"
#include "moving_ctrl.h"
#include "special_motor.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal_uart.h"


//#include "tim.h"

//#include "stm32f4xx_hal_gpio.h"

/*------------------------Including Over---------------------*/

/*------------------------Define Begin---------------------*/

#define WIFI_UART huart2 //定义通信端口（ESP8266端口）
#define Motor_CAN hacn1 //定义电机控制端口
#define Motor_TIMER htim2 //定义循环定时器
#define WIFI_BUFFERSIZE 32

#define CRC_LED() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8) //校验灯，如有需要可更改

//#define multiple_num 100 //摇杆转换电机数值倍率

#define DELAY osDelay(10) //接收后延时，根据具体情况更改为osdelay等不同delay函数

/*------------------------Define Over---------------------*/

/*------------------------Variables Begin---------------------*/

/*初始化需要用到的比较和缓冲字符串*/
//uint8_t test_str[]="AT+RST\n";
//uint8_t joystick[]="_ctrl"; //摇杆
//uint8_t symbol=';'; //数据分分隔符
uint8_t Rx_Buffer[32]={0};
//uint8_t Rx_Len=0;
//uint8_t* CRC_pointer;

/*按钮字校验符串初始化*/
uint8_t fire_down[]="_fire_down"; //放环
uint8_t fire_up[]="_fire_up";

uint8_t left_down[]="_left_down"; //左
uint8_t left_up[]="_left_up";

uint8_t rght_down[]="_rght_down"; //右
uint8_t rght_up[]="_rght_up";

uint8_t frwd[]="_frwd";
uint8_t frwd_down[]="_frwd_down"; //前
uint8_t frwd_up[]="_frwd_up";


uint8_t bkwd_down[]="_bkwd_down"; //后
uint8_t bkwd_up[]="_bkwd_up";

uint8_t trnl_down[]="_trnl_down"; //左转trnl
uint8_t trnl_up[]="_trnl_up";

uint8_t trnr[]="_trnr";
uint8_t trnr_down[]="_trnr_down"; //右转trnr
uint8_t trnr_up[]="_trnr_up";

uint8_t pick_down[]="_pick_down"; //取环pick
uint8_t pick_up[]="_pick_up";

uint8_t ctrl_down[]="_ctrl_down"; //操作键ctrl
uint8_t ctrl_up[]="_ctrl_up";

/*初始化各种标志位*/
uint8_t count_i=1;//各种计数用的
uint8_t press_flag=0; //按键是否处于按下标志位
uint8_t ctrl_flag=0; //操作键开启标志位
//uint8_t digit=0;
//uint8_t signal_flag=1;//正负号标志,1代表正号，0代表符号

/*字符串转整形数据处理部分*/
//uint8_t minus_signal='-';
//uint8_t x_buff[3]={0};
//uint8_t y_buff[3]={0};
//int x_data=0;
//int y_data=0;


/*------------------------Variables Over---------------------*/

/*FIFO0的回调函数*/
 void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == hcan1.Instance)
	{
		CAN_RxHeaderTypeDef RxMessage;
		uint8_t RxData[8] = {0};

		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, RxData);
		if(RxMessage.StdId>=0x201 && RxMessage.StdId<=0x208)
		{
			RM3508_Get_Feedback(RxMessage.StdId,RxData);
		}
	/*自己写解析函数*/
	}
 }


/* 
* name:移动控制初始化校验函数
* function:协助初始化（已失效）
* parameter:无
* return:无
* attetion:不知道写出来管什么用
*/
//void move_ctrl_init_CRC()
//{
//	HAL_UART_Receive_IT(&UART,Rx_Buffer,32);
//	HAL_UART_Transmit(&UART,test_str,sizeof(test_str),100);

//	if(Rx_Buffer[0]=='O' && Rx_Buffer[1]=='K')
//	{
//		CRC_LED();
//		HAL_UART_Receive_IT(&UART,Rx_Buffer,32);
//		CRC_LED();
//	}
//	else
//	{
//		if(count_i<=5)
//		{
//			count_i++;
//			move_ctrl_init_CRC();
//		}
//	}
//}

/* 
* name:移动控制初始化
* function:开启接收中断，尝试resetESP8266（已失效）
* parameter:无
* return:无
* attetion:别用，没用
*/
void move_ctrl_init()
{
//	count_i=1;
	HAL_UART_Receive_DMA(&huart2,Rx_Buffer,WIFI_BUFFERSIZE);
//	HAL_UART_Transmit(&UART,test_str,sizeof(test_str),100);
//	move_ctrl_init_CRC();
//	count_i=1;
}

/* 
* name:移动控制数据接收
* function:专门接收ESP8266的数据，装在Rx_Buffer里
* parameter:无
* return:无
* attetion:可以用，但没必要
*/
void move_ctrl_DataReceive()
{
	HAL_UART_Receive_DMA(&WIFI_UART,Rx_Buffer,WIFI_BUFFERSIZE);
//	DELAY;
}

/* 
* name:360度摇杆数据处理
* function:处理接收到的joystick数据（0~99），变成可以使用的整形数据（暂时用不到）
* parameter:无
* return:无
* attetion:如果要使用记得补上已经被删除的int x_data、int y_data等变量
*/
//void move_ctrl_Data_Transform()
//{
//	CRC_pointer=&Rx_Buffer[0];//CRC指针和Buffer对齐
//	/*--x轴坐标转换--*/
//	signal_flag=1;
//	digit=0;
//	CRC_pointer=&Rx_Buffer[5];
//	if(*CRC_pointer=='-') 
//	{
//		signal_flag=0;
//		CRC_pointer++;
//	}//置符号位
//	if(*CRC_pointer>='0' && *CRC_pointer<='9') 
//	{
//		digit=1;
//		if(*(CRC_pointer+1)>='0' && *(CRC_pointer+1)<='9') 
//		{
//			digit=2;
//			if(*(CRC_pointer+2)>='0' && *(CRC_pointer+2)<='9') 
//			{
//				digit=3;
//			}
//		}
//	} //ascii码中'0'=48
//	switch(digit)
//	{
//		case 1:
//		{
//			x_data=((*CRC_pointer)-48);
//			break;
//		}
//		case 2:
//		{
//			x_data=(((*CRC_pointer)-48)*10)+((*(CRC_pointer+1))-48);
//			break;
//		}
//		case 3:
//		{
//			x_data=(((*CRC_pointer)-48)*100)+(((*(CRC_pointer+1))-48)*10)+((*(CRC_pointer+2))-48);
//			break;
//		}
//	}//按照位数字符串转整形数据
//	if(!signal_flag)
//	{
//		x_data=-x_data;
//	}//符号判断
//	
//	/*--y轴坐标转换再来一遍--*/
//	
//	signal_flag=1;
//	CRC_pointer+=digit;
//	CRC_pointer++;//移动到y轴数据起始位
//	digit=0;

//	if(*CRC_pointer=='-') 
//	{
//		signal_flag=0;
//		CRC_pointer++;
//	}//置符号位
//	if(*CRC_pointer>='0' && *CRC_pointer<='9') 
//	{
//		digit=1;
//		if(*(CRC_pointer+1)>='0' && *(CRC_pointer+1)<='9') 
//		{
//			digit=2;
//			if(*(CRC_pointer+2)>='0' && *(CRC_pointer+2)<='9') 
//			{
//				digit=3;
//			}
//		}
//	} //ascii码中'0'=48
//	switch(digit)
//	{
//		case 1:
//		{
//			y_data=((*CRC_pointer)-48);
//			break;
//		}
//		case 2:
//		{
//			y_data=(((*CRC_pointer)-48)*10)+((*(CRC_pointer+1))-48);
//			break;
//		}
//		case 3:
//		{
//			y_data=(((*CRC_pointer)-48)*100)+(((*(CRC_pointer+1))-48)*10)+((*(CRC_pointer+2))-48);
//			break;
//		}
//	}//按照位数字符串转整形数据
//	if(!signal_flag)
//	{
//		y_data=-y_data;
//	}//符号判断
////转换结束，得到整形数据x_data和y_data
//}


/* 
* name:执行普通指令
* function:执行左平移、右平移、前进后退，原地左右转，实现方式是判断指令内容，调用moving_motor中相应控制函数
* parameter:无
* return:无
* attetion:一定要搭配moving_motor库使用！
*/
void excute_normal_order() //判断、执行除了投环/取环操作外的其他操作
{
	press_flag=1;
	
	switch(Rx_Buffer[1])//关键字判断
	{
		case 'l':
		{
			motor_task_id=1;
			break;
		}
		case 'r':
		{
			motor_task_id=2;
			break;
		}
		case 'f':
		{
			motor_task_id=3;
			break;
		}
		case 'b':
			motor_task_id=4;
		{
			break;
		}
		case 't'://转向需要两个关键字才能判断
		{
			if(Rx_Buffer[4]=='l')
			{
				motor_task_id=5;
			}
			else if(Rx_Buffer[4]=='r')
			{
				motor_task_id=6;
			}
			break;
		}
	}
}

/* 
* name:执行特殊指令
* function:执行投环和取环，实现方式是判断指令内容，调用special_motor中相应控制函数
* parameter:无
* return:无
* attetion:一定要搭配special_motor库使用！
*/

void excute_special_order()//执行投环/取环操作
{
	if(Rx_Buffer[1]=='f')
	{
		spcmove_fire();
	}
	else if(Rx_Buffer[1]=='p')
	{
		spcmove_pickup();
	}
}

/* 
* name:停止普通指令
* function:按键抬起的时候停止执行普通指令，实现方式是关闭定时器，停止循环发送指令
* parameter:无
* return:无
* attetion:无
*/
void stop_normal_order()//停止普通操作
{
//	HAL_TIM_Base_Stop_IT(&Motor_TIMER);
	motor_task_id=0;
	press_flag=0;
}

/* 
* name:huart接收中断回调
* function:huart2->指令初级判断;
* parameter:不知道这是啥？
* return:看情况
* attetion:目前只能有一个huart接收中断回调函数！小心重定义！
*/
/*接收中断回调函数的内容可以自己写*/
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	/*---huart2的内容开始---*/
//	if(huart->Instance==UART.Instance)
//	{
//		if(Rx_Buffer[0]=='_')
//		{
//			USART2->DR=0;
//			if(press_flag==0 && Rx_Buffer[1]!='c' && ctrl_flag==0) //非按键状态，进判断
//			{
//				excute_normal_order();
//			}
//			else if(ctrl_flag==1 && Rx_Buffer[2]=='i' && Rx_Buffer[6]=='d') //在ctrl位，按下两个特殊操作，进判断
//			{
//				excute_special_order();
//			}

//			else if(ctrl_flag==0 && Rx_Buffer[1]=='c') //不在ctrl位，按下ctrl，置ctrl位
//			{
//				ctrl_flag=1;
////				excute_special_order();
//			}
//			else if((press_flag==1 || ctrl_flag==1) && Rx_Buffer[6]=='u')//检测到按键抬起，判断，停止普通指令并清除按下标志或清除ctrl标志
//			{
//				if(Rx_Buffer[1]=='c')//抬起的是ctrl
//				{
//					ctrl_flag=0; //清除ctrl标志
//				}
//				else if(Rx_Buffer[2]!='i')
//				{
//					stop_normal_order(); //停止、清除
//				}			
//			}
//		}
//	}
////	HAL_UART_Receive_IT(&huart2,Rx_Buffer,8);//再启动接收中断，以防万一
//	/*---huart2的内容结束---*/

//}

