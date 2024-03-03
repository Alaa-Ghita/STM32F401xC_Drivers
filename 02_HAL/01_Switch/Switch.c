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
 #include "Switch.h"
 #include "GPIO.h"
/********************************************************************************************************/


/************************************************Defines*************************************************/
 #define IS_VALID_CONNECTION(CONNECTION)        (((CONNECTION) == Switch_CONNECTION_FORWARD) \
                                                || ((CONNECTION) == Switch_CONNECTION_REVERSE))

 #define IS_VALID_Switch(SWITCH)                      ((SWITCH) < _Switch_num)

/********************************************************************************************************/


/************************************************Types***************************************************/

/********************************************************************************************************/


/************************************************Variables***********************************************/
 extern  const Switchcfg_t Switches[_Switch_num];

/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/
 enuErrorStatus_t Switch_init(void)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint8_t Loc_u8Counter = 0;
   GPIO_PinCfg_t Loc_CurrentSwitch;
   Loc_CurrentSwitch.GPIO_MODE = GPIO_MODE_IN;
   Loc_CurrentSwitch.GPIO_OSPEED = GPIO_OSPEED_HIGH;
   for(Loc_u8Counter < _Switch_num)
   {
      if(IS_VALID_CONNECTION(Switches[Loc_u8Counter].Connection))
      {
        Loc_CurrentSwitch.GPIO_PORT = Switches[Loc_u8Counter].Port;
        Loc_CurrentSwitch.GPIO_PIN  = Switches[Loc_u8Counter].Pin;
        Loc_CurrentSwitch.GPIO_PUPD = Switches[Loc_u8Counter].Connection + GPIO_PUPD_PU;
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
   uint32_t Loc_u32PinState;
   uint8_t Loc_u8Timeout = 600;
   if(IS_VALID_Switch(Copy_u32Switch) == 0)
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else if(Add_u8SwitchState == NULL)
   {
      Ret_enuErrorStatus = enuErrorStatus_NULLPointer;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      Ret_enuErrorStatus = GPIO_GetPinValue( &Switches[Copy_u32Switch].Pin , &Loc_u32PinState);
      if(Ret_enuErrorStatus == enuErrorStatus_Ok)
      {
        if(Loc_u32PinState ^ Switches[Copy_u32Switch].Connection)
        {
          while((Loc_u32PinState ^ Switches[Copy_u32Switch].Connection) && Loc_u8Timeout)
          {
            Ret_enuErrorStatus = GPIO_GetPinValue( &Switches[Copy_u32Switch].Pin , &Loc_u32PinState);
            Loc_u8Timeout--;
          }
          *Add_enuSwitchState = enuSwitch_Pressed;
        }
        else
        {
          *Add_enuSwitchState = enuSwitch_Released;
        }
      }
      else{ /*Do Nothing!*/ }
   }
   return Ret_enuErrorStatus;
 }

/********************************************************************************************************/
