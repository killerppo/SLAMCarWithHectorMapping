#include "stm32f10x.h"
#ifndef __PWM_H__
#define __PWM_H__

void PWM_Init(void);
void PWM_SetCompare3(uint16_t Compare3);
void PWM_SetCompare4(uint16_t Compare4);

#endif
