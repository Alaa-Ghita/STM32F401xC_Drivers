/**
* 
* @file    : Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @version : 0.1v
* Driver   : LED Driver (HAL)
* Machine  : STM32F401xC 
* 
*/



/************************************************Includes************************************************/
 #include "LED.h"
 #include "GPIO.h"
/********************************************************************************************************/


/************************************************Defines*************************************************/
 #define IS_VALID_CONNECTION(CONNECTION)        (((CONNECTION) == LED_CONNECTION_FORWARD) \
                                                || ((CONNECTION) == LED_CONNECTION_REVERSE))

 #define IS_VALID_STATE(STATE)                  (((STATE) == LED_STATE_ON) \
                                                || ((STATE) == LED_STATE_OFF))

 #define IS_VALID_LED(LED)                      ((LED) < _LED_num)

/********************************************************************************************************/


/************************************************Types***************************************************/

/********************************************************************************************************/


/************************************************Variables***********************************************/
 extern  const LEDcfg_t LEDs[_LED_num];

/********************************************************************************************************/


/*****************************************Static Functions Prototype*************************************/

/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/
 enuErrorStatus_t LED_init(void)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
   uint8_t Loc_u8Counter = 0;
   GPIO_PinCfg_t Loc_CurrentLed;
   Loc_CurrentLed.GPIO_MODE = GPIO_MODE_OUT_PP;
   Loc_CurrentLed.GPIO_OSPEED = GPIO_OSPEED_HIGH;
   for(Loc_u8Counter = 0; Loc_u8Counter < _LED_num ; Loc_u8Counter++)
   {
      if(IS_VALID_CONNECTION(LEDs[Loc_u8Counter].Connection)
         && IS_VALID_STATE(LEDs[Loc_u8Counter].DefaultState))
      {
         Loc_CurrentLed.GPIO_PORT = LEDs[Loc_u8Counter].Port;
         Loc_CurrentLed.GPIO_PIN  = LEDs[Loc_u8Counter].Pin;
         Loc_CurrentLed.GPIO_PUPD = LEDs[Loc_u8Counter].Connection + GPIO_PUPD_PU;
         Ret_enuErrorStatus = GPIO_InitPin(&Loc_CurrentLed);
         if (Ret_enuErrorStatus != enuErrorStatus_Ok)
         { break; }
         Ret_enuErrorStatus = GPIO_SetPinValue( LEDs[Loc_u8Counter].Pin, LEDs[Loc_u8Counter].Port, (LEDs[Loc_u8Counter].Connection)^(LEDs[Loc_u8Counter].DefaultState));
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
 
 enuErrorStatus_t LED_SetStatus(uint32_t Copy_u32LED, uint32_t LED_STATE)
 {
   enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_NotOk;
   if((IS_VALID_STATE(LED_STATE) == 0) || (IS_VALID_LED(Copy_u32LED) == 0))
   {
      Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
   }
   else
   {
      Ret_enuErrorStatus = enuErrorStatus_Ok;
      Ret_enuErrorStatus = GPIO_SetPinValue(LEDs[Copy_u32LED].Pin, LEDs[Copy_u32LED].Port, (LEDs[Copy_u32LED].Connection)^LED_STATE);
   }
   return Ret_enuErrorStatus;
 }

/********************************************************************************************************/
