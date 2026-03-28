/*
 * File: FOC_Motor.c
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

#include "FOC_Motor.h"
#include "rtwtypes.h"
#include "EHB_MOTOR.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */

/* Block signals and states (default storage) */
D_Work rtDWork;

/* External inputs (root inport signals with default storage) */
ExternalInputs rtU;

/* External outputs (root outports fed by signals with default storage) */
ExternalOutputs rtY;

/* data stores shared across model instances */
SharedDSM rtSharedDSM;                 /* '<Root>/Data Store Memory15' */

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static int16_T look1_bfts16Dd_binlc(real_T u0, const real32_T bp0[], const
    int16_T table[], uint32_T maxIndex);
static int16_T look1_bfts16Dd_binlc(real_T u0, const real32_T bp0[], const
    int16_T table[], uint32_T maxIndex)
{
    real_T frac;
    uint32_T bpIdx;
    uint32_T iLeft;
    uint32_T iRght;
    int16_T yL_0d0;

    /* Column-major Lookup 1-D
       Search method: 'binary'
       Use previous index: 'off'
       Interpolation method: 'Linear point-slope'
       Extrapolation method: 'Clip'
       Use last breakpoint for index at or above upper limit: 'off'
       Remove protection against out-of-range input in generated code: 'off'
     */
    /* Prelookup - Index and Fraction
       Index Search method: 'binary'
       Extrapolation method: 'Clip'
       Use previous index: 'off'
       Use last breakpoint for index at or above upper limit: 'off'
       Remove protection against out-of-range input in generated code: 'off'
     */
    if (u0 <= bp0[0U])
    {
        iLeft = 0U;
        frac = 0.0;
    }
    else if (u0 < bp0[maxIndex])
    {
        /* Binary Search */
        bpIdx = maxIndex >> 1U;
        iLeft = 0U;
        iRght = maxIndex;
        while (iRght - iLeft > 1U)
        {
            if (u0 < bp0[bpIdx])
            {
                iRght = bpIdx;
            }
            else
            {
                iLeft = bpIdx;
            }

            bpIdx = (iRght + iLeft) >> 1U;
        }

        frac = (u0 - bp0[iLeft]) / ((real_T)bp0[iLeft + 1U] - bp0[iLeft]);
    }
    else
    {
        iLeft = maxIndex - 1U;
        frac = 1.0;
    }

    /* Column-major Interpolation 1-D
       Interpolation method: 'Linear point-slope'
       Use last breakpoint for index at or above upper limit: 'off'
       Overflow mode: 'wrapping'
     */
    yL_0d0 = table[iLeft];
    return (int16_T)((int16_T)(((real_T)table[iLeft + 1U] - (real_T)yL_0d0) *
                      frac) + yL_0d0);
}

