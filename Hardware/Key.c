#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "sys.h"
#include "Key.h"

uint8_t Control_20msFlag = 0;
#define A4  4
#define A5  5
#define A6  6
#define A7  7

#define KEY_SHORT_PRESS_ADC_LOW      200
#define KEY_LONG_PRESS_ADC_HIGH      (4095 - 500)
#define KEY_IDLE_ADC_MIN             (2048 - 900)
#define KEY_IDLE_ADC_MAX             (2048 + 900)
#define KEY_LONG_PRESS_TICKS         30

uint8_t Key_Num[8];
uint8_t Key_Chan[8];

//void Key_Init(void)
//{
uint8_t Key_GetCH(uint8_t ch)
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	uint16_t value = KEY_GetValue(ch);
	if(value <= KEY_SHORT_PRESS_ADC_LOW)
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		return 1;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	if(value >= KEY_LONG_PRESS_ADC_HIGH)
//	
		return 2;
//	//GPIO_Init(GPIOA, &GPIO_InitStructure);
	if((value >= KEY_IDLE_ADC_MIN) && (value <= KEY_IDLE_ADC_MAX))

		return 0;
//{
//	uint8_t Temp;
	return 0;
//	{
//		Temp = Key_Num;
//		Key_Num = 0;
//		return Temp;
const uint8_t* Key_GetState(void)
//}

	static const uint8_t key_channels[8] = {A4, A5, A6, A7, A4, A5, A6, A7};
	static const uint8_t key_levels[8] = {1, 1, 1, 1, 2, 2, 2, 2};

	for (uint8_t index = 0; index < 8; index++)
	{
		temp[index] = (Key_GetCH(key_channels[index]) == key_levels[index]) ? 1 : 0;
	}
//uint8_t Key_GetChan(void)
	{
		temp = 1;
	}
/* 20 ms 扫描一次，按下稳定后分发短按或长按事件。 */
	{
		temp = 2;
	}



uint8_t* Key_GetState(void)
		const uint8_t *key_state = Key_GetState();
		static uint16_t long_press_ticks[8];
		static uint8_t current_state[8];
		static uint8_t previous_state[8];

		for(uint8_t index = 0; index < 8; index++)
	static uint8_t temp[8] = {0};
			previous_state[index] = current_state[index];
			current_state[index] = key_state[index];			

			if(current_state[index] != 0 && previous_state[index] == 0)
	}
				long_press_ticks[index] = 0;
	{
		temp[0] = 0;
			if(key_state[index] != 0)
	
				long_press_ticks[index]++;
	{
			if(long_press_ticks[index] < KEY_LONG_PRESS_TICKS)
	else
				if (current_state[index] == 0 && previous_state[index] != 0)
		temp[1] = 0;
					Key_Num[index] = previous_state[index];
	
				Key_Chan[index] = 0;		
	{
		temp[2] = 1;
	}
				Key_Chan[index] = key_state[index];
	{
		temp[2] = 0;
	}
	
	if (Key_GetCH(A7) == 1)
	{
		temp[3] = 1;
	}
	else
	{
		temp[3] = 0;
	}
	
	if (Key_GetCH(A4) == 2)
	{
		temp[4] = 1;
	}
	else
	{
		temp[4] = 0;
	}	
	
	if (Key_GetCH(A5) == 2)
	{
		temp[5] = 1;
	}
	else
	{
		temp[5] = 0;
	}	
	
	if (Key_GetCH(A6) == 2)
	{
		temp[6] = 1;
	}
	else
	{
		temp[6] = 0;
	}	
	
	if (Key_GetCH(A7) == 2)
	{
		temp[7] = 1;
	}
	else
	{
		temp[7] = 0;
	}	

	return temp;
}

//1.5s内为短按，超过为长按
extern uint16_t task_20;
void Key_Tick(void)
{
	
	//static uint8_t Count;
	static uint16_t Count_la[8];
	static uint8_t CurrState[8];
	static uint8_t PrevState[8];
		
	//Count ++;
	if (Control_20msFlag == 1)
	{
		task_20++;
		Control_20msFlag = 0;
		for(uint8_t i = 0;i<8;i++)
		{
		PrevState[i] = CurrState[i];
		CurrState[i] = Key_GetState()[i];			
		
		if(CurrState[i] != 0 && PrevState[i] == 0)
		{
			Count_la[i] = 0;
		}
		
		if(Key_GetState()[i] != 0)
		{
			Count_la[i]++;
		}
		//Serial_Printf("%d,%d\r\n", Count_la[i], CurrState[i]);
		if(Count_la[i] < 30)
		{
			if (CurrState[i] == 0 && PrevState[i] != 0)
			{
				Key_Num[i] = PrevState[i];
			}	
			Key_Chan[i] = 0;		
		}
		else
		{
			Key_Chan[i] = Key_GetState()[i];
		}

	    }
	}	
}
