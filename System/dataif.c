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
	rtSharedDSM.Theta_Inte = AS5600_GetData();
	rtSharedDSM.Theta_zero = FOC_Parame.zero_electric_angle;
	rtU.Ud = (int16_t)0;
	rtU.Uq = (int16_t)Speed_Out;
}
void MBD_APIOUT(void)
{
	//out
	SVPWM_Parame.cmpA = (uint32_t)rtY.PWM_Duty_U*2;
	SVPWM_Parame.cmpB = (uint32_t)rtY.PWM_Duty_V*2;
	SVPWM_Parame.cmpC = (uint32_t)rtY.PWM_Duty_W*2;
}

void MBDSV_APIIN(void)
{
	Spwm_a = SVPWM_Parame.pwm_a;                /* '<Root>/pwm_a' */
	Spwm_b = SVPWM_Parame.pwm_b;                /* '<Root>/pwm_b' */
	Spwm_c = SVPWM_Parame.pwm_c;                /* '<Root>/pwm_c' */
	voltage_power_supply = FOC_Parame.voltage_power_supply;  /* '<Root>/voltage_power_supply' */
}