/* Model step function */
void FOC_Motor_step(void)
{
    real_T Y;
    real_T Y_tmp;
    real_T Z;
    real_T rtb_Divide;
    real_T rtb_Tb;
    int32_T tmp;
    int32_T tmp_0;
    int16_T rtb_Gain1;
    int16_T rtb_Gain_n;
    int16_T rtb_alpha_voltage;
    int16_T rtb_beta_voltage;
    uint16_T tmp_1;
    uint8_T rtb_Sector_Lookup_Table;

    /* Switch: '<S5>/Angle_Val' incorporates:
     *  Constant: '<S5>/Max_Count'
     *  DataStoreRead: '<Root>/Data Store Read15'
     *  DataStoreRead: '<Root>/Data Store Read16'
     *  RelationalOperator: '<S5>/Relational Operator'
     *  Sum: '<S5>/Theta_to_Max'
     *  Sum: '<S5>/Zero_to_Theta'
     */
    if (rtSharedDSM.Theta_Inte >= rtSharedDSM.Theta_zero)
    {
        tmp_1 = (uint16_T)(rtSharedDSM.Theta_Inte - rtSharedDSM.Theta_zero);
    }
    else
    {
        tmp_1 = (uint16_T)((rtSharedDSM.Theta_Inte - rtSharedDSM.Theta_zero) +
                           4095);
    }

    /* Product: '<S2>/Divide' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S2>/Constant1'
     *  Gain: '<S2>/Gain'
     *  Math: '<S5>/Mod'
     *  Product: '<S2>/Product'
     *  Switch: '<S5>/Angle_Val'
     */
    rtb_Divide = (real_T)(tmp_1 % 585) * 3.14159265359 * 2.0 / 585.0;

    /* Lookup_n-D: '<S2>/Sin_LookUp' incorporates:
     *  Product: '<S2>/Divide'
     *  Sum: '<S3>/Add1'
     */
    rtb_alpha_voltage = look1_bfts16Dd_binlc(rtb_Divide, &Sin_BreakPoint[0],
        &Sin_Table[0], 99U);

    /* Lookup_n-D: '<S2>/Cos_LookUp' incorporates:
     *  Gain: '<S7>/Gain1'
     *  Product: '<S2>/Divide'
     */
    rtb_Gain1 = look1_bfts16Dd_binlc(rtb_Divide, &Sin_BreakPoint[0], &Cos_Table
        [0], 99U);

    /* Product: '<S3>/Product' incorporates:
     *  Inport: '<Root>/Ud'
     *  Sum: '<S3>/Add1'
     */
    tmp = rtU.Ud * rtb_alpha_voltage;

    /* Product: '<S3>/Product1' incorporates:
     *  Gain: '<S7>/Gain1'
     *  Inport: '<Root>/Uq'
     */
    tmp_0 = rtU.Uq * rtb_Gain1;

    /* Sum: '<S3>/Add' incorporates:
     *  Product: '<S3>/Product'
     *  Product: '<S3>/Product1'
     */
    rtb_beta_voltage = (int16_T)((int16_T)(((tmp < 0 ? 16383 : 0) + tmp) >> 14)
        + (int16_T)(((tmp_0 < 0 ? 16383 : 0) + tmp_0) >> 14));

    /* Gain: '<S7>/Gain' incorporates:
     *  Sum: '<S3>/Add'
     */
    rtb_Gain_n = (int16_T)(rtb_beta_voltage >> 1);

    /* Product: '<S3>/Product2' incorporates:
     *  Gain: '<S7>/Gain1'
     *  Inport: '<Root>/Ud'
     */
    tmp = rtU.Ud * rtb_Gain1;

    /* Product: '<S3>/Product3' incorporates:
     *  Inport: '<Root>/Uq'
     *  Sum: '<S3>/Add1'
     */
    tmp_0 = rtU.Uq * rtb_alpha_voltage;

    /* Sum: '<S3>/Add1' incorporates:
     *  Product: '<S3>/Product2'
     *  Product: '<S3>/Product3'
     */
    rtb_alpha_voltage = (int16_T)((int16_T)(((tmp < 0 ? 16383 : 0) + tmp) >> 14)
        - (int16_T)(((tmp_0 < 0 ? 16383 : 0) + tmp_0) >> 14));

    /* Gain: '<S7>/Gain1' incorporates:
     *  Sum: '<S3>/Add1'
     */
    rtb_Gain1 = (int16_T)((28377 * rtb_alpha_voltage) >> 15);

    /* LookupNDDirect: '<S7>/Sector_Lookup_Table' incorporates:
     *  Gain: '<S7>/Gain'
     *  Gain: '<S7>/Gain1'
     *  Gain: '<S7>/Gain2'
     *  Gain: '<S7>/Sector_Gain_VB'
     *  Gain: '<S7>/Sector_Gain_VC'
     *  RelationalOperator: '<S10>/Compare'
     *  RelationalOperator: '<S11>/Compare'
     *  RelationalOperator: '<S12>/Compare'
     *  Sum: '<S3>/Add'
     *  Sum: '<S7>/Add'
     *  Sum: '<S7>/Add1'
     *  Sum: '<S7>/Calculate_Phase_Advanced_Sector'
     *
     * About '<S7>/Sector_Lookup_Table':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_Sector_Lookup_Table = (uint8_T)(((uint32_T)(((int16_T)(rtb_Gain1 -
        rtb_Gain_n) > 0) << 1) + (uint32_T)(rtb_beta_voltage > 0)) + (uint32_T)
        (((int16_T)(rtb_Gain1 + rtb_Gain_n) * -32768 > 0) << 2));
    if (rtb_Sector_Lookup_Table > 6)
    {
        rtb_Sector_Lookup_Table = 6U;
    }

    rtb_Sector_Lookup_Table =
        rtConstP.Sector_Lookup_Table_table[rtb_Sector_Lookup_Table];

    /* End of LookupNDDirect: '<S7>/Sector_Lookup_Table' */

    /* MATLAB Function: '<S6>/矢量作用时间' */
    rtb_Divide = 0.0;
    rtb_Tb = 0.0;

    /* DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
     *  Sum: '<S3>/Add'
     */
    Y = (real_T)rtb_beta_voltage * 0.000244140625;

    /* MATLAB Function: '<S6>/矢量作用时间' incorporates:
     *  Constant: '<S6>/Bus_Voltage'
     *  Constant: '<S6>/Bus_Voltage1'
     *  DataTypeConversion: '<S6>/Data Type Conversion1'
     */
    rtDWork.X = Y * 692.8203230275509;

    /* DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
     *  Sum: '<S3>/Add1'
     */
    Z = (real_T)rtb_alpha_voltage * 0.000244140625;

    /* MATLAB Function: '<S6>/矢量作用时间' incorporates:
     *  Constant: '<S6>/Bus_Voltage'
     *  Constant: '<S6>/Bus_Voltage1'
     *  DataTypeConversion: '<S6>/Data Type Conversion'
     */
    Y_tmp = Y * 0.5;
    Y = (Z * 0.8660254037844386 - Y_tmp) * 692.8203230275509;
    Z = (Z * -0.8660254037844386 - Y_tmp) * 692.8203230275509;
    if (rtb_Sector_Lookup_Table == 1)
    {
        rtb_Divide = Y;
        rtb_Tb = rtDWork.X;
    }

    if (rtb_Sector_Lookup_Table == 2)
    {
        rtb_Divide = -Y;
        rtb_Tb = -Z;
    }

    if (rtb_Sector_Lookup_Table == 3)
    {
        rtb_Divide = rtDWork.X;
        rtb_Tb = Z;
    }

    if (rtb_Sector_Lookup_Table == 4)
    {
        rtb_Divide = -rtDWork.X;
        rtb_Tb = -Y;
    }

    if (rtb_Sector_Lookup_Table == 5)
    {
        rtb_Divide = Z;
        rtb_Tb = Y;
    }

    if (rtb_Sector_Lookup_Table == 6)
    {
        rtb_Divide = -Z;
        rtb_Tb = -rtDWork.X;
    }

    /* Outport: '<Root>/PWM_Duty_U' incorporates:
     *  MATLAB Function: '<S6>/CCR'
     */
    rtY.PWM_Duty_U = 0.0;

    /* Outport: '<Root>/PWM_Duty_V' incorporates:
     *  MATLAB Function: '<S6>/CCR'
     */
    rtY.PWM_Duty_V = 0.0;

    /* Outport: '<Root>/PWM_Duty_W' incorporates:
     *  MATLAB Function: '<S6>/CCR'
     */
    rtY.PWM_Duty_W = 0.0;

    /* MATLAB Function: '<S6>/CCR' incorporates:
     *  Constant: '<S6>/Bus_Voltage1'
     */
    rtDWork.X = rtb_Divide + rtb_Tb;
    if (rtDWork.X > 4800.0)
    {
        rtb_Divide = rtb_Divide / rtDWork.X * 4800.0;
        rtb_Tb = rtb_Tb / rtDWork.X * 4800.0;
    }

    rtDWork.X = (4800.0 - rtb_Divide) - rtb_Tb;
    switch (rtb_Sector_Lookup_Table)
    {
      case 1U:
        /* Outport: '<Root>/PWM_Duty_U' */
        rtY.PWM_Duty_U = ((rtb_Divide + rtb_Tb) + rtDWork.X / 2.0) / 2.0;

        /* Outport: '<Root>/PWM_Duty_V' */
        rtY.PWM_Duty_V = (rtDWork.X / 2.0 + rtb_Tb) / 2.0;

        /* Outport: '<Root>/PWM_Duty_W' */
        rtY.PWM_Duty_W = rtDWork.X / 2.0 / 2.0;
        break;

      case 2U:
        /* Outport: '<Root>/PWM_Duty_U' */
        rtY.PWM_Duty_U = (rtDWork.X / 2.0 + rtb_Tb) / 2.0;

        /* Outport: '<Root>/PWM_Duty_V' */
        rtY.PWM_Duty_V = ((rtb_Divide + rtb_Tb) + rtDWork.X / 2.0) / 2.0;

        /* Outport: '<Root>/PWM_Duty_W' */
        rtY.PWM_Duty_W = rtDWork.X / 2.0 / 2.0;
        break;

      case 3U:
        /* Outport: '<Root>/PWM_Duty_U' */
        rtY.PWM_Duty_U = rtDWork.X / 2.0 / 2.0;

        /* Outport: '<Root>/PWM_Duty_V' */
        rtY.PWM_Duty_V = ((rtb_Divide + rtb_Tb) + rtDWork.X / 2.0) / 2.0;

        /* Outport: '<Root>/PWM_Duty_W' */
        rtY.PWM_Duty_W = (rtDWork.X / 2.0 + rtb_Tb) / 2.0;
        break;

      case 4U:
        /* Outport: '<Root>/PWM_Duty_U' */
        rtY.PWM_Duty_U = rtDWork.X / 2.0 / 2.0;

        /* Outport: '<Root>/PWM_Duty_V' */
        rtY.PWM_Duty_V = (rtDWork.X / 2.0 + rtb_Tb) / 2.0;

        /* Outport: '<Root>/PWM_Duty_W' */
        rtY.PWM_Duty_W = ((rtb_Divide + rtb_Tb) + rtDWork.X / 2.0) / 2.0;
        break;

      case 5U:
        /* Outport: '<Root>/PWM_Duty_U' */
        rtY.PWM_Duty_U = (rtDWork.X / 2.0 + rtb_Tb) / 2.0;

        /* Outport: '<Root>/PWM_Duty_V' */
        rtY.PWM_Duty_V = rtDWork.X / 2.0 / 2.0;

        /* Outport: '<Root>/PWM_Duty_W' */
        rtY.PWM_Duty_W = ((rtb_Divide + rtb_Tb) + rtDWork.X / 2.0) / 2.0;
        break;

      case 6U:
        /* Outport: '<Root>/PWM_Duty_U' */
        rtY.PWM_Duty_U = ((rtb_Divide + rtb_Tb) + rtDWork.X / 2.0) / 2.0;

        /* Outport: '<Root>/PWM_Duty_V' */
        rtY.PWM_Duty_V = rtDWork.X / 2.0 / 2.0;

        /* Outport: '<Root>/PWM_Duty_W' */
        rtY.PWM_Duty_W = (rtDWork.X / 2.0 + rtb_Tb) / 2.0;
        break;

      default:
        /* no actions */
        break;
    }
}

/* Model initialize function */
void FOC_Motor_initialize(void)
{
    /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
