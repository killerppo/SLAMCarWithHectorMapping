#include "stm32f10x.h"   // Device header
 
void Timer_Init(void)
{
     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
     
    TIM_InternalClockConfig(TIM4);//选择内部时钟，不写也是默认使用内部时钟
     
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//滤波器一分频，貌似没什么用
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数方式，向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 2500 - 1;//周期，自动重装器ARR的值，两个参数都在0~65535之间
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;//PSC预分频器的值 CK_CNT_OV = CK_PSC/(PSC+1)/(ARR+1)
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//重复计数器，高级计数器才有
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);//时基单元配置
     
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);//手动清除中断标志位
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//使能更新中断
     
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
     
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);
     
    TIM_Cmd(TIM4, ENABLE);
     
}