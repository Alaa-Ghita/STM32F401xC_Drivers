/**
* 
* @file    : Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : RCC Driver (MCAL)
* Machine  : STM32F401xC 
* 
*/


/*Includes*/
 #include "RCC.h" 
 #include "MASKS.h"
/**********/

/*Defines*/
 #define RCC_BASE_ADDRESS          0x40023800

 #define HSI_RDY                   BIT1_MASK
 #define HSE_RDY                   BIT17_MASK
 #define PLL_RDY                   BIT25_MASK
 #define PLLI2S_RDY                BIT27_MASK

 #define SYSCLK_CLR_MASK           (~(0x3))
 #define SYSCLK_USED               2

 #define PLLSRC_CLR_MASK           (~(BIT22_MASK))
 #define PLLM_POS                  0
 #define PLLN_POS                  6
 #define PLLP_POS                  16
 #define PLLQ_POS                  24
 #define PLL_CFG_CLR_MASK          0xf0fc8000

 #define SET_PRESCALE_CLR_MASK     0xffff030f

 #define PERIPHERALS_CLR_MASK      0x30000000

 #define GET_SYSCLK                (~SYSCLK_CLR_MASK & ((RCC->CFGR)>>SYSCLK_USED))

 #define IS_VALID_CLK(CLK)               (((CLK) == CLK_ON_HSI) || ((CLK) == CLK_ON_HSE)||\
                                          ((CLK) == CLK_ON_PLL) || ((CLK) == CLK_ON_PLLI2S)||\
                                          ((CLK) == CLK_ON_CSS) || ((CLK) == CLK_ON_HSEBYP))
/*********/

/*Types*/
 typedef struct
 {
  volatile uint32_t CR;
  volatile uint32_t PLLCFGR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t reserved1[2];
  volatile uint32_t APB1RSTR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t reserved2[2];
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  volatile uint32_t reserved3[2];
  volatile uint32_t APB1ENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t reserved4[2];
  volatile uint32_t AHB1LPENR;
  volatile uint32_t AHB2LPENR;
  volatile uint32_t reserved5[2];
  volatile uint32_t APB1LPENR;
  volatile uint32_t APB2LPENR;
  volatile uint32_t reserved6[2];
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
  volatile uint32_t reserved7[2];
  volatile uint32_t SSCGR;
  volatile uint32_t PLLI2SCFGR;
  volatile uint32_t reserved8;
  volatile uint32_t DCKCFGR;

 }enuRCCPeri_t;
 
/*******/

/*Variables*/
 static volatile enuRCCPeri_t * const RCC = (volatile enuRCCPeri_t * const)(RCC_BASE_ADDRESS);
/***********/

/*Static Functions Prototypes*/
/*****************************/

