/*
* 
* File    : Source File
* Driver  : RCC Driver
* Machine : ARM 
* MC      : STM32F401xC 
* Auther  : Alaa Ghita
* Date    : Feb 2024
* 
*/


/*Includes*/
 #include "RCC.h" 
 #include "MASKS.h"
/**********/

/*Defines*/
 #define RCC_BASE_ADDRESS          0x40023800

 #define HSI_RDY                   1
 #define HSE_RDY                   17
 #define PLL_RDY                   25
 #define PLLI2S_RDY                27

 #define SYSCLK_CLR_MASK           (~(0x3))
 #define SYSCLK_USED               2

 #define PLLSCR_CLR_MASK           (~(BIT22_MASK))
 #define PLLM_POS                  0
 #define PLLN_POS                  6
 #define PLLP_POS                  16
 #define PLLQ_POS                  24
 #define PLL_CFG_CLR_MASK          0xf0fc8000

 #define SET_PRESCALE_CLR_MASK     0xffff030f

/*********/

/*Types*/
 typedef struct
 {
    uint32_t CR;
    uint32_t PLLCFGR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t AHB1RSTR;
    uint32_t AHB2RSTR;
    uint32_t reserved1[2];
    uint32_t APB1RSTR;
    uint32_t APB2RSTR;
    uint32_t reserved2[2];
    uint32_t AHB1ENR;
    uint32_t AHB2ENR;
    uint32_t reserved3[2];
    uint32_t APB1ENR;
    uint32_t APB2ENR;
    uint32_t reserved4[2];
    uint32_t AHB1LPENR;
    uint32_t AHB2LPENR;
    uint32_t reserved5[2];
    uint32_t APB1LPENR;
    uint32_t APB2LPENR;
    uint32_t reserved6[2];
    uint32_t BDCR;
    uint32_t CSR;
    uint32_t reserved7[2];
    uint32_t SSCGR;
    uint32_t PLLI2SCFGR;
    uint32_t reserved8;
    uint32_t DCKCFGR;

 }enuRCCPeri_t;
 
/*******/

/*Variables*/
 volatile enuRCCPeri_t * const RCC = (volatile enuRCCPeri_t * const)(RCC_BASE_ADDRESS);
/***********/

/*Static Functions Prototypes*/
 uint8_t GetSysCLK();
/*****************************/

/*Implementation*/
 enuErrorStatus_t RCC_TurnONCLK(uint32_t CLK_ON)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint16_t Loc_u8Timeout = 400;

   switch(CLK_ON)
   {
    case CLK_ON_HSI:
    case CLK_ON_HSE:
    case CLK_ON_PLL:
    case CLK_ON_PLLI2S:
      (RCC->CR) |= (CLK_ON);
      while((CLK_ON<<1)&RCC->CR || Loc_u8Timeout!=0)
        Loc_u8Timeout--;
      break;
    case CLK_ON_CSS:
    case CLK_ON_HSEBYP:
      (RCC->CR) |= (CLK_ON);
      break;
    default:
      Ret_enuErrorStatus = enuErrorStatus_NotOk;
      break;
   }
   return Ret_enuErrorStatus;
 }

 enuErrorStatus_t RCC_TurnOFFCLK(uint32_t CLK_ON)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;

    switch (CLK_ON)
    {
    case CLK_ON_HSI:
      if(GetSysCLK() != SYSCLK_HSI)
      {
        (RCC->CR) &= (~ CLK_ON);
      }
      else
      {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
      }
      break;
    case CLK_ON_HSE:
      if(GetSysCLK() != SYSCLK_HSE)
      {
        (RCC->CR) &= (~ CLK_ON);
      }
      else
      {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
      }
      break;
    case CLK_ON_PLL:
      if(GetSysCLK() != SYSCLK_PLL)
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
        if(RCC->CR & RDY_HSI)
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
        if(RCC->CR & RDY_HSE)
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
        if(RCC->CR & RDY_PLL)
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
   return GetSysCLK();
 }

 enuErrorStatus_t RCC_SelectPLLSrc(uint32_t PLLSCR)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint32_t Loc_u32RCC_PLLCFGR_Value = RCC->PLLCFGR;

    switch(PLLSCR)
    {
      case PLLSCR_HSI:
        if(RCC->CR & RDY_HSI)
        {
         Loc_u32RCC_PLLCFGR_Value &= PLLSCR_CLR_MASK;
         Loc_u32RCC_PLLCFGR_Value |= PLLSCR;
         RCC->PLLCFGR              = Loc_u32RCC_PLLCFGR_Value;
        }
        else
       {
         Ret_enuErrorStatus = enuErrorStatus_NotOk;
       }
      break;
    case PLLSRC_HSE:
      if(RCC->CR & RDY_HSE)
      {
        Loc_u32RCC_PLLCFGR_Value &= PLLSCR_CLR_MASK;
        Loc_u32RCC_PLLCFGR_Value |= PLLSCR;
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
      && (Copy_p>1 && Copy_P<9)
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


   uint8_t GetSysCLK()
 {
   return (~SYSCLK_CLR_MASK & ((RCC->CFGR)>>SYSCLK_USED));
 }
/****************/