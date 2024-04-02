/**
* 
* @file    : Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : GPIO Driver (MCAL)
* Machine  : STM32F401xC 
* 
*/

/*Includes*/
#include "GPIO.h"
/**********/


/*Defines*/
 #define GPIOA_BASE_ADD             0x40020000
 #define GPIOB_BASE_ADD             0x40020400
 #define GPIOC_BASE_ADD             0x40020800
 /*
 #define GPIOD_BASE_ADD             0x40020c00
 #define GPIOE_BASE_ADD             0x40021000
 #define GPIOH_BASE_ADD             0x40021c00
 */

 #define GPIO_MODE_MASK             0x00000003
 #define GPIO_OTYPE_MASK            0x00000030

 #define MASK_1BIT                  0x00000001
 #define MASK_2BITS                 0x00000003
 #define MASK_3BITS                 0x00000007
 #define MASK_4BITS                 0x0000000f

 #define HALF_REGISTER_SIZE         0x10

#define NUM_OF_PORTS				6
#define NUM_OF_PIN_PER_PORT			16

 #define IS_VALID_PORT(PORT)          ((PORT) < NUM_OF_PORTS)
 #define IS_VALID_PIN(PIN)            ((PIN)  < NUM_OF_PIN_PER_PORT)

 #define IS_VALID_MODE(MODE)        (((MODE) == GPIO_MODE_IN)      || ((MODE) == GPIO_MODE_OUT_PP)||\
                                    ((MODE) == GPIO_MODE_OUT_OD)   || ((MODE) == GPIO_MODE_AF_PP)||\
                                    ((MODE) == GPIO_MODE_AF_OD)    || ((MODE) == GPIO_MODE_ANALOG) )

 #define IS_VALID_OSPEED(SPEED)      (((SPEED) == GPIO_OSPEED_LOW) || ((SPEED) == GPIO_OSPEED_MEDIUM)||\
                                     ((SPEED) == GPIO_OSPEED_HIGH) || ((SPEED) == GPIO_OSPEED_VERYHIGH))

 #define IS_VALID_OUTPUT(MODE)      (((MODE) == GPIO_MODE_OUT_PP)  || ((MODE) == GPIO_MODE_OUT_OD)||\
                                    ((MODE) == GPIO_MODE_AF_PP)    || ((MODE) == GPIO_MODE_AF_OD))

 #define IS_VALID_PULL(PULL)        (((PULL) == GPIO_PUPD_NONE) || ((PULL) == GPIO_PUPD_PU) || ((PULL) == GPIO_PUPD_PD))

 #define IS_VALID_VALUE(VALUE)       (((VALUE) == PIN_VALUE_HIGH) || ((VALUE) == PIN_VALUE_LOW))


/*Types*/
typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
}GPIOx_t;

/*******/


/*Variables*/
  static volatile GPIOx_t * const GPIOx [] =
  {
      [GPIO_PORT_A] = (volatile GPIOx_t * const) (GPIOA_BASE_ADD),
      [GPIO_PORT_B] = (volatile GPIOx_t * const) (GPIOB_BASE_ADD),
      [GPIO_PORT_C] = (volatile GPIOx_t * const) (GPIOC_BASE_ADD)
      /*
      [GPIO_PORT_D] = (volatile GPIOx_t * const) (GPIOD_BASE_ADD),
      [GPIO_PORT_E] = (volatile GPIOx_t * const) (GPIOE_BASE_ADD),
      [GPIO_PORT_H] = (volatile GPIOx_t * const) (GPIOH_BASE_ADD)
      */
  };
/**********/


