/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.59
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Wed Jul 22 22:58:03 2015
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"

/* Named constants for Chart: '<S1>/Chart' */
#define Control_IN_TEMPORARY_DISABLED_c ((uint8_T)1U)
#define Controlle_IN_TEMPORARY_DISABLED ((uint8_T)3U)
#define Controller_IN_ERROR_STATE      ((uint8_T)1U)
#define Controller_IN_IDLE             ((uint8_T)1U)
#define Controller_IN_NORMAL_STATE     ((uint8_T)2U)
#define Controller_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define Controller_IN_OFF_STATE        ((uint8_T)1U)
#define Controller_IN_ON_STATE         ((uint8_T)2U)
#define Controller_IN_QUEUEING         ((uint8_T)2U)
#define Controller_IN_SEND_BREAK       ((uint8_T)1U)
#define Controller_IN_SEND_GO          ((uint8_T)2U)
#define Controller_IN_WAIT_A_LITTLE    ((uint8_T)2U)
#define NumBitsPerChar                 8U

extern real_T rt_powd_snf(real_T u0, real_T u1);

/* Forward declaration for local functions */
static void Cont_exit_internal_NORMAL_STATE(boolean_T *Controller_Y_break_cmd,
  boolean_T *Controller_Y_go_cmd, DW_Controller_T *Controller_DW);
extern real_T rtGetInf(void);
extern real32_T rtGetInfF(void);
extern real_T rtGetMinusInf(void);
extern real32_T rtGetMinusInfF(void);
extern real_T rtGetNaN(void);
extern real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
extern void rt_InitInfAndNaN(size_t realSize);
extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0 } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)((value!=value) ? 1U : 0U);
}

/* Test if single-precision value is not a number */
boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(((value!=value) ? 1U : 0U));
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = (rtNaN);
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Function for Chart: '<S1>/Chart' */
static void Cont_exit_internal_NORMAL_STATE(boolean_T *Controller_Y_break_cmd,
  boolean_T *Controller_Y_go_cmd, DW_Controller_T *Controller_DW)
{
  /* Exit Internal 'NORMAL_STATE': '<S2>:22' */
  if (Controller_DW->is_NORMAL_STATE == Controller_IN_ON_STATE) {
    /* Exit Internal 'ON_STATE': '<S2>:3' */
    if (Controller_DW->is_ON_STATE == Controller_IN_QUEUEING) {
      /* Exit Internal 'QUEUEING': '<S2>:14' */
      switch (Controller_DW->is_QUEUEING) {
       case Controller_IN_SEND_BREAK:
        /* Exit 'SEND_BREAK': '<S2>:38' */
        *Controller_Y_break_cmd = false;
        Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
        break;

       case Controller_IN_SEND_GO:
        /* Exit 'SEND_GO': '<S2>:37' */
        *Controller_Y_go_cmd = false;
        Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
        break;

       default:
        Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
        break;
      }

      Controller_DW->is_ON_STATE = Controller_IN_NO_ACTIVE_CHILD;
    } else {
      Controller_DW->is_ON_STATE = Controller_IN_NO_ACTIVE_CHILD;
    }

    Controller_DW->is_NORMAL_STATE = Controller_IN_NO_ACTIVE_CHILD;
  } else {
    Controller_DW->is_NORMAL_STATE = Controller_IN_NO_ACTIVE_CHILD;
  }
}

