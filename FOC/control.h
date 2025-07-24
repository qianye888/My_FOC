#ifndef  _CONTROL_H
#define  _CONTROL_H

extern float Angle_Out;
extern float Speed_Out;

//void TIM3_IRQHandler(void);
float Angle_Control(float Angle_Err);
float Speed_Control(float Speed_Err);
void XianFu(void);
//void PID_Control(PID* pid);

#endif
