/*
 * File: FOC_Motor.h
 *
 * Code generated for Simulink model 'FOC_Motor'.
 *
 * Model version                  : 12.38
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Mon Apr 14 21:31:43 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: NXP->Cortex-M0/M0+
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

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define FOC_Motor_M                    (rtM)

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
    real_T X;
}
D_Work;

/* data stores shared across model instances, for system '<Root>' */
typedef struct
{
    uint16_T Theta_Inte;               /* '<Root>/Data Store Memory15' */
    uint16_T Theta_zero;               /* '<Root>/Data Store Memory16' */
}
SharedDSM;

/* Constant parameters (default storage) */
typedef struct
{
    /* Computed Parameter: Sector_Lookup_Table_table
     * Referenced by: '<S7>/Sector_Lookup_Table'
     */
    uint8_T Sector_Lookup_Table_table[7];
}
ConstParam;

/* External inputs (root inport signals with default storage) */
typedef struct
{
    int16_T Ud;                        /* '<Root>/Ud' */
    int16_T Uq;                        /* '<Root>/Uq' */
}
ExternalInputs;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
    real_T PWM_Duty_U;                 /* '<Root>/PWM_Duty_U' */
    real_T PWM_Duty_V;                 /* '<Root>/PWM_Duty_V' */
    real_T PWM_Duty_W;                 /* '<Root>/PWM_Duty_W' */
}
ExternalOutputs;

/* Real-time Model Data Structure */
struct tag_RTM
{
    const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern D_Work rtDWork;

/* data stores shared across model instances */
extern SharedDSM rtSharedDSM;          /* '<Root>/Data Store Memory15' */

/* External inputs (root inport signals with default storage) */
extern ExternalInputs rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExternalOutputs rtY;

/* Constant parameters (default storage) */
extern const ConstParam rtConstP;

/* Model entry point functions */
extern void FOC_Motor_initialize(void);
extern void FOC_Motor_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S3>/Scope' : Unused code path elimination
 * Block '<S6>/Scope' : Unused code path elimination
 * Block '<S6>/Scope1' : Unused code path elimination
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
 * '<S4>'   : 'FOC_Motor/FOC/SVPWM'
 * '<S5>'   : 'FOC_Motor/FOC/electri_angle_zero2'
 * '<S6>'   : 'FOC_Motor/FOC/SVPWM/Calculate_Phase_Voltages'
 * '<S7>'   : 'FOC_Motor/FOC/SVPWM/Sector Caculate'
 * '<S8>'   : 'FOC_Motor/FOC/SVPWM/Calculate_Phase_Voltages/CCR'
 * '<S9>'   : 'FOC_Motor/FOC/SVPWM/Calculate_Phase_Voltages/矢量作用时间'
 * '<S10>'  : 'FOC_Motor/FOC/SVPWM/Sector Caculate/Compare To Constant'
 * '<S11>'  : 'FOC_Motor/FOC/SVPWM/Sector Caculate/Compare To Constant1'
 * '<S12>'  : 'FOC_Motor/FOC/SVPWM/Sector Caculate/Compare To Constant2'
 */
#endif                                 /* RTW_HEADER_FOC_Motor_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
