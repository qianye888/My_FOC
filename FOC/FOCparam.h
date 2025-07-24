#ifndef __FOCPARAM_H_
#define __FOCPARAM_H_

#include "sys.h"

typedef struct//����pid�ṹ��
{
	float TarValue;//����Ŀ��ֵ
	float ActValue;//������ʵֵ
	
	float Err;//����ƫ��ֵ
	float Err_last_1;//������һ��ƫ��ֵ
	float Err_last_2;//����������ƫ��ֵ
	float Kp,Ki,Kd;//������������֣�΢��
	float Voltage;//�����ѹֵ
	float Integral;//�������ֵ
    float Int_Limit;
    float OUT_Limit;
	float OUT;
}PID;

typedef struct//����svpwm�ṹ��
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


typedef struct//����FOC�ṹ��
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
	int PP;	//������
	int DIR;	//��ˢ�����ƫ��ת����
}FOC;

extern SVPWM SVPWM_Parame;
extern FOC FOC_Parame;//����FOC����
extern PID pid_angle;//�����ٶȻ�pid
extern PID pid_speed;//������뻷pid

void PID_init(void);//PID��ʼ��
void FOCPARAM_init(void);
void SVPWMPARAM_init(void);

#endif
