/**
* 
* @file    : NVIC Driver Header File (MCAL)
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Machine  : STM32F401xC 
* 
*/

#ifndef	 _NVIC_H_
#define	 _NVIC_H_


/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "ErrorStatus.h"
 #include "assert.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 

 /**
  * Priority Grouping Options
  * @brief  : These options represents the numebr of the last bit the Sub-Priority Group
  * @note   : Refer to the Datasheets of the Microcontroller you are using as the Interrupt Priority Register may not be represented in a full byte 
  */
  #define NVIC_PRIGROUP_SUB_BIT_0               0X05fa0000
  #define NVIC_PRIGROUP_SUB_BIT_1               0X05fa0100
  #define NVIC_PRIGROUP_SUB_BIT_2               0X05fa0200
  #define NVIC_PRIGROUP_SUB_BIT_3               0X05fa0300  
  #define NVIC_PRIGROUP_SUB_BIT_4               0X05fa0400
  #define NVIC_PRIGROUP_SUB_BIT_5               0X05fa0500
  #define NVIC_PRIGROUP_SUB_BIT_6               0X05fa0600
  #define NVIC_PRIGROUP_SUB_BIT_7               0X05fa0700
 /***************************/


/********************************************************************************************************/



/************************************************Types***************************************************/
 /**
  * @brief : The Active States for an IRQ
 */
 typedef enum{
    ActiveState_Inactive,
    ActiveState_Active
 }NVIC_ActiveState_t;

/********************************************************************************************************/



/************************************************APIs****************************************************/
 
 /**
 * @brief   : Function to enable an IRQ in the NVIC
 * @param   : The IRQ to be Enabled (Microcontroller Dependant)
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_EnableIRQ(uint32_t NVIC_IRQ);

 /**
 * @brief   : Function to Disable an IRQ in the NVIC
 * @param   : The IRQ to be Disabled (Microcontroller Dependant)
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_DisableIRQ(uint32_t NVIC_IRQ);

 /**
 * @brief   : Function to Set the pending state of an IRQ
 * @param   : The IRQ to Set its pending state (Microcontroller Dependant)
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_SetPending(uint32_t NVIC_IRQ);

 /**
 * @brief   : Function to Clear the pending state of an IRQ
 * @param   : The IRQ to Clear its pending state (Microcontroller Dependant)
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_ClearPending(uint32_t NVIC_IRQ);

 /**
 * @brief   : Function to Get the Active State on an IRQ
 * @param   : The IRQ to Get its Active State (Microcontroller Dependant)
 * @param   : A Pointer to variable of type NVIC_ActiveState_t to assign the Active State in it
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_GetActiveStatus(uint32_t NVIC_IRQ, NVIC_ActiveState_t * Add_u8pActiveState);

 /**
 * @brief   : Function to Generate a Software IRQ 
 * @param   : The IRQ to generate (Microcontroller Dependant)
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_Generate_SW_IRQ(uint32_t NVIC_IRQ);

 /**
 * @brief   : Function to Set the Priority Group Mode 
 * @param   : The number of the subpriority bit, you can choose from the options above (Microcontroller Dependant)
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_SetPriorityGroup(uint32_t NVIC_PRIGROUP_SUB_BIT);

 /**
 * @brief   : Function to Set the Priority of an IRQ (Preemption-Priority and Sub-Priority both as one value) 
 * @param   : The IRQ to set its priority (Microcontroller Dependant)
 * @param   : The Priority Value
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_SetIRQFullPriority(uint32_t NVIC_IRQ, uint32_t Copy_u8IRQ_PRIORITY);

  /**
 * @brief   : Function to Set the Priority of an IRQ (Preemption-Priority and Sub-Priority each as there own parameter) 
 * @param   : The IRQ to set its priority (Microcontroller Dependant)
 * @param   : The Preemption-Priority Value
 * @param   : The Sub-Priority Value
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_SetIRQPriority(uint32_t NVIC_IRQ, uint32_t Copy_u8PrePriority, uint32_t Copy_u8SubPriority);

 /**
 * @brief   : Function to Get the Priority Group Mode 
 * @param   : A pointer of type uint32_t to assign the priority value in it, the value is one of the above options (The number of the subpriority bit)
 * @return  : It returns a variable of type enuErrorStatus_t with "enuErrorStatus_Ok" of value if the Operation was Successful
 * @note    : Please note that this is a Generic Driver for ARM Cortex-M(3,4) Processors, so you must refer to the datasheets
 *            of the spacific Microcontroller you are working with to get more details about the IRQs used in the chip.
 */
 enuErrorStatus_t NVIC_GetPriority(uint32_t * Add_u8pPriority);
/********************************************************************************************************/



#endif /*_NVIC_H_*/