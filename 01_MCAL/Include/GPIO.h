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
#include "../../00_LIB/Typedefs.h"
#include "../../00_LIB/MASKS"
/*********/

/*Defines*/

 /*GPIO Port Options*/
 #define GPIO_PORT_A   0
 #define GPIO_PORT_B   1
 #define GPIO_PORT_C   2

 /*GPIO Pins Options*/
 #define GPIO_PIN_0      0
 #define GPIO_PIN_1      1
 #define GPIO_PIN_2      2   
 #define GPIO_PIN_3      3
 #define GPIO_PIN_4      4
 #define GPIO_PIN_5      5
 #define GPIO_PIN_6      6   
 #define GPIO_PIN_7      7
 #define GPIO_PIN_8      8
 #define GPIO_PIN_9      9
 #define GPIO_PIN_10     10
 #define GPIO_PIN_11     11
 #define GPIO_PIN_12     12
 #define GPIO_PIN_13     13
 #define GPIO_PIN_14     14
 #define GPIO_PIN_15     15

 /*GPIO Modes Options*/                   
 #define GPIO_MODE_IN                      0x00000000      /*Input Pin (without Pullup nor Pulldown)*/
 #define GPIO_MODE_OUT_PP                  0x00000001      /*Output Pin of type PushPull (without Pullup nor Pulldown)*/       
 #define GPIO_MODE_OUT_OD                  0x00000011      /*Output Pin of type OpenDrain*/
 #define GPIO_MODE_AF_PP                   0x00000002      /*Alternate Function Pin of type PushPull (without Pullup nor Pulldown)*/
 #define GPIO_MODE_AF_OD                   0x00000012      /*Alternate Function Pin of type OpenDrain (without Pullup nor Pulldown)*/
 #define GPIO_MODE_ANALOG                  0x00000003      /*Analog pin*/

 /*GPIO Pull-up Pull-down Options*/
 #define GPIO_PUPD_NONE                    0x00000000     /*No Pull-up Nor Pull-down*/
 #define GPIO_PUPD_PU                      0x00000001     /*Pull-up*/
 #define GPIO_PUPD_PD                      0x00000002     /*Pull-down*/

 /*GPIO Output Speed Options*/
 #define GPIO_OSPEED_LOW                   0x00000000
 #define GPIO_OSPEED_MEDIUM                0x00000001
 #define GPIO_OSPEED_HIGH                  0x00000002
 #define GPIO_OSPEED_VERYHIGH              0x00000003

 /*GPIO Alternate Function Options*/
 #define GPIO_AF_0                         0x00
 #define GPIO_AF_1                         0x01
 #define GPIO_AF_2                         0x02
 #define GPIO_AF_3                         0x03
 #define GPIO_AF_4                         0x04
 #define GPIO_AF_5                         0x05
 #define GPIO_AF_6                         0x06
 #define GPIO_AF_7                         0x07
 #define GPIO_AF_8                         0x08
 #define GPIO_AF_9                         0x09
 #define GPIO_AF_10                        0x0a
 #define GPIO_AF_11                        0x0b
 #define GPIO_AF_12                        0x0c
 #define GPIO_AF_13                        0x0d
 #define GPIO_AF_14                        0x0e
 #define GPIO_AF_15                        0x0f

 /*Pin Output Value Options*/
 #define PIN_VALUE_HIGH                    0x01
 #define PIN_VALUE_LOW                     0x02

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
 enuErrorStatus_t GPIO_InitPin(GPIO_PinCfg_t * Pin_Cfg);

 /**
 * @brief   : Function to set an output pin High or Low
 * @param   : It takes a pointer to a variable of type GPIO_PinCfg_t containing the desired configurations
 *          & the value to be presented on the pin.
*            (Please just choose from the provided options above)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : The pointer parameter equals to NULL
 *            enuErrorStatus_InvalidCfg         : The pin is not configured as an output pin
 *            enuErrorStatus_InvalidParameter   : The Pin Value is not valid
 */
 enuErrorStatus_t GPIO_SetPinValue(GPIO_PinCfg_t * Pin_Cfg, uint32_t PIN_VALUE);

 /**
 * @brief   : Function to get the current value represented on the pin.
 * @param   : It takes a pointer to a variable of type GPIO_PinCfg_t containing the desired configurations
 *          & a Pointer to uint32_t to return the pin state on it
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values:
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : One or both of the pointer parameters equal to NULL
 *            enuErrorStatus_InvalidCfg         : The configuration of the pin is not right
 */
 enuErrorStatus_t GPIO_GetPinValue(GPIO_PinCfg_t * Pin_Cfg, uint32_t * Pin_State);

/*****/



#endif /*_GPIO_H_*/