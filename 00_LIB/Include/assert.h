/**
* 
* @file    : Header File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @brief   : This the header file contains assert_param macro like a funcion which is used to validate the inputs to a function.
* 
*/


#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "Typedefs.h"

/**
* @brief  You can undefine this USE_FULL_ASSERT macro to not use the assert_param functionality in validating the input param in the function
*/
#define USE_FULL_ASSERT    1U

#ifdef  USE_FULL_ASSERT
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t * file, uint32_t line);
#else
  #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#endif /*_ASSERT_H_*/