/* Model step function */
void Controller_step(RT_MODEL_Controller_T *const Controller_M, real_T
                     Controller_U_distance, real_T Controller_U_speed, boolean_T
                     Controller_U_gp_pressed, boolean_T Controller_U_bp_pressed,
                     boolean_T Controller_U_switch_on, int32_T
                     *Controller_Y_output_led, boolean_T *Controller_Y_break_cmd,
                     boolean_T *Controller_Y_go_cmd)
{
  P_Controller_T *Controller_P = ((P_Controller_T *)
    Controller_M->ModelData.defaultParam);
  DW_Controller_T *Controller_DW = ((DW_Controller_T *)
    Controller_M->ModelData.dwork);
  real_T rtb_Delay1;
  real_T rtb_Delay2;
  real_T rtb_Delay3;
  real_T rtb_Divide;
  real_T rtb_Delay1_h;
  real_T rtb_Delay2_e;
  real_T rtb_Delay3_g;
  real_T rtb_Divide_h;
  real_T rtb_MathFunction;
  boolean_T LogicalOperator1;
  boolean_T RelationalOperator;
  boolean_T LogicalOperator;
  boolean_T LogicalOperator2;

  /* Delay: '<S7>/Delay1' */
  rtb_Delay1 = Controller_DW->Delay1_DSTATE;

  /* Delay: '<S7>/Delay2' */
  rtb_Delay2 = Controller_DW->Delay2_DSTATE;

  /* Delay: '<S7>/Delay3' */
  rtb_Delay3 = Controller_DW->Delay3_DSTATE;

  /* Product: '<S7>/Divide' incorporates:
   *  Constant: '<S7>/Constant'
   *  Delay: '<S7>/Delay1'
   *  Delay: '<S7>/Delay2'
   *  Delay: '<S7>/Delay3'
   *  Delay: '<S7>/Delay4'
   *  Inport: '<Root>/speed '
   *  Sum: '<S7>/Sum1'
   *  Sum: '<S7>/Sum2'
   *  Sum: '<S7>/Sum3'
   *  Sum: '<S7>/Sum4'
   */
  rtb_Divide = ((((Controller_U_speed + Controller_DW->Delay1_DSTATE) +
                  Controller_DW->Delay2_DSTATE) + Controller_DW->Delay3_DSTATE)
                + Controller_DW->Delay4_DSTATE) / Controller_P->Constant_Value;

  /* Delay: '<S6>/Delay1' */
  rtb_Delay1_h = Controller_DW->Delay1_DSTATE_i;

  /* Delay: '<S6>/Delay2' */
  rtb_Delay2_e = Controller_DW->Delay2_DSTATE_c;

  /* Delay: '<S6>/Delay3' */
  rtb_Delay3_g = Controller_DW->Delay3_DSTATE_k;

  /* Product: '<S6>/Divide' incorporates:
   *  Constant: '<S6>/Constant'
   *  Delay: '<S6>/Delay1'
   *  Delay: '<S6>/Delay2'
   *  Delay: '<S6>/Delay3'
   *  Delay: '<S6>/Delay4'
   *  Inport: '<Root>/distance'
   *  Sum: '<S6>/Sum1'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   *  Sum: '<S6>/Sum4'
   */
  rtb_Divide_h = ((((Controller_U_distance + Controller_DW->Delay1_DSTATE_i) +
                    Controller_DW->Delay2_DSTATE_c) +
                   Controller_DW->Delay3_DSTATE_k) +
                  Controller_DW->Delay4_DSTATE_c) /
    Controller_P->Constant_Value_o;

  /* Logic: '<S5>/Logical Operator1' incorporates:
   *  Constant: '<S5>/Constant2'
   *  Constant: '<S5>/Constant3'
   *  Constant: '<S5>/Constant4'
   *  Logic: '<S5>/Logical Operator'
   *  RelationalOperator: '<S5>/Relational Operator1'
   *  RelationalOperator: '<S5>/Relational Operator2'
   *  RelationalOperator: '<S5>/Relational Operator3'
   */
  LogicalOperator1 = ((rtb_Divide > Controller_P->Constant2_Value) &&
                      (rtb_Divide < Controller_P->Constant3_Value) &&
                      (rtb_Divide_h < Controller_P->Constant4_Value));

  /* Product: '<S5>/Divide' incorporates:
   *  Constant: '<S5>/Constant'
   */
  rtb_MathFunction = rtb_Divide / Controller_P->Constant_Value_b;

  /* Math: '<S5>/Math Function' incorporates:
   *  Constant: '<S5>/Constant1'
   */
  if ((rtb_MathFunction < 0.0) && (Controller_P->Constant1_Value > floor
       (Controller_P->Constant1_Value))) {
    rtb_MathFunction = -rt_powd_snf(-rtb_MathFunction,
      Controller_P->Constant1_Value);
  } else {
    rtb_MathFunction = rt_powd_snf(rtb_MathFunction,
      Controller_P->Constant1_Value);
  }

  /* End of Math: '<S5>/Math Function' */

  /* RelationalOperator: '<S5>/Relational Operator' */
  RelationalOperator = (rtb_Divide_h < rtb_MathFunction);

  /* Logic: '<S4>/Logical Operator' incorporates:
   *  Inport: '<Root>/bp_pressed'
   *  Inport: '<Root>/gp_pressed'
   */
  LogicalOperator = (Controller_U_gp_pressed || Controller_U_bp_pressed);

  /* Logic: '<S3>/Logical Operator2' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Constant: '<S3>/Constant2'
   *  Constant: '<S3>/Constant3'
   *  Logic: '<S3>/Logical Operator1'
   *  Logic: '<S3>/Logical Operator5'
   *  RelationalOperator: '<S3>/Relational Operator'
   *  RelationalOperator: '<S3>/Relational Operator1'
   *  RelationalOperator: '<S3>/Relational Operator2'
   *  RelationalOperator: '<S3>/Relational Operator3'
   */
  LogicalOperator2 = ((rtb_Divide_h >= Controller_P->Constant_Value_i) &&
                      (rtb_Divide_h <= Controller_P->Constant1_Value_d) &&
                      ((rtb_Divide >= Controller_P->Constant2_Value_h) &&
                       (rtb_Divide <= Controller_P->Constant3_Value_c)));

  /* Chart: '<S1>/Chart' incorporates:
   *  Inport: '<Root>/switch_on'
   */
  if (Controller_DW->temporalCounter_i1 < 15U) {
    Controller_DW->temporalCounter_i1++;
  }

  /* Gateway: Controller/Chart */
  /* During: Controller/Chart */
  if (Controller_DW->is_active_c1_Controller == 0U) {
    /* Entry: Controller/Chart */
    Controller_DW->is_active_c1_Controller = 1U;

    /* Entry Internal: Controller/Chart */
    /* Transition: '<S2>:8' */
    Controller_DW->is_c1_Controller = Controller_IN_NORMAL_STATE;
    Controller_DW->is_NORMAL_STATE = Controller_IN_OFF_STATE;

    /* Outport: '<Root>/output_led' */
    /* Entry 'OFF_STATE': '<S2>:2' */
    *Controller_Y_output_led = 0;

    /* Outport: '<Root>/break_cmd' */
    *Controller_Y_break_cmd = false;

    /* Outport: '<Root>/go_cmd' */
    *Controller_Y_go_cmd = false;
  } else {
    switch (Controller_DW->is_c1_Controller) {
     case Controller_IN_ERROR_STATE:
      /* During 'ERROR_STATE': '<S2>:30' */
      if (LogicalOperator2) {
        /* Transition: '<S2>:33' */
        Controller_DW->is_c1_Controller = Controller_IN_NORMAL_STATE;
        Controller_DW->is_NORMAL_STATE = Controller_IN_ON_STATE;

        /* Entry Internal 'ON_STATE': '<S2>:3' */
        /* Transition: '<S2>:50' */
        Controller_DW->is_ON_STATE = Controller_IN_IDLE;

        /* Outport: '<Root>/output_led' */
        /* Entry 'IDLE': '<S2>:6' */
        *Controller_Y_output_led = 1;
      }
      break;

     case Controller_IN_NORMAL_STATE:
      /* During 'NORMAL_STATE': '<S2>:22' */
      if (!LogicalOperator2) {
        /* Transition: '<S2>:32' */
        Cont_exit_internal_NORMAL_STATE(Controller_Y_break_cmd,
          Controller_Y_go_cmd, Controller_DW);
        Controller_DW->is_c1_Controller = Controller_IN_ERROR_STATE;

        /* Outport: '<Root>/output_led' */
        /* Entry 'ERROR_STATE': '<S2>:30' */
        *Controller_Y_output_led = 5;
      } else if (Controller_DW->is_NORMAL_STATE == Controller_IN_OFF_STATE) {
        /* During 'OFF_STATE': '<S2>:2' */
        if (Controller_U_switch_on) {
          /* Transition: '<S2>:4' */
          Controller_DW->is_NORMAL_STATE = Controller_IN_ON_STATE;
          Controller_DW->is_ON_STATE = Controller_IN_IDLE;

          /* Outport: '<Root>/output_led' */
          /* Entry 'IDLE': '<S2>:6' */
          *Controller_Y_output_led = 1;
        }
      } else {
        /* During 'ON_STATE': '<S2>:3' */
        if (!Controller_U_switch_on) {
          /* Transition: '<S2>:5' */
          /* Exit Internal 'ON_STATE': '<S2>:3' */
          if (Controller_DW->is_ON_STATE == Controller_IN_QUEUEING) {
            /* Exit Internal 'QUEUEING': '<S2>:14' */
            switch (Controller_DW->is_QUEUEING) {
             case Controller_IN_SEND_BREAK:
              /* Outport: '<Root>/break_cmd' */
              /* Exit 'SEND_BREAK': '<S2>:38' */
              *Controller_Y_break_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;

             case Controller_IN_SEND_GO:
              /* Outport: '<Root>/go_cmd' */
              /* Exit 'SEND_GO': '<S2>:37' */
              *Controller_Y_go_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;

             default:
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;
            }

            Controller_DW->is_ON_STATE = Controller_IN_NO_ACTIVE_CHILD;
          } else {
            Controller_DW->is_ON_STATE = Controller_IN_NO_ACTIVE_CHILD;
          }

          Controller_DW->is_NORMAL_STATE = Controller_IN_OFF_STATE;

          /* Outport: '<Root>/output_led' */
          /* Entry 'OFF_STATE': '<S2>:2' */
          *Controller_Y_output_led = 0;

          /* Outport: '<Root>/break_cmd' */
          *Controller_Y_break_cmd = false;

          /* Outport: '<Root>/go_cmd' */
          *Controller_Y_go_cmd = false;
        } else if (Controller_DW->is_ON_STATE == Controller_IN_IDLE) {
          /* During 'IDLE': '<S2>:6' */
          if (LogicalOperator1) {
            /* Transition: '<S2>:40' */
            if (!RelationalOperator) {
              /* Transition: '<S2>:42' */
              Controller_DW->is_ON_STATE = Controller_IN_QUEUEING;
              Controller_DW->is_QUEUEING = Controller_IN_SEND_GO;

              /* Outport: '<Root>/output_led' */
              /* Entry 'SEND_GO': '<S2>:37' */
              *Controller_Y_output_led = 3;

              /* Outport: '<Root>/go_cmd' */
              *Controller_Y_go_cmd = true;
            } else {
              /* Transition: '<S2>:43' */
              Controller_DW->is_ON_STATE = Controller_IN_QUEUEING;
              Controller_DW->is_QUEUEING = Controller_IN_SEND_BREAK;

              /* Outport: '<Root>/output_led' */
              /* Entry 'SEND_BREAK': '<S2>:38' */
              *Controller_Y_output_led = 2;

              /* Outport: '<Root>/break_cmd' */
              *Controller_Y_break_cmd = true;
            }
          }
        } else {
          /* During 'QUEUEING': '<S2>:14' */
          if (!LogicalOperator1) {
            /* Transition: '<S2>:16' */
            /* Exit Internal 'QUEUEING': '<S2>:14' */
            switch (Controller_DW->is_QUEUEING) {
             case Controller_IN_SEND_BREAK:
              /* Outport: '<Root>/break_cmd' */
              /* Exit 'SEND_BREAK': '<S2>:38' */
              *Controller_Y_break_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;

             case Controller_IN_SEND_GO:
              /* Outport: '<Root>/go_cmd' */
              /* Exit 'SEND_GO': '<S2>:37' */
              *Controller_Y_go_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;

             default:
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;
            }

            Controller_DW->is_ON_STATE = Controller_IN_IDLE;

            /* Outport: '<Root>/output_led' */
            /* Entry 'IDLE': '<S2>:6' */
            *Controller_Y_output_led = 1;
          } else if (LogicalOperator) {
            /* Transition: '<S2>:18' */
            /* Exit Internal 'QUEUEING': '<S2>:14' */
            switch (Controller_DW->is_QUEUEING) {
             case Controller_IN_SEND_BREAK:
              /* Outport: '<Root>/break_cmd' */
              /* Exit 'SEND_BREAK': '<S2>:38' */
              *Controller_Y_break_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;

             case Controller_IN_SEND_GO:
              /* Outport: '<Root>/go_cmd' */
              /* Exit 'SEND_GO': '<S2>:37' */
              *Controller_Y_go_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;

             default:
              Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
              break;
            }

            Controller_DW->is_ON_STATE = Controller_IN_NO_ACTIVE_CHILD;
            Controller_DW->is_NORMAL_STATE = Controller_IN_NO_ACTIVE_CHILD;
            Controller_DW->is_c1_Controller = Controlle_IN_TEMPORARY_DISABLED;
            Controller_DW->is_TEMPORARY_DISABLED =
              Control_IN_TEMPORARY_DISABLED_c;

            /* Outport: '<Root>/output_led' */
            /* Entry 'TEMPORARY_DISABLED': '<S2>:17' */
            *Controller_Y_output_led = 4;
          } else if (Controller_DW->is_QUEUEING == Controller_IN_SEND_BREAK) {
            /* During 'SEND_BREAK': '<S2>:38' */
            if (!RelationalOperator) {
              /* Outport: '<Root>/break_cmd' */
              /* Transition: '<S2>:45' */
              /* Exit 'SEND_BREAK': '<S2>:38' */
              *Controller_Y_break_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_SEND_GO;

              /* Outport: '<Root>/output_led' */
              /* Entry 'SEND_GO': '<S2>:37' */
              *Controller_Y_output_led = 3;

              /* Outport: '<Root>/go_cmd' */
              *Controller_Y_go_cmd = true;
            }
          } else {
            /* During 'SEND_GO': '<S2>:37' */
            if (RelationalOperator) {
              /* Outport: '<Root>/go_cmd' */
              /* Transition: '<S2>:44' */
              /* Exit 'SEND_GO': '<S2>:37' */
              *Controller_Y_go_cmd = false;
              Controller_DW->is_QUEUEING = Controller_IN_SEND_BREAK;

              /* Outport: '<Root>/output_led' */
              /* Entry 'SEND_BREAK': '<S2>:38' */
              *Controller_Y_output_led = 2;

              /* Outport: '<Root>/break_cmd' */
              *Controller_Y_break_cmd = true;
            }
          }
        }
      }
      break;

     default:
      /* During 'TEMPORARY_DISABLED': '<S2>:47' */
      if (Controller_DW->is_TEMPORARY_DISABLED ==
          Control_IN_TEMPORARY_DISABLED_c) {
        /* During 'TEMPORARY_DISABLED': '<S2>:17' */
        if (!LogicalOperator) {
          /* Transition: '<S2>:49' */
          Controller_DW->is_TEMPORARY_DISABLED = Controller_IN_WAIT_A_LITTLE;
          Controller_DW->temporalCounter_i1 = 0U;
        }
      } else {
        /* During 'WAIT_A_LITTLE': '<S2>:48' */
        if (Controller_DW->temporalCounter_i1 >= 10U) {
          /* Transition: '<S2>:26' */
          Controller_DW->is_TEMPORARY_DISABLED = Controller_IN_NO_ACTIVE_CHILD;
          Controller_DW->is_c1_Controller = Controller_IN_NORMAL_STATE;
          Controller_DW->is_NORMAL_STATE = Controller_IN_ON_STATE;

          /* Entry Internal 'ON_STATE': '<S2>:3' */
          /* Transition: '<S2>:50' */
          Controller_DW->is_ON_STATE = Controller_IN_IDLE;

          /* Outport: '<Root>/output_led' */
          /* Entry 'IDLE': '<S2>:6' */
          *Controller_Y_output_led = 1;
        }
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Chart' */

  /* Update for Delay: '<S7>/Delay1' incorporates:
   *  Update for Inport: '<Root>/speed '
   */
  Controller_DW->Delay1_DSTATE = Controller_U_speed;

  /* Update for Delay: '<S7>/Delay2' */
  Controller_DW->Delay2_DSTATE = rtb_Delay1;

  /* Update for Delay: '<S7>/Delay3' */
  Controller_DW->Delay3_DSTATE = rtb_Delay2;

  /* Update for Delay: '<S7>/Delay4' */
  Controller_DW->Delay4_DSTATE = rtb_Delay3;

  /* Update for Delay: '<S6>/Delay1' incorporates:
   *  Update for Inport: '<Root>/distance'
   */
  Controller_DW->Delay1_DSTATE_i = Controller_U_distance;

  /* Update for Delay: '<S6>/Delay2' */
  Controller_DW->Delay2_DSTATE_c = rtb_Delay1_h;

  /* Update for Delay: '<S6>/Delay3' */
  Controller_DW->Delay3_DSTATE_k = rtb_Delay2_e;

  /* Update for Delay: '<S6>/Delay4' */
  Controller_DW->Delay4_DSTATE_c = rtb_Delay3_g;
}

/* Model initialize function */
void Controller_initialize(RT_MODEL_Controller_T *const Controller_M, real_T
  *Controller_U_distance, real_T *Controller_U_speed, boolean_T
  *Controller_U_gp_pressed, boolean_T *Controller_U_bp_pressed, boolean_T
  *Controller_U_switch_on, int32_T *Controller_Y_output_led, boolean_T
  *Controller_Y_break_cmd, boolean_T *Controller_Y_go_cmd)
{
  P_Controller_T *Controller_P = ((P_Controller_T *)
    Controller_M->ModelData.defaultParam);
  DW_Controller_T *Controller_DW = ((DW_Controller_T *)
    Controller_M->ModelData.dwork);

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* states (dwork) */
  (void) memset((void *)Controller_DW, 0,
                sizeof(DW_Controller_T));

  /* external inputs */
  (*Controller_U_distance) = 0.0;
  (*Controller_U_speed) = 0.0;
  (*Controller_U_gp_pressed) = false;
  (*Controller_U_bp_pressed) = false;
  (*Controller_U_switch_on) = false;

  /* external outputs */
  (*Controller_Y_output_led) = 0;
  (*Controller_Y_break_cmd) = false;
  (*Controller_Y_go_cmd) = false;

  /* InitializeConditions for Delay: '<S7>/Delay1' */
  Controller_DW->Delay1_DSTATE = Controller_P->Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<S7>/Delay2' */
  Controller_DW->Delay2_DSTATE = Controller_P->Delay2_InitialCondition;

  /* InitializeConditions for Delay: '<S7>/Delay3' */
  Controller_DW->Delay3_DSTATE = Controller_P->Delay3_InitialCondition;

  /* InitializeConditions for Delay: '<S7>/Delay4' */
  Controller_DW->Delay4_DSTATE = Controller_P->Delay4_InitialCondition;

  /* InitializeConditions for Delay: '<S6>/Delay1' */
  Controller_DW->Delay1_DSTATE_i = Controller_P->Delay1_InitialCondition_i;

  /* InitializeConditions for Delay: '<S6>/Delay2' */
  Controller_DW->Delay2_DSTATE_c = Controller_P->Delay2_InitialCondition_j;

  /* InitializeConditions for Delay: '<S6>/Delay3' */
  Controller_DW->Delay3_DSTATE_k = Controller_P->Delay3_InitialCondition_o;

  /* InitializeConditions for Delay: '<S6>/Delay4' */
  Controller_DW->Delay4_DSTATE_c = Controller_P->Delay4_InitialCondition_l;

  /* InitializeConditions for Chart: '<S1>/Chart' */
  Controller_DW->is_NORMAL_STATE = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DW->is_ON_STATE = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DW->is_QUEUEING = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DW->is_TEMPORARY_DISABLED = Controller_IN_NO_ACTIVE_CHILD;
  Controller_DW->temporalCounter_i1 = 0U;
  Controller_DW->is_active_c1_Controller = 0U;
  Controller_DW->is_c1_Controller = Controller_IN_NO_ACTIVE_CHILD;
}

/* Model terminate function */
void Controller_terminate(RT_MODEL_Controller_T *const Controller_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(Controller_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
