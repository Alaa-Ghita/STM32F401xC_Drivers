/**
* 
* @file    : Scheduler Configuration Source File
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "Sched.h"
#include "Sched_cfg.h"
/********************************************************************************************************/

/*******************************Call Back Functions (Runnable Functions)********************************/
 extern void TrafficLight_Runnable(void);
/********************************************************************************************************/

/************************************************Types***************************************************/
 const Runnable_t RunnablesUsed[_Runnables_Num] =
 {
    [TrafficLight_Run] = { .Name            = "Traffic Light",
                           .delay_ms        = 0,
                           .periodicity_ms  = 1000,
                           .CallBack        = TrafficLight_Runnable},

    /*[App2_Runnable] = { .Name            = "App2",
                        .delay_ms        = 7, 
                        .periodicity_ms  = 5,
                        .CallBack        = App2_Runnable}*/
 };
 
/********************************************************************************************************/
