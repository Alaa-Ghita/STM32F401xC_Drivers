/**
* 
* @file    : Scheduler Header File
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

#ifndef	 _SCHED_H_
#define	 _SCHED_H_

/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "ErrorStatus.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
 /*The Datatype of the function to be passed as the call back function, to be called inside the handler*/
 typedef void (*RunnableCBF_t) (void);

 /**
  * @brief : The Datatype of all runnables created in the system, you should add all the runnables you need in the Sched_cfg.c file 
 */
 typedef struct
 {
   /*The Name of the Runnable*/
   char * Name;
   /*The Time for the runnable to start running for the first time during the runtime*/
   uint32_t delay_ms;
   /*The Period between the each time the runnable run*/
   uint32_t periodicity_ms;
   /*The Priority of the runnable*/
   uint32_t priority;
   /*The Function to run (The runnable)*/
   RunnableCBF_t CallBack;
 }Runnable_t;
/********************************************************************************************************/



/************************************************APIs****************************************************/
 /**
 * @brief   : Function to intialize the neaded sources for the scheduler
 */
 void Sched_Init(void);

 /**
 * @brief   : Function to Start Running the scheduler
 */
 void Sched_Start(void);
/********************************************************************************************************/

#endif /*_SCHED_H_*/