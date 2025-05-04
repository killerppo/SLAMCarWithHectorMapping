#include "stm32f10x.h"
#ifndef _ENCODER_H_
#define _ENCODER_H_

void Encoder_Init();
int16_t Encoder1_GetCount();
int16_t Encoder2_GetCount();

#endif