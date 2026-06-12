#ifndef __FOCPARAM_H_
#define __FOCPARAM_H_

#include "sys.h"

// PID 参数块
// TarValue: 目标值
// ActValue: 实际值
// Err: 当前误差
// Err_last_1 / Err_last_2: 历史误差，用于微分或扩展控制
// Kp / Ki / Kd: 比例、积分、微分系数
// Voltage: 控制输出对应的电压量
// Integral: 积分累积量
// Int_Limit / OUT_Limit: 积分和输出限幅
// OUT: 最终控制输出
typedef struct
{
    float TarValue;
    float ActValue;
	
    float Err;
    float Err_last_1;
    float Err_last_2;
    float Kp,Ki,Kd;
    float Voltage;
    float Integral;
    float Int_Limit;
    float OUT_Limit;
	float OUT;
}PID;

// SVPWM 中间量与输出参数块
// Tpwm: PWM 周期计数值
// sector_pre / sector: 扇区判定中间值和最终扇区
// Ta / Tb / Tc: 三相作用时间
// cmpA / cmpB / cmpC: 写入 TIM1 的比较值
// pwm_a / pwm_b / pwm_c: 预留的原始 PWM 值
// calculate_Ua / Ub / Uc: 调试用三相电压计算结果
typedef struct
{
    uint32_t Tpwm;
    uint8_t sector_pre;
    uint8_t sector;
    float Ta;
    float Tb;
    float Tc;
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


// FOC 主状态参数块
// voltage_limit: 允许输出的最大相电压
// voltage_power_supply: 母线电压
// zero_electric_angle: 编码器零位对应的电角度偏置
// Ualpha / Ubeta: α/β 坐标系电压分量
// Ua / Ub / Uc: 三相相电压
// dc_a / dc_b / dc_c: 三相占空比
// Sensor_Angle / Sensor_Speed: 当前反馈值
// lastSensor_Angle / lastSensor_Speed: 上次反馈值
// Angle_target / Speed_target: 目标位置和目标速度
// Angle_loop: 用于速度开环轨迹累计
// foc_on: 闭环开关
// PP: 极对数
// DIR: 方向修正因子
typedef struct
{
    float voltage_limit;
    float voltage_power_supply;
    float voltage_margin;
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
    uint8_t field_weakening_on;
    float field_weakening_speed_threshold;
    float field_weakening_voltage_threshold;
    float field_weakening_min_ud;
    float field_weakening_ud_ref;
    float field_weakening_uq_ref;
	int PP;	//极对数
	int DIR;	//无刷电机纠偏旋转方向
}FOC;

extern SVPWM SVPWM_Parame;
extern FOC FOC_Parame;
extern PID pid_angle;
extern PID pid_speed;

void PID_init(void);
void FOCPARAM_init(void);
void SVPWMPARAM_init(void);

#endif
