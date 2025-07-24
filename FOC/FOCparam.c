#include "FOCparam.h"
#include "sys.h" 

SVPWM SVPWM_Parame;
FOC FOC_Parame;//定义FOC参数
PID pid_angle;//定义速度环pid
PID pid_speed;//定义距离环pid

/**********************
PID配置函数:
**********************/
void PID_init(void)//初始化pid变量
{
	//位置环pid
	pid_angle.TarValue=0.0;
	pid_angle.ActValue=0.0;
	pid_angle.Err=0.0;
	pid_angle.Err_last_1=0.0;
	pid_angle.Err_last_2=0.0;
	pid_angle.Voltage=0.0;
	pid_angle.Integral=0.0;
	pid_angle.Kp=0.563;//待调节0.043
	pid_angle.Ki=0.0000;//待调节0.0005
	pid_angle.Kd=0.22;//待调节0.22
	pid_angle.OUT = 0;
	pid_angle.Int_Limit = 0;
	pid_angle.OUT_Limit = 0;

	//速度环pid
	pid_speed.TarValue=0.0;
	pid_speed.ActValue=0.0;
	pid_speed.Err=0.0;
	pid_speed.Err_last_1=0.0;
	pid_speed.Err_last_2=0.0;
	pid_speed.Voltage=0.0;
	pid_speed.Integral=0.0;	
	pid_speed.Kp=0.005;//待调节0.11
	pid_speed.Ki=0.0001;//待调节0.005
	pid_speed.Kd=0.0000;//待调节0.0008
	pid_speed.OUT = 0;
	pid_speed.Int_Limit = 0;
	pid_speed.OUT_Limit = 0;
}

void FOCPARAM_init(void)//初始化FOC变量
{
	FOC_Parame.voltage_limit = 10;
	FOC_Parame.voltage_power_supply = 12.0;
	FOC_Parame.zero_electric_angle = 0.0689936;
	FOC_Parame.Ualpha = 0;
	FOC_Parame.Ubeta = 0;
	FOC_Parame.Ua = 0;
	FOC_Parame.Ub = 0;
	FOC_Parame.Uc = 0;
	FOC_Parame.dc_a =  0;
	FOC_Parame.dc_b = 0;
	FOC_Parame.dc_c = 0;
	FOC_Parame.Sensor_Angle = 0;
	FOC_Parame.lastSensor_Angle = 0;	
	FOC_Parame.Angle_target = 3.00;	
	FOC_Parame.Sensor_Speed = 0;
	FOC_Parame.lastSensor_Speed = 0;	
	FOC_Parame.Speed_target = 0.0;	
	FOC_Parame.PP = 7;	//极对数
	FOC_Parame.DIR = 1;	//无刷电机纠偏旋转方向
	FOC_Parame.Angle_loop = 0;	
    FOC_Parame.foc_on = 0;
}

void SVPWMPARAM_init(void)//初始化SVPWM变量
{
	SVPWM_Parame.Tpwm = 3600*2;
	SVPWM_Parame.sector = 0;
	SVPWM_Parame.sector_pre = 0;
	SVPWM_Parame.Ta = 0;
	SVPWM_Parame.Tb = 0;
	SVPWM_Parame.Tc = 0;
	SVPWM_Parame.cmpA = 0;
	SVPWM_Parame.cmpB = 0;
	SVPWM_Parame.cmpC = 0;
	
	SVPWM_Parame.pwm_a = 0;
	SVPWM_Parame.pwm_b = 0;
	SVPWM_Parame.pwm_c = 0;
	
	SVPWM_Parame.calculate_Ua = 0;
	SVPWM_Parame.calculate_Ub = 0;
	SVPWM_Parame.calculate_Uc = 0;
}
