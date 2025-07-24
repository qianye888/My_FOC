#include "FOC.h"
#include "AS5600.h"
#include "sys.h"

#define Xlimit 300
/*******************************************
SysTick初始化(模拟micros函数初始化)：

备注：     
	1.从0xFFFFFF到0循环计数
	2.开启后无法再使用delay延时函数
*******************************************/
void Systick_CountMode(void)
{
	SysTick->LOAD = 0xFFFFFF-1;
	SysTick->VAL  = 0;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
}
/*******************************************
电角度求解：

备注：     
	1.     电角度      =   机械角度  *  极对数
	2._electricalAngle = shaft_angle * pole_pairs
*******************************************/
float _electricalAngle(void)
{
	return _normalizeAngle((float)(FOC_Parame.DIR * FOC_Parame.PP) * get_Angle_2PI()-FOC_Parame.zero_electric_angle);
}

/*******************************************
角度归一化处理:
*******************************************/
float _normalizeAngle(float angle)
{
	float a = fmod(angle,2*PI);
	return a >= 0 ? a : (a+ 2*PI);
	//三目运算符。格式：condition ? expr1 : expr2
	//其中,condition式要求值的条件表达式,如果条件成立,则返回 expr1 的值。可以将三目运算符看作if-else的简化形式
}

/*******************************************
PWM输出计算:
*******************************************/
void setPWM(float Ua,float Ub,float Uc)
{
	//输出限幅
	Ua = _constrain(Ua,0.0f,FOC_Parame.voltage_limit);
	Ub = _constrain(Ub,0.0f,FOC_Parame.voltage_limit);
	Uc = _constrain(Uc,0.0f,FOC_Parame.voltage_limit);
	//占空比计算+输出限幅
	FOC_Parame.dc_a = _constrain(Ua/FOC_Parame.voltage_power_supply,0.0f,1.0f);
	FOC_Parame.dc_b = _constrain(Ub/FOC_Parame.voltage_power_supply,0.0f,1.0f);
	FOC_Parame.dc_c = _constrain(Uc/FOC_Parame.voltage_power_supply,0.0f,1.0f);
	//PWM赋值
	PWM_SetCompare1(FOC_Parame.dc_a*2400);
	PWM_SetCompare2(FOC_Parame.dc_b*2400);
	PWM_SetCompare3(FOC_Parame.dc_c*2400);
}
/*******************************************
力矩控制:
*******************************************/
void setTorque(float Uq,float angle_el)
{
	//力矩限幅
	Uq = _constrain(Uq,-FOC_Parame.voltage_power_supply/2,FOC_Parame.voltage_power_supply/2);
	/*float Ud=0;*/
	angle_el = _normalizeAngle(angle_el);
	//帕克逆变换
	FOC_Parame.Ualpha = -Uq*sin(angle_el);
	FOC_Parame.Ubeta  = Uq*cos(angle_el); 
	//克拉克逆变换
	FOC_Parame.Ua = FOC_Parame.Ualpha + FOC_Parame.voltage_power_supply/2;
	FOC_Parame.Ub = (sqrt(3)*FOC_Parame.Ubeta-FOC_Parame.Ualpha)/2 + FOC_Parame.voltage_power_supply/2;
	FOC_Parame.Uc = (-FOC_Parame.Ualpha-sqrt(3)*FOC_Parame.Ubeta)/2 + FOC_Parame.voltage_power_supply/2;
	//PWM赋值
	setPWM(FOC_Parame.Ua,FOC_Parame.Ub,FOC_Parame.Uc);
}

/*******************************************
SVPWM控制:
*******************************************/

