// Header:__MOVING_MOTOR_H__
// File Name: 电机驱动麦轮
// Author:Xiayuan（GTY）
// Date: 8.15.2023 v0.1 阳炎日快乐！添加了基础的函数原型（内容未编写）

/*-----------------------INCLUDING BEGIN--------------------*/
#include "main.h"
#include "RM3508.h"
#include "can_bsp.h"
#include "moving_motor.h"
#include "moving_ctrl.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

//#include "tim.h"
/*------------------------Define Begin---------------------*/

#define Motor_CAN hacn1 //定义电机控制端口
#define Motor_TIMER htim2 //定义循环定时器

/*定义电机id*/
#define M1 1
#define M2 2
#define M3 3
#define M4 4

/*定义电机任务id （标志位）*/
#define Motor_Task_0 0 //停止
#define Motor_Task_1 1 //左移
#define Motor_Task_2 2 //右移
#define Motor_Task_3 3 //前进
#define Motor_Task_4 4 //后退
#define Motor_Task_5 5 //左转
#define Motor_Task_6 6 //右转

/*定义各种速度*/
#define Forward_Speed 1000
#define Backward_Speed 1000

/*------------------------Define Over---------------------*/

/*------------------------Variables Begin---------------------*/
int8_t motor_task_id=1; 
/*------------------------Variables Over---------------------*/

void moving_stop(void)
{
	RM3508_Set_Speed(0,1); //电机停止
	RM3508_Set_Speed(0,2); 
	RM3508_Set_Speed(0,3); 
	RM3508_Set_Speed(0,4); 

}

void moving_left(void)
{

}

void moving_right(void)
{
	
}

void moving_forward(void)
{
	RM3508_Set_Speed(Forward_Speed,1); //前进
	RM3508_Set_Speed(Forward_Speed,2); //前进
	RM3508_Set_Speed(Forward_Speed,3); //前进
	RM3508_Set_Speed(Forward_Speed,4); //前进
}

void moving_backward(void)
{
	
}

void moving_turnleft(void)
{
	
}

void moving_turnright(void)
{
	
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim->Instance==Motor_TIMER.Instance)
//	{
//		RM3508_Set_Speed(Forward_Speed,M1);
//	}
//}

//void spcmove_pickup(void)
//{
//	
//}

//void spcmove_fire(void)
//{
//	
//}
