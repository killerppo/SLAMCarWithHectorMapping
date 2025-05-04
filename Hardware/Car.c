#include "Motor.h"
#include "Encoder.h"

void Car_Init(void)
{
	Motor_Init();
	Encoder_Init();
}

void Car_SetSpeed(int16_t Speed)
{
	Motor1_SetSpeed(Speed);
	Motor2_SetSpeed(Speed);
}