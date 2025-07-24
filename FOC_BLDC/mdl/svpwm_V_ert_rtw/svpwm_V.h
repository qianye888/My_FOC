/*
 * File: svpwm_V.h
 *
 * Code generated for Simulink model 'svpwm_V'.
 *
 * Model version                  : 19.0
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Sat Apr 26 10:36:40 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_svpwm_V_h_
#define RTW_HEADER_svpwm_V_h_
#ifndef svpwm_V_COMMON_INCLUDES_
#define svpwm_V_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* svpwm_V_COMMON_INCLUDES_ */

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint16_T Spwm_a;                /* '<Root>/pwm_a' */
extern uint16_T Spwm_b;                /* '<Root>/pwm_b' */
extern uint16_T Spwm_c;                /* '<Root>/pwm_c' */
extern real32_T voltage_power_supply;  /* '<Root>/voltage_power_supply' */
extern real32_T OutUb;                 /* '<S5>/Subtract' */
extern real32_T OutUa;                 /* '<S4>/Subtract' */
extern real32_T OutUc;                 /* '<S6>/Subtract' */

/* Model entry point functions */
extern void svpwm_V_initialize(void);
extern void svpwm_V_step(void);

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
 * '<Root>' : 'svpwm_V'
 * '<S1>'   : 'svpwm_V/Compare To Constant'
 * '<S2>'   : 'svpwm_V/Compare To Constant1'
 * '<S3>'   : 'svpwm_V/Compare To Constant2'
 * '<S4>'   : 'svpwm_V/Ua '
 * '<S5>'   : 'svpwm_V/Ub '
 * '<S6>'   : 'svpwm_V/Uc  '
 */
#endif                                 /* RTW_HEADER_svpwm_V_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
