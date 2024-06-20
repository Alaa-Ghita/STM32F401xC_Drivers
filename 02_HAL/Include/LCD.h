/**
* 
* @file    : LCD Driver Header File (HAL)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

#ifndef	 _LCD_H_
#define	 _LCD_H_

/************************************************Includes************************************************/
 #include "Typedefs.h"
 #include "ErrorStatus.h"
 #include "LCD_cfg.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define ROW_1              0x00
 #define ROW_2              0x01

 #define COLUMN_1           0x00
 #define COLUMN_2           0x01
 #define COLUMN_3           0x02
 #define COLUMN_4           0x03
 #define COLUMN_5           0x04
 #define COLUMN_6           0x05
 #define COLUMN_7           0x06
 #define COLUMN_8           0x07
 #define COLUMN_9           0x08
 #define COLUMN_10          0x09
 #define COLUMN_11          0x0a
 #define COLUMN_12          0x0b
 #define COLUMN_13          0x0c
 #define COLUMN_14          0x0d
 #define COLUMN_15          0x0e
 #define COLUMN_16          0x0f
/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef enum
 {
    Enable_Pin,   
    ReadWrite_Pin,
    RegSelect_Pin,
    _ControlPins_num
 }LCD_ControlPins_t;

 typedef enum
 {
    Data_Pin0,
    Data_Pin1,
    Data_Pin2,
    Data_Pin3, 
    Data_Pin4, 
    Data_Pin5, 
    Data_Pin6, 
    Data_Pin7,
    _DataPins_num
 }LCD_DataPins_t;

 typedef struct
 {
    uint32_t Pin;
    uint32_t Port;
 }LCDPins_t;

 typedef enum
 {
   ReqState_Ready,
   ReqState_Busy,
   ReqState_Done
 }ReqState_t;
 
 typedef enum
 {
   LCDState_Init,
   LCDState_Operational,
   LCDState_OFF,
 }LCDState_t;

 typedef void (*NotificationCBF_t) (void);
/********************************************************************************************************/



/************************************************APIs****************************************************/
 /**
 * @brief   : Asynchronous function to init the LCD, and the hardware connections
 */
 void LCD_InitAsynch(void);

 /**
 * @brief   : Function to get the Current State of the LCD (LCDState_Init, LCDState_Operational, or LCDState_OFF)
 * @return  : It returns a variable of type LCDState_t indicating to the current State of the LCD
 */
 LCDState_t LCD_GetState(void);

 /**
 * @brief   : Function to get the Current State of the assigned requset (Init, Operational, or OFF)
 * @param   : The mode of the SysTick To Start (Use the Options declared above)
 * @return  :  It returns a variable of type ReqState_t indicating to the current State of the request 
 */
 //ReqState_t LCD_GetRequestState(void);

 /**
 * @brief   : Asynchronous Function to Clear the LCD screen
 * @param   : An address of a call back function (Notification) to call it after finishing this request (optional, pass a null if you don't want a notification function)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NotOk              : The LCD is currently busy serving another request, and can't take any requests right now.
 */
 enuErrorStatus_t LCD_ClearScreanAsynch(NotificationCBF_t Add_CallBack);

 /**
 * @brief   : Asynchronous Function to Set a new porition to the cursor
 * @param   : ROW is the row of the cursor's new position (Choose from the options above)
 * @param   : CULOMN is the column of the cursor's new position (Choose from the options above)
 * @param   : Add_CallBack is the address of a call back function (Notification) to call it after finishing this request (optional, pass a null if you don't want a notification function)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_InvalidParameter   : If the passed row number, or culomn is not from the options above
 *            enuErrorStatus_NotOk              : The LCD is currently busy serving another request, and can't take any requests right now.
 */
 enuErrorStatus_t LCD_SetCursorAsynch(uint8_t ROW, uint8_t CULOMN, NotificationCBF_t Add_CallBack);

 enuErrorStatus_t LCD_DisplayCursorAsynch(NotificationCBF_t Add_CallBack);

 enuErrorStatus_t LCD_HideCursorAsynch(NotificationCBF_t Add_CallBack);

 /**
 * @brief   : Asynchronous Function to display Data to the LCD (Single Charachter) 
 * @param   : Add_u8pData is The address of the string to be displayed
 * @param   : Add_CallBack is the address of a call back function (Notification) to call it after finishing this request (optional, pass a null if you don't want a notification function)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NotOk              : The LCD is currently busy serving another request, and can't take any requests right now.
 */
 enuErrorStatus_t LCD_WriteDataAsynch(uint8_t Copy_u8Data, NotificationCBF_t Add_CallBack);

 /**
 * @brief   : Asynchronous Function to display a string to the LCD 
 * @param   : Add_u8pString is The address of the string to be displayed (make sure you don't change the value of the string in this address till the request is served)
 * @param   : Copy_u16Length is the length of the string to be displayed
 * @param   : Add_CallBack is the address of a call back function (Notification) to call it after finishing this request (optional, pass a null if you don't want a notification function)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NULLPointer        : The address of the string to be dispalyed is NULL
 *            enuErrorStatus_NotOk              : The LCD is currently busy serving another request, and can't take any requests right now.
 */
 enuErrorStatus_t LCD_WriteStringAsynch(char * Add_u8pString, uint16_t Copy_u16Length, NotificationCBF_t Add_CallBack);

 /**
 * @brief   : Asynchronous Function to return the cursor back to it's starting position (1,1)
 * @param   : Add_CallBack is the address of a call back function (Notification) to call it after finishing this request (optional, pass a null if you don't want a notification function)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NotOk              : The LCD is currently busy serving another request, and can't take any requests right now.
 */
 enuErrorStatus_t LCD_ReturnHomeAsynch(NotificationCBF_t Add_CallBack);

 /**
 * @brief   : Asynchronous Function to shift the displayed screen to the left by one digit
 * @param   : Add_CallBack is the address of a call back function (Notification) to call it after finishing this request (optional, pass a null if you don't want a notification function)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NotOk              : The LCD is currently busy serving another request, and can't take any requests right now.
 */
 enuErrorStatus_t LCD_DisplayShiftLeftAsynch(NotificationCBF_t Add_CallBack);

 /**
 * @brief   : Asynchronous Function to shift the displayed screen to the right by one digit
 * @param   : Add_CallBack is the address of a call back function (Notification) to call it after finishing this request (optional, pass a null if you don't want a notification function)
 * @return  : It returns a variable of type enuErrorStatus_t with one of these values: 
 *            enuErrorStatus_Ok                 : Successful Operation
 *            enuErrorStatus_NotOk              : The LCD is currently busy serving another request, and can't take any requests right now.
 */
 enuErrorStatus_t LCD_DisplayShiftRightAsynch(NotificationCBF_t Add_CallBack);     

 /**
 * @brief   : The Runnable to add in the scheduler, this runnable should come every 2ms
 */
 void LCD_Runnable(void);
/********************************************************************************************************/




#endif /*_LCD_H_*/