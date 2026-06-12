#ifndef __KEY_H
#define __KEY_H

void Key_Tick(void);
uint8_t Key_GetCH(uint8_t ch);
const uint8_t* Key_GetState(void);

extern uint8_t Key_Num[8];
extern uint8_t Key_Chan[8];
#endif
