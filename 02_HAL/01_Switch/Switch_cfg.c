/**
* 
* @file    : Configuration Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : Switch Driver (HAL)
* Machine  : STM32F401xC 
* 
*/

/************************************************Includes************************************************/
 #include "GPIO.h"
 #include "Switch.h"
 #include "Switch_cfg.h"
/********************************************************************************************************/


/************************************************Defines*************************************************/

/********************************************************************************************************/


/************************************************Types***************************************************/

/********************************************************************************************************/


/************************************************Variables***********************************************/
 const Switchcfg_t Switches[_Switch_num]
 {
    [PowerON_Switch]   = {.Port         = GPIO_PORT_A,
                          .Pin          = GPIO_PIN_1,
                          .Connection   = Switch_CONNECTION_FORWARD},
                     
    [PowerOFF_Switch] = {.Port         = GPIO_PORT_B,
                         .Pin          = GPIO_PIN_1,
                         .Connection   = Switch_CONNECTION_REVERSE },
 };
/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/

/********************************************************************************************************/