#include "main.h"


#ifndef __MOVING_CTRL_H__
#define __MOVING_CTRL_H__


#define WIFI_UART huart2 //定义通信端口（ESP8266端口）
#define Motor_CAN hacn1 //定义电机控制端口
#define Motor_TIMER htim2 //定义循环定时器
#define BUFFERSIZE 32


extern uint8_t Rx_Buffer[32];
extern uint8_t Rx_Len;
extern uint8_t press_flag; 
extern uint8_t ctrl_flag; 


void move_ctrl_init(void);
void move_ctrl_DataReceive(void);
void excute_special_order(void);
void stop_normal_order(void);
void excute_normal_order(void);


#endif

