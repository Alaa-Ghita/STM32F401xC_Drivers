/**
* 
* @file    : Scheduler Configuration Source File
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "../Include/Sched.h"
 #include "../Include/Sched_cfg.h"
/********************************************************************************************************/

/************************************************Types***************************************************/
 const Runnable_t RunnablesUsed[_Runnables_Num] =
 {  [App1_Runnable] = { .Name            = "App1",
                        .delay_ms        = 3, 
                        .periodicity_ms  = 10,
                        .CallBack        = App1_Runnable},

    [App2_Runnable] = { .Name            = "App2",
                        .delay_ms        = 7, 
                        .periodicity_ms  = 5,
                        .CallBack        = App2_Runnable}
 };
 
/********************************************************************************************************/