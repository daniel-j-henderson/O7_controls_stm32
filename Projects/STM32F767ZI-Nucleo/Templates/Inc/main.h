/**
  ******************************************************************************
  * @file    Templates/Inc/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-April-2016
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144.h"
#include "stdio.h"
/* Exported types ------------------------------------------------------------*/
#define op_mode uint8_t
/* Exported constants --------------------------------------------------------*/
#define UART_MODE 0
#define I2C_MODE 1
#define MOTOR_ON 2
#define MOTOR_OFF 3

/* Exported macro ------------------------------------------------------------*/

#define TIMx                           TIM3
#define TIMx_CLK_ENABLE()              __TIM3_CLK_ENABLE()

#define TIMy                           TIM4
#define TIMy_CLK_ENABLE()              __TIM4_CLK_ENABLE()

/* Definition for TIMx Channel Pins */
#define TIMx_CHANNEL_GPIO_PORT()       __HAL_RCC_GPIOA_CLK_ENABLE();
#define TIMx_CHANNEL_GPIO_PORTB()       __HAL_RCC_GPIOB_CLK_ENABLE();
#define TIMx_GPIO_PORT_CHANNEL1        GPIOA
#define TIMx_GPIO_PORT_CHANNEL2        GPIOA
#define TIMx_GPIO_PORT_CHANNEL3        GPIOB
#define TIMx_GPIO_PORT_CHANNEL4        GPIOB

#define TIMx_GPIO_PIN_CHANNEL1         GPIO_PIN_6
#define TIMx_GPIO_PIN_CHANNEL2         GPIO_PIN_7
#define TIMx_GPIO_PIN_CHANNEL3         GPIO_PIN_0
#define TIMx_GPIO_PIN_CHANNEL4         GPIO_PIN_1

#define TIMx_GPIO_AF_CHANNEL1          GPIO_AF2_TIM3
#define TIMx_GPIO_AF_CHANNEL2          GPIO_AF2_TIM3
#define TIMx_GPIO_AF_CHANNEL3          GPIO_AF2_TIM3
#define TIMx_GPIO_AF_CHANNEL4          GPIO_AF2_TIM3

#define TIMy_CHANNEL_GPIO_PORTD()       __HAL_RCC_GPIOD_CLK_ENABLE();
#define TIMy_GPIO_PORT_CHANNEL1        GPIOD
#define TIMy_GPIO_PORT_CHANNEL2        GPIOD
#define TIMy_GPIO_PORT_CHANNEL3        GPIOD
#define TIMy_GPIO_PORT_CHANNEL4        GPIOD

#define TIMy_GPIO_PIN_CHANNEL1         GPIO_PIN_12
#define TIMy_GPIO_PIN_CHANNEL2         GPIO_PIN_13
#define TIMy_GPIO_PIN_CHANNEL3         GPIO_PIN_14
#define TIMy_GPIO_PIN_CHANNEL4         GPIO_PIN_15

#define TIMy_GPIO_AF_CHANNEL1          GPIO_AF2_TIM4
#define TIMy_GPIO_AF_CHANNEL2          GPIO_AF2_TIM4
#define TIMy_GPIO_AF_CHANNEL3          GPIO_AF2_TIM4
#define TIMy_GPIO_AF_CHANNEL4          GPIO_AF2_TIM4


#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART3_IRQn
#define USARTx_IRQHandler                USART3_IRQHandler

/* Auxillary USART */
#define USARTaux                           USART2
#define USARTaux_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define USARTaux_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTaux_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTaux_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTaux_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for USARTaux Pins */
#define USARTaux_TX_PIN                    GPIO_PIN_5
#define USARTaux_TX_GPIO_PORT              GPIOD
#define USARTaux_TX_AF                     GPIO_AF7_USART2
#define USARTaux_RX_PIN                    GPIO_PIN_6
#define USARTaux_RX_GPIO_PORT              GPIOD
#define USARTaux_RX_AF                     GPIO_AF7_USART2

/* Definition for USARTaux's NVIC */
#define USARTaux_IRQn                      USART2_IRQn
#define USARTaux_IRQHandler                USART2_IRQHandler


/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))



/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
