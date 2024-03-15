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
 
 #define MAX_RUNNNABLES             100
/********************************************************************************************************/



/************************************************Types***************************************************/
 /*The Datatype of the function to be passed as the call back function, to be called inside the handler*/
 typedef void (*RunnableCBF_t) (void);

 /**
  * @brief : The Datatype of all runnables created in the system, and passed to the Scheduler to handle them
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
 * @brief   : Function to Register a new runnable to the scheduler
 * @param   : (Add_runnable) a pointer to a struct of type Runnable_t (declared above)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : The pointer passed is NULL, or the priority of the passed runnable is not available
 */
 enuErrorStatus_t Sched_RegisterRunnable(Runnable_t * Add_runnable);

 /**
 * @brief   : Function to Start Running the scheduler
 */
 void Sched_Start(void);
/********************************************************************************************************/

#endif /*_SCHED_H_*/