/**
* 
* @file    : UART Driver Source File (MCAL)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/


/************************************************Includes************************************************/
 #include "UART.h"
 #include "UART_cfg.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define UART1_BASE_ADD                   0x40011000
 #define UART2_BASE_ADD                   0x40004400
 #define UART6_BASE_ADD                   0x40011400
   
 #define UART_ENABLE                      BIT13_MASK
 #define TC_BIT                           BIT6_MASK
 #define RXNE_BIT                         BIT5_MASK
 #define TE_ENABLE                        BIT3_MASK
 #define RE_ENABLE                        BIT2_MASK
 #define OVER8_BIT                        BIT15_MASK
 #define TCIE_BIT                         BIT6_MASK
 #define RXNEIE_BIT					      BIT5_MASK
 #define OVER8_BIT_NO                     15

 #define CR1_CLR_MASK                     0xffff49ff
 #define CR2_CLR_STOP_BITS                0xffffcfff 
 #define CR3_CLR_SAMPLE_BIT               0xfffff7ff
 #define MASK_16BITS                      0x0000ffff
 #define DIV_MANTISSA_START_BIT           0x4

 #define ROUND_TO_INTEGER(FLOAT_NUM)      ((uint32_t)((float32_t)(FLOAT_NUM) + 0.5))  

 #define IS_VALID_CHANNEL(CHANNEL)        ((CHANNEL) <= UART_CHANNEL_6)
 #define IS_VALID_WORD_LENGTH(LENGTH)     (((LENGTH) == WORD_LENGTH_8)  || ((LENGTH) == WORD_LENGTH_9))
 #define IS_VALID_STOP_BITS(STOP_BIT)     (((STOP_BIT) == STOP_BITS_HALF) || ((STOP_BIT) == STOP_BITS_ONE) || ((STOP_BIT) == STOP_BITS_ONE_AND_HALF) || ((STOP_BIT) == STOP_BITS_TWO))  
 #define IS_VALID_SAMPLING(SAMPLING)      (((SAMPLING) == OVER_SAMPLING_8) || ((SAMPLING) == OVER_SAMPLING_16))
 #define IS_VALID_SAMPLE_METHOD(METHOD)   (((METHOD) == SAMPLE_BIT_METHOD_1) || ((METHOD) == SAMPLE_BIT_METHOD_3))
 #define IS_VALID_PARITY(PARITY)          (((PARITY) == PARITY_DISABLE) || ((PARITY) == PARITY_ENABLE_EVEN) || ((PARITY) == PARITY_ENABLE_ODD))           
 #define IS_NOT_NULL(PTR)                 ((PTR) != NULL)
/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef struct 
 {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
 }UARTx_t;
 
/*  typedef struct
 {
    uint8_t * Data_Buffer;
    uint16_t Buffer_Length;
    NotificationCBF_t Req_CBF;
 }UART_BufferReq_t; */
typedef enum 
{
	ReqState_Busy,
	ReqState_Done
}RequestState_t; 

typedef struct 
{
	UART_BufferReq_t User_Req;
	uint16_t Index;
	RequestState_t Req_State;
}UserRequest_t;

/********************************************************************************************************/



