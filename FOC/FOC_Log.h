#ifndef __FOC_LOG_H
#define __FOC_LOG_H

#include "sys.h"

#define FOC_LOG_DEFAULT_DIVIDER 5

typedef struct
{
	uint32_t time_ms;
	float angle_cmd;
	float angle_fb;
	float speed_cmd;
	float speed_fb;
	float uq_cmd;
	float ud_cmd;
	float pwm_amp;
	uint32_t cmp_a;
	uint32_t cmp_b;
	uint32_t cmp_c;
}FOC_LogSample;

void FOC_LogInit(void);
void FOC_LogEnable(uint8_t enable);
void FOC_LogSetDivider(uint16_t divider);
void FOC_LogCapture(uint32_t time_ms);
void FOC_LogPrintLatestCsv(void);
void FOC_LogPrintHeader(void);

#endif
