/**
* 
* @file    : Scheduler Configuration Header File
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

#ifndef	 _SCHED_CFG_H_
#define	 _SCHED_CFG_H_

/**
 * @brief   : List of the Runnables implemented in the system, you can add any Runnable with any name
 * @note    : The Order of the Runnables here is the priority of them at executing 
 */
typedef enum{
    App1_Runnable,  /*An Example*/
    App2_Runnable,  /*An Example*/
    _Runnables_Num  /*MUST KEEP IT AS IT IS*/
}Runnables_t;

#endif /*_SCHED_CFG_H_*/