void SVPWM_Generate(float Uq, float angle_el)
{
	//力矩限幅
	Uq = _constrain(Uq,-FOC_Parame.voltage_power_supply/2,FOC_Parame.voltage_power_supply/2);
	/*float Ud=0;*/
	angle_el = _normalizeAngle(angle_el);
	//帕克逆变换
	FOC_Parame.Ualpha = -Uq*sin(angle_el);
	FOC_Parame.Ubeta  = Uq*cos(angle_el); 

    // 1. 计算扇区
    float Vref1 = FOC_Parame.Ubeta;
    float Vref2 = (_SQRT3*FOC_Parame.Ualpha - FOC_Parame.Ubeta) / 2.0f;
    float Vref3 = (-(_SQRT3*FOC_Parame.Ualpha + FOC_Parame.Ubeta)) / 2.0f;
    
    SVPWM_Parame.sector_pre = 0;
	SVPWM_Parame.sector = 0;
    if (Vref1 > 0) SVPWM_Parame.sector_pre += 1;
    if (Vref2 > 0) SVPWM_Parame.sector_pre += 2;
    if (Vref3 > 0) SVPWM_Parame.sector_pre += 4;
    
    const uint8_t sector_table[7] = {2, 2, 6, 1, 4, 3, 5};
    SVPWM_Parame.sector = sector_table[SVPWM_Parame.sector_pre];

    // 2. 计算基本矢量作用时间
	float base = ((_SQRT3 * SVPWM_Parame.Tpwm)/FOC_Parame.voltage_power_supply);
    float X = base * FOC_Parame.Ubeta;
    float Y = base * ((_SQRT3 * FOC_Parame.Ualpha - FOC_Parame.Ubeta)/2.0f);
    float Z = base * ((-(_SQRT3 * FOC_Parame.Ualpha) - FOC_Parame.Ubeta)/2.0f);
    
    float T1, T2;
    switch(SVPWM_Parame.sector) 
	{
        case 1: T1 = Y; T2 = X;
		break;
        case 2: T1 = -Y; T2 = -Z; 
		break;
        case 3: T1 = X; T2 = Z; 
		break;
        case 4: T1 = -X; T2 = -Y; 
		break;
        case 5: T1 = Z; T2 = Y; 
		break;
        case 6: T1 = -Z; T2 = -X; 
		break;
        default: T1 = 0; T2 = 0;
		break;
    }

    // 3. 限幅处理
    T1 = _constrain(T1, 0.0f, 1.0f * SVPWM_Parame.Tpwm);
    T2 = _constrain(T2, 0.0f, 1.0f * SVPWM_Parame.Tpwm);
	float Temp = T1 + T2;
	if(Temp > SVPWM_Parame.Tpwm)
	{
		T1 = T1/Temp * SVPWM_Parame.Tpwm;
		T2 = T2/Temp * SVPWM_Parame.Tpwm;
	}
    float T0 = 1.0f * SVPWM_Parame.Tpwm - T1 - T2;

    // 4. 计算占空比（中央对齐模式）
	float value1, value2, value3;
	value1 = T1 + T2 + T0/2;
	value2 = T2 + T0/2;
	value3 = T0/2;
    switch(SVPWM_Parame.sector) 
	{
        case 1:
		SVPWM_Parame.Ta = value1; 
		SVPWM_Parame.Tb = value2; 
		SVPWM_Parame.Tc = value3; 
		break;
        case 2: 
		SVPWM_Parame.Ta = value2; 
		SVPWM_Parame.Tb = value1; 
		SVPWM_Parame.Tc = value3; 
		break;
        case 3: 
		SVPWM_Parame.Ta = value3; 
		SVPWM_Parame.Tb = value1; 
		SVPWM_Parame.Tc = value2; 
		break;
        case 4: 
		SVPWM_Parame.Ta = value3; 
		SVPWM_Parame.Tb = value2; 
		SVPWM_Parame.Tc = value1; 
		break;
        case 5: 
		SVPWM_Parame.Ta = value2; 
		SVPWM_Parame.Tb = value3; 
		SVPWM_Parame.Tc = value1; 
		break;
        case 6: 
		SVPWM_Parame.Ta = value1; 
		SVPWM_Parame.Tb = value3; 
		SVPWM_Parame.Tc = value2; 
		break;
        default: 
		SVPWM_Parame.Ta = 0;
		SVPWM_Parame.Tb = 0;
		SVPWM_Parame.Tc = 0; 
		break;
    }
    SVPWM_Parame.Ta = _constrain(SVPWM_Parame.Ta, 0, SVPWM_Parame.Tpwm);
    SVPWM_Parame.Tb = _constrain(SVPWM_Parame.Tb, 0, SVPWM_Parame.Tpwm);
    SVPWM_Parame.Tc = _constrain(SVPWM_Parame.Tc, 0, SVPWM_Parame.Tpwm);
    // 5. 转换为定时器比较值（假设PWM周期为中央对齐模式）
    SVPWM_Parame.cmpA = (uint32_t)((SVPWM_Parame.Ta) /2);
    SVPWM_Parame.cmpB = (uint32_t)((SVPWM_Parame.Tb) /2);
    SVPWM_Parame.cmpC = (uint32_t)((SVPWM_Parame.Tc) /2);
	
	PWM_SetCompare1(SVPWM_Parame.cmpA);
	PWM_SetCompare2(SVPWM_Parame.cmpB);
	PWM_SetCompare3(SVPWM_Parame.cmpC);	
}

