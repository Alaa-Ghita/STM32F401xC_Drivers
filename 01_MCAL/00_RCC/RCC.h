/*
* 
* File    : Header File
* Driver  : RCC Driver
* Machine : ARM 
* MC      : STM32F401xC 
* Author  : Alaa Ghita
* Date    : Feb 2024
* 
*/

#ifndef _RCC_H_ 
#define _RCC_H_

#include "MASKS.h"
#include "Typedefs.h"

/*#defines*/
 /*System Clock Options*/
 #define SYSCLK_HSI           0x00
 #define SYSCLK_HSE           0x01
 #define SYSCLK_PLL           0x02

 /*Clocks to turn ON*/
 #define CLK_ON_HSI           BIT0_MASK
 #define CLK_ON_HSE           BIT16_MASK
 #define CLK_ON_PLL           BIT24_MASK
 #define CLK_ON_HSEBYP        BIT18_MASK
 #define CLK_ON_PLLI2S        BIT26_MASK
 #define CLK_ON_CSS           BIT19_MASK

 /*PLL Source Options*/
 #define PLLSRC_HSI           0x00000000
 #define PLLSRC_HSE           BIT22_MASK

 /*AHB1 Prescale options*/
 #define PRE_AHB1_1           0x70
 #define PRE_AHB1_2           0x80
 #define PRE_AHB1_4           0x90
 #define PRE_AHB1_8           0xa0
 #define PRE_AHB1_16          0xb0
 #define PRE_AHB1_64          0xc0
 #define PRE_AHB1_128         0xd0
 #define PRE_AHB1_256         0xe0
 #define PRE_AHB1_512         0xf0

 /*APB1 Prescale options*/
 #define PRE_APB1_1           0x0c00
 #define PRE_APB1_2           0x1000
 #define PRE_APB1_4           0x1400
 #define PRE_APB1_8           0x1800
 #define PRE_APB1_16          0x1c00

 /*APB2 Prescale options*/
 #define PRE_APB2_1           0x6000
 #define PRE_APB2_2           0x8000
 #define PRE_APB2_4           0xa000
 #define PRE_APB2_8           0xc000
 #define PRE_APB2_16          0xe000

 /*Peripherals' Registers*/
 #define REG_AHB1ENR          0x30
 #define REG_AHB2ENR          0x34
 #define REG_APB1ENR          0x40
 #define REG_APB2ENR          0x44

 /*Peripherals in AHB1ENR Register*/
 #define PERI_AHB1ENR_GPIOAEN      BIT0_MASK
 #define PERI_AHB1ENR_GPIOBEN      BIT1_MASK
 #define PERI_AHB1ENR_GPIOCEN      BIT2_MASK
 #define PERI_AHB1ENR_GPIODEN      BIT3_MASK
 #define PERI_AHB1ENR_GPIOEEN      BIT4_MASK
 #define PERI_AHB1ENR_GPIOHEN      BIT7_MASK
 #define PERI_AHB1ENR_CRCEN        BIT12_MASK
 #define PERI_AHB1ENR_DMA1EN       BIT21_MASK
 #define PERI_AHB1ENR_DMA2EN       BIT22_MASK

 /*Peripherals in AHB2ENR Register*/
 #define PERI_AHB2ENR_OTGFSEN      BIT7_MASK

 /*Peripherals in APB1ENR Register*/
 #define PERI_APB1ENR_TIM2EN       BIT0_MASK
 #define PERI_APB1ENR_TIM3EN       BIT1_MASK
 #define PERI_APB1ENR_TIM4EN       BIT2_MASK
 #define PERI_APB1ENR_TIM5EN       BIT3_MASK
 #define PERI_APB1ENR_WWDGEN       BIT11_MASK
 #define PERI_APB1ENR_SPI2EN       BIT14_MASK
 #define PERI_APB1ENR_SPI3EN       BIT15_MASK
 #define PERI_APB1ENR_USART2EN     BIT17_MASK
 #define PERI_APB1ENR_I2C1EN       BIT21_MASK
 #define PERI_APB1ENR_I2C2EN       BIT22_MASK
 #define PERI_APB1ENR_I2C3EN       BIT23_MASK
 #define PERI_APB1ENR_PWDEN        BIT28_MASK

 /*Peripherals in APB2ENR Register*/
 #define PERI_APB2ENR_TIM1EN       BIT0_MASK
 #define PERI_APB2ENR_USART1EN     BIT4_MASK
 #define PERI_APB2ENR_USART6EN     BIT5_MASK
 #define PERI_APB2ENR_ADC1EN       BIT8_MASK
 #define PERI_APB2ENR_SDIOEN       BIT11_MASK
 #define PERI_APB2ENR_SPI1EN       BIT12_MASK
 #define PERI_APB2ENR_SPI4EN       BIT13_MASK
 #define PERI_APB2ENR_SYSCFGEN     BIT14_MASK
 #define PERI_APB2ENR_TIM9EN       BIT16_MASK
 #define PERI_APB2ENR_TIM10EN      BIT17_MASK
 #define PERI_APB2ENR_TIM11EN      BIT18_MASK

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

 void RCC_EnablePeri(uint32_t REG, uint32_t PERI);

 void RCC_DisablePeri(uint32_t REG, uint32_t PERI);

/******/


#endif /*_RCC_H_*/
