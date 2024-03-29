/**
* 
* @file    : Configuration Header File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : LED Driver (HAL)
* Machine  : STM32F401xC 
* 
*/

#ifndef _LED_CFG_H_
#define _LED_CFG_H_


/************************************************Includes************************************************/
 
/********************************************************************************************************/


/************************************************Defines*************************************************/

/********************************************************************************************************/


/************************************************Types***************************************************/

 /*List of the LEDs wanted in the system, you can add any LED with any name*/
 typedef enum{
   Green_LED,      /*An Example*/
   Yellow_LED,    /*An Example*/
   Red_LED,       /*An Example*/
   _LED_num        /*MUST KEEP IT AS IT IS*/
 }LEDs_t;

/********************************************************************************************************/


/*************************************************APIs***************************************************/

/********************************************************************************************************/


#endif /*_LED_CFG_H_*/