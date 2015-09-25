/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Controller.h
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

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#include <stddef.h>
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef Controller_COMMON_INCLUDES_
# define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_Controller_T RT_MODEL_Controller_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Delay1_DSTATE;                /* '<S7>/Delay1' */
  real_T Delay2_DSTATE;                /* '<S7>/Delay2' */
  real_T Delay3_DSTATE;                /* '<S7>/Delay3' */
  real_T Delay4_DSTATE;                /* '<S7>/Delay4' */
  real_T Delay1_DSTATE_i;              /* '<S6>/Delay1' */
  real_T Delay2_DSTATE_c;              /* '<S6>/Delay2' */
  real_T Delay3_DSTATE_k;              /* '<S6>/Delay3' */
  real_T Delay4_DSTATE_c;              /* '<S6>/Delay4' */
  uint8_T is_active_c1_Controller;     /* '<S1>/Chart' */
  uint8_T is_c1_Controller;            /* '<S1>/Chart' */
  uint8_T is_NORMAL_STATE;             /* '<S1>/Chart' */
  uint8_T is_ON_STATE;                 /* '<S1>/Chart' */
  uint8_T is_QUEUEING;                 /* '<S1>/Chart' */
  uint8_T is_TEMPORARY_DISABLED;       /* '<S1>/Chart' */
  uint8_T temporalCounter_i1;          /* '<S1>/Chart' */
} DW_Controller_T;

/* Parameters (auto storage) */
struct P_Controller_T_ {
  real_T Delay1_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<S7>/Delay1'
                                        */
  real_T Delay2_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<S7>/Delay2'
                                        */
  real_T Delay3_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<S7>/Delay3'
                                        */
  real_T Delay4_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<S7>/Delay4'
                                        */
  real_T Constant_Value;               /* Expression: 5
                                        * Referenced by: '<S7>/Constant'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 30
                                        * Referenced by: '<S5>/Constant3'
                                        */
  real_T Delay1_InitialCondition_i;    /* Expression: 0
                                        * Referenced by: '<S6>/Delay1'
                                        */
  real_T Delay2_InitialCondition_j;    /* Expression: 0
                                        * Referenced by: '<S6>/Delay2'
                                        */
  real_T Delay3_InitialCondition_o;    /* Expression: 0
                                        * Referenced by: '<S6>/Delay3'
                                        */
  real_T Delay4_InitialCondition_l;    /* Expression: 0
                                        * Referenced by: '<S6>/Delay4'
                                        */
  real_T Constant_Value_o;             /* Expression: 5
                                        * Referenced by: '<S6>/Constant'
                                        */
  real_T Constant4_Value;              /* Expression: 200
                                        * Referenced by: '<S5>/Constant4'
                                        */
  real_T Constant_Value_b;             /* Expression: 10
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 2
                                        * Referenced by: '<S5>/Constant1'
                                        */
  real_T Constant_Value_i;             /* Expression: 0
                                        * Referenced by: '<S3>/Constant'
                                        */
  real_T Constant1_Value_d;            /* Expression: 4000
                                        * Referenced by: '<S3>/Constant1'
                                        */
  real_T Constant2_Value_h;            /* Expression: 0
                                        * Referenced by: '<S3>/Constant2'
                                        */
  real_T Constant3_Value_c;            /* Expression: 200
                                        * Referenced by: '<S3>/Constant3'
                                        */
  uint32_T Delay1_DelayLength;         /* Computed Parameter: Delay1_DelayLength
                                        * Referenced by: '<S7>/Delay1'
                                        */
  uint32_T Delay2_DelayLength;         /* Computed Parameter: Delay2_DelayLength
                                        * Referenced by: '<S7>/Delay2'
                                        */
  uint32_T Delay3_DelayLength;         /* Computed Parameter: Delay3_DelayLength
                                        * Referenced by: '<S7>/Delay3'
                                        */
  uint32_T Delay4_DelayLength;         /* Computed Parameter: Delay4_DelayLength
                                        * Referenced by: '<S7>/Delay4'
                                        */
  uint32_T Delay1_DelayLength_h;       /* Computed Parameter: Delay1_DelayLength_h
                                        * Referenced by: '<S6>/Delay1'
                                        */
  uint32_T Delay2_DelayLength_c;       /* Computed Parameter: Delay2_DelayLength_c
                                        * Referenced by: '<S6>/Delay2'
                                        */
  uint32_T Delay3_DelayLength_l;       /* Computed Parameter: Delay3_DelayLength_l
                                        * Referenced by: '<S6>/Delay3'
                                        */
  uint32_T Delay4_DelayLength_b;       /* Computed Parameter: Delay4_DelayLength_b
                                        * Referenced by: '<S6>/Delay4'
                                        */
};

/* Parameters (auto storage) */
typedef struct P_Controller_T_ P_Controller_T;

/* Real-time Model Data Structure */
struct tag_RTM_Controller_T {
  const char_T * volatile errorStatus;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    P_Controller_T *defaultParam;
    DW_Controller_T *dwork;
  } ModelData;
};

/* Model entry point functions */
extern void Controller_initialize(RT_MODEL_Controller_T *const Controller_M,
  real_T *Controller_U_distance, real_T *Controller_U_speed, boolean_T
  *Controller_U_gp_pressed, boolean_T *Controller_U_bp_pressed, boolean_T
  *Controller_U_switch_on, int32_T *Controller_Y_output_led, boolean_T
  *Controller_Y_break_cmd, boolean_T *Controller_Y_go_cmd);
extern void Controller_step(RT_MODEL_Controller_T *const Controller_M, real_T
  Controller_U_distance, real_T Controller_U_speed, boolean_T
  Controller_U_gp_pressed, boolean_T Controller_U_bp_pressed, boolean_T
  Controller_U_switch_on, int32_T *Controller_Y_output_led, boolean_T
  *Controller_Y_break_cmd, boolean_T *Controller_Y_go_cmd);
extern void Controller_terminate(RT_MODEL_Controller_T *const Controller_M);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('qa/Controller')    - opens subsystem qa/Controller
 * hilite_system('qa/Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'qa'
 * '<S1>'   : 'qa/Controller'
 * '<S2>'   : 'qa/Controller/Chart'
 * '<S3>'   : 'qa/Controller/Data Checker'
 * '<S4>'   : 'qa/Controller/User Interaction Monitor'
 * '<S5>'   : 'qa/Controller/compute queue needing'
 * '<S6>'   : 'qa/Controller/distance avg computation'
 * '<S7>'   : 'qa/Controller/speed avg computation'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
