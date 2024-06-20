/**
* 
* @file    : LCD Driver Source File (HAL)
* @author  : Alaa Ghita
* @date    : April 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "LCD.h"
 #include "GPIO.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define CMD_8BIT_MODE_FUNCTION_SET    0x3B
 #define CMD_DISPLAY_SETTING           0x0F /*Display and cursor controlling*/
 #define CMD_CLEAR                     0x01
 #define CMD_ENTRY_MODE_SET            0x06
 #define CMD_RETURN_HOME               0x02
 #define CMD_DISP_SHIFT_LEFT           0x18
 #define CMD_DISP_SHIFT_RIGHT          0x1C
 #define CMD_DISPLAY_CURSOR            0x0e
 #define CMD_HIDE_CURSOR               0x0c

 #define REQ_TYPE_NONE                 0x00
 #define REQ_TYPE_CMD                  0x01
 #define REQ_TYPE_DATA                 0x02
 #define REQ_TYPE_STRING               0x03

 #define LCD_DDRAM_START_ADD           0x80
 #define LCD_SECOND_ROW                0x40

 #define LCD_WRITE_OPERATION            PIN_VALUE_LOW 
 #define LCD_WRITE_TYPE_CMD             PIN_VALUE_LOW
 #define LCD_WRITE_TYPE_DATA            PIN_VALUE_HIGH

 #define IS_NOT_NULL(PTR)              ((PTR) != NULL)
/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef enum
 {
    InitState_PowerON,
    InitState_FunctionSet,
    InitState_DisplaySetting,
    InitState_DisplayClear,
    InitState_EntryMode,
    InitState_End,
 }InitState_t;

 typedef struct
 {
    const char * S;
    uint16_t Length;
    uint8_t Data;
    uint8_t CMD;
    ReqState_t State;
    uint8_t Type;
    NotificationCBF_t CB;
 }UserReq_t;

 typedef struct
 {
    uint16_t CurrentPos;
    NotificationCBF_t CB;
 }WriteProgress_t;

 typedef enum
 {
    ProcState_Done,
    //ProcState_Ready,
    ProcState_Busy
 }ProcState_t;
/********************************************************************************************************/



