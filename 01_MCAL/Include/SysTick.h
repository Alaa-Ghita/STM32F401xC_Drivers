/**
* 
* @file    : SysTick Driver Header File (MCAL)
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

#ifndef	 _SYSTICK_H_
#define	 _SYSTICK_H_

/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "ErrorStatus.h"
 #include "MASKS.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 /*SysTick Clock Source options*/
 #define SYSTICK_CLK_SRC_EXTERNAL_CLK           (uint32_t)0x00 /*The SysTick Clock source is an external clock (The clock from the RCC (AHB1/8))*/
 #define SYSTICK_CLK_SRC_PROCESSOR_CLK          (uint32_t)0x01 /*The Systick Clock Source is the same as the processor clock*/

 /*SysTick Start Modes */
 #define SYSTICK_MODE_PERIODIC                  (uint32_t)0x000000002 /*The Systick will Count this value none stop, generating an exception each time it reaches the zero*/
 #define SYSTICK_MODE_ONE_TIME                  (uint32_t)0x000000000 /*The Systick will Count this value only once*/
/********************************************************************************************************/



/************************************************Types***************************************************/
 /**
  * @brief : The states of the SysTick Timer, Is it Counting or has it reached Zero
 */
 typedef enum{
    enuTimerState_Counting,
    enuTimerState_Expired
 }enuTimerState_t;

 /*The Datatype of the function to be passed as the call back function, to be called inside the handler*/
 typedef void (*SysTickCBF_t) (void);
/********************************************************************************************************/



/************************************************APIs****************************************************/
 /**
 * @brief   : Function to configure the SysTick Clock Source 
 * @param   : The SysTick Clock Source (Use the Options declared above)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidCfg         : The Clock Source configured is not valid.
 */
 enuErrorStatus_t SysTick_ConfigClkSrc(uint32_t SYSTICK_CLK_SRC);


 /**
 * @brief   : Function to set Time in Milliseconds
 * @param   : It takes a variable of type uint32_t with the value of time desired to set in Milliseconds.
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : The value passed to the function is too big.
 *                                                (In this case you can either Pass a smaller Time value, or configure the Clock Source Frequency to a smaller value)
 */
 enuErrorStatus_t SysTick_SetTime_ms(uint32_t Copy_u32Time_ms);


 /**
 * @brief   : Function to Start the SysTick Timer
 * @param   : The mode of the SysTick To Start (Use the Options declared above)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : The input Mode is not valid
 */
 enuErrorStatus_t SysTick_Start(uint32_t SYSTICK_MODE);


 /**
 * @brief   : Function to Stop the SysTick (Disable it)
 */
 void SysTick_Stop(void);


  /**
 * @brief   : Function to check if the SysTick has reached Zero before or not yet
 * @param   : It takes a pointer to a variable of type enuTimerState_t to assign in it the state of the SysTick(either enuTimerState_Counting, or enuTimerState_Expired)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : The pointer parameter equals to NULL
 */
 enuErrorStatus_t SysTick_IsExpired(enuTimerState_t * Add_enupTimerState);


 /**
 * @brief   : Function to to set the call back function that will be called when the SysTick interrupt occurs
 * @param   : It takes a pointer to a function of type SysTickCBF_t, to be called in the handler
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : The pointer passed to the function equals to NULL
 */
 enuErrorStatus_t SysTick_SetCallBack(SysTickCBF_t Add_CallBackFunc);
/********************************************************************************************************/




#endif /*_SYSTICK_H_*/