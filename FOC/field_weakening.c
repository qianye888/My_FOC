#include "field_weakening.h"

FieldWeakening FieldWeakening_Parame;

void FieldWeakening_Init(void)
{
    FieldWeakening_Parame.enabled = 0;
    FieldWeakening_Parame.target_voltage = 0.0f;
    FieldWeakening_Parame.min_ud = -2.0f;
    FieldWeakening_Parame.ud_limit = 0.0f;
    FieldWeakening_Parame.uq_limit = 0.0f;
    FieldWeakening_Parame.voltage_margin = 0.5f;
    FieldWeakening_Parame.ud_ref = 0.0f;
    FieldWeakening_Parame.uq_ref = 0.0f;
    FieldWeakening_Parame.voltage_actual = 0.0f;
    FieldWeakening_Parame.voltage_error = 0.0f;
    FieldWeakening_Parame.speed_threshold = 0.0f;
    FieldWeakening_Parame.voltage_threshold = 0.0f;
}

void FieldWeakening_Enable(uint8_t enable)
{
    FieldWeakening_Parame.enabled = enable;
}

void FieldWeakening_SetLimits(float uq_limit, float ud_limit)
{
    FieldWeakening_Parame.uq_limit = uq_limit;
    FieldWeakening_Parame.ud_limit = ud_limit;
}

void FieldWeakening_SetTargets(float speed_threshold, float voltage_threshold, float voltage_margin)
{
    FieldWeakening_Parame.speed_threshold = speed_threshold;
    FieldWeakening_Parame.voltage_threshold = voltage_threshold;
    FieldWeakening_Parame.voltage_margin = voltage_margin;
}

void FieldWeakening_Update(float speed_target, float speed_feedback, float uq_request, float voltage_limit)
{
    float speed_abs = speed_target >= 0.0f ? speed_target : -speed_target;
    float feedback_abs = speed_feedback >= 0.0f ? speed_feedback : -speed_feedback;
    float uq_abs = uq_request >= 0.0f ? uq_request : -uq_request;
    float allowed_voltage = voltage_limit - FieldWeakening_Parame.voltage_margin;
    float speed_error = speed_abs - feedback_abs;

    FieldWeakening_Parame.target_voltage = allowed_voltage;
    FieldWeakening_Parame.voltage_actual = uq_abs;
    FieldWeakening_Parame.voltage_error = allowed_voltage - uq_abs;

    FieldWeakening_Parame.ud_ref = 0.0f;
    FieldWeakening_Parame.uq_ref = uq_request;

    if(FieldWeakening_Parame.enabled == 0)
    {
        return;
    }

    if(allowed_voltage < 0.0f)
    {
        allowed_voltage = 0.0f;
    }

    if((speed_abs <= FieldWeakening_Parame.speed_threshold) && (uq_abs <= FieldWeakening_Parame.voltage_threshold))
    {
        return;
    }

    if((uq_abs > allowed_voltage) || (speed_error > 0.0f))
    {
        float ud_ref = -(uq_abs - allowed_voltage);
        ud_ref = _constrain(ud_ref, FieldWeakening_Parame.min_ud, 0.0f);
        FieldWeakening_Parame.ud_ref = ud_ref;
        FieldWeakening_Parame.uq_ref = _constrain(uq_request, -FieldWeakening_Parame.uq_limit, FieldWeakening_Parame.uq_limit);
    }
}

float FieldWeakening_GetUd(void)
{
    return FieldWeakening_Parame.ud_ref;
}

float FieldWeakening_GetUq(void)
{
    return FieldWeakening_Parame.uq_ref;
}
