/**
* 
* @file    : SysTick Driver Source File (MCAL)
* @author  : Alaa Ghita
* @date    : MAR 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "SysTick.h"
 #include "SysTick_cfg.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define SYSTICK_BASE_ADDRESS                   (uint32_t)0xe000e010

 #define ENABLE_BIT_MASK                         BIT0_MASK
 #define TIKINT_BIT_MASK                         BIT1_MASK
 #define CLKSOURCE_BIT_MASK                      BIT2_MASK
 #define CLKSOURCE_BIT                           2
 #define COUNTFLAG_BIT                           16
 #define CLR_CURRENT_VALUE                       0xff000000

 #define MAX_VALID_TICKS                         0x00ffffff
 #define NO_MODE                                 0xffffffff

 #define CLK_SRC_USED                           (SysTick->CTRL & CLKSOURCE_BIT_MASK)
 //#define CLK_VALUE                              (((CLK_SRC_USED) * (SYSTICK_PROCESSOR_CLK))+((!CLK_SRC_USED) * (SYSTICK_EXTERNAL_CLK)))

 #define IS_VALID_CLK_SRC(SRC)                  (((SRC) == SYSTICK_CLK_SRC_EXTERNAL_CLK) || ((SRC) == SYSTICK_CLK_SRC_PROCESSOR_CLK))
 #define Is_VALID_SYSTICK_MODE(MODE)            (((MODE) == SYSTICK_MODE_PERIODIC) || ((MODE) == SYSTICK_MODE_ONE_TIME))

/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef struct
 {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
 }SysTick_t;
 
/********************************************************************************************************/



/************************************************Variables***********************************************/
 static volatile SysTick_t * const SysTick = (volatile SysTick_t * const) (SYSTICK_BASE_ADDRESS);
 static SysTickCBF_t SysTickCBF = NULL;
 static uint32_t Current_SysTick_Mode = NO_MODE;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
 static void StopSysTick(void);
/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/
 enuErrorStatus_t SysTick_ConfigClkSrc(uint32_t SYSTICK_CLK_SRC)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if(IS_VALID_CLK_SRC(SYSTICK_CLK_SRC) == 0)
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      SysTick->CTRL = ((SysTick->CTRL & (~CLKSOURCE_BIT_MASK)) | (SYSTICK_CLK_SRC));
   }
   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t SysTick_SetTime_ms(uint32_t Copy_u32Time_ms)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   uint64_t Loc_u32ClockUsed = ((CLK_SRC_USED == SYSTICK_CLK_SRC_PROCESSOR_CLK) ? (SYSTICK_PROCESSOR_CLK) : (SYSTICK_EXTERNAL_CLK));
   uint32_t Loc_u32LoadValue = (uint32_t)(((uint64_t)Copy_u32Time_ms * Loc_u32ClockUsed)/(uint64_t)1000)-(uint32_t)1;
   if(Loc_u32LoadValue > MAX_VALID_TICKS)
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      SysTick->VAL       = 0;
      SysTick->LOAD      = Loc_u32LoadValue;
   }
   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t SysTick_Start(uint32_t SYSTICK_MODE)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   if(!Is_VALID_SYSTICK_MODE(SYSTICK_MODE))
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else
   {
      Current_SysTick_Mode = SYSTICK_MODE;
      SysTick->VAL  &= CLR_CURRENT_VALUE;
      SysTick->CTRL |= (ENABLE_BIT_MASK | TIKINT_BIT_MASK);
   } 
   return Ret_enuErrorStatus;
 }


 void SysTick_Stop(void)
 {
   StopSysTick();
 }


 enuErrorStatus_t SysTick_IsExpired(enuTimerState_t * Add_enupTimerState)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if(!Add_enupTimerState)
   {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      *Add_enupTimerState = (1 & (SysTick->CTRL >> COUNTFLAG_BIT)); 
   }
   return Ret_enuErrorStatus;
 }


  enuErrorStatus_t SysTick_SetCallBack(SysTickCBF_t Add_CallBackFunc)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if(!Add_CallBackFunc)
   {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      SysTickCBF = Add_CallBackFunc;
   }
   return Ret_enuErrorStatus;
 }


 void SysTick_Handler(void)
 {
    if(Current_SysTick_Mode == SYSTICK_MODE_ONE_TIME)
    {
      SysTick_Stop();
    }
    if(SysTickCBF)
    {
      SysTickCBF();
    }
 }

 void StopSysTick(void)
 {
   SysTick->CTRL &= (~(ENABLE_BIT_MASK | TIKINT_BIT_MASK));
 }

/********************************************************************************************************/


