/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "moving_ctrl.h"
#include "moving_motor.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for flag_master */
osThreadId_t flag_masterHandle;
const osThreadAttr_t flag_master_attributes = {
  .name = "flag_master",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for moving_ctrl_det */
osThreadId_t moving_ctrl_detHandle;
const osThreadAttr_t moving_ctrl_det_attributes = {
  .name = "moving_ctrl_det",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Start_flag_master(void *argument);
void Start_moving_ctrl_detect(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
//	vTaskSuspend(moving_ctrl_detHandle);

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of flag_master */
  flag_masterHandle = osThreadNew(Start_flag_master, NULL, &flag_master_attributes);

  /* creation of moving_ctrl_det */
  moving_ctrl_detHandle = osThreadNew(Start_moving_ctrl_detect, NULL, &moving_ctrl_det_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Start_flag_master */
/**
  * @brief  Function implementing the flag_master thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Start_flag_master */
void Start_flag_master(void *argument)
{
  /* USER CODE BEGIN Start_flag_master */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END Start_flag_master */
}

/* USER CODE BEGIN Header_Start_moving_ctrl_detect */
/**
* @brief Function implementing the moving_ctrl_det thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_moving_ctrl_detect */
void Start_moving_ctrl_detect(void *argument)
{
  /* USER CODE BEGIN Start_moving_ctrl_detect */
  /* Infinite loop */
  for(;;)
  {	
		move_ctrl_DataReceive();//�?启接�?
		osDelay(10);
		/*判断任务id*/
		if(motor_task_id!=0)
		{
			switch(motor_task_id)
			{
				case 3:
				{
					moving_forward();//�?
				}
			}
		}
		else if(motor_task_id==0)
		{
			moving_stop();
		}
    osDelay(1);
  }
  /* USER CODE END Start_moving_ctrl_detect */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

