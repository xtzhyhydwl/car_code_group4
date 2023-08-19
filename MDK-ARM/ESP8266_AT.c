// Header:__ESP8266_AT_H__
// File Name: ESP8266AT指令集模块
// Author:Xiayuan(GTY)
// Date:8.14.2023 *v0.1 添加一件初始化函数

/*
（编码格式：UTF-8）
简介：该模块集成了ESP8266的常用AT指令集，通过uart串口给ESP8266WIFI模块发送AT指令，实现单片机快速配置WIFI
注意：该模块函数基于keilv5.32和STM32CubeMXv6.9.1开发
*/

/*------------------------Including Begin---------------------*/
#include "main.h"//根据需要引用head
#include "usart.h"
#include "stdio.h"
#include "string.h"
//#include "stm32f4xx_hal_gpio.h"

/*------------------------Including Over---------------------*/

/*------------------------Define Begin---------------------*/
#define UART huart1 //定义指令发送端口
#define CRC_LED() HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8)
/*------------------------Define Over---------------------*/

/*------------------------Variables Begin---------------------*/
char Cmd_Buffer[64]={0};//指令缓存区

//指令集字符串初始化

//快速设置AP端，具体参数可改，从cmd2到cmd7执行下去即可配置好WiFi，别忘了reset！
char cmdtest[]="AT";
char cmd1[]="AT+RST";
char cmd2[]="AT+RESTORE";
char cmd3[]="AT+CWMODE_DEF=2";
char cmd4[]="AT+CIPAP_DEF=\"192.168.111.111\"";
char cmd5[]="AT+CWSAP_DEF=\"RobotGroup1\",\"12345678\",1,4";
char cmd6[]="AT+RFPOWER=82";
char cmd7[]="AT+SAVETRANSLINK=1,\"192.168.111.255\",8000,\"UDP\",8000";


/*------------------------Variables Over---------------------*/

/* 
* name:ESP8266_Send_Command
* function:通过UART发送预选好的AT指令
* parameter:无
* return:无
* attention:注意CRC校验灯宏定义IO口是否匹配
*/
void ESP8266_Send_Command(void)
{
	CRC_LED();
	HAL_UART_Transmit(&UART,(uint8_t*)Cmd_Buffer,sizeof(Cmd_Buffer),100);
	CRC_LED();
}

/* 
* name:ESP8266_Fast_Init（快速初始化）
* function:傻瓜式快速配置
* parameter:无
* return:无
* attention:注意如要改变参数，请在初始化字符串那边改
*/
void ESP8266_Fast_Init()
{
	strcpy(Cmd_Buffer,cmd2);
	ESP8266_Send_Command();
	HAL_Delay(20);
	strcpy(Cmd_Buffer,cmd3);
	ESP8266_Send_Command();
	HAL_Delay(20);
	strcpy(Cmd_Buffer,cmd4);
	ESP8266_Send_Command();
	HAL_Delay(20);
	strcpy(Cmd_Buffer,cmd5);
	ESP8266_Send_Command();
	HAL_Delay(20);
	strcpy(Cmd_Buffer,cmd6);
	ESP8266_Send_Command();
	HAL_Delay(20);
	strcpy(Cmd_Buffer,cmd7);
	ESP8266_Send_Command();
	HAL_Delay(20);
	strcpy(Cmd_Buffer,cmd1);
	ESP8266_Send_Command();
}

/* 
* name:ESP8266_Select_Command
* function:选择cmd_id,发送对应指令
* parameter:uint8_t cmd_id，指令id
* return:无
* attention:注意如要改变各项参数，请在初始化字符串那边改
*/

void ESP8266_Select_Command(uint8_t cmd_id)
{
	if(cmd_id>=1 && cmd_id<=9)
	{
		switch( cmd_id )
		{
			case 1:
			{
				strcpy(Cmd_Buffer,cmd1);
				ESP8266_Send_Command();
				break;
			}
			case 2:
			{
				strcpy(Cmd_Buffer,cmd2);
				ESP8266_Send_Command();
				break;
			}
			case 3:
			{
				strcpy(Cmd_Buffer,cmd3);
				ESP8266_Send_Command();
				break;
			}
			case 4:
			{
				strcpy(Cmd_Buffer,cmd4);
				ESP8266_Send_Command();
				break;
			}
			case 5:
			{
				strcpy(Cmd_Buffer,cmd5);
				ESP8266_Send_Command();
				break;
			}
			case 6:
			{
				strcpy(Cmd_Buffer,cmd6);
				ESP8266_Send_Command();
				break;
			}
			case 7:
			{
				strcpy(Cmd_Buffer,cmd7);
				ESP8266_Send_Command();
				break;
			}
		}
	}
}

