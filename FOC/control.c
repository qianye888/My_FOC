#include "control.h"
#include "sys.h"
#include "FOCparam.h"

float Angle_Out;//�Ƕ�PWM���
float Speed_Out;//�ٶ�PWM���
#define Speedlimit  7000
#define Anglelimit  7000


/**********************
�ǶȻ���pid����

���룺�Ƕ����
������ǶȻ����(��������)
**********************/
float Angle_Control(float Angle_Err)
{
	float PWM_Out;

	pid_angle.Err=Angle_Err;
	if(pid_angle.Err > 360)
	{
	pid_angle.Integral = 0;	
	}
	else 
	{
	pid_angle.Integral+=pid_angle.Err;
	}
	
	PWM_Out=pid_angle.Kp * pid_angle.Err + pid_angle.Ki * pid_angle.Integral + pid_angle.Kd * (pid_angle.Err-pid_angle.Err_last_1);

	pid_angle.Integral=pid_angle.Integral>Anglelimit?Anglelimit:(pid_angle.Integral<(-Anglelimit)?(-Anglelimit):pid_angle.Integral);//�����޷�
	
	pid_angle.Err_last_1=pid_angle.Err;
	
	return PWM_Out;
}
/**********************
�ٶȻ���pid����

���룺�ٶ����
������ٶȻ����(��������)
**********************/
float Speed_Control(float Speed_Err)
{
	float PWM_Out;

	pid_speed.Err=Speed_Err;
	
	pid_speed.Integral+=pid_speed.Err;
	
	PWM_Out=pid_speed.Kp * pid_speed.Err + pid_speed.Ki * pid_speed.Integral + pid_speed.Kd * (pid_speed.Err-pid_speed.Err_last_1);

	pid_speed.Integral=pid_speed.Integral>Speedlimit?Speedlimit:(pid_speed.Integral<(-Speedlimit)?(-Speedlimit):pid_speed.Integral);//�����޷�
	
	pid_speed.Err_last_1=pid_speed.Err;
	
	return PWM_Out;
}
/**********************
�޷�����:(��������)
**********************/
void XianFu(void)
{
	float Vlimit = 5;
	if(Angle_Out>Vlimit)Angle_Out=Vlimit;//�ǶȻ���������޷�
	if(Angle_Out<-Vlimit)Angle_Out=-Vlimit;
	if(Speed_Out>Vlimit)Speed_Out=Vlimit;//�ٶȻ���������޷�
	if(Speed_Out<-Vlimit)Speed_Out=-Vlimit;
}


//void PID_Control(PID* pid)
//{
//	pid->Integral += pid->Err;
//	
//	pid->OUT = pid->Kp * pid->Err + pid->Ki * pid->Integral + pid->Kd * (pid->Err - pid->Err_last_1);

//	pid->Integral = pid->Integral>pid->Int_Limit?pid->Int_Limit:(pid->Integral<(-pid->Int_Limit)?(-pid->Int_Limit):pid->Integral);//�����޷�
//	
//	pid->Err_last_2=pid->Err_last_1;
//	pid->Err_last_1=pid->Err;

//	if(pid->OUT > pid->OUT_Limit)
//	{
//		pid->OUT = pid->OUT_Limit;
//	}

//	if(pid->OUT < -pid->OUT_Limit)
//	{
//		pid->OUT = -pid->OUT_Limit;
//	}
//	
//	//pid->OUT = pid->OUT>pid->OUT_Limit?pid->OUT_Limit:(pid->OUT<(-pid->OUT_Limit)?(-pid->OUT_Limit):pid->OUT);
//}
