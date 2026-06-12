#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "main.h"	

// 全局状态集中在 main.c 定义，其他模块通过 main.h 引用。
int8_t temp_a = 1;
int8_t temp_s = 1;
uint16_t i = 0;
uint16_t task_10 = 0;
uint16_t task_20 = 0;
uint8_t KeyNum[8];
uint8_t KeyChan[8];
uint8_t motor_on = 0;
uint8_t Control_10msFlag = 0;
uint16_t pwm_a = 0;
uint16_t pwm_b = 0;
uint16_t pwm_c = 0;

/* 串口状态输出 */
void UsartDeal(void)
{
	Serial_Printf("%f,%f,%f,%f\r\n", FOC_Parame.Speed_target, FOC_Parame.Sensor_Speed, FOC_Parame.Angle_target, FOC_Parame.Sensor_Angle);
}

/* OLED 状态面板 */
void OLEDDeal(void)
{
	OLED_Printf(0, 0, OLED_6X8, "Angle");
	if(temp_a == 1)
	{
		OLED_Printf(40, 0, OLED_6X8, "+");
	}
	else
	{
		OLED_Printf(40, 0, OLED_6X8, "-");
	}
	OLED_Printf(0, 12, OLED_6X8, "At:%05.1f", FOC_Parame.Angle_target);
	OLED_Printf(0, 20, OLED_6X8, "Aa:%05.1f", FOC_Parame.Sensor_Angle);	
	OLED_Printf(0, 28, OLED_6X8, "Ap:%05.5f", pid_angle.Kp);
	OLED_Printf(0, 36, OLED_6X8, "Ai:%05.5f", pid_angle.Ki);
	OLED_Printf(0, 44, OLED_6X8, "Ad:%05.5f", pid_angle.Kd);
	
	
	OLED_Printf(64, 0, OLED_6X8, "Speed");	
	if(temp_s == 1)
	{
		OLED_Printf(104, 0, OLED_6X8, "+");
	}
	else
	{
		OLED_Printf(104, 0, OLED_6X8, "-");
	}	
	OLED_Printf(64, 12, OLED_6X8, "St:%05.1f", FOC_Parame.Speed_target);
	OLED_Printf(64, 20, OLED_6X8, "Sa:%05.1f", FOC_Parame.Sensor_Speed);		
	OLED_Printf(64, 28, OLED_6X8, "Sp:%05.5f", pid_speed.Kp);
	OLED_Printf(64, 36, OLED_6X8, "Si:%05.5f", pid_speed.Ki);
	OLED_Printf(64, 44, OLED_6X8, "Sd:%05.5f", pid_speed.Kd);
	
	if(motor_on)
	{	
		OLED_Printf(0, 56, OLED_6X8, "MOTOR_O N");
	}
	else
	{
		OLED_Printf(0, 56, OLED_6X8, "MOTOR_OFF");
	}
	OLED_Printf(64, 56, OLED_6X8, "Uq:%05.5f", Speed_Out);
	
	OLED_Update();	
}

int main(void)
{	
	// 先完成底层初始化，再进入周期任务循环。
	Bsw_Init();
	FOCPARAM_init();
	SVPWMPARAM_init();

	while(1)
	{
		task_10ms();
		KeyDeal();
		OLEDDeal();
		LEDDeal();
		ADCDeal();
	} 	
}

/* 10 ms 周期任务：控制计算、传感器刷新和输出更新都在这里收敛 */
void task_10ms(void)
{
	if(Control_10msFlag == 1)
	{
		Control_10msFlag = 0;
		task_10++;
		
		
		if(motor_on == 1)
		{
			MOTOR_ON();
			if(FOC_Parame.foc_on == 1)
			{
				Set_Speed(FOC_Parame.Speed_target);
			}
			else
			{
				Set_Angle(FOC_Parame.Angle_target);
				Set_Speed(FOC_Parame.Speed_target);
			}
		}
		else
		{
			MOTOR_OFF();
		}
		i++;
		
		FOC_Parame.Sensor_Angle = get_Angle();
		FOC_Parame.Sensor_Speed = get_Speed();
		
		FOC_Parame.lastSensor_Angle = FOC_Parame.Sensor_Angle;
		FOC_Parame.lastSensor_Speed = FOC_Parame.Sensor_Speed;
		UsartDeal();
		
		MBDSV_APIIN();
		svpwm_V_step();
		SVPWM_Parame.calculate_Ua = LOWPass_Filter((float)OutUa,Uafil,0.7);;
		SVPWM_Parame.calculate_Ub = LOWPass_Filter((float)OutUb,Ubfil,0.7);;
		SVPWM_Parame.calculate_Uc = LOWPass_Filter((float)OutUc,Ucfil,0.7);;
	}
}


