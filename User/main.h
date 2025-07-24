#ifndef  _MAIN_H
#define  _MAIN_H

#include "sys.h" 

uint16_t i = 0;
uint16_t task_10 = 0;
uint16_t task_20 = 0;
uint8_t KeyNum;
#define B0  1
#define B1  2
#define A1  3
#define pwmafil    3
#define pwmbfil    4
#define pwmcfil    5

#define Uafil    6
#define Ubfil    7
#define Ucfil    8

#define PWM_A    B0  
#define PWM_B    B1  
#define PWM_C    A1  
extern float full_rotations;

uint8_t Control_10msFlag = 0;
uint8_t Control_20msFlag = 0;

uint16_t pwm_a = 0;
uint16_t pwm_b = 0;
uint16_t pwm_c = 0;

void Bsw_Init(void);
void OLEDDeal(void);
void task_10ms(void);
void task_20ms(void);
void KeyDeal(void);
void LEDDeal(void);
void ADCDeal(void);
void UsartDeal(void);
void Set_MBU_loop(float loop_sp);


#endif

