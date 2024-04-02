/**
* 
* @file    : Header File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : GPIO Driver
* Machine  : STM32F401xC 
* 
*/



#ifndef _GPIO_H_
#define _GPIO_H_


/*Includes*/
#include "Typedefs.h"
#include "MASKS.h"
#include "ErrorStatus.h"
/*********/

/*Defines*/

 /*GPIO Port Options*/
 #define GPIO_PORT_A   (uint32_t)0
 #define GPIO_PORT_B   (uint32_t)1
 #define GPIO_PORT_C   (uint32_t)2

 /*GPIO Pins Options*/
 #define GPIO_PIN_0      (uint32_t)0
 #define GPIO_PIN_1      (uint32_t)1
 #define GPIO_PIN_2      (uint32_t)2   
 #define GPIO_PIN_3      (uint32_t)3
 #define GPIO_PIN_4      (uint32_t)4
 #define GPIO_PIN_5      (uint32_t)5
 #define GPIO_PIN_6      (uint32_t)6   
 #define GPIO_PIN_7      (uint32_t)7
 #define GPIO_PIN_8      (uint32_t)8
 #define GPIO_PIN_9      (uint32_t)9
 #define GPIO_PIN_10     (uint32_t)10
 #define GPIO_PIN_11     (uint32_t)11
 #define GPIO_PIN_12     (uint32_t)12
 #define GPIO_PIN_13     (uint32_t)13
 #define GPIO_PIN_14     (uint32_t)14
 #define GPIO_PIN_15     (uint32_t)15

 /*GPIO Modes Options*/                   
 #define GPIO_MODE_IN                      (uint32_t)0x00000000      /*Input Pin (without Pullup nor Pulldown)*/
 #define GPIO_MODE_OUT_PP                  (uint32_t)0x00000001      /*Output Pin of type PushPull (without Pullup nor Pulldown)*/       
 #define GPIO_MODE_OUT_OD                  (uint32_t)0x00000011      /*Output Pin of type OpenDrain*/
 #define GPIO_MODE_AF_PP                   (uint32_t)0x00000002      /*Alternate Function Pin of type PushPull (without Pullup nor Pulldown)*/
 #define GPIO_MODE_AF_OD                   (uint32_t)0x00000012      /*Alternate Function Pin of type OpenDrain (without Pullup nor Pulldown)*/
 #define GPIO_MODE_ANALOG                  (uint32_t)0x00000003      /*Analog pin*/

 /*GPIO Pull-up Pull-down Options*/
 #define GPIO_PUPD_NONE                    (uint32_t)0x00000000     /*No Pull-up Nor Pull-down*/
 #define GPIO_PUPD_PU                      (uint32_t)0x00000001     /*Pull-up*/
 #define GPIO_PUPD_PD                      (uint32_t)0x00000002     /*Pull-down*/

 /*GPIO(uint32_t) Output Speed Options*/
 #define GPIO_OSPEED_LOW                   (uint32_t)0x00000000
 #define GPIO_OSPEED_MEDIUM                (uint32_t)0x00000001
 #define GPIO_OSPEED_HIGH                  (uint32_t)0x00000002
 #define GPIO_OSPEED_VERYHIGH              (uint32_t)0x00000003

 /*GPIO Alternate Function Options*/
 #define GPIO_AF_0                         (uint32_t)0x00
 #define GPIO_AF_1                         (uint32_t)0x01
 #define GPIO_AF_2                         (uint32_t)0x02
 #define GPIO_AF_3                         (uint32_t)0x03
 #define GPIO_AF_4                         (uint32_t)0x04
 #define GPIO_AF_5                         (uint32_t)0x05
 #define GPIO_AF_6                         (uint32_t)0x06
 #define GPIO_AF_7                         (uint32_t)0x07
 #define GPIO_AF_8                         (uint32_t)0x08
 #define GPIO_AF_9                         (uint32_t)0x09
 #define GPIO_AF_10                        (uint32_t)0x0a
 #define GPIO_AF_11                        (uint32_t)0x0b
 #define GPIO_AF_12                        (uint32_t)0x0c
 #define GPIO_AF_13                        (uint32_t)0x0d
 #define GPIO_AF_14                        (uint32_t)0x0e
 #define GPIO_AF_15                        (uint32_t)0x0f

 /*Pin Output Value Options*/
 #define PIN_VALUE_HIGH                    (uint32_t)0x01
 #define PIN_VALUE_LOW                     (uint32_t)0x00

/*********/

/*Types*/
 
 /**
 * @brief : The options allowed for each member in this struct is metioned above
 * @note  : In stm32f401xc Port C has only pin13, pin14, and pin15. While both Ports A & B Support all the pins from 0 to 15
 */
 typedef struct
 {
   uint32_t GPIO_PORT;
   uint32_t GPIO_PIN;
   uint32_t GPIO_MODE;
   uint32_t GPIO_PUPD;
   uint32_t GPIO_OSPEED;

 }GPIO_PinCfg_t;

/******/

/*APIs*/

 /**
 * @brief   : Function to initialize a single Pin in the GPIO 
 * @param   : It takes a pointer to a variable of type GPIO_PinCfg_t containing the desired configurations
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : The pointer parameter equals to NULL
 *            enuErrorStatus_InvalidCfg         : The configuration of the pin is not right
 */
 enuErrorStatus_t GPIO_InitPin(GPIO_PinCfg_t * const Pin_Cfg);

 /**
 * @brief   : Function to set an output pin High or Low
 * @param   : It takes the Pin to be set and the Port of that Pin (Choose from the Options above)
 *          & the value to be presented on the pin.
 *            (Please just choose from the provided options above)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : The pointer parameter equals to NULL
 *            enuErrorStatus_InvalidCfg         : The pin is not configured as an output pin
 *            enuErrorStatus_InvalidParameter   : The Pin Value is not valid
 */
 enuErrorStatus_t GPIO_SetPinValue(uint32_t GPIO_PIN, uint32_t GPIO_PORT, uint32_t PIN_VALUE);

 /**
 * @brief   : Function to get the current value represented on the pin.
 * @param   : It takes the Pin to get its state and the Port of that Pin (Choose from the Options above)
 *          & a Pointer to uint32_t to return the pin state on it
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : One or both of the pointer parameters equal to NULL
 *            enuErrorStatus_InvalidCfg         : The configuration of the pin is not right
 */
 enuErrorStatus_t GPIO_GetPinValue(uint32_t GPIO_PIN, uint32_t GPIO_PORT, uint32_t * Pin_State);

/*****/



#endif /*_GPIO_H_*/
