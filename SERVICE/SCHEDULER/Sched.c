/**
* 
* @file    : Scheduler Source File
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "Sched.h"
#include "Sched_cfg.h"
#include "SysTick.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
  #define SCHED_TICK_TIME           1000
/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef struct
 {
    Runnable_t * runnable;
    uint32_t remainTime_ms;
 }RunnableInfo_t;
 
/********************************************************************************************************/



/************************************************Variables***********************************************/
 RunnableInfo_t Runnables[_Runnables_Num];
 extern const Runnable_t RunnablesUsed[_Runnables_Num];
 static volatile uint32_t PendingTicks = 0;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
 static void Sched_Scheduler (void);
 static void Sched_TicksPendingCB(void);
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
 void Sched_Init(void)
 {
    uint32_t Current_Runnable;

    SysTick_ConfigClkSrc(SYSTICK_CLK_SRC_PROCESSOR_CLK);
    SysTick_SetTime_ms(SCHED_TICK_TIME);
    SysTick_SetCallBack(Sched_TicksPendingCB);

    for(Current_Runnable = 0; Current_Runnable < _Runnables_Num; Current_Runnable++)
    {
        Runnables[Current_Runnable].runnable = &RunnablesUsed[Current_Runnable];
        Runnables[Current_Runnable].remainTime_ms = RunnablesUsed[Current_Runnable].delay_ms;
    }
 }


 void Sched_Start(void)
 {
    SysTick_Start(SYSTICK_MODE_PERIODIC);
    while(1)
    {
        if(PendingTicks)
        {
            PendingTicks--;
            Sched_Scheduler();
        }
    }
 }

 static void Sched_Scheduler (void)
 {
    uint32_t RunIndex;
    for(RunIndex=0; RunIndex < _Runnables_Num; RunIndex++)
    {
        if((Runnables[RunIndex].runnable->CallBack) && (Runnables[RunIndex].remainTime_ms == 0))
        {
            Runnables[RunIndex].runnable->CallBack();
            Runnables[RunIndex].remainTime_ms = Runnables[RunIndex].runnable->periodicity_ms;
        }
        Runnables[RunIndex].remainTime_ms -= SCHED_TICK_TIME;
    }
 }


 static void Sched_TicksPendingCB(void)
 {
    PendingTicks++;
 }
/********************************************************************************************************/


