#ifndef __FIELD_WEAKENING_H
#define __FIELD_WEAKENING_H

#include "sys.h"

// 弱磁控制状态
// enabled: 弱磁是否启用
// target_voltage: 目标电压幅值上限
// min_ud: 允许注入的最小 d 轴电压
// ud_limit: d 轴电压限幅
// uq_limit: q 轴电压限幅
// voltage_margin: 母线电压裕量，避免顶到调制边界
// ud_ref / uq_ref: 弱磁模块输出的参考量
// voltage_actual: 当前估算电压幅值
// voltage_error: 电压裕量误差
// speed_threshold: 进入弱磁的速度阈值
// voltage_threshold: 进入弱磁的电压阈值
typedef struct
{
    uint8_t enabled;
    float target_voltage;
    float min_ud;
    float ud_limit;
    float uq_limit;
    float voltage_margin;
    float ud_ref;
    float uq_ref;
    float voltage_actual;
    float voltage_error;
    float speed_threshold;
    float voltage_threshold;
} FieldWeakening;

extern FieldWeakening FieldWeakening_Parame;

void FieldWeakening_Init(void);
void FieldWeakening_Enable(uint8_t enable);
void FieldWeakening_SetLimits(float uq_limit, float ud_limit);
void FieldWeakening_SetTargets(float speed_threshold, float voltage_threshold, float voltage_margin);
void FieldWeakening_Update(float speed_target, float speed_feedback, float uq_request, float voltage_limit);
float FieldWeakening_GetUd(void);
float FieldWeakening_GetUq(void);

#endif
