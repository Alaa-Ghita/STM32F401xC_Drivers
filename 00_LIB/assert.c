/**
* 
* @file    : Source File
* @author  : Alaa Ghita
* @date    : Feb 2024
* @brief   : This the Source file contains assert_param macro like a funcion which is used to validate the inputs to a function.
* 
*/
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

//#include "diag/trace.h"

#if defined(USE_FULL_ASSERT)

void assert_failed (uint8_t* file, uint32_t line);

void assert_failed (uint8_t* file, uint32_t line)
{
    volatile int x;
    while(1)
    {
      x++;
    }
}

// Called from the assert_param() macro, usually defined in the stm32f*_conf.h
//void __attribute__((noreturn, weak))
//assert_failed (uint8_t* file, uint32_t line)
//{
//  trace_printf ("assert_param() failed: file \"%s\", line %d\n", file, line);
//  abort ();
  /* NOTREACHED */
//}

#endif // defined(USE_FULL_ASSERT)