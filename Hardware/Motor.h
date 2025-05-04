#include "stm32f10x.h"
#ifndef _MOTOR_H_
#define _MOTOR_H_

void Motor_Init(void);
void Motor1_SetSpeed(int16_t Speed);
void Motor2_SetSpeed(int16_t Speed);

#endif
