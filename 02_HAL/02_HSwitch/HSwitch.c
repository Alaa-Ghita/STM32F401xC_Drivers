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
 #define IS_VALID_CONNECTION(CONNECTION)        (((CONNECTION) == HSwitch_CONNECTION_FORWARD)||\
                                                 ((CONNECTION) == HSwitch_CONNECTION_REVERSE))

 #define IS_VALID_HSwitch(HSwitch)                      ((HSwitch) < _HSwitch_num)

/********************************************************************************************************/


/************************************************Types***************************************************/

/********************************************************************************************************/


/************************************************Variables***********************************************/
 extern const HSwitchcfg_t HSwitches[_HSwitch_num];

 static uint32_t HSwitches_PinStates[_HSwitch_num];
/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/
 enuErrorStatus_t HSwitch_init(void)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint16_t Loc_u16Counter = 0;
   GPIO_PinCfg_t Loc_CurrentHSwitch;
   Loc_CurrentHSwitch.GPIO_MODE = GPIO_MODE_IN;
   Loc_CurrentHSwitch.GPIO_OSPEED = GPIO_OSPEED_HIGH;
   for(Loc_u16Counter = 0;Loc_u16Counter < _HSwitch_num; Loc_u16Counter++)
   {
      if(IS_VALID_CONNECTION(HSwitches[Loc_u16Counter].Connection))
      {
        Loc_CurrentHSwitch.GPIO_PORT = HSwitches[Loc_u16Counter].Port;
        Loc_CurrentHSwitch.GPIO_PIN  = HSwitches[Loc_u16Counter].Pin;
        Loc_CurrentHSwitch.GPIO_PUPD = HSwitches[Loc_u16Counter].Connection + GPIO_PUPD_PU;
        Ret_enuErrorStatus = GPIO_InitPin(&Loc_CurrentHSwitch);
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
 
 enuErrorStatus_t HSwitch_GetStatus(uint32_t Copy_u32HSwitch, enuHSwitchState_t * Add_enuHSwitchState)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if(IS_VALID_HSwitch(Copy_u32HSwitch) == 0)
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else if(Add_enuHSwitchState == NULL)
   {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      *Add_enuHSwitchState = !((HSwitches_PinStates[Copy_u32HSwitch]) ^ (HSwitches[Copy_u32HSwitch].Connection));
   }
   return Ret_enuErrorStatus;
 }

 /*This Runnable should come every 5ms*/
 void HSwitch_Runnable(void)
 {
    static uint32_t HSwitches_PrevStates[_HSwitch_num] = {0};
    static uint32_t HSwitches_Counts[_HSwitch_num] = {0};
    static uint32_t Loc_u32HSwitchCurState =0;
    uint16_t Loc_u16Counter = 0;
    for(Loc_u16Counter=0; Loc_u16Counter < _HSwitch_num; Loc_u16Counter++)
    {
      GPIO_GetPinValue(HSwitches[Loc_u16Counter].Pin, HSwitches[Loc_u16Counter].Port, &Loc_u32HSwitchCurState);
      if(Loc_u32HSwitchCurState == HSwitches_PrevStates[Loc_u16Counter])
      {
        HSwitches_Counts[Loc_u16Counter]++;
      }
      else
      {
        HSwitches_Counts[Loc_u16Counter] = 0;
      }

      if((HSwitches_Counts[Loc_u16Counter] % 5 ) == 0)
      {
        HSwitches_PinStates[Loc_u16Counter] = Loc_u32HSwitchCurState;
      }

      HSwitches_PrevStates[Loc_u16Counter] = Loc_u32HSwitchCurState;
    }
 }
/********************************************************************************************************/
