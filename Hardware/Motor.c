#include "stm32f10x.h"
#include "PWM.h"

void Motor_Init(void)
{
	PWM_Init();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void Motor1_SetSpeed(int16_t Speed)
{
    if(Speed > 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_3);
        GPIO_ResetBits(GPIOB, GPIO_Pin_4);
        PWM_SetCompare3(Speed);
    }
    else if(Speed < 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_4);
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);
        PWM_SetCompare3(-Speed);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4);
        PWM_SetCompare3(0);
    }
}

void Motor2_SetSpeed(int16_t Speed)
{
    if(Speed > 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_5);
        GPIO_ResetBits(GPIOB, GPIO_Pin_6);
        PWM_SetCompare4(Speed);
    }
    else if(Speed < 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_6);
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        PWM_SetCompare4(-Speed);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_5 | GPIO_Pin_6);
        PWM_SetCompare4(0);
    }
}