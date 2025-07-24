#include "stm32f10x.h"                  // Device header
#include "dataif.h"
#include "sys.h"


low_pass Low_pass[10];

float LOWPass_Filter(float pre_in,uint8_t index,float fif)
{
	Low_pass[index].fif = fif;
	float out = Low_pass[index].fif*Low_pass[index].out_prev + (1-Low_pass[index].fif)*pre_in;
	
	Low_pass[index].out_prev=out;
	
	return out;
}
uint32_t loop_mbd = 0;
uint32_t a = 0;


void MBD_APIIN(void)
{
	rtU.Theta_Inte = AS5600_GetData();
	rtU.Theta_zero = 0;
	
	rtU.Tar_speed = FOC_Parame.Speed_target;
	rtU.Speed_kp = pid_speed.Kp;
	rtU.Speed_ki = pid_speed.Ki;	
	rtU.Speed_kd = pid_speed.Kd;
}
//void MBD_APIOUT(void)
//{
//	//out
//	SVPWM_Parame.cmpA = rtY.PWM_Duty_U;
//	SVPWM_Parame.cmpB = rtY.PWM_Duty_V;
//	SVPWM_Parame.cmpC = rtY.PWM_Duty_W;
//}

void MBDSV_APIIN(void)
{
	Spwm_a = SVPWM_Parame.pwm_a;                /* '<Root>/pwm_a' */
	Spwm_b = SVPWM_Parame.pwm_b;                /* '<Root>/pwm_b' */
	Spwm_c = SVPWM_Parame.pwm_c;                /* '<Root>/pwm_c' */
	voltage_power_supply = FOC_Parame.voltage_power_supply;  /* '<Root>/voltage_power_supply' */
}

