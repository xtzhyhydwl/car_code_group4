#ifndef __MOVING_MOTOR_H__
#define __MOVING_MOTOR_H__

#include "main.h"

void moving_stop(void);
void moving_left(void);
void moving_right(void);
void moving_forward(void);
void moving_backward(void);
void moving_turnleft(void);
void moving_turnright(void);
//void spcmove_pickup(void);
//void spcmove_fire(void);

extern int8_t motor_task_id; 


#endif
