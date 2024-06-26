/**
* 
* @file    : NVIC Driver Source File (MCAL)
* @author  : Alaa Ghita
* @date    : Mar 2024
* @version : 0.1v
* Machine  : STM32F401xC 
* 
*/


/************************************************Includes************************************************/
 #include "NVIC.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define NVIC_BASE_ADDRESS              0xe000e100U
 #define SCB_BASE_ADDRESS               0xe000ed00U

 #define SCB_AIRCR_CLR                  0x0000f8ffU
 #define SCB_AIRCR_CLR_KEY              0x00000700U
 #define SCB_AIRCR_PRI_LOCATION         0x00000008U
 #define IRQ_IP_SIZE                    0x00000008U

 #define MASK_8BITS                     0x000000ffU
 #define MASK_CLR_3BITS                 0xfffffff8U
 #define MASK_CLR_8BITS                 0xffffff00U
 #define MASK_CLR_16BITS                0xffff0000U

 #define NVIC_MAX_IRQS                  0x000000f0U

 #define GET_PRIORITY                   ((SCB_AIRCR_CLR_KEY & SCB->AIRCR) >> SCB_AIRCR_PRI_LOCATION)

 #define IS_VALID_IRQ(IRQn)                                       ((IRQn) < (NVIC_MAX_IRQS))
 #define IS_NOT_NULL(PTR)                                         ((PTR) != NULL)
 #define IS_VALID_PRIGROUP_SUB_BIT(PRIORITY)                      ((PRIORITY) < 8)
 #define IS_VALID_IRQ_PRIORITY(IRQ_PRIORITY)                      ((IRQ_PRIORITY) < 256)
 //#define IS_VALID_SUBPRIORITY(PRIORITY_MODE,SUB_PRIORITY)         (((uint32_t)(1 << ((PRIORITY_MODE)+ 1))) > ((uint32_t)(SUB_PRIORITY)))
 //#define IS_VALID_PREPRIORITY(PRIORITY_MODE,PRE_PRIORITY)         ((1 << (IRQ_IP_SIZE - (PRIORITY_MODE))) < (PRE_PRIORITY))
/********************************************************************************************************/



/************************************************Types***************************************************/

 typedef struct
 {
    volatile uint32_t ISER[8];
    volatile uint32_t Reserved1[24];
    volatile uint32_t ICER[8];
    volatile uint32_t Reserved2[24];
    volatile uint32_t ISPR[8];
    volatile uint32_t Reserved3[24];
    volatile uint32_t ICPR[8];
    volatile uint32_t Reserved4[24];
    volatile uint32_t IABR[8];
    volatile uint32_t Reserved5[56];
    volatile uint32_t IPR[60];
    volatile uint32_t Reserved6[580];
    volatile uint32_t STIR;
 }NVIC_t;
 
 typedef struct
 {
    volatile uint32_t CPUID;
    volatile uint32_t ICSR;
    volatile uint32_t VTOR;
    volatile uint32_t AIRCR;
    volatile uint32_t SCR;
    volatile uint32_t CCR;
    volatile uint32_t SHPR1;
    volatile uint32_t SHPR2;
    volatile uint32_t SHPR3;
    volatile uint32_t SHCSR;
    volatile uint32_t CFSR;
    volatile uint32_t HFSR;
    volatile uint32_t Reserved1;
    volatile uint32_t MMAR;
    volatile uint32_t BFAR;
    volatile uint32_t AFSR;
 }SCB_t;
 
/********************************************************************************************************/



