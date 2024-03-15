/**
* 
* @file    : Scheduler Source File
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "../Include/Sched.h"
 #include "../Include/Sched_cfg.h"
 #include "SysTick.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define SCHED_TICK_TIME                          1
/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef struct
 {
    Runnable_t * runnable;
    uint32_t remainTime_ms;
 }RunnableInfo_t;
 
/********************************************************************************************************/



/************************************************Variables***********************************************/
 RunnableInfo_t Runnables[MAX_RUNNNABLES];
 static volatile uint32_t PendingTicks = 0;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
 static void Sched_Scheduler (void);
 static void Sched_TicksPendingCB(void);
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
 void Sched_Init(void)
 {
    SysTick_ConfigClkSrc(SYSTICK_CLK_SRC_PROCESSOR_CLK);
    SysTick_SetTime_ms(SCHED_TICK_TIME);
    SysTick_SetCallBack(Sched_TicksPendingCB);
 }


 enuErrorStatus_t Sched_RegisterRunnable(Runnable_t * Add_runnable)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if((Add_runnable) && (Runnables[Add_runnable->priority].runnable))
    {
        Runnables[Add_runnable->priority].runnable = Add_runnable;
        Runnables[Add_runnable->priority].remainTime_ms = Add_runnable->delay_ms;
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }

    return Ret_enuErrorStatus;
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
    for(RunIndex=0; RunIndex < MAX_RUNNNABLES; RunIndex++)
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