/*Implementation*/
 enuErrorStatus_t RCC_TurnONCLK(uint32_t CLK_ON)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint16_t Loc_u8Timeout = 600;

   if(IS_VALID_CLK(CLK_ON) == 0)
   {
	   Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else
   {
    (RCC->CR) |= (CLK_ON);
    if(((CLK_ON) == CLK_ON_HSI) || ((CLK_ON) == CLK_ON_HSE)|| ((CLK_ON) == CLK_ON_PLL) || ((CLK_ON) == CLK_ON_PLLI2S))
    {
      while(!((CLK_ON<<1)&RCC->CR) && Loc_u8Timeout!=0)
      {
        Loc_u8Timeout--;
        Ret_enuErrorStatus = enuErrorStatus_Timeout;
      }
    }
    else { /*Do Nothing*/ }
   }
    
   return Ret_enuErrorStatus;
 }

 enuErrorStatus_t RCC_TurnOFFCLK(uint32_t CLK_ON)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;

    switch (CLK_ON)
    {
    case CLK_ON_HSI:
      if(GET_SYSCLK != SYSCLK_HSI)
      {
        (RCC->CR) &= (~ CLK_ON);
      }
      else
      {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
      }
      break;
    case CLK_ON_HSE:
      if(GET_SYSCLK != SYSCLK_HSE)
      {
        (RCC->CR) &= (~ CLK_ON);
      }
      else
      {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
      }
      break;
    case CLK_ON_PLL:
      if(GET_SYSCLK != SYSCLK_PLL)
      {
        (RCC->CR) &= (~ CLK_ON);
      }
      else
      {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
      }
      break;
    case CLK_ON_CSS:
    case CLK_ON_HSEBYP:
    case CLK_ON_PLLI2S:
        (RCC->CR) &= (~ CLK_ON);
    break;
    default:
      Ret_enuErrorStatus = enuErrorStatus_NotOk;
    break;
    }

   return Ret_enuErrorStatus;

 }

 enuErrorStatus_t RCC_SelectSysCLK(uint32_t SYSCLK)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint32_t Loc_u32RCC_CFGR_Value;

    switch(SYSCLK)
    {
      case SYSCLK_HSI:
        if(RCC->CR & HSI_RDY)
        {
          Loc_u32RCC_CFGR_Value  = RCC->CFGR;
          Loc_u32RCC_CFGR_Value &= SYSCLK_CLR_MASK;
          Loc_u32RCC_CFGR_Value |= SYSCLK;
          RCC->CFGR              = Loc_u32RCC_CFGR_Value;
        }
        else
        {
          Ret_enuErrorStatus = enuErrorStatus_NotOk;
        }
        break;
      case SYSCLK_HSE:
        if(RCC->CR & HSE_RDY)
        {
          Loc_u32RCC_CFGR_Value  = RCC->CFGR;
          Loc_u32RCC_CFGR_Value &= SYSCLK_CLR_MASK;
          Loc_u32RCC_CFGR_Value |= SYSCLK;
          RCC->CFGR              = Loc_u32RCC_CFGR_Value;
        }
        else
        {
          Ret_enuErrorStatus = enuErrorStatus_NotOk;
        }
        break;
      case SYSCLK_PLL:
        if(RCC->CR & PLL_RDY)
        {
          Loc_u32RCC_CFGR_Value  = RCC->CFGR;
          Loc_u32RCC_CFGR_Value &= SYSCLK_CLR_MASK;
          Loc_u32RCC_CFGR_Value |= SYSCLK;
          RCC->CFGR              = Loc_u32RCC_CFGR_Value;
        }
        else
        {
          Ret_enuErrorStatus = enuErrorStatus_NotOk;
        }
        break;
      default:
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
   }

    return Ret_enuErrorStatus;
 }

 uint8_t RCC_GetSysCLK()
 {
   return GET_SYSCLK;
 }

 enuErrorStatus_t RCC_SelectPLLSrc(uint32_t PLLSRC)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint32_t Loc_u32RCC_PLLCFGR_Value = RCC->PLLCFGR;

    switch(PLLSRC)
    {
      case PLLSRC_HSI:
        if(RCC->CR & HSI_RDY)
        {
         Loc_u32RCC_PLLCFGR_Value &= PLLSRC_CLR_MASK;
         Loc_u32RCC_PLLCFGR_Value |= PLLSRC;
         RCC->PLLCFGR              = Loc_u32RCC_PLLCFGR_Value;
        }
        else
       {
         Ret_enuErrorStatus = enuErrorStatus_NotOk;
       }
      break;
    case PLLSRC_HSE:
      if(RCC->CR & HSE_RDY)
      {
        Loc_u32RCC_PLLCFGR_Value &= PLLSRC_CLR_MASK;
        Loc_u32RCC_PLLCFGR_Value |= PLLSRC;
        RCC->PLLCFGR              = Loc_u32RCC_PLLCFGR_Value;
      }
      else
      {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
      }
      break;
    default:
      Ret_enuErrorStatus = enuErrorStatus_NotOk;
   }

   return Ret_enuErrorStatus;
 }

 enuErrorStatus_t RCC_ConfigPLL(uint32_t Copy_M,uint32_t Copy_N,uint32_t Copy_P,uint32_t Copy_Q)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint32_t Loc_u32RCC_PLLCFGR_Value = RCC->PLLCFGR;

   if((Copy_M>1 && Copy_M<64) 
      && (Copy_N>1 && Copy_N<511 && Copy_N!=433)
      && (Copy_P>1 && Copy_P<9)
      && (Copy_Q>1 && Copy_Q<16))
   {
    Copy_P = (Copy_P/2)>>1;
    Copy_P = Copy_P<<PLLP_POS;
    Copy_N = Copy_N<<PLLN_POS;
    Copy_Q = Copy_Q<<PLLQ_POS;

    Loc_u32RCC_PLLCFGR_Value &= PLL_CFG_CLR_MASK;
    Loc_u32RCC_PLLCFGR_Value |= Copy_P | Copy_M | Copy_N | Copy_Q;
    RCC->PLLCFGR              = Loc_u32RCC_PLLCFGR_Value;
   }
   else
   {
    Ret_enuErrorStatus = enuErrorStatus_NotOk;
   }

   return Ret_enuErrorStatus;
 }

 enuErrorStatus_t RCC_SetPrescaler(uint32_t PRE_AHB1, uint32_t PRE_APB1, uint32_t PRE_APB2)
 {
   enuErrorStatus_t Ret_enuErrorStatus  = enuErrorStatus_Ok;
   uint32_t Loc_u32RCC_CFGR_Value = RCC->CFGR;

   if((PRE_AHB1>PRE_AHB1_1 && PRE_AHB1<PRE_AHB1_512)
    &&(PRE_APB1>PRE_APB1_1 && PRE_APB1<PRE_APB1_16)
    &&(PRE_APB2>PRE_APB2_1 && PRE_APB2<PRE_APB2_16))
   {
    Loc_u32RCC_CFGR_Value &= SET_PRESCALE_CLR_MASK;
    Loc_u32RCC_CFGR_Value |= PRE_AHB1 | PRE_APB1 | PRE_APB2;
    RCC->CFGR              = Loc_u32RCC_CFGR_Value;
   }
   else
   {
    Ret_enuErrorStatus = enuErrorStatus_NotOk;
   }
   return Ret_enuErrorStatus;
 }

 enuErrorStatus_t RCC_AHB1EnablePeri(uint32_t PERI_AHB1)
 {
  /*assert*/
  RCC->AHB1ENR |= PERI_AHB1;
  return enuErrorStatus_Ok;
 }

 enuErrorStatus_t RCC_AHB2EnablePeri(uint32_t PERI_AHB2)
 {
  /*assert*/
  RCC->AHB2ENR |= PERI_AHB2;
  return enuErrorStatus_Ok;
 }

 enuErrorStatus_t RCC_APB1EnablePeri(uint32_t PERI_APB1)
 {
  /*assert*/
  //PERI_APB1 = PERI_APB1 && PERIPHERALS_CLR_MASK;
  RCC->APB1ENR |= PERI_APB1;
  return enuErrorStatus_Ok;
 }

 enuErrorStatus_t RCC_APB2EnablePeri(uint32_t PERI_APB2)
 {
  /*assert*/
  //PERI_APB2 = PERI_APB2 && PERIPHERALS_CLR_MASK;
  RCC->APB2ENR |= PERI_APB2;
  return enuErrorStatus_Ok;
 }

 enuErrorStatus_t RCC_AHB1DisablePeri(uint32_t PERI_AHB1)
 {
   /*assert*/
  //PERI_AHB1 = PERI_AHB1 && PERIPHERALS_CLR_MASK;
  RCC->APB2ENR &= (~PERI_AHB1);
  return enuErrorStatus_Ok;
 }

 enuErrorStatus_t RCC_AHB2DisablePeri(uint32_t PERI_AHB2)
 {
  /*assert*/
  //PERI_AHB2 = PERI_AHB2 && PERIPHERALS_CLR_MASK;
  RCC->APB2ENR &= (~PERI_AHB2);
  return enuErrorStatus_Ok;
 }

 enuErrorStatus_t RCC_APB1DisablePeri(uint32_t PERI_APB1)
 {
  /*assert*/
  //PERI_APB1 = PERI_APB1 && PERIPHERALS_CLR_MASK;
  RCC->APB2ENR &= (~PERI_APB1);
  return enuErrorStatus_Ok;
 }

 enuErrorStatus_t RCC_APB2DisablePeri(uint32_t PERI_APB2)
 {
  /*assert*/
  //PERI_APB2 = PERI_APB2 && PERIPHERALS_CLR_MASK;
  RCC->APB2ENR &= (~PERI_APB2);
  return enuErrorStatus_Ok;
 }
/****************/
