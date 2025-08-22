#include "FOC.h"
#include "AS5600.h"
#include "sys.h"
#include "main.h"

#define Xlimit 300
/*******************************************
SysTick��ʼ��(ģ��micros������ʼ��)��

��ע��     
	1.��0xFFFFFF��0ѭ������
	2.�������޷���ʹ��delay��ʱ����
*******************************************/
void Systick_CountMode(void)
{
	SysTick->LOAD = 0xFFFFFF-1;
	SysTick->VAL  = 0;
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
}
/*******************************************
��Ƕ���⣺

��ע��     
	1.     ��Ƕ�      =   ��е�Ƕ�  *  ������
	2._electricalAngle = shaft_angle * pole_pairs
*******************************************/
float _electricalAngle(void)
{
	return _normalizeAngle((float)(FOC_Parame.DIR * FOC_Parame.PP) * get_Angle_2PI()-FOC_Parame.zero_electric_angle);
}

/*******************************************
�Ƕȹ�һ������:
*******************************************/
float _normalizeAngle(float angle)
{
	float a = fmod(angle,2*PI);
	return a >= 0 ? a : (a+ 2*PI);
	//��Ŀ���������ʽ��condition ? expr1 : expr2
	//����,conditionʽҪ��ֵ����������ʽ,�����������,�򷵻� expr1 ��ֵ�����Խ���Ŀ���������if-else�ļ���ʽ
}

/*******************************************
PWM�������:
*******************************************/
void setPWM(float Ua,float Ub,float Uc)
{
	//����޷�
	Ua = _constrain(Ua,0.0f,FOC_Parame.voltage_limit);
	Ub = _constrain(Ub,0.0f,FOC_Parame.voltage_limit);
	Uc = _constrain(Uc,0.0f,FOC_Parame.voltage_limit);
	//ռ�ձȼ���+����޷�
	FOC_Parame.dc_a = _constrain(Ua/FOC_Parame.voltage_power_supply,0.0f,1.0f);
	FOC_Parame.dc_b = _constrain(Ub/FOC_Parame.voltage_power_supply,0.0f,1.0f);
	FOC_Parame.dc_c = _constrain(Uc/FOC_Parame.voltage_power_supply,0.0f,1.0f);
	//PWM��ֵ
	PWM_SetCompare1(FOC_Parame.dc_a*2400);
	PWM_SetCompare2(FOC_Parame.dc_b*2400);
	PWM_SetCompare3(FOC_Parame.dc_c*2400);
}
/*******************************************
���ؿ���:
*******************************************/
void setTorque(float Uq,float angle_el)
{
	//�����޷�
	Uq = _constrain(Uq,-FOC_Parame.voltage_power_supply/2,FOC_Parame.voltage_power_supply/2);
	/*float Ud=0;*/
	angle_el = _normalizeAngle(angle_el);
	//������任
	FOC_Parame.Ualpha = -Uq*sin(angle_el);
	FOC_Parame.Ubeta  = Uq*cos(angle_el); 
	//��������任
	FOC_Parame.Ua = FOC_Parame.Ualpha + FOC_Parame.voltage_power_supply/2;
	FOC_Parame.Ub = (sqrt(3)*FOC_Parame.Ubeta-FOC_Parame.Ualpha)/2 + FOC_Parame.voltage_power_supply/2;
	FOC_Parame.Uc = (-FOC_Parame.Ualpha-sqrt(3)*FOC_Parame.Ubeta)/2 + FOC_Parame.voltage_power_supply/2;
	//PWM��ֵ
	setPWM(FOC_Parame.Ua,FOC_Parame.Ub,FOC_Parame.Uc);
}

/*******************************************
SVPWM����:
*******************************************/

