#include "stm32f10x.h"                  // Device header
#include "Key.h"

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}


//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//	{
//		Key_Tick();
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//	}
//}
 
extern uint16_t i;
uint16_t flag10ms_cnt;
uint8_t flag20ms_cnt;
extern uint8_t Control_10msFlag;
extern uint8_t Control_20msFlag;
void TIM2_IRQHandler(void)
{
	//static uint8_t count;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		
		if(flag20ms_cnt < 10)
		{
			flag20ms_cnt++;
	
			if(flag20ms_cnt>=10)
			{
				i++;
				flag20ms_cnt=0;
			}
		}
		
		
		if(Control_10msFlag != 1)
		{
			flag10ms_cnt++;
	
			if(flag10ms_cnt>=10)
			{
				Control_10msFlag=1;
				flag10ms_cnt=0;
			}
		}

		
		Key_Tick();

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

