

#ifndef _ERROR_STATUS_H_
#define _ERROR_STATUS_H_

typedef enum
 {
    /**
 	*@brief : Everything OK, The Function Performed Correctly.
	*/
    enuErrorStatus_Ok,
    /**
	*@brief : Something went Wrong, The Function didn't Perform Incorrectly.
	*/
    enuErrorStatus_NotOk,
    /**
	*@brief : Passing NULL Pointer.
	*/
    enuErrorStatus_NULLPointer,
    /**
	*@brief : The Function Timed out.
	*/ 
    enuErrorStatus_Timeout,
    /**
	*@brief : The Function Timed out.
	*/ 
    enuErrorStatus_InvalidParameter,
    /**
    *@brief : Something is wrong in the configurations
    */
    enuErrorStatus_InvalidCfg

 }enuErrorStatus_t;


 #endif /*_ERROR_STATUS_H_*/