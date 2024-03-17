/**
* 
* @file    : Configuration Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : LED Driver (HAL)
* Machine  : STM32F401xC 
* 
*/

/************************************************Includes************************************************/
 #include "GPIO.h"
 #include "LED.h"
 #include "LED_cfg.h"
/********************************************************************************************************/


/************************************************Defines*************************************************/

/********************************************************************************************************/


/************************************************Types***************************************************/

/********************************************************************************************************/


/************************************************Variables***********************************************/
 const LEDcfg_t LEDs[_LED_num] =
 {  [Green_LED]  = {.Port         = GPIO_PORT_A,
                    .Pin          = GPIO_PIN_0,
                    .Connection   = LED_CONNECTION_FORWARD,
                    .DefaultState = LED_STATE_OFF              },
                     
    [Yellow_LED] = {.Port         = GPIO_PORT_A,
                    .Pin          = GPIO_PIN_1,
                    .Connection   = LED_CONNECTION_FORWARD,
                    .DefaultState = LED_STATE_OFF             },

    [Red_LED]    = {.Port         = GPIO_PORT_A,
                    .Pin          = GPIO_PIN_2,
                    .Connection   = LED_CONNECTION_FORWARD,
                    .DefaultState = LED_STATE_OFF             } 
};
/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/

/********************************************************************************************************/