/* 按键输入：短按用于目标值调整，长按用于 PID 参数微调 */
void KeyDeal(void)
{	
	    Key_Tick();
		static uint8_t CurrState_a = 1;
		static uint8_t PrevState_a = 1;	
		static uint8_t CurrState_s = 1;
		static uint8_t PrevState_s = 1;	
		if (Key_Num[0] == 1)
		{
			FOC_Parame.Angle_target +=10;
			
		}
		if (Key_Num[1] == 1)
		{
			FOC_Parame.Angle_target -=10;
		}
		if (Key_Num[2] == 1)
		{
			FOC_Parame.Angle_target =0;
		}
		if (Key_Num[3] == 1)
		{
			if(FOC_Parame.foc_on == 1)
			{
				FOC_Parame.foc_on = 0;
			}
			else
			{
				FOC_Parame.foc_on = 1;
			}
		}
		if (Key_Num[4] == 1)
		{
			FOC_Parame.Speed_target +=10;
		}
		if (Key_Num[5] == 1)
		{
			FOC_Parame.Speed_target -=10;
		}
		if (Key_Num[6] == 1)
		{
			FOC_Parame.Speed_target =0;
		}
		if (Key_Num[7] == 1)
		{
			motor_on = !motor_on;
		}
		
		PrevState_a = CurrState_a;
		CurrState_a = Key_Chan[3];
		PrevState_s = CurrState_s;
		CurrState_s = Key_Chan[7];
		if (Key_Chan[0] == 1)
		{
			pid_angle.Kd+=(temp_a*0.001);
		}	
		if (Key_Chan[1] == 1)
		{
			pid_angle.Ki+=(temp_a*0.00001);
		}			
		if (Key_Chan[2] == 1)
		{
			pid_angle.Kp+=(temp_a*0.00001);
		}	
		if (CurrState_a == 0 && PrevState_a != 0)
		{
			if(temp_a == 1)
			{
				temp_a = -1;
			}
			else
			{
				temp_a = 1;
			}
		}	
		
		
		if (Key_Chan[4] == 1)
		{
			pid_speed.Kd+=(temp_s*0.001);
		}	
		if (Key_Chan[5] == 1)
		{
			pid_speed.Ki+=(temp_s*0.00001);
		}			
		if (Key_Chan[6] == 1)
		{
			pid_speed.Kp+=(temp_s*0.00001);
		}	
		if (CurrState_s == 0 && PrevState_s != 0)
		{
			if(temp_s == 1)
			{
				temp_s = -1;
			}
			else
			{
				temp_s = 1;
			}
		}
		for(uint8_t i = 0;i<8;i++)
		{
			Key_Num[i] = 0;
		}
}


/*LED测试*/
void LEDDeal(void)
{
	if(FOC_Parame.foc_on == 1)
	{
		LED_ON();
	}		
	else
	{
	LED_OFF();
	}
}

void Bsw_Init(void)
{
	Timer_Init();	
	FOC_Init(12.6);
	FOC_AS5600_Init(7,1);
	OLED_Init();
	RP_Init();
	Serial_Init(19200);
	LED_Init();
	//Key_Init();
}

/*ADC测试*/
void ADCDeal(void)
{
	pwm_a = (uint16_t)LOWPass_Filter((float)(RP_GetValue(PWM_A)),pwmafil,0.7);
	pwm_b = (uint16_t)LOWPass_Filter((float)(RP_GetValue(PWM_B)),pwmafil,0.7);
	pwm_c = (uint16_t)LOWPass_Filter((float)(RP_GetValue(PWM_C)),pwmafil,0.7);
	
	SVPWM_Parame.pwm_a = (uint16_t)(RP_GetValue(PWM_A));
	SVPWM_Parame.pwm_b = (uint16_t)(RP_GetValue(PWM_B));
	SVPWM_Parame.pwm_c = (uint16_t)(RP_GetValue(PWM_C));
}


void Set_MBU_loop(float loop_sp)
{
	
	loop_mbd += (uint32_t)loop_sp*100;
	a = fmod(loop_mbd,4095);
	//float loop_angle = _normalizeAngle((float)(FOC_Parame.DIR * FOC_Parame.PP) * FOC_Parame.Angle_loop-FOC_Parame.zero_electric_angle);	
	//SVPWM_Generate(FOC_Parame.voltage_limit,loop_angle);
}

/*PWM测试*/

//int main(void)
//{
//	OLED_Init();
//	
//	PWMFOC_Init();
//	
//	uint16_t i = 0;
//	while (1)
//	{
//		if(i < 2400)
//		{
//			i+=30;
//		}
//		else
//		{
//			i=0;
//		}
//		PWM_SetCompare1(i);
//		PWM_SetCompare2(i);
//		PWM_SetCompare3(i);
//		
//		OLED_Printf(0, 0, OLED_8X16, "PWM:%+04d", i);
//		
//		OLED_Update();
//	}
//}



/*编码器测试*/

//int main(void)
//{
//	OLED_Init();
//	Timer_Init();
//	AS5600_Init();
//	
//	while (1)
//	{
//		
//		//OLED_Printf(0, 0, OLED_8X16, "Speed:%+05d", getVelocity);
//		//OLED_Printf(0, 16, OLED_8X16, "Location:%+05d", get_Angle_360);
//		//OLED_Printf(0, 32, OLED_8X16, "yuans:%+05d", AS5600_GetData);
//		OLED_ShowFloatNum(0, 0, getVelocity(), 5, 0, OLED_8X16);
//		OLED_ShowFloatNum(0, 16, get_Angle(), 5, 0, OLED_8X16);
//		OLED_ShowFloatNum(0, 32, get_Angle_360(), 5, 0, OLED_8X16);
//		OLED_Update();
//	}
//}

//void TIM1_UP_IRQHandler(void)
//{
//	static uint16_t Count;
//	
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
//	{
//		Count ++;
//		if (Count >= 40)
//		{
//			Count = 0;
//			
//			Speed = Encoder_Get();
//			Location += Speed;
//		}
//		
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	}
//}









