#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "main.h"	
//FOC_MBD

//TEST
/*串口测试*/
void UsartDeal(void)
{
	//Serial_SendByte((uint8_t)getVelocity());
	//Serial_Printf("%d,%d,%d\r\n", SVPWM_Parame.pwm_a, SVPWM_Parame.pwm_b, SVPWM_Parame.pwm_c);
	
	//Serial_Printf("%f,%f,%f\r\n", SVPWM_Parame.calculate_Ua, SVPWM_Parame.calculate_Ub, SVPWM_Parame.calculate_Uc);	
	//Serial_Printf("%d,%d\r\n", i, task_10);
	Serial_Printf("%d,%d,%d,%d,%f\r\n", rtY.Section, rtY.PWM_Duty_U, rtY.PWM_Duty_V, rtY.PWM_Duty_W,rtY.Act_speed);
	//Serial_Printf("%d,%d,%d,%d,%d\r\n", SVPWM_Parame.sector, SVPWM_Parame.Ta, SVPWM_Parame.Tb, SVPWM_Parame.Tc, SVPWM_Parame.Tpwm);
}

/*OLED测试*/
void OLEDDeal(void)
{
//	OLED_Printf(0, 0, OLED_8X16, "data:%+d", i);
//	OLED_Printf(0, 16, OLED_8X16, "task10:%+d", task_10);	
	
//	OLED_Printf(0, 16, OLED_8X16, "task:%+d", task_10);
//	OLED_Printf(0, 32, OLED_8X16, "task_20:%+04d", task_20);
	
	OLED_ShowFloatNum(0, 0, rtY.Act_speed, 5, 5, OLED_8X16);
//	OLED_ShowFloatNum(0, 16, _electricalAngle(), 5, 5, OLED_8X16);
//	OLED_ShowFloatNum(0, 32, get_Angle_2PI(), 5, 5, OLED_8X16);
	
//	OLED_ShowFloatNum(0, 32, get_Angle(), 5, 5, OLED_8X16);
//	OLED_ShowFloatNum(0, 48, full_rotations, 5, 5, OLED_8X16);	
	
	
//	OLED_ShowFloatNum(0, 0, FOC_Parame.Speed_target, 5, 0, OLED_8X16);
//	OLED_ShowFloatNum(0, 16, Speed_Out, 5, 5, OLED_8X16);
//	OLED_ShowFloatNum(0, 32, FOC_Parame.Sensor_Angle, 3, 8, OLED_8X16);	
//	OLED_ShowFloatNum(0, 48, FOC_Parame.Sensor_Speed, 3, 8, OLED_8X16);
	
	OLED_Update();	
}

int main(void)
{	
	Bsw_Init();
	FOCPARAM_init();
	
	//SVPWMPARAM_init();
	FOC_Motor_initialize();
	while(1)
	{
		task_10ms();
		KeyDeal();
		OLEDDeal();
		LEDDeal();
		//ADCDeal();
	} 	
}

/*10ms周期*/
void task_10ms(void)
{
	if(Control_10msFlag == 1)
	{
		Control_10msFlag = 0;
		task_10++;
		
		
		
		if(FOC_Parame.foc_on == 0)
		{
			//j = j+FOC_Parame.Speed_target/100;
		    //Set_Speed_loop(j);//
			
			//Set_Speed(FOC_Parame.Speed_target);
			//SVPWM_Generate(2,0);
			
			//Set_Speed_loop(FOC_Parame.Speed_target);
		}
		else
		{
			//Set_MBU_loop(FOC_Parame.Speed_target);
			//Set_Speed(FOC_Parame.Speed_target);
			
			MBD_APIIN();
			FOC_Motor_step();
			PWM_SetCompare1(rtY.PWM_Duty_U);
			PWM_SetCompare2(rtY.PWM_Duty_V);
			PWM_SetCompare3(rtY.PWM_Duty_W);	
			
//			Set_Angle(FOC_Parame.Angle_target);
//			Set_Speed(FOC_Parame.Speed_target);
		}
		//i++;
		
		FOC_Parame.Sensor_Angle = get_Angle();
		FOC_Parame.Sensor_Speed = get_Speed();
		//LOWPass_Filter(FOC_Parame.DIR* (FOC_Parame.Sensor_Angle - FOC_Parame.lastSensor_Angle)*100,speedfil,0.8);
		
		FOC_Parame.lastSensor_Angle = FOC_Parame.Sensor_Angle;
		FOC_Parame.lastSensor_Speed = FOC_Parame.Sensor_Speed;
		UsartDeal();
		
//		MBDSV_APIIN();
//		svpwm_V_step();
//		SVPWM_Parame.calculate_Ua = LOWPass_Filter((float)OutUa,Uafil,0.7);;
//		SVPWM_Parame.calculate_Ub = LOWPass_Filter((float)OutUb,Ubfil,0.7);;
//		SVPWM_Parame.calculate_Uc = LOWPass_Filter((float)OutUc,Ucfil,0.7);;
	}
}


/*KEY测试*/
void KeyDeal(void)
{
	    KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			FOC_Parame.Speed_target +=10;
			FOC_Parame.Angle_target +=10;
		}
		if (KeyNum == 2)
		{
			FOC_Parame.Speed_target -=10;
			FOC_Parame.Angle_target -=10;
		}
		if (KeyNum == 3)
		{
			FOC_Parame.Speed_target =0;
			FOC_Parame.Angle_target =0;
		}
		if (KeyNum == 4)
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
	Key_Init();
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









