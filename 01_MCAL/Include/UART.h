/**
* 
* @file    : UART Driver Header File (MCAL)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/
#ifndef	 _UART_H_
#define	 _UART_H_

/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "ErrorStatus.h"
 #include "MASKS.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define UART_CHANNEL_1                        (uint32_t)0X00
 #define UART_CHANNEL_2                        (uint32_t)0X01
 #define UART_CHANNEL_6                        (uint32_t)0X02
 
 #define WORD_LENGTH_8                         (uint32_t)0x00
 #define WORD_LENGTH_9                         (uint32_t)BIT12_MASK

 #define STOP_BITS_HALF                        (uint32_t)0X1000
 #define STOP_BITS_ONE                         (uint32_t)0X0000
 #define STOP_BITS_ONE_AND_HALF                (uint32_t)0X3000
 #define STOP_BITS_TWO                         (uint32_t)0X2000

 #define OVER_SAMPLING_8                       (uint32_t)BIT15_MASK
 #define OVER_SAMPLING_16                      (uint32_t)0x00

 #define SAMPLE_BIT_METHOD_1                   (uint32_t)BIT11_MASK
 #define SAMPLE_BIT_METHOD_3                   (uint32_t)0x00

 #define PARITY_DISABLE                        (uint32_t)0x00
 #define PARITY_ENABLE_EVEN                    (uint32_t)(BIT10_MASK)
 #define PARITY_ENABLE_ODD                     (uint32_t)(BIT10_MASK | BIT9_MASK)


 #define LIN_BREAK_DETECT_INTERRUPT_ENABLE     (uint32_t)BIT6_MASK
 #define LIN_BREAK_DETECT_INTERRUPT_DISABLE    (uint32_t)0x00

 #define LIN_BREAK_DETECT_LENGTH_10            (uint32_t)0x00
 #define LIN_BREAK_DETECT_LENGTH_11            (uint32_t)BIT5_MASK
 
/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef void (*NotificationCBF_t) (void);

 typedef struct
 {
    uint32_t UART_CHANNEL;
    uint32_t BaudRate;
    uint32_t WORD_LENGTH;
    uint32_t STOP_BITS;
    uint32_t OVER_SAMPLING;
    uint32_t SAMPLE_BIT_METHOD;
    uint32_t PARITY;
 }UARTcfg_t;

 typedef struct
 {
    char * Data_Buffer;
    uint16_t Buffer_Length;
    NotificationCBF_t Req_CBF;
 }UART_BufferReq_t;
 
/********************************************************************************************************/



/************************************************APIs****************************************************/
 /**
 * @brief   : Function to intialize the UART channel to be used with the input configuration
 * @param   : Copy_UARTcfg Variable contains the needed configuration, @note: Every element in this struct 
 *            has its own options defined above to choose from except for the BaudRate
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidCfg         : The input configuration has something wrong in it
 */
 enuErrorStatus_t UART_Init(UARTcfg_t Copy_UARTcfg);

 /**
 * @brief   : Function to send one single byte
 * @param   : UART_CHANNEL is the channel to send the byte over (Choose form the options above)
 * @param   : Copy_u8Data The data to be sent
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : Invalid UART_CHANNEL has been passed
 */
 enuErrorStatus_t UART_SendByte(uint32_t UART_CHANNEL, uint8_t Copy_u8Data);

 /**
 * @brief   : Function to receive one single byte
 * @param   : UART_CHANNEL is the channel to receive the byte over (Choose form the options above)
 * @param   : Add_u8Data address of the variable to receive the data in
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : Invalid UART_CHANNEL has been passed
 *            enuErrorStatus_NULLPointer        : Add_u8Data is a NULL pointer
 */
 enuErrorStatus_t UART_ReceiveByte(uint32_t UART_CHANNEL, uint8_t *Add_u8Data);

 /**
 * @brief   : Function to send a buffer of data Asynchronously
 * @param   : UART_CHANNEL is the channel to send the byte over (Choose form the options above)
 * @param   : Add_Buffer is an address to a varaible of type UART_BufferReq_t that holds the info of the data to be sent
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : Invalid UART_CHANNEL has been passed
 *            enuErrorStatus_NULLPointer        : Add_Buffer is a NULL pointer
 *            enuErrorStatus_NotOk              : This UART Channel is currently busy serving another request
 */
 enuErrorStatus_t UART_SendBufferAsynch(uint32_t UART_CHANNEL, UART_BufferReq_t *Add_Buffer);

 /**
 * @brief   : Function to receive a buffer of data Asynchronously
 * @param   : UART_CHANNEL is the channel to receive the byte over (Choose form the options above)
 * @param   : Add_Buffer is an address to a varaible of type UART_BufferReq_t that holds the info of the data to be received
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : Invalid UART_CHANNEL has been passed
 *            enuErrorStatus_NULLPointer        : Add_Buffer is a NULL pointer
 *            enuErrorStatus_NotOk              : This UART Channel is currently busy serving another request
 */
 enuErrorStatus_t UART_ReceiveBufferAsynch(uint32_t UART_CHANNEL, UART_BufferReq_t *Add_Buffer);

 /*LIN send break function*/
 /*LIN BREAK DETECTION ENABLE*/
/********************************************************************************************************/




#endif /*_UART_H_*/