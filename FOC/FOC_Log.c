#include "FOC_Log.h"
#include "FOCparam.h"
#include "control.h"
#include "Serial.h"
#include <math.h>

static FOC_LogSample foc_log_latest;
static uint8_t foc_log_enabled;
static uint8_t foc_log_header_printed;
static uint8_t foc_log_ready;
static uint16_t foc_log_divider;
static uint16_t foc_log_count;

void FOC_LogInit(void)
{
	foc_log_enabled = 1;
	foc_log_header_printed = 0;
	foc_log_ready = 0;
	foc_log_divider = FOC_LOG_DEFAULT_DIVIDER;
	foc_log_count = 0;
}

void FOC_LogEnable(uint8_t enable)
{
	foc_log_enabled = enable ? 1 : 0;
}

void FOC_LogSetDivider(uint16_t divider)
{
	if(divider == 0)
	{
		divider = 1;
	}
	foc_log_divider = divider;
}

void FOC_LogCapture(uint32_t time_ms)
{
	float alpha = FOC_Parame.Ualpha;
	float beta = FOC_Parame.Ubeta;

	if(foc_log_enabled == 0)
	{
		return;
	}

	foc_log_count++;
	if(foc_log_count < foc_log_divider)
	{
		return;
	}
	foc_log_count = 0;

	foc_log_latest.time_ms = time_ms;
	foc_log_latest.angle_cmd = FOC_Parame.Angle_target;
	foc_log_latest.angle_fb = FOC_Parame.Sensor_Angle;
	foc_log_latest.speed_cmd = FOC_Parame.Speed_target;
	foc_log_latest.speed_fb = FOC_Parame.Sensor_Speed;
	foc_log_latest.uq_cmd = Speed_Out;
	foc_log_latest.ud_cmd = FOC_Parame.field_weakening_ud_ref;
	foc_log_latest.pwm_amp = sqrt(alpha * alpha + beta * beta);
	foc_log_latest.cmp_a = SVPWM_Parame.cmpA;
	foc_log_latest.cmp_b = SVPWM_Parame.cmpB;
	foc_log_latest.cmp_c = SVPWM_Parame.cmpC;
	foc_log_ready = 1;
}

void FOC_LogPrintHeader(void)
{
	Serial_Printf("time_ms,angle_cmd,angle_fb,speed_cmd,speed_fb,uq_cmd,ud_cmd,pwm_amp,cmp_a,cmp_b,cmp_c\r\n");
	foc_log_header_printed = 1;
}

void FOC_LogPrintLatestCsv(void)
{
	if(foc_log_enabled == 0)
	{
		return;
	}
	if(foc_log_ready == 0)
	{
		return;
	}

	if(foc_log_header_printed == 0)
	{
		FOC_LogPrintHeader();
	}

	Serial_Printf("%lu,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%.5f,%lu,%lu,%lu\r\n",
		(unsigned long)foc_log_latest.time_ms,
		foc_log_latest.angle_cmd,
		foc_log_latest.angle_fb,
		foc_log_latest.speed_cmd,
		foc_log_latest.speed_fb,
		foc_log_latest.uq_cmd,
		foc_log_latest.ud_cmd,
		foc_log_latest.pwm_amp,
		(unsigned long)foc_log_latest.cmp_a,
		(unsigned long)foc_log_latest.cmp_b,
		(unsigned long)foc_log_latest.cmp_c);
	foc_log_ready = 0;
}