/*Implemention*/
 enuErrorStatus_t GPIO_InitPin(GPIO_PinCfg_t * const Pin_Cfg)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;

    volatile GPIOx_t * const GPIO = (volatile GPIOx_t * const) (GPIOx[Pin_Cfg->GPIO_PORT]);
    uint32_t Loc_u32GPIO_Temp_Value;
    if(Pin_Cfg == NULL)
    {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
    else if((IS_VALID_PORT(Pin_Cfg->GPIO_PORT) == 0)
    	   || (IS_VALID_PIN(Pin_Cfg->GPIO_PIN) == 0)
           || (IS_VALID_MODE(Pin_Cfg->GPIO_OSPEED) == 0)
           || (IS_VALID_OSPEED(Pin_Cfg->GPIO_OSPEED) == 0)
           || (IS_VALID_PULL(Pin_Cfg->GPIO_PUPD) == 0)) 
    {
      Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
    }
    else
    {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      Loc_u32GPIO_Temp_Value  = GPIO->MODER;
      Loc_u32GPIO_Temp_Value &= ~(MASK_2BITS<<(Pin_Cfg->GPIO_PIN * 2));
      Loc_u32GPIO_Temp_Value |= (((GPIO_MODE_MASK)&(Pin_Cfg->GPIO_MODE))<<(Pin_Cfg->GPIO_PIN * 2));
      GPIO->MODER             = Loc_u32GPIO_Temp_Value;

      Loc_u32GPIO_Temp_Value  = GPIO->OTYPER;
      Loc_u32GPIO_Temp_Value &= ~(MASK_1BIT<<Pin_Cfg->GPIO_PIN);
      Loc_u32GPIO_Temp_Value |= ((((GPIO_OTYPE_MASK)&(Pin_Cfg->GPIO_MODE))>>4)<<(Pin_Cfg->GPIO_PIN));
      GPIO->OTYPER            = Loc_u32GPIO_Temp_Value;

      
      Loc_u32GPIO_Temp_Value  = GPIO->PUPDR;
      Loc_u32GPIO_Temp_Value &= ~(MASK_2BITS<<(Pin_Cfg->GPIO_PIN * 2));
      Loc_u32GPIO_Temp_Value |= ((Pin_Cfg->GPIO_PUPD)<<(Pin_Cfg->GPIO_PIN * 2));
      GPIO->PUPDR             = Loc_u32GPIO_Temp_Value;

      Loc_u32GPIO_Temp_Value  = GPIO->OSPEEDR;
      Loc_u32GPIO_Temp_Value &= ~(MASK_2BITS<<(Pin_Cfg->GPIO_PIN * 2));
      Loc_u32GPIO_Temp_Value |= ((Pin_Cfg->GPIO_OSPEED)<<(Pin_Cfg->GPIO_PIN * 2));
      GPIO->OSPEEDR           = Loc_u32GPIO_Temp_Value;

    }

   return Ret_enuErrorStatus;
 }

 enuErrorStatus_t GPIO_SetPinValue(uint32_t GPIO_PIN, uint32_t GPIO_PORT, uint32_t PIN_VALUE)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;

    if((IS_VALID_PORT(GPIO_PORT) == 0) || (IS_VALID_PIN(GPIO_PIN) == 0))
    {
      Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
    }
    else if((IS_VALID_VALUE(PIN_VALUE)) == 0)
    {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
    }
    else
    {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      switch(PIN_VALUE)
      {
        case (PIN_VALUE_LOW): 
          GPIOx[GPIO_PORT]->BSRR |= (1<<(GPIO_PIN + HALF_REGISTER_SIZE));
        break;
        case (PIN_VALUE_HIGH): 
          GPIOx[GPIO_PORT]->BSRR |= (1<<GPIO_PIN);
        break;
        default:
          /*Do Nothing*/
        break;

      }
    }

    return Ret_enuErrorStatus;
 }

 enuErrorStatus_t GPIO_GetPinValue(uint32_t GPIO_PIN, uint32_t GPIO_PORT, uint32_t * Pin_State)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if(Pin_State == NULL)
    {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
   else if((IS_VALID_PORT(GPIO_PORT) == 0) || (IS_VALID_PIN(GPIO_PIN) == 0))
    {
         Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
    }
    else
    {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      *Pin_State = (1&((GPIOx[GPIO_PORT]->IDR)>>GPIO_PIN));
    }

    return Ret_enuErrorStatus;
 }

 
/*************/
