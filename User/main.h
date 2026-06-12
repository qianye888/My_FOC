#ifndef  _MAIN_H
#define  _MAIN_H

#include "sys.h" 

extern int8_t temp_a;
extern int8_t temp_s;
extern uint16_t i;
extern uint16_t task_10;
extern uint16_t task_20;
extern uint8_t KeyNum[8];
extern uint8_t KeyChan[8];
extern uint8_t motor_on;

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

extern uint8_t Control_10msFlag;


extern uint16_t pwm_a;
extern uint16_t pwm_b;
extern uint16_t pwm_c;

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