/************************************************Variables***********************************************/
 static volatile UARTx_t * const UARTx [] = 
 {
    [UART_CHANNEL_1] = (volatile UARTx_t * const) (UART1_BASE_ADD),
    [UART_CHANNEL_2] = (volatile UARTx_t * const) (UART2_BASE_ADD),
    [UART_CHANNEL_6] = (volatile UARTx_t * const) (UART6_BASE_ADD)
 };

 static volatile UserRequest_t G_CurrTransReq [] =
 {
    [UART_CHANNEL_1] = {.Req_State = ReqState_Done}, 
    [UART_CHANNEL_2] = {.Req_State = ReqState_Done},
    [UART_CHANNEL_6] = {.Req_State = ReqState_Done} 
 };
 static volatile UserRequest_t G_CurrReceiveReq [] =
 {
    [UART_CHANNEL_1] = {.Req_State = ReqState_Done}, 
    [UART_CHANNEL_2] = {.Req_State = ReqState_Done},
    [UART_CHANNEL_6] = {.Req_State = ReqState_Done} 
 };
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
 enuErrorStatus_t UART_Init(UARTcfg_t Copy_UARTcfg)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    volatile UARTx_t * const UART = UARTx[Copy_UARTcfg.UART_CHANNEL];
    uint32_t Loc_u32Temp           = UART->CR1;
    float32_t UART_DIV;
    uint16_t DIV_Mantissa;
    float32_t DIV_fFraction;
    uint8_t DIV_u8Fraction;
    uint8_t OVER8_Value;
    if((IS_VALID_CHANNEL(Copy_UARTcfg.UART_CHANNEL) == 0) ||
       (IS_VALID_WORD_LENGTH(Copy_UARTcfg.WORD_LENGTH) == 0) ||
       (IS_VALID_STOP_BITS(Copy_UARTcfg.STOP_BITS) == 0) ||
       (IS_VALID_SAMPLING(Copy_UARTcfg.OVER_SAMPLING) == 0) ||
       (IS_VALID_SAMPLE_METHOD(Copy_UARTcfg.SAMPLE_BIT_METHOD) == 0) ||
       (IS_VALID_PARITY(Copy_UARTcfg.PARITY) == 0))
    {
      Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
    }
    else
    {

        Loc_u32Temp &= CR1_CLR_MASK;
        Loc_u32Temp |= Copy_UARTcfg.OVER_SAMPLING | Copy_UARTcfg.PARITY | Copy_UARTcfg.WORD_LENGTH | UART_ENABLE;
        UART->CR1    = Loc_u32Temp;

        Loc_u32Temp  = UART->CR2;
        Loc_u32Temp &= CR2_CLR_STOP_BITS;
        Loc_u32Temp |= Copy_UARTcfg.STOP_BITS;
        UART->CR2    = Loc_u32Temp;

        Loc_u32Temp  = UART->CR3;
        Loc_u32Temp &= CR3_CLR_SAMPLE_BIT;
        Loc_u32Temp |= Copy_UARTcfg.SAMPLE_BIT_METHOD;
        UART->CR3    = Loc_u32Temp;

        OVER8_Value    = (8.0 * (2 - (1&((UART->CR1) >> (OVER8_BIT_NO)))));
        UART_DIV       = (float)UART_SRC_CLK_VALUE / ((float)(OVER8_Value) * (float)Copy_UARTcfg.BaudRate);
        DIV_Mantissa   = (uint16_t) UART_DIV;
        DIV_fFraction  = (float)((uint16_t)(UART_DIV * 100.0) % 100 ) / (float)(OVER8_Value);
        DIV_u8Fraction = ROUND_TO_INTEGER(DIV_fFraction);
        if(DIV_u8Fraction >= OVER8_Value)
        {
          DIV_Mantissa++;
          DIV_u8Fraction--;
        }
        else
        {
          /*Do Nothing*/
        }

        Loc_u32Temp  = UART->BRR;
        Loc_u32Temp &= ~MASK_16BITS;
        Loc_u32Temp |= (DIV_Mantissa<<DIV_MANTISSA_START_BIT) | (DIV_u8Fraction);
        UART->BRR    = Loc_u32Temp;

        UART->CR1 |= TE_ENABLE;
        UART->CR1 |= RE_ENABLE;

    }
    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t UART_SendByte(uint32_t UART_CHANNEL, uint8_t Copy_u8Data)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    uint16_t Loc_u16TimeOut = 6000;

    if(IS_VALID_CHANNEL(UART_CHANNEL) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
    }
    else
    {
        UARTx[UART_CHANNEL]->CR1 &= ~TCIE_BIT;
        UARTx[UART_CHANNEL]->DR   = Copy_u8Data;
        UARTx[UART_CHANNEL]->SR  &= ~TC_BIT;
        while(/* ((UARTx[UART_CHANNEL]->SR & TC_BIT) == 0) && */ (Loc_u16TimeOut != 1)){Loc_u16TimeOut--;};
        /* if(Loc_u16TimeOut == 0)
        {
            Ret_enuErrorStatus = enuErrorStatus_Timeout;
        } */
    }
    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t UART_ReceiveByte(uint32_t UART_CHANNEL, uint8_t *Add_u8Data)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    uint16_t Loc_u16TimeOut = 6000;
   
    if(IS_VALID_CHANNEL(UART_CHANNEL) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
    }
    else if(IS_NOT_NULL(Add_u8Data) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
    else
    { 
        while(--Loc_u16TimeOut)
        {
            if((UARTx[UART_CHANNEL]->SR & RXNE_BIT))
            {
                *Add_u8Data = UARTx[UART_CHANNEL]->DR;
                break;
            }
        }
        if(Loc_u16TimeOut == 0 )
        {
            Ret_enuErrorStatus = enuErrorStatus_Timeout;
        }
    }
    return Ret_enuErrorStatus;
 }



 /*NOTE: I think this function needs a runnable*/
 /*
 enuErrorStatus_t UART_SendByteAsynch(uint32_t UART_CHANNEL, uint8_t Copy_u8Data)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;

    if(IS_VALID_CHANNEL(UART_CHANNEL) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
    }
    else
    {
      //  UARTx[UART_CHANNEL]->CR1 &= ~TCIE_BIT;
      //  UARTx[UART_CHANNEL]->CR1 |= TE_ENABLE;
      //  UARTx[UART_CHANNEL]->DR   = Copy_u8Data;
      //  UARTx[UART_CHANNEL]->CR1 |= TCIE_BIT;

    }
    return Ret_enuErrorStatus;
 }
*/

 /*NOTE: I think this function needs a runnable*/
