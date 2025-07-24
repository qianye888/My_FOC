/*
 * File: FOC_Motor.h
 *
 * Code generated for Simulink model 'FOC_Motor'.
 *
 * Model version                  : 12.40
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Tue Apr 29 18:57:09 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_Motor_h_
#define RTW_HEADER_FOC_Motor_h_
#ifndef FOC_Motor_COMMON_INCLUDES_
#define FOC_Motor_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Motor_COMMON_INCLUDES_ */

#include "FOC_Motor_types.h"

/* Includes for objects with custom storage classes */
#include "EHB_MOTOR.h"

/* user code (top of header file) */
#define MCU_IDLE_ST                    0
#define MCU_INIT_ST                    1
#define MCU_START_ST                   2
#define MCU_RUN_ST                     3
#define MCU_FAULT_ST                   4
#define MCU_WAIT_ST                    5

// MCU_IDLE_ST = 0;
// MCU_INIT_ST = 1;
// MCU_START_ST = 2;
// MCU_RUN_ST = 3;
// MCU_FAULT_ST = 4;
// MCU_WAIT_ST = 5;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct
{
    int64_T i;
    int64_T i1;
    real32_T UnitDelay_DSTATE;         /* '<S18>/Unit Delay' */
    real32_T UnitDelay_DSTATE_h;       /* '<S17>/Unit Delay' */
    real32_T DataTypeConversion;       /* '<S6>/Data Type Conversion' */
    real32_T Add1;                     /* '<S18>/Add1' */
    int32_T UnitDelay1_DSTATE;         /* '<S15>/Unit Delay1' */
    int32_T UnitDelay1_DSTATE_g;       /* '<S17>/Unit Delay1' */
    int32_T UnitDelay_DSTATE_j;        /* '<S20>/Unit Delay' */
    int32_T UnitDelay1_DSTATE_h;       /* '<S20>/Unit Delay1' */
    int32_T UnitDelay2_DSTATE;         /* '<S20>/Unit Delay2' */
    int32_T UnitDelay3_DSTATE;         /* '<S20>/Unit Delay3' */
    int32_T UnitDelay4_DSTATE;         /* '<S20>/Unit Delay4' */
    int32_T UnitDelay5_DSTATE;         /* '<S20>/Unit Delay5' */
    int32_T UnitDelay6_DSTATE;         /* '<S20>/Unit Delay6' */
    int32_T UnitDelay7_DSTATE;         /* '<S20>/Unit Delay7' */
    int32_T UnitDelay_DSTATE_b;        /* '<S21>/Unit Delay' */
    int32_T UnitDelay_DSTATE_l;        /* '<S16>/Unit Delay' */
    int32_T UnitDelay1_DSTATE_p;       /* '<S16>/Unit Delay1' */
    int32_T UnitDelay_DSTATE_a;        /* '<S19>/Unit Delay' */
    int32_T Add2_e;                    /* '<S16>/Add2' */
    int32_T Saturation;                /* '<S16>/Saturation' */
    int32_T Add1_d;                    /* '<S15>/Add1' */
    int32_T UnitDelay_i;               /* '<S20>/Unit Delay' */
    int32_T UnitDelay1;                /* '<S20>/Unit Delay1' */
    int16_T UnitDelay_DSTATE_ln;       /* '<S15>/Unit Delay' */
}
D_Work;

/* Constant parameters (default storage) */
typedef struct
{
    /* Computed Parameter: Sector_Lookup_Table_table
     * Referenced by: '<S10>/Sector_Lookup_Table'
     */
    uint8_T Sector_Lookup_Table_table[7];
}
ConstParam;

/* External inputs (root inport signals with default storage) */
typedef struct
{
    real32_T Tar_speed;                /* '<Root>/Tar_speed' */
    real32_T Speed_kp;                 /* '<Root>/Speed_kp' */
    uint16_T Theta_Inte;               /* '<Root>/Theta_Inte' */
    uint16_T Theta_zero;               /* '<Root>/Theta_zero' */
    real32_T Speed_ki;                 /* '<Root>/Speed_ki' */
    real32_T Speed_kd;                 /* '<Root>/Speed_kd' */
}
ExternalInputs;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
    uint16_T PWM_Duty_U;               /* '<Root>/PWM_Duty_U' */
    uint16_T PWM_Duty_V;               /* '<Root>/PWM_Duty_V' */
    uint16_T PWM_Duty_W;               /* '<Root>/PWM_Duty_W' */
    uint8_T Section;                   /* '<Root>/Section' */
    real32_T Act_speed;                /* '<Root>/Act_speed' */
}
ExternalOutputs;

/* Block signals and states (default storage) */
extern D_Work rtDWork;

/* External inputs (root inport signals with default storage) */
extern ExternalInputs rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExternalOutputs rtY;

/* Constant parameters (default storage) */
extern const ConstParam rtConstP;

/* Model entry point functions */
extern void FOC_Motor_initialize(void);
extern void FOC_Motor_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S8>/Scope' : Unused code path elimination
 * Block '<S8>/Scope1' : Unused code path elimination
 * Block '<S8>/Scope2' : Unused code path elimination
 * Block '<S9>/Scope' : Unused code path elimination
 * Block '<S5>/Scope' : Unused code path elimination
 * Block '<S10>/Scope' : Unused code path elimination
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S15>/Scope1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FOC_Motor'
 * '<S1>'   : 'FOC_Motor/FOC'
 * '<S2>'   : 'FOC_Motor/FOC/Function_LookUp'
 * '<S3>'   : 'FOC_Motor/FOC/Inverse_Park_Transform'
 * '<S4>'   : 'FOC_Motor/FOC/PWM scaling'
 * '<S5>'   : 'FOC_Motor/FOC/SVPWM'
 * '<S6>'   : 'FOC_Motor/FOC/Subsystem'
 * '<S7>'   : 'FOC_Motor/FOC/electri_angle_zero2'
 * '<S8>'   : 'FOC_Motor/FOC/SVPWM/Calculate_Phase_Voltages'
 * '<S9>'   : 'FOC_Motor/FOC/SVPWM/Calculate_Phase_Voltages1'
 * '<S10>'  : 'FOC_Motor/FOC/SVPWM/Sector Caculate'
 * '<S11>'  : 'FOC_Motor/FOC/SVPWM/Calculate_Phase_Voltages/Compare To Constant'
 * '<S12>'  : 'FOC_Motor/FOC/SVPWM/Sector Caculate/Compare_VA_To_Zero'
 * '<S13>'  : 'FOC_Motor/FOC/SVPWM/Sector Caculate/Compare_VB_To_Zero'
 * '<S14>'  : 'FOC_Motor/FOC/SVPWM/Sector Caculate/Compare_VC_To_Zero'
 * '<S15>'  : 'FOC_Motor/FOC/Subsystem/electri_angle_zero1'
 * '<S16>'  : 'FOC_Motor/FOC/Subsystem/electri_angle_zero2'
 * '<S17>'  : 'FOC_Motor/FOC/Subsystem/electri_angle_zero3'
 * '<S18>'  : 'FOC_Motor/FOC/Subsystem/electri_angle_zero1/LOWPASS'
 * '<S19>'  : 'FOC_Motor/FOC/Subsystem/electri_angle_zero2/LOWPASS'
 * '<S20>'  : 'FOC_Motor/FOC/Subsystem/electri_angle_zero3/AV'
 * '<S21>'  : 'FOC_Motor/FOC/Subsystem/electri_angle_zero3/LOWPASS'
 */
#endif                                 /* RTW_HEADER_FOC_Motor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
