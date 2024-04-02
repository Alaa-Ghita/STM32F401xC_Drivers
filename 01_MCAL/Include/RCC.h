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
#include "ErrorStatus.h"
#include "assert.h"

/*Defines*/
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


 /*Peripherals connected to AHB1*/
 #define PERI_AHB1_GPIOA      (uint32_t)0x00000001
 #define PERI_AHB1_GPIOB      (uint32_t)0x00000002
 #define PERI_AHB1_GPIOC      (uint32_t)0x00000004
 #define PERI_AHB1_GPIOD      (uint32_t)0x00000008
 #define PERI_AHB1_GPIOE      (uint32_t)0x00000010
 #define PERI_AHB1_GPIOH      (uint32_t)0x00000080
 #define PERI_AHB1_CRC        (uint32_t)0x00001000
 #define PERI_AHB1_DMA1       (uint32_t)0x00200000
 #define PERI_AHB1_DMA2       (uint32_t)0x00400000

 /*Peripherals conted to AHB2*/
 #define PERI_AHB2_OTGFS      (uint32_t)0x40000080

 /*Peripherals connected to APB1*/
 #define PERI_APB1_TIM2       (uint32_t)0x80000001
 #define PERI_APB1_TIM3       (uint32_t)0x80000002
 #define PERI_APB1_TIM4       (uint32_t)0x80000004
 #define PERI_APB1_TIM5       (uint32_t)0x80000008
 #define PERI_APB1_WWDG       (uint32_t)0x80000800
 #define PERI_APB1_SPI2       (uint32_t)0x80004000
 #define PERI_APB1_SPI3       (uint32_t)0x80008000
 #define PERI_APB1_USART2     (uint32_t)0x80020000
 #define PERI_APB1_I2C1       (uint32_t)0x80200000
 #define PERI_APB1_I2C2       (uint32_t)0x80400000
 #define PERI_APB1_I2C3       (uint32_t)0x80800000
 #define PERI_APB1_PW         (uint32_t)0xd0000000

 /*Peripherals connected to APB2*/
 #define PERI_APB2_TIM1       (uint32_t)0xc0000001
 #define PERI_APB2_USART1     (uint32_t)0xc0000010
 #define PERI_APB2_USART6     (uint32_t)0xc0000020
 #define PERI_APB2_ADC1       (uint32_t)0xc0000100
 #define PERI_APB2_SDIO       (uint32_t)0xc0000800
 #define PERI_APB2_SPI1       (uint32_t)0xc0001000
 #define PERI_APB2_SPI4       (uint32_t)0xc0002000
 #define PERI_APB2_SYSCFG     (uint32_t)0xc0004000
 #define PERI_APB2_TIM9       (uint32_t)0xc0010000
 #define PERI_APB2_TIM10      (uint32_t)0xc0020000
 #define PERI_APB2_TIM11      (uint32_t)0xc0040000

/*types*/

/**********/

/*APIs*/
 
 /**
 *@brief  : Function to Select the System Clock.
 *@param  : Takes one parameter as the selected system clock (Choose from the options above).
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

 enuErrorStatus_t RCC_AHB1EnablePeri(uint32_t PERI_AHB1);

 enuErrorStatus_t RCC_AHB2EnablePeri(uint32_t PERI_AHB2);

 enuErrorStatus_t RCC_APB1EnablePeri(uint32_t PERI_APB1);

 enuErrorStatus_t RCC_APB2EnablePeri(uint32_t PERI_APB2);

 enuErrorStatus_t RCC_AHB1DisablePeri(uint32_t PERI_AHB1);

 enuErrorStatus_t RCC_AHB2DisablePeri(uint32_t PERI_AHB2);

 enuErrorStatus_t RCC_APB1DisablePeri(uint32_t PERI_APB1);

 enuErrorStatus_t RCC_APB2DisablePeri(uint32_t PERI_APB2);

/******/


#endif /*_RCC_H_*/
