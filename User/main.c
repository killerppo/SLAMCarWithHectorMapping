#include "stm32f10x.h"   // Device header
#include "OLED.h"
#include "Encoder.h"
#include "PWM.h"
#include "Car.h"
#include "Timer.h"
#include "Motor.h"
#include "Serial.h"

uint8_t RxNum,Op;

int16_t E = 0, countE = 0, lastE = 0, last2E, Speed = 0,Target,Target2;
int16_t E2 = 0, countE2 = 0, lastE2 = 0, last2E2, Speed2 = 0;
 
int16_t PWM = 0, Delta = 0;
int16_t PWM2 = 0, Delta2 = 0;
 
float P = 0.1, I = 0.2, D = 0.02;
 
 
int main(void){

    OLED_Init();
	Timer_Init();
    Car_Init();
	Serial_Init();

	Serial_SendByte(0x41);
	Target = 0;
	Target2 = 0;
 
     
    OLED_ShowString(2, 1, "Speed1:");
    OLED_ShowString(3, 1, "Speed2:");
    OLED_ShowString(4, 1, "Target:");

     
    while(1)
    {
        OLED_ShowSignedNum(2, 8, Speed, 5);
        OLED_ShowSignedNum(3, 8, Speed2, 5);
        OLED_ShowSignedNum(4, 8, Target, 4);
		if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
		{
			Op = USART_ReceiveData(USART3);
			Serial_SendByte(Op);
			OLED_ShowNum(1, 1, Op, 3);
			if (Op == 'w'){
				Target = 500;
				Target2 = 500;
			}
			if (Op == 'd'){
				Target = 0;
				Target2 = 300;
			}
			if (Op == 'a'){
				Target = 300;
				Target2 = 0;
			}
			if (Op == 's'){
				Target = 0;
				Target2 = 0;
			}
		}


         
    }
}
 
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
        Speed = Encoder2_GetCount() * 60 / 100;//0.25s测速间隔，编码器一圈输出100个脉冲
         
        E = Target - Speed;
        countE += E;
        Delta = P * (E - lastE) + I * E + D * (E + last2E - 2 * lastE);
        PWM += Delta;
         
        if(PWM > 1000)//限制转速
            PWM = 1000;
 
        Motor1_SetSpeed(PWM);//电机接收低电平转动
        last2E = lastE;
        lastE = E;

        Speed2 = Encoder1_GetCount() * 60 / 100; //为什么speed和encoder是反过来的呢，因为接错了
        E2 = Target2 - Speed2;
        countE2 += E2;
        Delta2 = P * (E2 - lastE2) + I * E2 + D * (E2 + last2E2 - 2 * lastE2);
        PWM2 += Delta2;
        if(PWM2 > 1000)//限制转速
            PWM2 = 1000;
        
        Motor2_SetSpeed(PWM2);
        last2E2 = lastE2;
        lastE2 = E2;
         
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}
