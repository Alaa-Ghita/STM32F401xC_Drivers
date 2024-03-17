/**
* 
* @file    : Traffic Light Application Soucre file 
* @author  : Alaa Ghita
* @date    : Mar 2024
* @version : 0.1v
* 
*/

/************************************************Includes************************************************/
 #include "LED.h"
 #include "TrafficLight.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
 #define PERIODECITY_SEC     1
/********************************************************************************************************/



/************************************************Types***************************************************/
 typedef enum{
    Green,
    Yellow,
    Red,
    None
}State_t;
/********************************************************************************************************/



/************************************************Variables***********************************************/
 static State_t State = Green;
 static State_t Prev  = None;
/********************************************************************************************************/


/*********************************************APIs Implementation****************************************/
 void TrafficLight_Init(void)
 {
    LED_init();
 }


 void TrafficLight_Runnable(void)
 {
    static uint32_t Loc_u32Counter=0;
    Loc_u32Counter += PERIODECITY_SEC;
    switch(State)
    {
        case Green:
            LED_SetStatus(Green, LED_STATE_ON);
            LED_SetStatus(Yellow, LED_STATE_OFF);
            LED_SetStatus(Red, LED_STATE_OFF);
            if(Loc_u32Counter == 6)
            {
                Loc_u32Counter = 0;
                State = Yellow;
                Prev  = Green;
            }
        break;
        case Yellow:
            LED_SetStatus(Green, LED_STATE_OFF);
            LED_SetStatus(Yellow, LED_STATE_ON);
            LED_SetStatus(Red, LED_STATE_OFF);
            if(Loc_u32Counter == 2)
            {
                Loc_u32Counter = 0;
                if(Prev == Green)
                {
                    State = Red;
                }
                else if(Prev == Red)
                {
                    State = Green;
                }
            }
        break;
        case Red:
            LED_SetStatus(Green, LED_STATE_OFF);
            LED_SetStatus(Yellow, LED_STATE_OFF);
            LED_SetStatus(Red, LED_STATE_ON);
            if(Loc_u32Counter == 20)
            {
                Loc_u32Counter = 0;
                State = Yellow;
                Prev  = Red;
            }
        break;
        default:
            /*Do Nothing*/
        break;
    } 
 }   
/********************************************************************************************************/


