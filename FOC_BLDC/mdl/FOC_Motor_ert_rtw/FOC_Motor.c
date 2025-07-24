/*
 * File: FOC_Motor.c
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

#include "FOC_Motor.h"
#include <math.h>
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
static int16_T look1_iflfts16Df_binlc(real32_T u0, const real32_T bp0[], const
    int16_T table[], uint32_T maxIndex);
static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator);
static int16_T look1_iflfts16Df_binlc(real32_T u0, const real32_T bp0[], const
    int16_T table[], uint32_T maxIndex)
{
    real32_T frac;
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
        frac = 0.0F;
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

        frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
    }
    else
    {
        iLeft = maxIndex - 1U;
        frac = 1.0F;
    }

    /* Column-major Interpolation 1-D
       Interpolation method: 'Linear point-slope'
       Use last breakpoint for index at or above upper limit: 'off'
       Overflow mode: 'wrapping'
     */
    yL_0d0 = table[iLeft];
    return (int16_T)((int16_T)(((real32_T)table[iLeft + 1U] - (real32_T)yL_0d0) *
                      frac) + yL_0d0);
}

static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
    return (((numerator < 0) != (denominator < 0)) && (numerator % denominator
             != 0) ? -1 : 0) + numerator / denominator;
}

/* Model step function */
void FOC_Motor_step(void)
{
    int32_T rtb_Add1_b;
    int32_T rtb_Add_2;
    int32_T rtb_Add_m;
    int32_T rtb_Add_p_tmp_0;
    int32_T rtb_Sector_slect_e_tmp;
    int32_T rtb_UnitDelay2;
    int32_T rtb_UnitDelay3;
    int32_T rtb_UnitDelay4;
    int32_T rtb_UnitDelay5;
    int32_T rtb_UnitDelay6;
    real32_T tmp;
    uint32_T tmp_0;
    int16_T rtb_Add_b;
    int16_T rtb_Add_p_tmp;
    int16_T rtb_Gain3;
    int16_T rtb_Sector_slect;
    int16_T rtb_Sector_slect1_j;
    int16_T rtb_Sector_slect_d;
    uint16_T tmp_2;
    int8_T tmp_1;
    uint8_T rtb_Sector_Lookup_Table;

    /* DataTypeConversion: '<Root>/Data Type Conversion1' incorporates:
     *  Inport: '<Root>/Tar_speed'
     */
    rtDWork.DataTypeConversion = (real32_T)floor(rtU.Tar_speed * 1024.0F);
    if (rtDWork.DataTypeConversion < 2.14748365E+9F)
    {
        if (rtDWork.DataTypeConversion >= -2.14748365E+9F)
        {
            rtDWork.Add2_e = (int32_T)rtDWork.DataTypeConversion;
        }
        else
        {
            rtDWork.Add2_e = MIN_int32_T;
        }
    }
    else
    {
        rtDWork.Add2_e = MAX_int32_T;
    }

    /* Gain: '<S15>/Gain' incorporates:
     *  Inport: '<Root>/Theta_Inte'
     */
    tmp_0 = (51445U * rtU.Theta_Inte) >> 13;
    if (tmp_0 > 32767U)
    {
        tmp_0 = 32767U;
    }

    /* Sum: '<S15>/Add' incorporates:
     *  Gain: '<S15>/Gain'
     *  UnitDelay: '<S15>/Unit Delay'
     */
    rtb_Add_b = (int16_T)((int32_T)tmp_0 - rtDWork.UnitDelay_DSTATE_ln);

    /* Abs: '<S15>/Abs' incorporates:
     *  Sum: '<S15>/Add'
     */
    if (rtb_Add_b < 0)
    {
        rtb_Gain3 = (int16_T)-rtb_Add_b;
    }
    else
    {
        rtb_Gain3 = rtb_Add_b;
    }

    /* Switch: '<S15>/Switch' incorporates:
     *  Abs: '<S15>/Abs'
     *  Constant: '<S15>/Constant1'
     *  RelationalOperator: '<S15>/Relational Operator'
     */
    if (rtb_Gain3 >= 20480)
    {
        /* Switch: '<S15>/Switch1' incorporates:
         *  Constant: '<S15>/Constant2'
         *  Constant: '<S15>/Constant3'
         *  Sum: '<S15>/Add'
         */
        if (rtb_Add_b > 0)
        {
            tmp_1 = -1;
        }
        else
        {
            tmp_1 = 1;
        }

        /* End of Switch: '<S15>/Switch1' */
    }
    else
    {
        tmp_1 = 0;
    }

    /* Sum: '<S15>/Add1' incorporates:
     *  Switch: '<S15>/Switch'
     *  UnitDelay: '<S15>/Unit Delay1'
     */
    rtDWork.Add1_d = tmp_1 + rtDWork.UnitDelay1_DSTATE;

    /* Sum: '<S18>/Add1' incorporates:
     *  Constant: '<S18>/Constant'
     *  Constant: '<S18>/Constant1'
     *  DataTypeConversion: '<S15>/Data Type Conversion'
     *  Gain: '<S15>/Gain'
     *  Gain: '<S15>/Gain1'
     *  Product: '<S18>/Product'
     *  Product: '<S18>/Product1'
     *  Sum: '<S15>/Add2'
     *  UnitDelay: '<S18>/Unit Delay'
     */
    rtDWork.Add1 = (6.28318548F * (real32_T)rtDWork.Add1_d + (real32_T)tmp_0 *
                    0.000244140625F) * 0.5F + 0.5F * rtDWork.UnitDelay_DSTATE;

    /* Sum: '<S17>/Add' incorporates:
     *  UnitDelay: '<S17>/Unit Delay'
     */
    rtDWork.DataTypeConversion = (real32_T)floor((rtDWork.Add1 -
        rtDWork.UnitDelay_DSTATE_h) * 1024.0F);
    if (rtDWork.DataTypeConversion < 2.14748365E+9F)
    {
        if (rtDWork.DataTypeConversion >= -2.14748365E+9F)
        {
            rtb_Add_2 = (int32_T)rtDWork.DataTypeConversion;
        }
        else
        {
            rtb_Add_2 = MIN_int32_T;
        }
    }
    else
    {
        rtb_Add_2 = MAX_int32_T;
    }

    /* Switch: '<S17>/Switch' incorporates:
     *  Gain: '<S17>/Gain'
     *  RelationalOperator: '<S17>/Relational Operator'
     *  Sum: '<S17>/Add'
     *  UnitDelay: '<S17>/Unit Delay1'
     */
    if (rtb_Add_2 > 3 * rtDWork.UnitDelay1_DSTATE_g)
    {
        rtDWork.Saturation = rtDWork.UnitDelay1_DSTATE_g;
    }
    else
    {
        rtDWork.Saturation = rtb_Add_2;
    }

    /* Product: '<S17>/Product' incorporates:
     *  Switch: '<S17>/Switch'
     */
    rtDWork.i1 = rtDWork.Saturation * 955LL;
    if (rtDWork.i1 > 2147483647LL)
    {
        rtDWork.i1 = 2147483647LL;
    }
    else if (rtDWork.i1 < -2147483648LL)
    {
        rtDWork.i1 = -2147483648LL;
    }

    /* UnitDelay: '<S20>/Unit Delay' */
    rtDWork.UnitDelay_i = rtDWork.UnitDelay_DSTATE_j;

    /* UnitDelay: '<S20>/Unit Delay1' */
    rtDWork.UnitDelay1 = rtDWork.UnitDelay1_DSTATE_h;

    /* UnitDelay: '<S20>/Unit Delay2' */
    rtb_UnitDelay2 = rtDWork.UnitDelay2_DSTATE;

    /* UnitDelay: '<S20>/Unit Delay3' */
    rtb_UnitDelay3 = rtDWork.UnitDelay3_DSTATE;

    /* UnitDelay: '<S20>/Unit Delay4' */
    rtb_UnitDelay4 = rtDWork.UnitDelay4_DSTATE;

    /* UnitDelay: '<S20>/Unit Delay5' */
    rtb_UnitDelay5 = rtDWork.UnitDelay5_DSTATE;

    /* UnitDelay: '<S20>/Unit Delay6' */
    rtb_UnitDelay6 = rtDWork.UnitDelay6_DSTATE;

    /* Sum: '<S21>/Add1' incorporates:
     *  Constant: '<S21>/Constant'
     *  Constant: '<S21>/Constant1'
     *  Product: '<S17>/Product'
     *  Product: '<S20>/Divide'
     *  Product: '<S21>/Product'
     *  Product: '<S21>/Product1'
     *  Sum: '<S20>/Sum'
     *  Sum: '<S20>/Sum1'
     *  Sum: '<S20>/Sum2'
     *  Sum: '<S20>/Sum3'
     *  Sum: '<S20>/Sum4'
     *  Sum: '<S20>/Sum5'
     *  Sum: '<S20>/Sum6'
     *  Sum: '<S20>/Sum7'
     *  UnitDelay: '<S20>/Unit Delay'
     *  UnitDelay: '<S20>/Unit Delay1'
     *  UnitDelay: '<S20>/Unit Delay2'
     *  UnitDelay: '<S20>/Unit Delay3'
     *  UnitDelay: '<S20>/Unit Delay4'
     *  UnitDelay: '<S20>/Unit Delay5'
     *  UnitDelay: '<S20>/Unit Delay6'
     *  UnitDelay: '<S20>/Unit Delay7'
     *  UnitDelay: '<S21>/Unit Delay'
     */
    rtb_Add1_b = (int32_T)((div_nde_s32_floor(((((((((int32_T)rtDWork.i1 +
        rtDWork.UnitDelay_DSTATE_j) + rtDWork.UnitDelay1_DSTATE_h) +
        rtDWork.UnitDelay2_DSTATE) + rtDWork.UnitDelay3_DSTATE) +
        rtDWork.UnitDelay4_DSTATE) + rtDWork.UnitDelay5_DSTATE) +
        rtDWork.UnitDelay6_DSTATE) + rtDWork.UnitDelay7_DSTATE, 9) * 205LL) >>
                           10) + (int16_T)((819 * rtDWork.UnitDelay_DSTATE_b) >>
        10);

    /* Sum: '<S6>/Add' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion1'
     *  Sum: '<S21>/Add1'
     */
    rtb_Add_m = rtDWork.Add2_e - rtb_Add1_b;

    /* Switch: '<S16>/Switch' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion1'
     *  Sum: '<S16>/Add'
     *  Sum: '<S6>/Add'
     *  UnitDelay: '<S16>/Unit Delay'
     */
    if (rtDWork.Add2_e != 0)
    {
        rtDWork.Add2_e = rtb_Add_m + rtDWork.UnitDelay_DSTATE_l;
    }

    /* End of Switch: '<S16>/Switch' */

    /* DataTypeConversion: '<Root>/Data Type Conversion2' incorporates:
     *  Inport: '<Root>/Speed_ki'
     */
    rtDWork.DataTypeConversion = (real32_T)floor(rtU.Speed_ki * 4096.0F);
    if (rtDWork.DataTypeConversion < 32768.0F)
    {
        if (rtDWork.DataTypeConversion >= -32768.0F)
        {
            rtb_Gain3 = (int16_T)rtDWork.DataTypeConversion;
        }
        else
        {
            rtb_Gain3 = MIN_int16_T;
        }
    }
    else
    {
        rtb_Gain3 = MAX_int16_T;
    }

    /* Product: '<S16>/Product1' incorporates:
     *  DataTypeConversion: '<Root>/Data Type Conversion2'
     *  Switch: '<S16>/Switch'
     */
    rtDWork.i = ((int64_T)rtDWork.Add2_e * rtb_Gain3) >> 12;
    if (rtDWork.i > 2147483647LL)
    {
        rtDWork.i = 2147483647LL;
    }
    else if (rtDWork.i < -2147483648LL)
    {
        rtDWork.i = -2147483648LL;
    }

    /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
     *  Inport: '<Root>/Speed_kp'
     */
    rtDWork.DataTypeConversion = (real32_T)floor(rtU.Speed_kp * 4096.0F);

    /* DataTypeConversion: '<Root>/Data Type Conversion3' incorporates:
     *  Inport: '<Root>/Speed_kd'
     */
    tmp = (real32_T)floor(rtU.Speed_kd * 4096.0F);

    /* DataTypeConversion: '<Root>/Data Type Conversion' */
    if (rtDWork.DataTypeConversion < 32768.0F)
    {
        if (rtDWork.DataTypeConversion >= -32768.0F)
        {
            rtb_Gain3 = (int16_T)rtDWork.DataTypeConversion;
        }
        else
        {
            rtb_Gain3 = MIN_int16_T;
        }
    }
    else
    {
        rtb_Gain3 = MAX_int16_T;
    }

    /* Saturate: '<S16>/Saturation' incorporates:
     *  Product: '<S16>/Product1'
     */
    if ((int32_T)rtDWork.i > 3072)
    {
        rtDWork.Saturation = 3072;
    }
    else if ((int32_T)rtDWork.i < -3072)
    {
        rtDWork.Saturation = -3072;
    }
    else
    {
        rtDWork.Saturation = (int32_T)rtDWork.i;
    }

    /* DataTypeConversion: '<Root>/Data Type Conversion3' */
    if (tmp < 32768.0F)
    {
        if (tmp >= -32768.0F)
        {
            rtb_Add_b = (int16_T)tmp;
        }
        else
        {
            rtb_Add_b = MIN_int16_T;
        }
    }
    else
    {
        rtb_Add_b = MAX_int16_T;
    }

    /* Sum: '<S19>/Add1' incorporates:
     *  Constant: '<S19>/Constant'
     *  Constant: '<S19>/Constant1'
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     *  DataTypeConversion: '<Root>/Data Type Conversion3'
     *  Product: '<S16>/Product'
     *  Product: '<S16>/Product2'
     *  Product: '<S19>/Product'
     *  Product: '<S19>/Product1'
     *  Saturate: '<S16>/Saturation'
     *  Sum: '<S16>/Add1'
     *  Sum: '<S16>/Add2'
     *  Sum: '<S6>/Add'
     *  UnitDelay: '<S16>/Unit Delay1'
     *  UnitDelay: '<S19>/Unit Delay'
     */
    rtDWork.Saturation = (int32_T)(((((int32_T)(((int64_T)rtb_Add_m * rtb_Gain3)
        >> 12) + rtDWork.Saturation) + (int32_T)(((int64_T)(rtb_Add_m -
        rtDWork.UnitDelay1_DSTATE_p) * rtb_Add_b) >> 12)) * 205LL) >> 10) +
        (int16_T)((819 * rtDWork.UnitDelay_DSTATE_a) >> 10);

    /* Switch: '<S7>/Angle_Val' incorporates:
     *  Constant: '<S7>/Max_Count'
     *  Inport: '<Root>/Theta_Inte'
     *  Inport: '<Root>/Theta_zero'
     *  RelationalOperator: '<S7>/Relational Operator'
     *  Sum: '<S7>/Theta_to_Max'
     *  Sum: '<S7>/Zero_to_Theta'
     */
    if (rtU.Theta_Inte >= rtU.Theta_zero)
    {
        tmp_2 = (uint16_T)(rtU.Theta_Inte - rtU.Theta_zero);
    }
    else
    {
        tmp_2 = (uint16_T)((rtU.Theta_Inte - rtU.Theta_zero) + 4095);
    }

    /* Gain: '<S2>/Gain2' incorporates:
     *  Math: '<S7>/Mod'
     *  Switch: '<S7>/Angle_Val'
     */
    rtDWork.DataTypeConversion = (real32_T)(tmp_2 % 585) * 0.0107405186F;

    /* Product: '<S3>/Product' incorporates:
     *  DataTypeConversion: '<S6>/Data Type Conversion'
     *  Lookup_n-D: '<S2>/Sin_LookUp'
     *  Sum: '<S19>/Add1'
     */
    rtDWork.i = (int64_T)rtDWork.Saturation * look1_iflfts16Df_binlc
        (rtDWork.DataTypeConversion, &Sin_BreakPoint[0], &Sin_Table[0], 99U);

    /* Sum: '<S3>/Add' incorporates:
     *  Gain: '<S9>/Gain3'
     *  Product: '<S3>/Product'
     */
    rtb_Gain3 = (int16_T)(((rtDWork.i < 0LL ? 4095LL : 0LL) + rtDWork.i) >> 12);

    /* Gain: '<S10>/Gain' incorporates:
     *  Gain: '<S8>/Gain3'
     *  Gain: '<S9>/Gain3'
     */
    rtb_Add_p_tmp = (int16_T)(rtb_Gain3 >> 1);

    /* Product: '<S3>/Product2' incorporates:
     *  DataTypeConversion: '<S6>/Data Type Conversion'
     *  Lookup_n-D: '<S2>/Cos_LookUp'
     *  Sum: '<S19>/Add1'
     */
    rtDWork.i = (int64_T)rtDWork.Saturation * look1_iflfts16Df_binlc
        (rtDWork.DataTypeConversion, &Sin_BreakPoint[0], &Cos_Table[0], 99U);

    /* Sum: '<S3>/Add1' incorporates:
     *  MultiPortSwitch: '<S9>/Sector_slect2'
     *  Product: '<S3>/Product2'
     */
    rtb_Sector_slect_d = (int16_T)(((rtDWork.i < 0LL ? 4095LL : 0LL) + rtDWork.i)
        >> 12);

    /* Gain: '<S10>/Gain1' incorporates:
     *  MultiPortSwitch: '<S9>/Sector_slect'
     *  MultiPortSwitch: '<S9>/Sector_slect2'
     */
    rtb_Sector_slect = (int16_T)((28377 * rtb_Sector_slect_d) >> 15);

    /* LookupNDDirect: '<S10>/Sector_Lookup_Table' incorporates:
     *  Gain: '<S10>/Gain'
     *  Gain: '<S10>/Sector_Gain_VB'
     *  Gain: '<S10>/Sector_Gain_VC'
     *  Gain: '<S9>/Gain3'
     *  MultiPortSwitch: '<S9>/Sector_slect'
     *  RelationalOperator: '<S12>/Compare'
     *  RelationalOperator: '<S13>/Compare'
     *  RelationalOperator: '<S14>/Compare'
     *  Sum: '<S10>/Add'
     *  Sum: '<S10>/Add1'
     *  Sum: '<S10>/Calculate_Phase_Advanced_Sector'
     *
     * About '<S10>/Sector_Lookup_Table':
     *  1-dimensional Direct Look-Up returning a Scalar,
     *
     *     Remove protection against out-of-range input in generated code: 'off'
     */
    rtb_Sector_Lookup_Table = (uint8_T)(((uint32_T)(((int16_T)(rtb_Sector_slect
        - rtb_Add_p_tmp) > 0) << 1) + (uint32_T)(rtb_Gain3 > 0)) + (uint32_T)
        (((int16_T)(-rtb_Add_p_tmp - rtb_Sector_slect) > 0) << 2));
    if (rtb_Sector_Lookup_Table > 6)
    {
        rtb_Sector_Lookup_Table = 6U;
    }

    rtb_Sector_Lookup_Table =
        rtConstP.Sector_Lookup_Table_table[rtb_Sector_Lookup_Table];

    /* End of LookupNDDirect: '<S10>/Sector_Lookup_Table' */

    /* Product: '<S8>/Product1' incorporates:
     *  Gain: '<S8>/Gain1'
     *  MultiPortSwitch: '<S9>/Sector_slect1'
     *  MultiPortSwitch: '<S9>/Sector_slect2'
     *  Sum: '<S8>/Add'
     */
    rtb_Sector_slect1_j = (int16_T)(((int16_T)(((14189 * rtb_Sector_slect_d) >>
        14) - rtb_Add_p_tmp) * 147) >> 10);

    /* Product: '<S8>/Product2' incorporates:
     *  Gain: '<S8>/Gain4'
     *  Gain: '<S9>/Gain4'
     *  MultiPortSwitch: '<S9>/Sector_slect2'
     *  Sum: '<S8>/Add1'
     */
    rtb_Add_b = (int16_T)(((int16_T)(((-14189 * rtb_Sector_slect_d) >> 14) -
                            rtb_Add_p_tmp) * 147) >> 10);

    /* MultiPortSwitch: '<S8>/Sector_slect' incorporates:
     *  Gain: '<S8>/Gain1'
     *  Gain: '<S8>/Gain5'
     *  Gain: '<S8>/Gain6'
     *  Gain: '<S8>/Gain7'
     *  Gain: '<S9>/Gain3'
     *  Gain: '<S9>/Gain4'
     *  MultiPortSwitch: '<S9>/Sector_slect2'
     *  Product: '<S8>/Product'
     *  Product: '<S8>/Product1'
     *  Sum: '<S8>/Add'
     */
    switch (rtb_Sector_Lookup_Table)
    {
      case 1:
        rtb_Sector_slect_d = (int16_T)(((int16_T)(((14189 * rtb_Sector_slect_d) >>
            14) - rtb_Add_p_tmp) * 147) >> 10);

        /* MultiPortSwitch: '<S8>/Sector_slect1' incorporates:
         *  Gain: '<S8>/Gain1'
         *  Gain: '<S9>/Gain3'
         *  MultiPortSwitch: '<S8>/Sector_slect'
         *  MultiPortSwitch: '<S9>/Sector_slect2'
         *  Product: '<S8>/Product'
         *  Product: '<S8>/Product1'
         *  Sum: '<S8>/Add'
         */
        rtb_Add_b = (int16_T)((147 * rtb_Gain3) >> 10);
        break;

      case 2:
        rtb_Sector_slect_d = (int16_T)-(int16_T)(((int16_T)(((14189 *
            rtb_Sector_slect_d) >> 14) - rtb_Add_p_tmp) * 147) >> 10);

        /* MultiPortSwitch: '<S8>/Sector_slect1' incorporates:
         *  Gain: '<S8>/Gain1'
         *  Gain: '<S8>/Gain6'
         *  Gain: '<S8>/Gain7'
         *  Gain: '<S9>/Gain4'
         *  MultiPortSwitch: '<S8>/Sector_slect'
         *  MultiPortSwitch: '<S9>/Sector_slect2'
         *  Product: '<S8>/Product1'
         *  Sum: '<S8>/Add'
         */
        rtb_Add_b = (int16_T)-rtb_Add_b;
        break;

      case 3:
        rtb_Sector_slect_d = (int16_T)((147 * rtb_Gain3) >> 10);
        break;

      case 4:
        rtb_Sector_slect_d = (int16_T)-((147 * rtb_Gain3) >> 10);

        /* MultiPortSwitch: '<S8>/Sector_slect1' incorporates:
         *  Gain: '<S8>/Gain5'
         *  Gain: '<S8>/Gain6'
         *  Gain: '<S9>/Gain3'
         *  MultiPortSwitch: '<S8>/Sector_slect'
         *  MultiPortSwitch: '<S9>/Sector_slect1'
         *  Product: '<S8>/Product'
         */
        rtb_Add_b = (int16_T)-rtb_Sector_slect1_j;
        break;

      case 5:
        rtb_Sector_slect_d = rtb_Add_b;

        /* MultiPortSwitch: '<S8>/Sector_slect1' incorporates:
         *  Gain: '<S9>/Gain4'
         *  MultiPortSwitch: '<S8>/Sector_slect'
         *  MultiPortSwitch: '<S9>/Sector_slect1'
         */
        rtb_Add_b = rtb_Sector_slect1_j;
        break;

      default:
        rtb_Sector_slect_d = (int16_T)-rtb_Add_b;

        /* MultiPortSwitch: '<S8>/Sector_slect1' incorporates:
         *  Gain: '<S8>/Gain5'
         *  Gain: '<S8>/Gain7'
         *  Gain: '<S9>/Gain3'
         *  Gain: '<S9>/Gain4'
         *  MultiPortSwitch: '<S8>/Sector_slect'
         *  Product: '<S8>/Product'
         */
        rtb_Add_b = (int16_T)-((147 * rtb_Gain3) >> 10);
        break;
    }

    /* End of MultiPortSwitch: '<S8>/Sector_slect' */

    /* Sum: '<S8>/Add2' incorporates:
     *  MultiPortSwitch: '<S8>/Sector_slect'
     *  MultiPortSwitch: '<S8>/Sector_slect1'
     */
    rtb_Sector_slect = (int16_T)(rtb_Sector_slect_d + rtb_Add_b);

    /* Switch: '<S8>/Switch' incorporates:
     *  Gain: '<S9>/Gain2'
     *  Gain: '<S9>/Gain3'
     *  MultiPortSwitch: '<S8>/Sector_slect'
     *  MultiPortSwitch: '<S8>/Sector_slect1'
     *  Product: '<S8>/Divide'
     *  Product: '<S8>/Divide1'
     *  RelationalOperator: '<S11>/Compare'
     *  Sum: '<S8>/Add2'
     *  Switch: '<S8>/Switch1'
     */
    if (rtb_Sector_slect > 4096)
    {
        rtb_Sector_slect_d = (int16_T)div_nde_s32_floor(rtb_Sector_slect_d << 12,
            rtb_Sector_slect);
        rtb_Gain3 = (int16_T)div_nde_s32_floor(rtb_Add_b << 12, rtb_Sector_slect);
    }
    else
    {
        rtb_Gain3 = rtb_Add_b;
    }

    /* End of Switch: '<S8>/Switch' */

    /* Sum: '<S9>/Add' incorporates:
     *  Gain: '<S9>/Gain2'
     *  Gain: '<S9>/Gain3'
     *  Sum: '<S9>/Add1'
     */
    rtb_Add_p_tmp_0 = rtb_Sector_slect_d + rtb_Gain3;

    /* Gain: '<S9>/Gain' incorporates:
     *  Constant: '<S9>/Constant'
     *  Gain: '<S9>/Gain1'
     *  Sum: '<S9>/Add'
     */
    rtb_Sector_slect_e_tmp = (int16_T)(4096 - rtb_Add_p_tmp_0) >> 1;

    /* Gain: '<S9>/Gain2' incorporates:
     *  Gain: '<S9>/Gain'
     *  Sum: '<S9>/Add1'
     */
    rtb_Sector_slect_d = (int16_T)((int16_T)(rtb_Add_p_tmp_0 +
        rtb_Sector_slect_e_tmp) >> 1);

    /* Gain: '<S9>/Gain3' incorporates:
     *  Gain: '<S9>/Gain1'
     *  Sum: '<S9>/Add2'
     */
    rtb_Gain3 = (int16_T)((int16_T)(rtb_Gain3 + (int16_T)rtb_Sector_slect_e_tmp)
                          >> 1);

    /* MultiPortSwitch: '<S9>/Sector_slect' incorporates:
     *  Gain: '<S9>/Gain1'
     *  Gain: '<S9>/Gain2'
     *  Gain: '<S9>/Gain3'
     *  Gain: '<S9>/Gain4'
     */
    switch (rtb_Sector_Lookup_Table)
    {
      case 1:
        rtb_Sector_slect = rtb_Sector_slect_d;

        /* MultiPortSwitch: '<S9>/Sector_slect1' incorporates:
         *  Gain: '<S9>/Gain2'
         *  Gain: '<S9>/Gain3'
         *  MultiPortSwitch: '<S9>/Sector_slect'
         */
        rtb_Sector_slect1_j = rtb_Gain3;

        /* MultiPortSwitch: '<S9>/Sector_slect2' incorporates:
         *  Gain: '<S9>/Gain1'
         *  Gain: '<S9>/Gain4'
         */
        rtb_Sector_slect_d = (int16_T)((int16_T)rtb_Sector_slect_e_tmp >> 1);
        break;

      case 2:
        rtb_Sector_slect = rtb_Gain3;

        /* MultiPortSwitch: '<S9>/Sector_slect1' incorporates:
         *  Gain: '<S9>/Gain2'
         *  Gain: '<S9>/Gain3'
         *  MultiPortSwitch: '<S9>/Sector_slect'
         */
        rtb_Sector_slect1_j = rtb_Sector_slect_d;

        /* MultiPortSwitch: '<S9>/Sector_slect2' incorporates:
         *  Gain: '<S9>/Gain1'
         *  Gain: '<S9>/Gain4'
         */
        rtb_Sector_slect_d = (int16_T)((int16_T)rtb_Sector_slect_e_tmp >> 1);
        break;

      case 3:
        rtb_Sector_slect = (int16_T)((int16_T)rtb_Sector_slect_e_tmp >> 1);

        /* MultiPortSwitch: '<S9>/Sector_slect1' incorporates:
         *  Gain: '<S9>/Gain1'
         *  Gain: '<S9>/Gain2'
         *  Gain: '<S9>/Gain4'
         *  MultiPortSwitch: '<S9>/Sector_slect'
         */
        rtb_Sector_slect1_j = rtb_Sector_slect_d;

        /* MultiPortSwitch: '<S9>/Sector_slect2' incorporates:
         *  Gain: '<S9>/Gain3'
         */
        rtb_Sector_slect_d = rtb_Gain3;
        break;

      case 4:
        rtb_Sector_slect = (int16_T)((int16_T)rtb_Sector_slect_e_tmp >> 1);

        /* MultiPortSwitch: '<S9>/Sector_slect1' incorporates:
         *  Gain: '<S9>/Gain1'
         *  Gain: '<S9>/Gain3'
         *  Gain: '<S9>/Gain4'
         *  MultiPortSwitch: '<S9>/Sector_slect'
         */
        rtb_Sector_slect1_j = rtb_Gain3;
        break;

      case 5:
        rtb_Sector_slect = rtb_Gain3;

        /* MultiPortSwitch: '<S9>/Sector_slect1' incorporates:
         *  Gain: '<S9>/Gain1'
         *  Gain: '<S9>/Gain3'
         *  Gain: '<S9>/Gain4'
         *  MultiPortSwitch: '<S9>/Sector_slect'
         */
        rtb_Sector_slect1_j = (int16_T)((int16_T)rtb_Sector_slect_e_tmp >> 1);
        break;

      default:
        rtb_Sector_slect = rtb_Sector_slect_d;

        /* MultiPortSwitch: '<S9>/Sector_slect1' incorporates:
         *  Gain: '<S9>/Gain1'
         *  Gain: '<S9>/Gain2'
         *  Gain: '<S9>/Gain4'
         *  MultiPortSwitch: '<S9>/Sector_slect'
         */
        rtb_Sector_slect1_j = (int16_T)((int16_T)rtb_Sector_slect_e_tmp >> 1);

        /* MultiPortSwitch: '<S9>/Sector_slect2' incorporates:
         *  Gain: '<S9>/Gain3'
         */
        rtb_Sector_slect_d = rtb_Gain3;
        break;
    }

    /* End of MultiPortSwitch: '<S9>/Sector_slect' */

    /* Outport: '<Root>/PWM_Duty_U' incorporates:
     *  DataTypeConversion: '<S4>/Data Type Conversion'
     *  Gain: '<S4>/Gain'
     */
    rtY.PWM_Duty_U = (uint16_T)((225 * rtb_Sector_slect) >> 7);

    /* Outport: '<Root>/PWM_Duty_V' incorporates:
     *  DataTypeConversion: '<S4>/Data Type Conversion'
     *  Gain: '<S4>/Gain'
     */
    rtY.PWM_Duty_V = (uint16_T)((225 * rtb_Sector_slect1_j) >> 7);

    /* Outport: '<Root>/PWM_Duty_W' incorporates:
     *  DataTypeConversion: '<S4>/Data Type Conversion'
     *  Gain: '<S4>/Gain'
     */
    rtY.PWM_Duty_W = (uint16_T)((225 * rtb_Sector_slect_d) >> 7);

    /* Outport: '<Root>/Section' */
    rtY.Section = rtb_Sector_Lookup_Table;

    /* Outport: '<Root>/Act_speed' incorporates:
     *  DataTypeConversion: '<S6>/Data Type Conversion'
     *  Sum: '<S21>/Add1'
     */
    rtY.Act_speed = (real32_T)rtb_Add1_b * 0.0009765625F;

    /* Update for UnitDelay: '<S17>/Unit Delay1' incorporates:
     *  Sum: '<S17>/Add'
     */
    rtDWork.UnitDelay1_DSTATE_g = rtb_Add_2;

    /* Update for UnitDelay: '<S15>/Unit Delay' incorporates:
     *  Gain: '<S15>/Gain'
     */
    rtDWork.UnitDelay_DSTATE_ln = (int16_T)tmp_0;

    /* Update for UnitDelay: '<S15>/Unit Delay1' */
    rtDWork.UnitDelay1_DSTATE = rtDWork.Add1_d;

    /* Update for UnitDelay: '<S18>/Unit Delay' */
    rtDWork.UnitDelay_DSTATE = rtDWork.Add1;

    /* Update for UnitDelay: '<S17>/Unit Delay' */
    rtDWork.UnitDelay_DSTATE_h = rtDWork.Add1;

    /* Update for UnitDelay: '<S20>/Unit Delay' incorporates:
     *  Product: '<S17>/Product'
     */
    rtDWork.UnitDelay_DSTATE_j = (int32_T)rtDWork.i1;

    /* Update for UnitDelay: '<S20>/Unit Delay1' incorporates:
     *  UnitDelay: '<S20>/Unit Delay'
     */
    rtDWork.UnitDelay1_DSTATE_h = rtDWork.UnitDelay_i;

    /* Update for UnitDelay: '<S20>/Unit Delay2' incorporates:
     *  UnitDelay: '<S20>/Unit Delay1'
     */
    rtDWork.UnitDelay2_DSTATE = rtDWork.UnitDelay1;

    /* Update for UnitDelay: '<S20>/Unit Delay3' incorporates:
     *  UnitDelay: '<S20>/Unit Delay2'
     */
    rtDWork.UnitDelay3_DSTATE = rtb_UnitDelay2;

    /* Update for UnitDelay: '<S20>/Unit Delay4' incorporates:
     *  UnitDelay: '<S20>/Unit Delay3'
     */
    rtDWork.UnitDelay4_DSTATE = rtb_UnitDelay3;

    /* Update for UnitDelay: '<S20>/Unit Delay5' incorporates:
     *  UnitDelay: '<S20>/Unit Delay4'
     */
    rtDWork.UnitDelay5_DSTATE = rtb_UnitDelay4;

    /* Update for UnitDelay: '<S20>/Unit Delay6' incorporates:
     *  UnitDelay: '<S20>/Unit Delay5'
     */
    rtDWork.UnitDelay6_DSTATE = rtb_UnitDelay5;

    /* Update for UnitDelay: '<S20>/Unit Delay7' incorporates:
     *  UnitDelay: '<S20>/Unit Delay6'
     */
    rtDWork.UnitDelay7_DSTATE = rtb_UnitDelay6;

    /* Update for UnitDelay: '<S21>/Unit Delay' incorporates:
     *  Sum: '<S21>/Add1'
     */
    rtDWork.UnitDelay_DSTATE_b = rtb_Add1_b;

    /* Update for UnitDelay: '<S16>/Unit Delay' incorporates:
     *  Switch: '<S16>/Switch'
     */
    rtDWork.UnitDelay_DSTATE_l = rtDWork.Add2_e;

    /* Update for UnitDelay: '<S16>/Unit Delay1' incorporates:
     *  Sum: '<S6>/Add'
     */
    rtDWork.UnitDelay1_DSTATE_p = rtb_Add_m;

    /* Update for UnitDelay: '<S19>/Unit Delay' incorporates:
     *  Sum: '<S19>/Add1'
     */
    rtDWork.UnitDelay_DSTATE_a = rtDWork.Saturation;
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
