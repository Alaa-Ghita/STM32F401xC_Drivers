/*
* 
* File    : Header File
* Driver  : RCC Driver
* Machine : ARM 
* MC      : STM32F401xC 
* Auther  : Alaa Ghita
* Date    : Feb 2024
* 
*/

#ifndef _RCC_H_ 
#define _RCC_H_

#include "Typedefs.h"

/*#defines*/
 #define SYSCLK_HSI        0x00
 #define SYSCLK_HSE        0x01
 #define SYSCLK_PLL        0x02

 #define CLK_ON_HSI        BIT0_MASK
 #define CLK_ON_HSE        BIT16_MASK
 #define CLK_ON_PLL        BIT24_MASK
 #define CLK_ON_HSEBYP     BIT18_MASK
 #define CLK_ON_PLLI2S     BIT26_MASK
 #define CLK_ON_CSS        BIT19_MASK

 #define PLLSCR_HSI        (~(BIT22_MASK))
 #define PLLSRC_HSE        BIT22_MASK

 #define PRE_AHB1_1        0x70
 #define PRE_AHB1_2        0x80
 #define PRE_AHB1_4        0x90
 #define PRE_AHB1_8        0xa0
 #define PRE_AHB1_16       0xb0
 #define PRE_AHB1_64       0xc0
 #define PRE_AHB1_128      0xd0
 #define PRE_AHB1_256      0xe0
 #define PRE_AHB1_512      0xf0

 #define PRE_APB1_1        0x0c00
 #define PRE_APB1_2        0x1000
 #define PRE_APB1_4        0x1400
 #define PRE_APB1_8        0x1800
 #define PRE_APB1_16       0x1c00

 #define PRE_APB2_1        0x6000
 #define PRE_APB2_2        0x8000
 #define PRE_APB2_4        0xa000
 #define PRE_APB2_8        0xc000
 #define PRE_APB2_16       0xe000

/**********/

/*types*/

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
   enuErrorStatus_timeout

 }enuErrorStatus_t;

/**********/

/*APIs*/
 
 /**
 *@brief  : Function to Select the System Clock.
 *@param  : Takes one paramtere as the selected system clock (Choose from the options above).
 *@return : Error State.                                                                     
 */
 enuErrorStatus_t RCC_SelectSysCLK(uint32_t SYSCLK);

 /**
 *@brief  : Function to turn ON a Clock.
 *@param  : Takes one parameter as the clock to be turned ON (Choose from the options above).
 *@return : Error State.                                                                     
 */
 enuErrorStatus_t RCC_TurnONCLK(uint32_t CLK_ON);

  /**
 *@brief  : Function to turn OFF a Clock.
 *@param  : Takes one parameter as the clock to be turned OFF (Choose from the options above).
 *@return : Error State.                                                                     
 */
 enuErrorStatus_t RCC_TurnOFFCLK(uint32_t CLK_ON);
 
 /**
 *@brief  : Function to check the currently working system clock .
 *@param  : Takes one parameter (uint32_t) to return the current system clock.
 *@return : Error State.                                                                     
 */
 uint8_t RCC_GetSysCLK();

 /**
 *@brief  : Function to select the PLL source.
 *@param  : Takes one parameter as the PLL selected source (Choose from the options above).
 *@return : Error State.                                                                     
 */
 enuErrorStatus_t RCC_SelectPLLSrc(uint32_t PLLSCR);
 
 /**
 *@brief  : Function to configure the PLL.
 *@param  : Takes Four Parameters representing the PLLM, PLLN, PLLP, and PLLQ values.
 *@return : Error State.                                                                     
 */
 enuErrorStatus_t RCC_ConfigPLL(uint32_t PLLM,uint32_t PLLN,uint32_t PLLP,uint32_t PLLQ);
 
 /**
 *@brief  : Function to Set a Prescaler value for either AHB, APB1, or APB2.
 *@param  : Takes Three Parameter as the Prescalers Value for AHB1, APB1, and APB2 (Choose from the options above).
 *@return : Error State.                                                                     
 */
 enuErrorStatus_t RCC_SetPrescaler(uint32_t PRE_AHB1, uint32_t PRE_APB1, uint32_t PRE_APB2);

/******/


#endif /*_RCC_H_*/