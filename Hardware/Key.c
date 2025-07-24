#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "sys.h"

uint8_t Control_20msFlag = 0;
#define A4  4
#define A5  5
#define A6  6
#define A7  7
//uint8_t Key_Num;
//uint8_t Key_Chan;

uint8_t Key_Num[8];
uint8_t Key_Chan[8];

//void Key_Init(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
//	//GPIO_Init(GPIOA, &GPIO_InitStructure);
//}

//uint8_t Key_GetNum(void)
//{
//	uint8_t Temp;
//	if (Key_Num)
//	{
//		Temp = Key_Num;
//		Key_Num = 0;
//		return Temp;
//	}
//	return 0;
//}

//uint8_t Key_GetChan(void)
//{
//	return Key_Chan;
//}

//uint8_t Key_GetState(void)
//{
//	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == 0)
//	{
//		return 1;
//	}
//	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
//	{
//		return 2;
//	}
//	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
//	{
//		return 3;
//	}
//	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0)
//	{
//		return 4;
//	}
//	return 0;
//}

////1.5s内为短按，超过为长按

//void Key_Tick(void)
//{
//	static uint8_t Count;
//	static uint16_t Count_la;
//	static uint8_t CurrState, PrevState;
//	
//	Count ++;
//	if (Count >= 20)
//	{
//		Count = 0;
//		PrevState = CurrState;
//		CurrState = Key_GetState();
//		
//		if(CurrState != 0 && PrevState == 0)
//		{
//			Count_la = 0;
//		}
//		
//		if(Key_GetState() != 0)
//		{
//			Count_la++;
//		}
//		
//		if(Count_la < 100)
//		{
//			if (CurrState == 0 && PrevState != 0)
//			{
//				Key_Num = PrevState;
//			}	
//			Key_Chan = 0;		
//		}
//		else
//		{
//			Key_Chan = Key_GetState();
//		}

//	}
//}



uint8_t Key_GetCH(uint8_t ch)
{
	uint8_t temp;
	if(KEY_GetValue(ch) <= 0+500)
	{
		temp = 1;
	}
	else if(KEY_GetValue(ch) >= 4095-500)
	{
		temp = 2;
	}
	else if((KEY_GetValue(ch) >= 2048-900)&&(KEY_GetValue(ch) <= 2048+900))
	{
		temp = 0;
	}
	
	return temp;
}



uint8_t* Key_GetState(void)
{
	static uint8_t temp[8] = {0};

	if (Key_GetCH(A4) == 1)
	{
		temp[0] = 1;
	}
	else
	{
		temp[0] = 0;
	}
	
	if (Key_GetCH(A5) == 1)
	{
		temp[1] = 1;
	}
	else
	{
		temp[1] = 0;
	}	
	
	if (Key_GetCH(A6) == 1)
	{
		temp[2] = 1;
	}
	else
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
