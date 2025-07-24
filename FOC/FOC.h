#ifndef __FOC_H
#define __FOC_H

#include "sys.h"

#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))


void Systick_CountMode(void);
float _electricalAngle(void);
float _normalizeAngle(float angle);
void setPWM(float Ua,float Ub,float Uc);
void setTorque(float Uq,float angle_el);
void FOC_Init(float power_supply);
void FOC_AS5600_Init(int _PP,int _DIR);
void Set_Angle(float Angle);
void Set_Speed(float Speed);
void Set_Speed_loop(float loop_speed);
void SVPWM_Generate(float Uq, float angle_el);
	
#endif