/************************************************Variables***********************************************/
 static volatile NVIC_t * const NVIC = (volatile NVIC_t * const)(NVIC_BASE_ADDRESS);
 static volatile SCB_t * const SCB   = (volatile SCB_t * const)(SCB_BASE_ADDRESS);
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
 enuErrorStatus_t NVIC_EnableIRQ(uint32_t NVIC_IRQ)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   if(IS_VALID_IRQ(NVIC_IRQ) == 0)
   {
	   Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else
   {
	   NVIC->ISER[NVIC_IRQ/32] |= (1<<(NVIC_IRQ%32));
   }
   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_DisableIRQ(uint32_t NVIC_IRQ)
 {
	 enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
	 if(IS_VALID_IRQ(NVIC_IRQ) == 0)
	 {
		 Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
	 }

	 else
	 {
		 NVIC->ICER[NVIC_IRQ/32] = (1<<(NVIC_IRQ%32));
	 }
   
   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_SetPending(uint32_t NVIC_IRQ)
 {
	 enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
	 if(IS_VALID_IRQ(NVIC_IRQ) == 0)
	 {
		 Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
	 }

	 else
	 {
		 NVIC->ISPR[NVIC_IRQ/32] |= (1<<(NVIC_IRQ%32));
	 }

   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_ClearPending(uint32_t NVIC_IRQ)
 {
	 enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
	 if(IS_VALID_IRQ(NVIC_IRQ) == 0)
	 {
		 Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
	 }

	 else
	 {
		 NVIC->ICPR[NVIC_IRQ/32] = (1<<(NVIC_IRQ%32));
	 }

   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_GetActiveStatus(uint32_t NVIC_IRQ, NVIC_ActiveState_t * Add_u8pActiveState)
 {
	 enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
	 if(IS_VALID_IRQ(NVIC_IRQ) == 0)
	 {
	    Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
	 }
	 else if(IS_NOT_NULL(Add_u8pActiveState) == 0)
	 {
		 Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
	 }
	 else
	 {
		*Add_u8pActiveState = ( 1 & ((NVIC->IABR[NVIC_IRQ/32]) >> (NVIC_IRQ%32)));
	 }

   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_Generate_SW_IRQ(uint32_t NVIC_IRQ)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   if(IS_VALID_IRQ(NVIC_IRQ) == 0)
   {
	   Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else
   {
	   NVIC->STIR = NVIC_IRQ;
   }

   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_SetPriorityGroup(uint32_t NVIC_PRIGROUP_SUB_BIT)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint32_t Loc_u32AIRCR_TempValue = SCB->AIRCR;

   if(IS_VALID_PRIGROUP_SUB_BIT((NVIC_PRIGROUP_SUB_BIT) & 0x0f) == 0)
   {
	   Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
   }
   else
   {
	   Loc_u32AIRCR_TempValue &= SCB_AIRCR_CLR;
	   Loc_u32AIRCR_TempValue |= NVIC_PRIGROUP_SUB_BIT;
	   SCB->AIRCR              = Loc_u32AIRCR_TempValue;
   }

   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_SetIRQFullPriority(uint32_t NVIC_IRQ, uint32_t Copy_u32IRQ_PRIORITY)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint32_t Loc_u32NVIC_IPRx = NVIC->IPR[NVIC_IRQ/4];
   uint8_t Loc_u8IRQ_IP = 8*(NVIC_IRQ%4);
   
   if(IS_VALID_IRQ(NVIC_IRQ) == 0)
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else if(IS_VALID_IRQ_PRIORITY(Copy_u32IRQ_PRIORITY) == 0)
   {
	   Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
   }
   else
   {
      Loc_u32NVIC_IPRx     &= ~(MASK_8BITS << Loc_u8IRQ_IP);
      Loc_u32NVIC_IPRx     |= Copy_u32IRQ_PRIORITY << Loc_u8IRQ_IP;
      NVIC->IPR[NVIC_IRQ/4] = Loc_u32NVIC_IPRx;
   }

   return Ret_enuErrorStatus;
 }

 
 enuErrorStatus_t NVIC_SetIRQPriority(uint32_t NVIC_IRQ, uint32_t Copy_u8PrePriority, uint32_t Copy_u8SubPriority)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint32_t Loc_u32NVIC_IPRx = NVIC->IPR[NVIC_IRQ/4];
   uint8_t Loc_u8IRQ_IP = 8*(NVIC_IRQ%4);
   uint32_t Loc_u32PriorityMode;
   
   Loc_u32PriorityMode = GET_PRIORITY;

   if(IS_VALID_IRQ(NVIC_IRQ) == 0 )
   {
	   Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else if(     (((1 << (Loc_u32PriorityMode+ 1)) > Copy_u8SubPriority) == 0) ||
		   ( ((1 << (IRQ_IP_SIZE - Loc_u32PriorityMode)) < Copy_u8PrePriority) == 0 )  )
   {
	   Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
   }
   else
   {
	   Loc_u32NVIC_IPRx     &= ~(MASK_8BITS << Loc_u8IRQ_IP);
	   Loc_u32NVIC_IPRx     |= ((Copy_u8PrePriority << (Loc_u32PriorityMode+1)) | Copy_u8SubPriority);
	   NVIC->IPR[NVIC_IRQ/4] = Loc_u32NVIC_IPRx;
   }
   
   return Ret_enuErrorStatus;
 }


 enuErrorStatus_t NVIC_GetPriority(uint32_t * Add_u8pPriorityMode)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   if(IS_NOT_NULL(Add_u8pPriorityMode) == 0)
   {
	   Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
   }
   else
   {
      *Add_u8pPriorityMode = GET_PRIORITY;
   }

   return Ret_enuErrorStatus;
 }

/********************************************************************************************************/