/*
 enuErrorStatus_t UART_ReceiveByteAsynch(uint32_t UART_CHANNEL, uint8_t *Add_u8Data)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    uint16_t Loc_u16TimeOut = 6000;

    UARTx[UART_CHANNEL]->CR1 |= RE_ENABLE;
    while(--Loc_u16TimeOut)
    {
        if((UARTx[UART_CHANNEL]->SR & RXNE_BIT))
        {
            *Add_u8Data = UARTx[UART_CHANNEL]->DR;
            break;
        }
    }
    if(Loc_u16TimeOut == 0 )
    {
        Ret_enuErrorStatus = enuErrorStatus_Timeout;
    }

    return Ret_enuErrorStatus;
 }

*/
 enuErrorStatus_t UART_SendBufferAsynch(uint32_t UART_CHANNEL, UART_BufferReq_t *Add_Buffer)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;

     if(IS_VALID_CHANNEL(UART_CHANNEL) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
    }
    else if(IS_NOT_NULL(Add_Buffer) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
	else if(G_CurrTransReq[UART_CHANNEL].Req_State == ReqState_Busy)
	{
		Ret_enuErrorStatus = enuErrorStatus_NotOk;
	}
    else
    {
		G_CurrTransReq[UART_CHANNEL].Req_State = ReqState_Busy;
		G_CurrTransReq[UART_CHANNEL].User_Req  = *Add_Buffer;
		G_CurrTransReq[UART_CHANNEL].Index     = 0; 

        UARTx[UART_CHANNEL]->CR1 &= ~TCIE_BIT;
        UARTx[UART_CHANNEL]->CR1 |= TE_ENABLE;
        UARTx[UART_CHANNEL]->DR   = G_CurrTransReq[UART_CHANNEL].User_Req.Data_Buffer[G_CurrTransReq[UART_CHANNEL].Index];
        UARTx[UART_CHANNEL]->SR  &= ~TC_BIT;
        UARTx[UART_CHANNEL]->CR1 |= TCIE_BIT;
    }
    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t UART_ReceiveBufferAsynch(uint32_t UART_CHANNEL, UART_BufferReq_t *Add_Buffer)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;

     if(IS_VALID_CHANNEL(UART_CHANNEL) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
    }
    else if(IS_NOT_NULL(Add_Buffer) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
	else if(G_CurrReceiveReq[UART_CHANNEL].Req_State == ReqState_Busy)
	{
		Ret_enuErrorStatus = enuErrorStatus_NotOk;
	}
    else
    {
		G_CurrReceiveReq[UART_CHANNEL].Req_State = ReqState_Busy;
        G_CurrReceiveReq[UART_CHANNEL].User_Req  = *Add_Buffer;
		G_CurrReceiveReq[UART_CHANNEL].Index     = 0;

        UARTx[UART_CHANNEL]->CR1 |= RE_ENABLE;
        UARTx[UART_CHANNEL]->CR1 |= RXNEIE_BIT;
    }
    return Ret_enuErrorStatus;
 }


   void USART1_IRQHandler(void)
 {
	if(UARTx[UART_CHANNEL_1]->SR & TC_BIT)
	{
		UARTx[UART_CHANNEL_1]->CR1 &= ~TCIE_BIT;
		if((G_CurrTransReq[UART_CHANNEL_1].Index < G_CurrTransReq[UART_CHANNEL_1].User_Req.Buffer_Length) /* && (G_CurrTransReq.Req_State == ReqState_Busy) */)
		{
        	UARTx[UART_CHANNEL_1]->DR   = G_CurrTransReq[UART_CHANNEL_1].User_Req.Data_Buffer[G_CurrTransReq[UART_CHANNEL_1].Index++];
        	UARTx[UART_CHANNEL_1]->CR1 |= TCIE_BIT;
		}
		else /*Done transimission*/
		{
			G_CurrTransReq[UART_CHANNEL_1].Req_State = ReqState_Done;
			if(G_CurrTransReq[UART_CHANNEL_1].User_Req.Req_CBF)
			{
				G_CurrTransReq[UART_CHANNEL_1].User_Req.Req_CBF();
			}
		}
	}
	if(UARTx[UART_CHANNEL_1]->SR & RXNE_BIT)
	{
		UARTx[UART_CHANNEL_1]->CR1 &= ~RXNEIE_BIT;
		if(G_CurrReceiveReq[UART_CHANNEL_1].Index < G_CurrReceiveReq[UART_CHANNEL_1].User_Req.Buffer_Length)
		{
			G_CurrReceiveReq[UART_CHANNEL_1].User_Req.Data_Buffer[G_CurrReceiveReq[UART_CHANNEL_1].Index++] = UARTx[UART_CHANNEL_1]->DR;
			UARTx[UART_CHANNEL_1]->CR1 |= RXNEIE_BIT;
		}
		else 
		{
			G_CurrReceiveReq[UART_CHANNEL_1].Req_State = ReqState_Done;
			if(G_CurrReceiveReq[UART_CHANNEL_1].User_Req.Req_CBF)
			{
				G_CurrReceiveReq[UART_CHANNEL_1].User_Req.Req_CBF();
			}
		}
	}
 }


 void USART2_IRQHandler(void)
 {
	if(UARTx[UART_CHANNEL_2]->SR & TC_BIT)
	{
		UARTx[UART_CHANNEL_2]->CR1 &= ~TCIE_BIT;
		if((G_CurrTransReq[UART_CHANNEL_2].Index < G_CurrTransReq[UART_CHANNEL_2].User_Req.Buffer_Length) /* && (G_CurrTransReq.Req_State == ReqState_Busy) */)
		{
        	UARTx[UART_CHANNEL_2]->DR   = G_CurrTransReq[UART_CHANNEL_2].User_Req.Data_Buffer[G_CurrTransReq[UART_CHANNEL_2].Index++];
        	UARTx[UART_CHANNEL_2]->CR1 |= TCIE_BIT;
		}
		else /*Done transimission*/
		{
			G_CurrTransReq[UART_CHANNEL_2].Req_State = ReqState_Done;
			if(G_CurrTransReq[UART_CHANNEL_2].User_Req.Req_CBF)
			{
				G_CurrTransReq[UART_CHANNEL_2].User_Req.Req_CBF();
			}
		}
	}
	if(UARTx[UART_CHANNEL_2]->SR & RXNE_BIT)
	{
		UARTx[UART_CHANNEL_2]->CR1 &= ~RXNEIE_BIT;
		if(G_CurrReceiveReq[UART_CHANNEL_2].Index < G_CurrReceiveReq[UART_CHANNEL_2].User_Req.Buffer_Length)
		{
			G_CurrReceiveReq[UART_CHANNEL_2].User_Req.Data_Buffer[G_CurrReceiveReq[UART_CHANNEL_2].Index++] = UARTx[UART_CHANNEL_2]->DR;
			UARTx[UART_CHANNEL_2]->CR1 |= RXNEIE_BIT;
		}
		else 
		{
			G_CurrReceiveReq[UART_CHANNEL_2].Req_State = ReqState_Done;
			if(G_CurrReceiveReq[UART_CHANNEL_2].User_Req.Req_CBF)
			{
				G_CurrReceiveReq[UART_CHANNEL_2].User_Req.Req_CBF();
			}
		}
	}
 }

 void USART6_IRQHandler(void)
 {
	if(UARTx[UART_CHANNEL_6]->SR & TC_BIT)
	{
		UARTx[UART_CHANNEL_6]->CR1 &= ~TCIE_BIT;
		if((G_CurrTransReq[UART_CHANNEL_6].Index < G_CurrTransReq[UART_CHANNEL_6].User_Req.Buffer_Length) /* && (G_CurrTransReq.Req_State == ReqState_Busy) */)
		{
        	UARTx[UART_CHANNEL_6]->DR   = G_CurrTransReq[UART_CHANNEL_6].User_Req.Data_Buffer[G_CurrTransReq[UART_CHANNEL_6].Index++];
        	UARTx[UART_CHANNEL_6]->CR1 |= TCIE_BIT;
		}
		else /*Done transimission*/
		{
			G_CurrTransReq[UART_CHANNEL_6].Req_State = ReqState_Done;
			if(G_CurrTransReq[UART_CHANNEL_6].User_Req.Req_CBF)
			{
				G_CurrTransReq[UART_CHANNEL_6].User_Req.Req_CBF();
			}
		}
	}
	if(UARTx[UART_CHANNEL_6]->SR & RXNE_BIT)
	{
		UARTx[UART_CHANNEL_6]->CR1 &= ~RXNEIE_BIT;
		if(G_CurrReceiveReq[UART_CHANNEL_6].Index < G_CurrReceiveReq[UART_CHANNEL_6].User_Req.Buffer_Length)
		{
			G_CurrReceiveReq[UART_CHANNEL_6].User_Req.Data_Buffer[G_CurrReceiveReq[UART_CHANNEL_6].Index++] = UARTx[UART_CHANNEL_6]->DR;
			UARTx[UART_CHANNEL_6]->CR1 |= RXNEIE_BIT;
		}
		else 
		{
			G_CurrReceiveReq[UART_CHANNEL_6].Req_State = ReqState_Done;
			if(G_CurrReceiveReq[UART_CHANNEL_6].User_Req.Req_CBF)
			{
				G_CurrReceiveReq[UART_CHANNEL_6].User_Req.Req_CBF();
			}
		}
	}
 }
/********************************************************************************************************/


