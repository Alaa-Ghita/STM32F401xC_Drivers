

#ifndef	 _STM32F401CC_IRQS_H_
#define	 _STM32F401CC_IRQS_H_

/*The TRQs' IDs in stm32f401cc*/  
  #define NVIC_IRQ_WINDOW_WATCHDOG                   0
  #define NIVC_IRQ_EXTI16_PVD                        1
  #define NIVC_IRQ_EXTI21_TAMP_STAMP	               2
  #define NIVC_IRQ_EXTI22_RTC_WKUP			             3
  #define NIVC_IRQ_FLASH			                       4
  #define NVIC_IRQ_RCC				                       5
  #define NVIC_IRQ_EXTI0			                       6
  #define NVIC_IRQ_EXTI1			                       7
  #define NVIC_IRQ_EXTI2			                       8
  #define NVIC_IRQ_EXTI3			                       9
  #define NVIC_IRQ_EXTI4			                       10
  #define NVIC_IRQ_DMA1_STREAM0			      	         11 
  #define NVIC_IRQ_DMA1_STREAM1     				         12
  #define NVIC_IRQ_DMA1_STREAM2				               13 
  #define NVIC_IRQ_DMA1_STREAM3				               14
  #define NVIC_IRQ_DMA1_STREAM4	      			         15
  #define NVIC_IRQ_DMA1_STREAM5				               16
  #define NVIC_IRQ_DMA1_STREAM6                      17
  #define NVIC_IRQ_ADC                               18
  #define NVIC_IRQ_EXTI9                             23
  #define NVIC_IRQ_TIM1_BRK_TIM9                     24
  #define NVIC_IRQ_TIM1_UP_TIM10                     25
  #define NVIC_IRQ_TIMI1_TRG_COM_TIM11               26
  #define NVIC_IRQ_TIMI1_CC                          27
  #define NVIC_IRQ_TIMI2                             28
  #define NVIC_IRQ_TIMI3                             29
  #define NVIC_IRQ_TIMI4                             30
  #define NVIC_IRQ_I2C1_EV                           31
  #define NVIC_IRQ_I2C1_ER                           32
  #define NVIC_IRQ_I2C2_EV                           33
  #define NVIC_IRQ_I2C2_ER                           34
  #define NVIC_IRQ_SPI1                              35
  #define NVIC_IRQ_SPI2                              36
  #define NVIC_IRQ_USART1                            37
  #define NVIC_IRQ_USART2                            38
  #define NVIC_IRQ_EXTI15_10                         40
  #define NVIC_IRQ_EXTI17_RTC_ALARM                  41
  #define NVIC_IRQ_EXTI18_OTG_FS_WKUP                42
  #define NVIC_IRQ_DMA1_STREAM7                      47
  #define NVIC_IRQ_SDIO                              49
  #define NVIC_IRQ_TIM5                              50
  #define NVIC_IRQ_SPI3                              51
  #define NVIC_IRQ_DMA2_STREAM0                      56
  #define NVIC_IRQ_DMA2_STREAM1                      57
  #define NVIC_IRQ_DMA2_STREAM2                      58
  #define NVIC_IRQ_DMA2_STREAM3                      59
  #define NVIC_IRQ_DMA2_STREAM4                      60
  #define NVIC_IRQ_OTG_FS                            67
  #define NVIC_IRQ_DMA2_STREAM5                      68
  #define NVIC_IRQ_DMA2_STREAM6                      69
  #define NVIC_IRQ_DMA2_STREAM7                      70
  #define NVIC_IRQ_USART6                            71
  #define NVIC_IRQ_I2C3_EV                           72
  #define NVIC_IRQ_I2C3_ER                           73
  #define NVIC_IRQ_FPU                               81
  #define NVIC_IRQ_SPI4                              84
/***********************************************/


#endif /*_STM32F401CC_IRQS_H_*/