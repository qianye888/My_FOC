#ifndef __DATAIF_H
#define __DATAIF_H

#include "stdio.h"	
#include "sys.h" 

typedef struct
{
	float fif;
	float out_prev;
}low_pass;
extern low_pass Low_pass[10];
extern uint32_t loop_mbd;
extern uint32_t a;

float LOWPass_Filter(float pre_in,uint8_t index,float fif);
void MBD_APIIN(void);
void MBD_APIOUT(void);
void MBDSV_APIIN(void);
#endif