/************************************************Variables***********************************************/
 static LCDState_t LCDState = LCDState_OFF;
 //static UserReq_t UserReq = {.State = ReqState_Ready, .Type = REQ_TYPE_NONE};
 //static WriteProgress_t WriteProgress = {.CurrentPos = 0, .CB = NULL};
 static UserReq_t UserReqs_Buffer[REQUESTS_BUFFER_SIZE];
 static WriteProgress_t WriteProgress_Buffer[REQUESTS_BUFFER_SIZE];
 static BufferCapacity_t Buffer_Head = 0;
 static BufferCapacity_t Buffer_Tail = 0;

 extern const LCDPins_t LCD_ControlPins[_ControlPins_num];
 extern const LCDPins_t LCD_DataPins[_DataPins_num];
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
 static void InitSM(void);
 static void OperationalSM(void);
 static ProcState_t Write_Proc(uint8_t Copy_u8Val, uint8_t LCD_WRITE_TYPE);
 static ProcState_t WriteDataHelper_Proc(void);
 static void HW_Init(void);
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
 void LCD_InitAsynch(void)
 {
    LCDState = LCDState_Init;
 }


 LCDState_t LCD_GetState(void)
 {
    return LCDState;
 }

 /*ReqState_t LCD_GetRequestState(void)
 {
    return UserReq.State;
 }*/


 enuErrorStatus_t LCD_ClearScreanAsynch(NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(/*(LCDState == LCDState_Operational) &&*/ (UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State   = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type    = REQ_TYPE_CMD;
        UserReqs_Buffer[Buffer_Head].CMD     = CMD_CLEAR;
        WriteProgress_Buffer[Buffer_Head].CB = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }

 
  enuErrorStatus_t LCD_DisplayCursorAsynch(NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(/*(LCDState == LCDState_Operational) &&*/ (UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type  = REQ_TYPE_CMD;
        UserReqs_Buffer[Buffer_Head].CMD   = CMD_DISPLAY_CURSOR;
        WriteProgress_Buffer[Buffer_Head].CB    = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t LCD_HideCursorAsynch(NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(/*(LCDState == LCDState_Operational) &&*/ (UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State  = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type   = REQ_TYPE_CMD;
        UserReqs_Buffer[Buffer_Head].CMD    = CMD_HIDE_CURSOR;
        WriteProgress_Buffer[Buffer_Head].CB     = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }



 enuErrorStatus_t LCD_SetCursorAsynch(uint8_t ROW, uint8_t COLUMN, NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    uint8_t Loc_u8Location = 0;
    if((ROW > ROW_2) || (COLUMN > COLUMN_16))
    {
        Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
    }
    else if(/*(LCDState == LCDState_Operational) && */(UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State   = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type    = REQ_TYPE_CMD;
        Loc_u8Location                       = COLUMN + (LCD_SECOND_ROW * ROW);
        UserReqs_Buffer[Buffer_Head].CMD     = Loc_u8Location + LCD_DDRAM_START_ADD;
        WriteProgress_Buffer[Buffer_Head].CB = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t LCD_WriteDataAsynch(uint8_t Copy_u8Data, NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(/*(LCDState == LCDState_Operational) && */(UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State   = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type    = REQ_TYPE_DATA;
        UserReqs_Buffer[Buffer_Head].Data    = Copy_u8Data;
        WriteProgress_Buffer[Buffer_Head].CB = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t LCD_WriteStringAsynch(char * Add_u8pString, uint16_t Copy_u16Length, NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(IS_NOT_NULL(Add_u8pString) == 0)
    {
        Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
    }
    else if(/*(LCDState == LCDState_Operational) && */(UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type = REQ_TYPE_STRING;
        UserReqs_Buffer[Buffer_Head].S = Add_u8pString;
        UserReqs_Buffer[Buffer_Head].Length = Copy_u16Length;
        WriteProgress_Buffer[Buffer_Head].CurrentPos = 0;
        WriteProgress_Buffer[Buffer_Head].CB  = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t LCD_ReturnHomeAsynch(NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(/*(LCDState == LCDState_Operational) && */(UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State      = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type       = REQ_TYPE_CMD;
        UserReqs_Buffer[Buffer_Head].CMD        = CMD_RETURN_HOME;
        WriteProgress_Buffer[Buffer_Head].CB   = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t LCD_DisplayShiftLeftAsynch(NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(/*(LCDState == LCDState_Operational) && */(UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State      = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type       = REQ_TYPE_CMD;
        UserReqs_Buffer[Buffer_Head].CMD        = CMD_DISP_SHIFT_LEFT;
        WriteProgress_Buffer[Buffer_Head].CB   = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }


 enuErrorStatus_t LCD_DisplayShiftRightAsynch(NotificationCBF_t Add_CallBack)
 {
    enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
    if(/*(LCDState == LCDState_Operational) && */(UserReqs_Buffer[Buffer_Head].State == ReqState_Ready))
    {
        UserReqs_Buffer[Buffer_Head].State      = ReqState_Busy;
        UserReqs_Buffer[Buffer_Head].Type       = REQ_TYPE_CMD;
        UserReqs_Buffer[Buffer_Head].CMD        = CMD_DISP_SHIFT_RIGHT;
        WriteProgress_Buffer[Buffer_Head].CB   = Add_CallBack;
        if(Buffer_Head >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Head = 0;
        }
        else
        {
        	Buffer_Head++;
        }
    }
    else
    {
        Ret_enuErrorStatus = enuErrorStatus_NotOk;
    }

    return Ret_enuErrorStatus;
 }


 /*Comes every 2ms*/
 void LCD_Runnable(void)
 {
    switch(LCDState)
    {
        case(LCDState_Init):
            InitSM();
        break;
        case(LCDState_Operational):
           OperationalSM();
        break;
        case(LCDState_OFF):
            /*Do Nothing*/
        break;
        default:
            /*Do Nothing*/
        break;
    }
 }
/********************************************************************************************************/



/**************************************Static Functions Implementation***********************************/
 static void InitSM(void)
 {
    static InitState_t InitState = InitState_PowerON;
    static ProcState_t CurrProcState = ProcState_Done;
    static uint32_t Loc_u32Counter = 0;
    Loc_u32Counter = Loc_u32Counter+2;
    switch(InitState)
    {
        case(InitState_PowerON):
            if(Loc_u32Counter == 2)
            {
                HW_Init();
            }
            else if(Loc_u32Counter == 30)
            {
                InitState = InitState_FunctionSet;
                Loc_u32Counter = 0;
            }
            break;
        case(InitState_FunctionSet):
            CurrProcState = Write_Proc(CMD_8BIT_MODE_FUNCTION_SET,LCD_WRITE_TYPE_CMD);
            if(CurrProcState == ProcState_Done)
            {
                InitState = InitState_DisplaySetting;
            }
            break;
        case(InitState_DisplaySetting):
            CurrProcState = Write_Proc(CMD_DISPLAY_SETTING,LCD_WRITE_TYPE_CMD);
            if(CurrProcState == ProcState_Done)
            {
                InitState = InitState_DisplayClear;
            }
            break;
        case(InitState_DisplayClear):
            CurrProcState = Write_Proc(CMD_CLEAR,LCD_WRITE_TYPE_CMD);
            if(CurrProcState == ProcState_Done)
            {
                InitState = InitState_EntryMode;
            }
            break;
        case(InitState_EntryMode):
            CurrProcState = Write_Proc(CMD_ENTRY_MODE_SET,LCD_WRITE_TYPE_CMD);
            if(CurrProcState == ProcState_Done)
            {
                InitState = InitState_End;
            }
            break;
        case(InitState_End):
            LCDState = LCDState_Operational;
            break;
        default:
            break;
    }
 }


 static void OperationalSM(void)
 {
    static uint32_t Loc_u32Counter = 0;
    static ProcState_t CurrProcState = ProcState_Done;
    Loc_u32Counter++;
    if(UserReqs_Buffer[Buffer_Tail].State == ReqState_Busy)
    {
        switch (UserReqs_Buffer[Buffer_Tail].Type)
        {
            case (REQ_TYPE_CMD):
                CurrProcState = Write_Proc(UserReqs_Buffer[Buffer_Tail].CMD, LCD_WRITE_TYPE_CMD);
                if(CurrProcState == ProcState_Done)
                {
                    UserReqs_Buffer[Buffer_Tail].State = ReqState_Done;
                }
                break;
            case (REQ_TYPE_DATA):
                CurrProcState = Write_Proc(UserReqs_Buffer[Buffer_Tail].Data, LCD_WRITE_TYPE_DATA);
                if(CurrProcState == ProcState_Done)
                {
                    UserReqs_Buffer[Buffer_Tail].State = ReqState_Done;
                }
                break;
            case (REQ_TYPE_STRING):
                CurrProcState = WriteDataHelper_Proc();
                if(CurrProcState == ProcState_Done)
                {
                    UserReqs_Buffer[Buffer_Tail].State = ReqState_Done;
                }
                break;
            case (REQ_TYPE_NONE):
                /*Do Nothing*/
                break;
            default:
                /*Do Nothing*/
                break;
        }
    }
    else if (UserReqs_Buffer[Buffer_Tail].State == ReqState_Done)
    {
        UserReqs_Buffer[Buffer_Tail].State = ReqState_Ready;
        if(Buffer_Tail >= (REQUESTS_BUFFER_SIZE-1))
        {
        	Buffer_Tail = 0;
        }
        else
        {
        	Buffer_Tail++;
        }
        if(WriteProgress_Buffer[Buffer_Tail].CB)
            WriteProgress_Buffer[Buffer_Tail].CB();
    }
 }
 

 static void HW_Init(void)
 {
    GPIO_PinCfg_t Loc_CurrentPin;
    uint8_t Loc_u8Counter = 0;

    Loc_CurrentPin.GPIO_MODE   = GPIO_MODE_OUT_PP;
    Loc_CurrentPin.GPIO_PUPD   = GPIO_PUPD_NONE;
    Loc_CurrentPin.GPIO_OSPEED = GPIO_OSPEED_HIGH;
    for(Loc_u8Counter = 0; Loc_u8Counter < _ControlPins_num; Loc_u8Counter++)
    {
        Loc_CurrentPin.GPIO_PIN  = LCD_ControlPins[Loc_u8Counter].Pin;
        Loc_CurrentPin.GPIO_PORT = LCD_ControlPins[Loc_u8Counter].Port;
        GPIO_InitPin(&Loc_CurrentPin);
    }

    for(Loc_u8Counter = 0; Loc_u8Counter < _DataPins_num; Loc_u8Counter++)
    {
        Loc_CurrentPin.GPIO_PIN  = LCD_DataPins[Loc_u8Counter].Pin;
        Loc_CurrentPin.GPIO_PORT = LCD_DataPins[Loc_u8Counter].Port;
        GPIO_InitPin(&Loc_CurrentPin);
    }
 }


 static ProcState_t Write_Proc(uint8_t Copy_u8Val, uint8_t LCD_WRITE_TYPE)
 {
    static ProcState_t ProcState = ProcState_Done;
    uint32_t Loc_u32Counter = 0;
    if(ProcState == ProcState_Done)
    {
        ProcState = ProcState_Busy;
        GPIO_SetPinValue(LCD_ControlPins[ReadWrite_Pin].Pin, LCD_ControlPins[ReadWrite_Pin].Port, LCD_WRITE_OPERATION);
        GPIO_SetPinValue(LCD_ControlPins[RegSelect_Pin].Pin, LCD_ControlPins[RegSelect_Pin].Port, LCD_WRITE_TYPE);

        for(Loc_u32Counter = 0; Loc_u32Counter < _DataPins_num; Loc_u32Counter++)
        {
            GPIO_SetPinValue(LCD_DataPins[Loc_u32Counter].Pin, LCD_DataPins[Loc_u32Counter].Port, ((Copy_u8Val>>Loc_u32Counter) & 1));
        }

        GPIO_SetPinValue(LCD_ControlPins[Enable_Pin].Pin, LCD_ControlPins[Enable_Pin].Port, PIN_VALUE_HIGH);
    }
    else if(ProcState == ProcState_Busy)
    {

        GPIO_SetPinValue(LCD_ControlPins[Enable_Pin].Pin, LCD_ControlPins[Enable_Pin].Port, PIN_VALUE_LOW);
        ProcState = ProcState_Done;

    }

    return ProcState;
 }

 static ProcState_t WriteDataHelper_Proc(void)
 {
    static ProcState_t ProcState = ProcState_Done;
    static ProcState_t ThreadProcState = ProcState_Done;

    if(IS_NOT_NULL(UserReqs_Buffer[Buffer_Tail].S) && (UserReqs_Buffer[Buffer_Tail].Length > WriteProgress_Buffer[Buffer_Tail].CurrentPos))
    {
        ProcState = ProcState_Busy;
        ThreadProcState = Write_Proc(UserReqs_Buffer[Buffer_Tail].S[WriteProgress_Buffer[Buffer_Tail].CurrentPos],LCD_WRITE_TYPE_DATA);
        if(ThreadProcState == ProcState_Done)
        {
            WriteProgress_Buffer[Buffer_Tail].CurrentPos++;
        }   
    }
    else 
    {
        ProcState = ProcState_Done;
    }

    return ProcState;
 }
/********************************************************************************************************/
