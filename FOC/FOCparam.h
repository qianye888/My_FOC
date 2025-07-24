#ifndef __FOCPARAM_H_
#define __FOCPARAM_H_

#include "sys.h"

typedef struct//定义pid结构体
{
	float TarValue;//定义目标值
	float ActValue;//定义真实值
	
	float Err;//定义偏差值
	float Err_last_1;//定义上一个偏差值
	float Err_last_2;//定义上两个偏差值
	float Kp,Ki,Kd;//定义比例，积分，微分
	float Voltage;//定义电压值
	float Integral;//定义积分值
    float Int_Limit;
    float OUT_Limit;
	float OUT;
}PID;

typedef struct//定义svpwm结构体
{
    uint32_t Tpwm;
    uint8_t sector_pre;
	uint8_t sector;//
	float Ta;//
	float Tb;//
	float Tc;//
    uint32_t cmpA;
    uint32_t cmpB;
    uint32_t cmpC;
	
	uint16_t pwm_a;
	uint16_t pwm_b;
	uint16_t pwm_c;
	
	float calculate_Ua;//
	float calculate_Ub;//
	float calculate_Uc;//
}SVPWM;


typedef struct//定义FOC结构体
{
    float voltage_limit;
    float voltage_power_supply;
    float zero_electric_angle;
    float Ualpha;
    float Ubeta;
    float Ua;
    float Ub;
    float Uc;
    float dc_a;
    float dc_b;
    float dc_c;
    float Sensor_Angle;		
    float lastSensor_Angle;		
    float Angle_target;	
    float Sensor_Speed;		
    float lastSensor_Speed;		
    float Speed_target;	
    float Angle_loop;	
    uint8_t foc_on;
	int PP;	//极对数
	int DIR;	//无刷电机纠偏旋转方向
}FOC;

extern SVPWM SVPWM_Parame;
extern FOC FOC_Parame;//定义FOC参数
extern PID pid_angle;//定义速度环pid
extern PID pid_speed;//定义距离环pid

void PID_init(void);//PID初始化
void FOCPARAM_init(void);
void SVPWMPARAM_init(void);

#endif
