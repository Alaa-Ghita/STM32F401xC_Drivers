/**
* 
* @file    : Header File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : Switch Driver (HAL)
* Machine  : STM32F401xC 
* 
*/

#ifndef _SWITCH_H_
#define _SWITCH_H_

/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "Switch_cfg.h"
/********************************************************************************************************/


/************************************************Defines*************************************************/
 /*Switch_CONNECTION Options*/
 #define SWITCH_CONNECTION_FORWARD         0   /*The Switch is connected with an Internal Pull-up */
 #define SWITCH_CONNECTION_REVERSE         1   /*The Switch is connected with an Internal Pull-down */

/********************************************************************************************************/


/************************************************Types***************************************************/
 /**
 *@brief: A struct used to create a new switch in the system, contains all the attributes that every switch must have defined.
 */
 typedef struct{
 uint32_t Port;
 uint32_t Pin;
 uint32_t Connection;
 }Switchcfg_t;
 
 /**
 *@brief: enum of the states that a switch can be on them.
 */
 typedef enum{
    uint32_t enuSwitch_Released;
    uint32_t enuSwitch_Pressed;
 }enuSwitchState_t;

 typedef enum
 {
    /**
 	*@brief : Everything OK, The Function Performed Correctly.
	*/
    enuErrorStatus_Ok,
    /**
	*@brief : Something went Wrong, The Function didn't Perform Incorrectly.
	*/
    enuErrorStatus_NotOk,
    /**
	*@brief : Passing NULL Pointer.
	*/
    enuErrorStatus_NULLPointer,
    /**
	*@brief : The Function Timed out.
	*/ 
    enuErrorStatus_Timeout,
    /**
	*@brief : The Function Timed out.
	*/ 
    enuErrorStatus_InvalidParameter,
    /**
    *@brief : Something is wrong in the configurations
    */
    enuErrorStatus_InvalidCfg

 }enuErrorStatus_t;
/********************************************************************************************************/


/*************************************************APIs***************************************************/
 /**
 * @brief   : Function to initialize all of the Switches 
 * @param   : It Doesn't take any parameters, but be sure to configure the Switches you want in the configuration files(Switch_cfg.h and Switch_cfg.c)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidCfg         : The configuration of the Switch is not valid
 */
 enuErrorStatus_t Switch_init(void);


 /**
 * @brief   : Function to get the State of a Switch
 * @param   : It takes two parameters, 
 *            First: The Switch Name,
 *            Second: Pointer of type enuSwitchState_t to get the Switch State in it (It assign one of the two values of the enuSwitchState_t metioned above).
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : The Switch doesn't exist
 *            enuErrorStatus_NULLPointer        : The pointer parameter equals to NULL
 */
 enuErrorStatus_t Switch_GetStatus(uint32_t Copy_u32Switch, enuSwitchState_t * Add_enuSwitchState);
/********************************************************************************************************/


#endif /*_SWITCH_H_*/