void SVPWM_Generate(float Uq, float angle_el)
{
	//�����޷�
	Uq = _constrain(Uq,-FOC_Parame.voltage_power_supply/2,FOC_Parame.voltage_power_supply/2);
	/*float Ud=0;*/
	angle_el = _normalizeAngle(angle_el);
	//������任
	FOC_Parame.Ualpha = -Uq*sin(angle_el);
	FOC_Parame.Ubeta  = Uq*cos(angle_el); 

    // 1. ��������
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

    // 2. �������ʸ������ʱ��
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

    // 3. �޷�����
    T1 = _constrain(T1, 0.0f, 1.0f * SVPWM_Parame.Tpwm);
    T2 = _constrain(T2, 0.0f, 1.0f * SVPWM_Parame.Tpwm);
	float Temp = T1 + T2;
	if(Temp > SVPWM_Parame.Tpwm)
	{
		T1 = T1/Temp * SVPWM_Parame.Tpwm;
		T2 = T2/Temp * SVPWM_Parame.Tpwm;
	}
    float T0 = 1.0f * SVPWM_Parame.Tpwm - T1 - T2;

    // 4. ����ռ�ձȣ��������ģʽ��
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
    // 5. ת��Ϊ��ʱ���Ƚ�ֵ������PWM����Ϊ�������ģʽ��
    SVPWM_Parame.cmpA = (uint32_t)((SVPWM_Parame.Ta) /2);
    SVPWM_Parame.cmpB = (uint32_t)((SVPWM_Parame.Tb) /2);
    SVPWM_Parame.cmpC = (uint32_t)((SVPWM_Parame.Tc) /2);
	
	PWM_SetCompare1(SVPWM_Parame.cmpA);
	PWM_SetCompare2(SVPWM_Parame.cmpB);
	PWM_SetCompare3(SVPWM_Parame.cmpC);	
}

/*******************************************
FOC���Ƴ�ʼ��:
*******************************************/
void FOC_Init(float power_supply)
{
	FOC_Parame.voltage_power_supply = power_supply;
	
	PWMFOC_Init();//3·PMW����ʼ��(30000HZ)
	
	NVIC_Config();//�ж����ȼ�����
	
	PID_init();//��ʼ��pid����
}
/*******************************************
FOC���������ݳ�ʼ��:
*******************************************/
void FOC_AS5600_Init(int _PP,int _DIR)
{
	AS5600_Init();//AS5600ģ��I2C��ʼ��
	
	FOC_Parame.PP=_PP;
	FOC_Parame.DIR=_DIR;
	setTorque(3, _3PI_2);
	
	Delay_ms(1000);
	Delay_ms(1000);//�ȴ�����׼�����

	FOC_Parame.zero_electric_angle = _electricalAngle();
	setTorque(0, _3PI_2);
	
	FOC_Parame.Sensor_Speed = get_Speed();//�ٶȳ�ʼֵ����
}

float round_float_5dec(float num) 
{
    int32_t scaled = (int32_t)(num * 100000.0f + 0.5f);
    return (float)scaled / 100000.0f;
}

/***********************************************
����Ƕȿ���:(rad)
***********************************************/
void Set_Angle(float Angle)
{
	//�Ƕȶ�ȡ
	//�Ƕȿ���
	float temp = round_float_5dec((Angle - FOC_Parame.DIR*FOC_Parame.Sensor_Angle)*180/PI);
	if(temp <5 && temp >-5)
	{
		temp = 0;
	}
	FOC_Parame.Speed_target = Angle_Control(temp);
	
	if(FOC_Parame.Speed_target>Xlimit)FOC_Parame.Speed_target=Xlimit;//�ǶȻ���������޷�
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
	//�Ƕȴ�ӡ
	//printf("%.2f,%.2f\n",Sensor_Angle,Angle_target);
}
/***********************************************
����ٶȿ���:(rad/s)
***********************************************/
void Set_Speed(float Speed)
{
	//�ٶȶ�ȡ
	//Sensor_Speed = get_Speed();
	//�ٶȿ���
	float temp = round_float_5dec(Speed - FOC_Parame.Sensor_Speed);
	
	Speed_Out = Speed_Control(temp);
	XianFu();
	if(Speed == 0)
	{
		Speed_Out = 0;
	}
	
	//setTorque(Speed_Out,_electricalAngle());
	//SVPWM_Generate(Speed_Out,_electricalAngle());
	//�ٶȴ�ӡ
	//printf("%.2f,%.2f\n",Sensor_Speed,Speed_target);
}
void Set_Speed_loop(float loop_speed)
{
	//�ٶȶ�ȡ
	//Sensor_Speed = get_Speed();
	//�ٶȿ���
	//float loop_angle = _normalizeAngle((float)(FOC_Parame.DIR * FOC_Parame.PP) * loop_speed-FOC_Parame.zero_electric_angle);
	FOC_Parame.Angle_loop += loop_speed;
	float loop_angle = _normalizeAngle((float)(FOC_Parame.DIR * FOC_Parame.PP) * FOC_Parame.Angle_loop-FOC_Parame.zero_electric_angle);	
	SVPWM_Generate(FOC_Parame.voltage_limit,loop_angle);
	//�ٶȴ�ӡ
	//printf("%.2f,%.2f\n",Sensor_Speed,Speed_target);
}
