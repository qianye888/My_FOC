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

uint8_t Key_GetCH(uint8_t ch)
{
	uint16_t value = KEY_GetValue(ch);
	if(value <= KEY_SHORT_PRESS_ADC_LOW)
	{
		return 1;
	}
	if(value >= KEY_LONG_PRESS_ADC_HIGH)
	{
		return 2;
	}
	if((value >= KEY_IDLE_ADC_MIN) && (value <= KEY_IDLE_ADC_MAX))
	{
		return 0;
	}

	return 0;
}

const uint8_t* Key_GetState(void)
{
	static uint8_t temp[8] = {0};
	static const uint8_t key_channels[8] = {A4, A5, A6, A7, A4, A5, A6, A7};
	static const uint8_t key_levels[8] = {1, 1, 1, 1, 2, 2, 2, 2};

	for (uint8_t index = 0; index < 8; index++)
	{
		temp[index] = (Key_GetCH(key_channels[index]) == key_levels[index]) ? 1 : 0;
	}

	return temp;
}

// 20 ms 扫描一次，按下稳定后分发短按或长按事件。
extern uint16_t task_20;
void Key_Tick(void)
{
	static uint16_t long_press_ticks[8];
	static uint8_t current_state[8];
	static uint8_t previous_state[8];

	if (Control_20msFlag == 1)
	{
		task_20++;
		Control_20msFlag = 0;

		const uint8_t *key_state = Key_GetState();
		for(uint8_t index = 0; index < 8; index++)
		{
			previous_state[index] = current_state[index];
			current_state[index] = key_state[index];

			if(current_state[index] != 0 && previous_state[index] == 0)
			{
				long_press_ticks[index] = 0;
			}

			if(key_state[index] != 0)
			{
				long_press_ticks[index]++;
			}

			if(long_press_ticks[index] < KEY_LONG_PRESS_TICKS)
			{
				if (current_state[index] == 0 && previous_state[index] != 0)
				{
					Key_Num[index] = previous_state[index];
				}
				Key_Chan[index] = 0;
			}
			else
			{
				Key_Chan[index] = key_state[index];
			}
		}
	}
}