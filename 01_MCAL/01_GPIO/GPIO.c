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

 #define GPIO_MODE_MASK             0x00000002
 #define GPIO_OTYPE_MASK            0x00000020

 #define MASK_1BIT                  0x00000001
 #define MASK_2BITS                 0x00000003
 #define MASK_3BITS                 0x00000007
 #define MASK_4BITS                 0x0000000f

 #define IS_VALID_PORT_PIN(PORT, PIN)         ((((PORT) == GPIO_PORT_A)  ||\
                                                ((PORT) == GPIO_PORT_B)) &&\
                                               (((PIN) >= GPIO_PIN_0)    &&\
                                                ((PIN) <= GPIO_PIN_15))) ||\
                                              (((PORT) == GPIO_PORT_C)   &&\
                                               (((PIN) >= GPIO_PIN_13)   &&\
                                                ((PIN) <= GPIO_PIN_15)))

 #define IS_VALID_MODE(MODE)        (  ((MODE) == GPIO_MODE_IN)       || ((MODE) == GPIO_MODE_OUT_PP)\
                                    || ((MODE) == GPIO_MODE_OUT_OD)   || ((MODE) == GPIO_MODE_AF_PP)\
                                    || ((MODE) == GPIO_MODE_AF_OD)    || ((MODE) == GPIO_MODE_ANALOG) )

 #define IS_VALID_OSPEED(SPEED)      (  ((SPEED) == GPIO_OSPEED_LOW)  || ((SPEED) == GPIO_OSPEED_MEDIUM)\
                                     || ((SPEED) == GPIO_OSPEED_HIGH) || ((SPEED) == GPIO_OSPEED_VERYHIGH))

 #define IS_VALID_OUTPUT(MODE)      (  ((MODE) == GPIO_MODE_OUT_PP)   || ((MODE) == GPIO_MODE_OUT_OD)\
                                    || ((MODE) == GPIO_MODE_AF_PP)    || ((MODE) == GPIO_MODE_AF_OD))

 #define IS_VALID_PULL(PULL)        (  ((PULL) == GPIO_PUPD_NONE)     || ((PULL) == GPIO_PUPD_PU)\ 
                                    || ((PULL) == GPIO_PUPD_PD) )

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
    else if((IS_VALID_PORT_PIN(Pin_Cfg->GPIO_PORT,Pin_Cfg->GPIO_PIN) == 0)
           || (IS_VALID_MODE(Pin_Cfg->GPIO_OSPEED) == 0)
           || (IS_VALID_OSPEED(Pin_Cfg->GPIO_OSPEED == 0))
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
      Loc_u32GPIO_Temp_Value |= (((GPIO_OTYPE_MASK)&(Pin_Cfg->GPIO_MODE))<<(Pin_Cfg->GPIO_PIN * 2));
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

 enuErrorStatus_t GPIO_SetPinValue(GPIO_PinCfg_t * const Pin_Cfg, uint32_t PIN_VALUE)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;

   if(Pin_Cfg == NULL)
    {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
    else if((IS_VALID_PORT_PIN(Pin_Cfg->GPIO_PORT,Pin_Cfg->GPIO_PIN) == 0)
           || (IS_VALID_OUTPUT(Pin_Cfg->GPIO_MODE) == 0)
           || (IS_VALID_OSPEED(Pin_Cfg->GPIO_OSPEED) == 0)
           || (IS_VALID_PULL(Pin_Cfg->GPIO_PUPD) == 0)) 
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
      GPIOx[Pin_Cfg->GPIO_PORT]->BSRR |= (1<<Pin_Cfg->GPIO_PIN * PIN_VALUE);
    }

    return Ret_enuErrorStatus;
 }

 enuErrorStatus_t GPIO_GetPinValue(GPIO_PinCfg_t * const Pin_Cfg, uint32_t * Pin_State)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if((Pin_Cfg == NULL) || (Pin_State == NULL))
    {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
    else if((IS_VALID_PORT_PIN(Pin_Cfg->GPIO_PORT,Pin_Cfg->GPIO_PIN) == 0)
           || (IS_VALID_MODE(Pin_Cfg->GPIO_OSPEED) == 0)
           || (IS_VALID_OSPEED(Pin_Cfg->GPIO_OSPEED == 0))
           || (IS_VALID_PULL(Pin_Cfg->GPIO_PUPD) == 0)) 
    {
      Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
    }
    else
    {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      *Pin_State = (1&((GPIOx[Pin_Cfg->GPIO_PORT]->IDR)>>Pin_Cfg->GPIO_PIN));
    }

    return Ret_enuErrorStatus;
 }

 
/*************/