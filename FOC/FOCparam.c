#include "FOCparam.h"
#include "sys.h" 

SVPWM SVPWM_Parame;
FOC FOC_Parame;
PID pid_angle;
PID pid_speed;

// PID 配置函数：
// 1. pid_angle 用于位置环，输出作为速度目标值。
// 2. pid_speed 用于速度环，输出作为最终力矩电压。
// 3. 这里初始化的是运行时控制参数，不是结构体默认值定义。
void PID_init(void)
{
	// 位置环 PID：用于把角度误差转换成速度目标。
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

	// 速度环 PID：用于把速度误差转换成力矩电压 Uq。
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

// FOC 默认参数初始化。
// 这些值决定了上电后控制环的起始状态、目标值和电机基础配置。
void FOCPARAM_init(void)
{
	// 母线和输出限制参数。
	FOC_Parame.voltage_limit = 10;
	FOC_Parame.voltage_power_supply = 12.0;
	// 编码器零电角，影响电角度对齐。
	FOC_Parame.zero_electric_angle = 0.0689936;
	// α/β 和三相量在启动时清零。
	FOC_Parame.Ualpha = 0;
	FOC_Parame.Ubeta = 0;
	FOC_Parame.Ua = 0;
	FOC_Parame.Ub = 0;
	FOC_Parame.Uc = 0;
	FOC_Parame.dc_a =  0;
	FOC_Parame.dc_b = 0;
	FOC_Parame.dc_c = 0;
	// 反馈值和历史值清零。
	FOC_Parame.Sensor_Angle = 0;
	FOC_Parame.lastSensor_Angle = 0;	
	// 位置目标值默认为 3 度，用于上电后提供一个静态初始偏置。
	FOC_Parame.Angle_target = 3.00;	
	FOC_Parame.Sensor_Speed = 0;
	FOC_Parame.lastSensor_Speed = 0;	
	// 速度目标值默认从 0 开始。
	FOC_Parame.Speed_target = 0.0;	
	// 电机基础参数。
	FOC_Parame.PP = 7;	//极对数
	FOC_Parame.DIR = 1;	//无刷电机纠偏旋转方向
	// 开环轨迹和闭环开关。
	FOC_Parame.Angle_loop = 0;	
    FOC_Parame.foc_on = 0;
}

// SVPWM 默认参数初始化。
// Tpwm 与 PWM 定时器周期对应，其余字段由 SVPWM_Generate() 动态更新。
void SVPWMPARAM_init(void)
{
	// 中央对齐 PWM 的周期计数值，和 PWMFOC_Init() 里的 ARR 配套。
	SVPWM_Parame.Tpwm = 3600*2;
	SVPWM_Parame.sector = 0;
	SVPWM_Parame.sector_pre = 0;
	SVPWM_Parame.Ta = 0;
	SVPWM_Parame.Tb = 0;
	SVPWM_Parame.Tc = 0;
	SVPWM_Parame.cmpA = 0;
	SVPWM_Parame.cmpB = 0;
	SVPWM_Parame.cmpC = 0;
	
	// 预留调试字段，当前主要用于观察输出占空比。
	SVPWM_Parame.pwm_a = 0;
	SVPWM_Parame.pwm_b = 0;
	SVPWM_Parame.pwm_c = 0;
	
	// 运行时调试输出：SVPWM 计算得到的三相电压。
	SVPWM_Parame.calculate_Ua = 0;
	SVPWM_Parame.calculate_Ub = 0;
	SVPWM_Parame.calculate_Uc = 0;
}
