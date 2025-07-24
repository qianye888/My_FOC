/*
 * File: EHB_MOTOR.h
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

#ifndef RTW_HEADER_EHB_MOTOR_h_
#define RTW_HEADER_EHB_MOTOR_h_
#include "rtwtypes.h"
#include "FOC_Motor_types.h"

/* Exported data declaration */

/* Declaration for custom storage class: Global */
extern int16_T Cos_Table[100];         /* Referenced by: '<S2>/Cos_LookUp' */
extern real32_T Sin_BreakPoint[100];   /* Referenced by:
                                        * '<S2>/Cos_LookUp'
                                        * '<S2>/Sin_LookUp'
                                        */
extern int16_T Sin_Table[100];         /* Referenced by: '<S2>/Sin_LookUp' */

#endif                                 /* RTW_HEADER_EHB_MOTOR_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
