/*
 * File: svpwm_V.c
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

#include "svpwm_V.h"
#include "rtwtypes.h"

/* Exported block signals */
uint16_T Spwm_a;                       /* '<Root>/pwm_a' */
uint16_T Spwm_b;                       /* '<Root>/pwm_b' */
uint16_T Spwm_c;                       /* '<Root>/pwm_c' */
real32_T voltage_power_supply;         /* '<Root>/voltage_power_supply' */
real32_T OutUb;                        /* '<S5>/Subtract' */
real32_T OutUa;                        /* '<S4>/Subtract' */
real32_T OutUc;                        /* '<S6>/Subtract' */

/* Model step function */
void svpwm_V_step(void)
{
  boolean_T OutUb_tmp;
  boolean_T OutUb_tmp_0;
  boolean_T rtb_Compare;
  boolean_T rtb_Compare_c;
  boolean_T rtb_LogicalOperator2_tmp;
  boolean_T rtb_LogicalOperator4;
  boolean_T rtb_LogicalOperator7;

  /* RelationalOperator: '<S1>/Compare' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/pwm_a'
   */
  rtb_Compare = (Spwm_a >= 2048);

  /* RelationalOperator: '<S2>/Compare' incorporates:
   *  Constant: '<S2>/Constant'
   *  Inport: '<Root>/pwm_b'
   */
  rtb_Compare_c = (Spwm_b >= 2048);

  /* RelationalOperator: '<S3>/Compare' incorporates:
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/pwm_c'
   */
  rtb_LogicalOperator4 = (Spwm_c >= 2048);

  /* Logic: '<S5>/Logical Operator1' */
  rtb_LogicalOperator7 = rtb_Compare ^ rtb_LogicalOperator4;

  /* Logic: '<S5>/Logical Operator3' incorporates:
   *  Logic: '<S4>/Logical Operator5'
   *  Logic: '<S6>/Logical Operator5'
   */
  rtb_LogicalOperator2_tmp = !rtb_Compare_c;

  /* Logic: '<S5>/Logical Operator5' incorporates:
   *  Logic: '<S4>/Logical Operator3'
   *  Logic: '<S6>/Logical Operator6'
   */
  OutUb_tmp = !rtb_Compare;

  /* Logic: '<S5>/Logical Operator6' incorporates:
   *  Logic: '<S4>/Logical Operator6'
   *  Logic: '<S6>/Logical Operator3'
   */
  OutUb_tmp_0 = !rtb_LogicalOperator4;

  /* Sum: '<S5>/Subtract' incorporates:
   *  Gain: '<S5>/Gain'
   *  Gain: '<S5>/Gain1'
   *  Gain: '<S5>/Gain2'
   *  Gain: '<S5>/Gain3'
   *  Inport: '<Root>/voltage_power_supply'
   *  Logic: '<S5>/Logical Operator'
   *  Logic: '<S5>/Logical Operator2'
   *  Logic: '<S5>/Logical Operator3'
   *  Logic: '<S5>/Logical Operator4'
   *  Logic: '<S5>/Logical Operator5'
   *  Logic: '<S5>/Logical Operator6'
   *  Logic: '<S5>/Logical Operator7'
   *  Product: '<S5>/Product'
   *  Product: '<S5>/Product1'
   *  Product: '<S5>/Product2'
   *  Product: '<S5>/Product3'
   */
  OutUb = (((real32_T)(rtb_Compare_c && rtb_LogicalOperator7) * (0.333333343F *
             voltage_power_supply) + (real32_T)(rtb_LogicalOperator2_tmp &&
             rtb_LogicalOperator7) * (-0.333333343F * voltage_power_supply)) +
           (real32_T)(rtb_Compare_c && OutUb_tmp && OutUb_tmp_0) * (0.666666687F
            * voltage_power_supply)) + (real32_T)(rtb_LogicalOperator2_tmp &&
    rtb_Compare && rtb_LogicalOperator4) * (-0.666666687F * voltage_power_supply);

  /* Logic: '<S4>/Logical Operator1' */
  rtb_LogicalOperator7 = rtb_Compare_c ^ rtb_LogicalOperator4;

  /* Sum: '<S4>/Subtract' incorporates:
   *  Gain: '<S4>/Gain'
   *  Gain: '<S4>/Gain1'
   *  Gain: '<S4>/Gain2'
   *  Gain: '<S4>/Gain3'
   *  Inport: '<Root>/voltage_power_supply'
   *  Logic: '<S4>/Logical Operator'
   *  Logic: '<S4>/Logical Operator2'
   *  Logic: '<S4>/Logical Operator4'
   *  Logic: '<S4>/Logical Operator7'
   *  Product: '<S4>/Product'
   *  Product: '<S4>/Product1'
   *  Product: '<S4>/Product2'
   *  Product: '<S4>/Product3'
   */
  OutUa = (((real32_T)(rtb_Compare && rtb_LogicalOperator7) * (0.333333343F *
             voltage_power_supply) + (real32_T)(OutUb_tmp &&
             rtb_LogicalOperator7) * (-0.333333343F * voltage_power_supply)) +
           (real32_T)(rtb_Compare && rtb_LogicalOperator2_tmp && OutUb_tmp_0) *
           (0.666666687F * voltage_power_supply)) + (real32_T)(OutUb_tmp &&
    rtb_Compare_c && rtb_LogicalOperator4) * (-0.666666687F *
    voltage_power_supply);

  /* Logic: '<S6>/Logical Operator1' */
  rtb_LogicalOperator7 = rtb_Compare_c ^ rtb_Compare;

  /* Sum: '<S6>/Subtract' incorporates:
   *  Gain: '<S6>/Gain'
   *  Gain: '<S6>/Gain1'
   *  Gain: '<S6>/Gain2'
   *  Gain: '<S6>/Gain3'
   *  Inport: '<Root>/voltage_power_supply'
   *  Logic: '<S6>/Logical Operator'
   *  Logic: '<S6>/Logical Operator2'
   *  Logic: '<S6>/Logical Operator4'
   *  Logic: '<S6>/Logical Operator7'
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product1'
   *  Product: '<S6>/Product2'
   *  Product: '<S6>/Product3'
   */
  OutUc = (((real32_T)(rtb_LogicalOperator4 && rtb_LogicalOperator7) *
            (0.333333343F * voltage_power_supply) + (real32_T)(OutUb_tmp_0 &&
             rtb_LogicalOperator7) * (-0.333333343F * voltage_power_supply)) +
           (real32_T)(rtb_LogicalOperator4 && rtb_LogicalOperator2_tmp &&
                      OutUb_tmp) * (0.666666687F * voltage_power_supply)) +
    (real32_T)(OutUb_tmp_0 && rtb_Compare_c && rtb_Compare) * (-0.666666687F *
    voltage_power_supply);
}

/* Model initialize function */
void svpwm_V_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
