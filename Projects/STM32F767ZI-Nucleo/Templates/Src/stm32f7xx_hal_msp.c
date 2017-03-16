/**
  ******************************************************************************
  * @file    Templates/Src/stm32f7xx_hal_msp.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-April-2016
  * @brief   HAL MSP module.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */



void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;

  if(huart->Instance == USARTx) {
	  /*##-1- Enable peripherals and GPIO Clocks #################################*/
	  /* Enable GPIO TX/RX clock */
	  USARTx_TX_GPIO_CLK_ENABLE();
	  USARTx_RX_GPIO_CLK_ENABLE();

	  /* Select SysClk as source of USART1 clocks */
	  RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	  RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
	  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

	  /* Enable USARTx clock */
	  USARTx_CLK_ENABLE();

	  /*##-2- Configure peripheral GPIO ##########################################*/
	  /* UART TX GPIO pin configuration  */
	  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
	  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull      = GPIO_PULLUP;
	  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.Alternate = USARTx_TX_AF;

	  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	  /* UART RX GPIO pin configuration  */
	  GPIO_InitStruct.Pin = USARTx_RX_PIN;
	  GPIO_InitStruct.Alternate = USARTx_RX_AF;

	  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

	  /*##-3- Configure the NVIC for UART ########################################*/
	  /* NVIC for USART */
	  HAL_NVIC_SetPriority(USARTx_IRQn, 1, 1);
	  HAL_NVIC_EnableIRQ(USARTx_IRQn);
  } else if (huart->Instance == USARTaux) {
	  /*##-1- Enable peripherals and GPIO Clocks #################################*/
	    /* Enable GPIO TX/RX clock */
	    USARTaux_TX_GPIO_CLK_ENABLE();
	    USARTaux_RX_GPIO_CLK_ENABLE();

	    /* Select SysClk as source of USART1 clocks */
	    RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
	    RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
	    HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);

	    /* Enable USARTx clock */
	    USARTaux_CLK_ENABLE();

	    /*##-2- Configure peripheral GPIO ##########################################*/
	    /* UART TX GPIO pin configuration  */
	    GPIO_InitStruct.Pin       = USARTaux_TX_PIN;
	    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull      = GPIO_PULLUP;
	    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = USARTaux_TX_AF;

	    HAL_GPIO_Init(USARTaux_TX_GPIO_PORT, &GPIO_InitStruct);

	    /* UART RX GPIO pin configuration  */
	    GPIO_InitStruct.Pin = USARTaux_RX_PIN;
	    GPIO_InitStruct.Alternate = USARTaux_RX_AF;

	    HAL_GPIO_Init(USARTaux_RX_GPIO_PORT, &GPIO_InitStruct);

	    /*##-3- Configure the NVIC for UART ########################################*/
	    /* NVIC for USART */
	    HAL_NVIC_SetPriority(USARTaux_IRQn, 0, 1);
	    HAL_NVIC_EnableIRQ(USARTaux_IRQn);
  } else {
	  while(1);
  }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* TIMx Peripheral clock enable */
	TIMx_CLK_ENABLE();
	TIMy_CLK_ENABLE();

	/* Enable all GPIO Channels Clock requested */
	TIMx_CHANNEL_GPIO_PORT();
	TIMx_CHANNEL_GPIO_PORTB();
	TIMy_CHANNEL_GPIO_PORTD();

	/* Configure PB.04 (pin 19 in CN7 connector) (TIM3_Channel1), PB.05 (pin 13 in CN7 connector) (TIM3_Channel2), PB.00 (pin 31 in CN10 connector) (TIM3_Channel3),
	PB.01 (pin 7 in CN10 connector) (TIM3_Channel4) in output, push-pull, alternate function mode
	*/
	/* Common configuration for all channels */
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL1;
	GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL1;
	HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL1, &GPIO_InitStruct);

	GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL2;
	GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL2;
	HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL2, &GPIO_InitStruct);

	GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL3;
	GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL3;
	HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL3, &GPIO_InitStruct);

	GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL4;
	GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL4;
	HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL4, &GPIO_InitStruct);



	GPIO_InitStruct.Alternate = TIMy_GPIO_AF_CHANNEL1;
	GPIO_InitStruct.Pin = TIMy_GPIO_PIN_CHANNEL1;
	HAL_GPIO_Init(TIMy_GPIO_PORT_CHANNEL1, &GPIO_InitStruct);

	GPIO_InitStruct.Alternate = TIMy_GPIO_AF_CHANNEL2;
	GPIO_InitStruct.Pin = TIMy_GPIO_PIN_CHANNEL2;
	HAL_GPIO_Init(TIMy_GPIO_PORT_CHANNEL2, &GPIO_InitStruct);

	GPIO_InitStruct.Alternate = TIMy_GPIO_AF_CHANNEL3;
	GPIO_InitStruct.Pin = TIMy_GPIO_PIN_CHANNEL3;
	HAL_GPIO_Init(TIMy_GPIO_PORT_CHANNEL3, &GPIO_InitStruct);

	GPIO_InitStruct.Alternate = TIMy_GPIO_AF_CHANNEL4;
	GPIO_InitStruct.Pin = TIMy_GPIO_PIN_CHANNEL4;
	HAL_GPIO_Init(TIMy_GPIO_PORT_CHANNEL4, &GPIO_InitStruct);


}


/**
  * @brief  Initializes the Global MSP.
  * @param  None
  * @retval None
  */
void HAL_MspInit(void)
{
}

/**
  * @brief  DeInitializes the Global MSP.
  * @param  None  
  * @retval None
  */
void HAL_MspDeInit(void)
{
}

/**
  * @brief  Initializes the PPP MSP.
  * @param  None
  * @retval None
  */
/*void HAL_PPP_MspInit(void)
{*/
/*}*/

/**
  * @brief  DeInitializes the PPP MSP.
  * @param  None  
  * @retval None
  */
/*void HAL_PPP_MspDeInit(void)
{*/
/*}*/

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
