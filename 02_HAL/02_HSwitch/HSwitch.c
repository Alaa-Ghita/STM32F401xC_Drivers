/**
* 
* @file    : Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : Switch Driver (HAL)
* Machine  : STM32F401xC 
* 
*/



/************************************************Includes************************************************/
 #include "HSwitch.h"
 #include "GPIO.h"
/********************************************************************************************************/


/************************************************Defines*************************************************/
 #define IS_VALID_CONNECTION(CONNECTION)        (((CONNECTION) == SWITCH_CONNECTION_FORWARD)||\
                                                 ((CONNECTION) == SWITCH_CONNECTION_REVERSE))

 #define IS_VALID_Switch(SWITCH)                      ((SWITCH) < _Switch_num)

/********************************************************************************************************/


/************************************************Types***************************************************/

/********************************************************************************************************/


/************************************************Variables***********************************************/
 extern const Switchcfg_t Switches[_Switch_num];

 static uint32_t Switches_PinStates[_Switch_num];
/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/
 enuErrorStatus_t Switch_init(void)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint16_t Loc_u16Counter = 0;
   GPIO_PinCfg_t Loc_CurrentSwitch;
   Loc_CurrentSwitch.GPIO_MODE = GPIO_MODE_IN;
   Loc_CurrentSwitch.GPIO_OSPEED = GPIO_OSPEED_HIGH;
   for(Loc_u16Counter = 0;Loc_u16Counter < _Switch_num; Loc_u16Counter++)
   {
      if(IS_VALID_CONNECTION(Switches[Loc_u16Counter].Connection))
      {
        Loc_CurrentSwitch.GPIO_PORT = Switches[Loc_u16Counter].Port;
        Loc_CurrentSwitch.GPIO_PIN  = Switches[Loc_u16Counter].Pin;
        Loc_CurrentSwitch.GPIO_PUPD = Switches[Loc_u16Counter].Connection + GPIO_PUPD_PU;
        Ret_enuErrorStatus = GPIO_InitPin(&Loc_CurrentSwitch);
        if (Ret_enuErrorStatus != enuErrorStatus_Ok)
        { break; }
      }
      else
      {
        Ret_enuErrorStatus = enuErrorStatus_InvalidCfg;
        break;
      }
   }
   return Ret_enuErrorStatus;
 }
 
 enuErrorStatus_t Switch_GetStatus(uint32_t Copy_u32Switch, enuSwitchState_t * Add_enuSwitchState)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if(IS_VALID_Switch(Copy_u32Switch) == 0)
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else if(Add_enuSwitchState == NULL)
   {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      /*Need to verify this*/
      *Add_enuSwitchState = (Switches_PinStates[Copy_u32Switch] ^ Switches[Copy_u32Switch].Connection);
   }
   return Ret_enuErrorStatus;
 }

 /*This Runnable should come every 5ms*/
 void Switch_Runnable(void)
 {
    static uint32_t Switches_PinStates[_Switch_num] = {0};
    static uint32_t Switches_Counts[_Switch_num] = {0};
    uint32_t Loc_u32SwitchCurState =0; 
    uint16_t Loc_u16Counter = 0;
    for(Loc_u16Counter=0; Loc_u16Counter < _Switch_num; Loc_u16Counter++)
    {
      GPIO_GetPinValue( &Switches[Loc_u16Counter].Pin , &Loc_u32SwitchCurState);
      if(Loc_u32SwitchCurState == Switches_PinStates[Loc_u16Counter])
      {
        Switches_Counts[Loc_u16Counter]++;
      }
      else
      {
        Switches_Counts[Loc_u16Counter] = 0;
      }

      if(Switches_Counts[Loc_u16Counter] % 5 == 0)
      {
        Switches_PinStates[Loc_u16Counter] = Loc_u32SwitchCurState;
      }

      Switches_PinStates[Loc_u16Counter] = Loc_u32SwitchCurState;
    }
 }
/********************************************************************************************************/
