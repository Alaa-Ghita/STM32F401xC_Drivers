/**
* 
* @file    : Header File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : LED Driver (HAL)
* Machine  : STM32F401xC 
* 
*/

#ifndef _LED_H_
#define _LED_H_

/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "LED_cfg.h"
 #include "ErrorStatus.h"
/********************************************************************************************************/


/************************************************Defines*************************************************/
 /*LED_CONNECTION Options*/
 #define LED_CONNECTION_FORWARD         0   /*The LED is connected with an Internal Pull-up */
 #define LED_CONNECTION_REVERSE         1   /*The LED is connected with an Internal Pull-down */

 /*LED_STATE Options*/
 #define LED_STATE_ON                   1   /*The LED is turned ON*/
 #define LED_STATE_OFF                  0   /*The LED is turned OFF*/
/********************************************************************************************************/


/************************************************Types***************************************************/
 typedef struct{
 uint32_t Port;
 uint32_t Pin;
 uint32_t Connection;
 uint32_t DefaultState;
 }LEDcfg_t;

/********************************************************************************************************/


/*************************************************APIs***************************************************/
 /**
 * @brief   : Function to initialize all of the LEDs 
 * @param   : It Doesn't take any parameters, but be sure to configure the LEDs you want in the configuration files(LED_cfg.h and LED_cfg.c)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidCfg         : The configuration of the LED is not valid
 */
 enuErrorStatus_t LED_init(void);


 /**
 * @brief   : Function to Set a State to the LED (Either LED_STATE_ON or LED_STATE_OFF)
 * @param   : It takes two parameters, First: The LED Name, Second: The LED State.
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : One or Two of the parameters is not valid
                                                  (Either the LED doesn't exists, or The LED_STATE is not correct) 
 */
 enuErrorStatus_t LED_SetStatus(uint32_t Copy_u32LED, uint32_t LED_STATE);
/********************************************************************************************************/


#endif /*_LED_H_*/