/*******************************************
FOC控制初始化:
*******************************************/
void FOC_Init(float power_supply)
{
	FOC_Parame.voltage_power_supply = power_supply;
	
	PWMFOC_Init();//3路PMW波初始化(30000HZ)
	
	NVIC_Config();//中断优先级分配
	
	PID_init();//初始化pid变量
}
/*******************************************
FOC编码器数据初始化:
*******************************************/
void FOC_AS5600_Init(int _PP,int _DIR)
{
	AS5600_Init();//AS5600模拟I2C初始化
	
	FOC_Parame.PP=_PP;
	FOC_Parame.DIR=_DIR;
	setTorque(3, _3PI_2);
	
	Delay_ms(1000);
	Delay_ms(1000);//等待外设准备完毕

	FOC_Parame.zero_electric_angle = _electricalAngle();
	setTorque(0, _3PI_2);
	
	FOC_Parame.Sensor_Speed = get_Speed();//速度初始值计算
}

float round_float_5dec(float num) 
{
    int32_t scaled = (int32_t)(num * 100000.0f + 0.5f);
    return (float)scaled / 100000.0f;
}

/***********************************************
电机角度控制:(rad)
***********************************************/
void Set_Angle(float Angle)
{
	//角度读取
	//角度控制
	float temp = round_float_5dec((Angle - FOC_Parame.DIR*FOC_Parame.Sensor_Angle)*180/PI);
	if(temp <5 && temp >-5)
	{
		temp = 0;
	}
	FOC_Parame.Speed_target = Angle_Control(temp);
	
	if(FOC_Parame.Speed_target>Xlimit)FOC_Parame.Speed_target=Xlimit;//角度环力矩输出限幅
	if(FOC_Parame.Speed_target<-Xlimit)FOC_Parame.Speed_target=-Xlimit;
	
	if(temp <5 && temp >-5)
	{
		FOC_Parame.Speed_target = 0;
	}
//	Angle_Out = ;
//	XianFu();
//	if(temp <10 && temp >-10)
//	{
//		Angle_Out = 0;
//	}
	//SVPWM_Generate(Angle_Out,_electricalAngle());
	//setTorque(Angle_Out,_electricalAngle());
	//角度打印
	//printf("%.2f,%.2f\n",Sensor_Angle,Angle_target);
}
/***********************************************
电机速度控制:(rad/s)
***********************************************/
void Set_Speed(float Speed)
{
	//速度读取
	//Sensor_Speed = get_Speed();
	//速度控制
	float temp = round_float_5dec(Speed - FOC_Parame.Sensor_Speed);
	
	Speed_Out = Speed_Control(temp);
	XianFu();
	if(temp <= 5&&temp >= -5)
	{
		Speed_Out = 0;
	}
	
		
	//setTorque(Speed_Out,_electricalAngle());
	SVPWM_Generate(Speed_Out,_electricalAngle());
	//速度打印
	//printf("%.2f,%.2f\n",Sensor_Speed,Speed_target);
}
void Set_Speed_loop(float loop_speed)
{
	//速度读取
	//Sensor_Speed = get_Speed();
	//速度控制
	//float loop_angle = _normalizeAngle((float)(FOC_Parame.DIR * FOC_Parame.PP) * loop_speed-FOC_Parame.zero_electric_angle);
	FOC_Parame.Angle_loop += loop_speed;
	float loop_angle = _normalizeAngle((float)(FOC_Parame.DIR * FOC_Parame.PP) * FOC_Parame.Angle_loop-FOC_Parame.zero_electric_angle);	
	SVPWM_Generate(FOC_Parame.voltage_limit,loop_angle);
	//速度打印
	//printf("%.2f,%.2f\n",Sensor_Speed,Speed_target);
}
