/**
  ******************************************************************************
  * @file    Templates/Src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    22-April-2016
  * @brief   Main program body
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


#define RXBUFFSIZE 20
#define AUXBUFFSIZE 0  //805 for goodnight moon
#define PERIOD_VALUE       (uint32_t)(2802 - 1)  /* Period Value  */
#define HALF_PULSE_VALUE       (uint32_t)(PERIOD_VALUE/2)        /* Capture Compare 1 Value  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t rxbuff[RXBUFFSIZE];
uint8_t auxbuff[AUXBUFFSIZE];
op_mode motor_status = MOTOR_OFF;

/* Buffer used for transmission */
//uint8_t lorem[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris dapibus sed justo maximus feugiat. Fusce lacinia dui lacus, eu feugiat tortor luctus eu. Aliquam ultricies mauris ut odio pharetra gravida. Vivamus tempus nibh ultricies ipsum vestibulum, vel ultricies magna commodo. Maecenas aliquet tristique viverra. Pellentesque tempor dignissim ex vel rutrum. Morbi dapibus in nibh quis bibendum. Nulla vulputate lacus non rhoncus maximus. In placerat arcu non eros tempus pretium. Duis auctor eros sit amet dolor molestie, ac ultricies libero hendrerit. Duis fringilla et neque id commodo. Cras nec dictum risus, facilisis commodo augue. Ut sed velit at erat tempor tristique. Duis at pulvinar enim. Etiam aliquam fermentum dapibus. Vestibulum rutrum, tortor id gravida vestibulum, tortor purus gravida nulla, sed rutrum leo turpis ac est.Maecenas eget efficitur lorem. Praesent eu euismod urna. Mauris convallis metus eu massa sagittis, nec consectetur ante blandit. Nulla facilisi. Class aptent taciti sociosqu ad amet.";
//uint8_t lorem[] = "In the great green room \nThere was a telephone \nAnd a red balloon \nAnd a picture of \nThe cow jumping over the moon \nAnd there were three little bears sitting on chairs \nAnd two little kittens \nAnd a pair of mittens \nAnd a little toy house \nAnd a young mouse \nAnd a comb and a brush and a bowl full of mush \nAnd a quiet old lady who was whispering hush \n\nGoodnight room \nGoodnight moon \nGoodnight cow jumping over the moon \nGoodnight light \nAnd the red balloon \n\nGoodnight bears \nGoodnight chairs \nGoodnight kittens \nAnd goodnight mittens \n\nGoodnight clocks \nAnd goodnight socks \nGoodnight little house \nAnd goodnight mouse \n\nGoodnight comb \nAnd goodnight brush \nGoodnight nobody \nGoodnight mush \n\nAnd goodnight to the old lady whispering hush \n\nGoodnight stars \nGoodnight air \nGood night noises everywhere";
uint8_t lorem[] = "";


UART_HandleTypeDef UartHandle;
UART_HandleTypeDef UartAux;

/* I2C handler declaration */
I2C_HandleTypeDef I2cHandle;

/* Timer handler declaration */
TIM_HandleTypeDef    TimHandleX;
TIM_HandleTypeDef    TimHandleY;

/* Timer Output Compare Configuration Structure declaration */
TIM_OC_InitTypeDef sConfig;

/* Counter Prescaler value */
uint32_t uhPrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{


	/* Configure the MPU attributes as Write Through */
	MPU_Config();

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	   - Configure the Flash ART accelerator on ITCM interface
	   - Configure the Systick to generate an interrupt each 1 msec
	   - Set NVIC Group Priority to 4
	   - Low Level Initialization
	*/

	HAL_Init();

	/* Configure the system clock to 216 MHz */
	SystemClock_Config();

	/* Compute the prescaler value for TIM3 counter clock*/
	uhPrescalerValue = (uint32_t)(114);


	/* Initialize first 4 PWMs */
	TimHandleX.Instance = TIMx;

	TimHandleX.Init.Prescaler         = uhPrescalerValue;
	TimHandleX.Init.Period            = PERIOD_VALUE;
	TimHandleX.Init.ClockDivision     = 0;
	TimHandleX.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandleX.Init.RepetitionCounter = 0;
	if (HAL_TIM_PWM_Init(&TimHandleX) != HAL_OK)
	{
	/* Initialization Error */
	Error_Handler();
	}


	/* Initialize second 4 PWMs */
	TimHandleY.Instance = TIMy;

	TimHandleY.Init.Prescaler         = uhPrescalerValue;
	TimHandleY.Init.Period            = PERIOD_VALUE;
	TimHandleY.Init.ClockDivision     = 0;
	TimHandleY.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandleY.Init.RepetitionCounter = 0;
	if (HAL_TIM_PWM_Init(&TimHandleY) != HAL_OK)
	{
	/* Initialization Error */
	Error_Handler();
	}

	/*##-2- Configure the PWM channels #########################################*/
	/* Common configuration for all channels */
	sConfig.OCMode       = TIM_OCMODE_PWM1;
	sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
	sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;

	/* Set the pulse value */
	sConfig.Pulse = HALF_PULSE_VALUE;

	if (HAL_TIM_PWM_ConfigChannel(&TimHandleX, &sConfig, TIM_CHANNEL_1) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}

	if (HAL_TIM_PWM_ConfigChannel(&TimHandleX, &sConfig, TIM_CHANNEL_2) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}

	if (HAL_TIM_PWM_ConfigChannel(&TimHandleX, &sConfig, TIM_CHANNEL_3) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}

	if (HAL_TIM_PWM_ConfigChannel(&TimHandleX, &sConfig, TIM_CHANNEL_4) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}



	if (HAL_TIM_PWM_ConfigChannel(&TimHandleY, &sConfig, TIM_CHANNEL_1) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}

	if (HAL_TIM_PWM_ConfigChannel(&TimHandleY, &sConfig, TIM_CHANNEL_2) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}

	if (HAL_TIM_PWM_ConfigChannel(&TimHandleY, &sConfig, TIM_CHANNEL_3) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}

	if (HAL_TIM_PWM_ConfigChannel(&TimHandleY, &sConfig, TIM_CHANNEL_4) != HAL_OK)
	{
		/* Configuration Error */
		Error_Handler();
	}

	/*
	 * USARTx is used to communicate to the USB port on the CT Board.
	 * printf() forwards to this port.
	 */

	UartHandle.Instance        = USARTx;

	UartHandle.Init.BaudRate   = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
	  /* Initialization Error */
	  Error_Handler();
	}


	/*
	 * Auxillary Uart: not used at present. Was used previously for
	 * having UART comms to another microcontroller.
	 */
//	UartAux.Instance        = USARTaux;
//
//	UartAux.Init.BaudRate   = 38400;
//	UartAux.Init.WordLength = UART_WORDLENGTH_8B;
//	UartAux.Init.StopBits   = UART_STOPBITS_1;
//	UartAux.Init.Parity     = UART_PARITY_NONE;
//	UartAux.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
//	UartAux.Init.Mode       = UART_MODE_TX_RX;
//	UartAux.Init.OverSampling = UART_OVERSAMPLING_16;
//	UartAux.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
//	if (HAL_UART_Init(&UartAux) != HAL_OK)
//	{
//	  /* Initialization Error */
//	  Error_Handler();
//	}


  printf("Begin\n");

  // Begin receiving interrupt-based UART communications
  if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)rxbuff, RXBUFFSIZE) != HAL_OK) {
	  Error_Handler();
  }

  while(1);
}

// END MAIN

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            PLL_R                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;
  
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);  

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  //RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 7;  
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Activate the OverDrive to reach the 216 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

/**
  * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
  * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
  *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;
  
  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

/* This function overrides the compiler's version of putchar to reroute those characters
 * to UartHandle, which sends to the computer terminal.
 */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

/*
 * This function updates the pwm signal for pwm channel 1 with a new duty cycle
 */
void update_pwm(int* dc) {
	if (motor_status == MOTOR_OFF) {
		sConfig.Pulse = (uint32_t)(PERIOD_VALUE * (float)*dc/3000.0f);
		if (HAL_TIM_PWM_ConfigChannel(&TimHandleX, &sConfig, TIM_CHANNEL_1) != HAL_OK)
		{
			/* Configuration Error */
			printf("\nupdate_pwm error\n");
			Error_Handler();
		}
		return;
	} else if (motor_status == MOTOR_ON) {
		if (HAL_TIM_PWM_Stop(&TimHandleX, TIM_CHANNEL_1) != HAL_OK)
		{
			/* PWM Generation Error */
			printf("\nupdate_pwm error\n");
			Error_Handler();
		}

		sConfig.Pulse = (uint32_t)(PERIOD_VALUE * (float)*dc/3000.0f);

		if (HAL_TIM_PWM_ConfigChannel(&TimHandleX, &sConfig, TIM_CHANNEL_1) != HAL_OK)
		{
			/* Configuration Error */
			printf("\nupdate_pwm error\n");
			Error_Handler();
		}
		if (HAL_TIM_PWM_Start(&TimHandleX, TIM_CHANNEL_1) != HAL_OK)
		{
			/* PWM Generation Error */
			printf("\nupdate_pwm error\n");
			Error_Handler();
		}

	}
}
/*
 * This function prints a char array to a given Uart of the F767
 */
void print(UART_HandleTypeDef *huart, uint8_t buff[], uint16_t n) {
	int i;
	for (i=0; i<n; i++) {
		if (buff[i] == 0x00) break;
		HAL_UART_Transmit(huart, (uint8_t *)&buff[i], 1, 0xFFFF);
	}
}

/*
 * Clears the rxbuff string
 */
void clearstring() {
	int i;
	for (i=0; i<RXBUFFSIZE; i++) {
		rxbuff[i] = 0x00;
	}
}

/*
 * Sends the rxbuff string to the terminal and clears it. Not super necessary to have anymore
 * but it is still and use and I haven't gotten around to replacing it.
 */
void sendstring() {
	print(&UartHandle, rxbuff, RXBUFFSIZE);
	clearstring();
}

/*
 * Returns the length of the string in the char array of length n
 */
uint8_t lenstr(uint8_t *str, uint8_t n) {
	uint16_t i=0;
	while (i < n) {
		if (str[i] == 0x00) break;
		i++;
	}
	return i;
}

/*
 * Compares the first 'index' values of the char arrays a and b and returns the number of
 * inequalities found.
 */
uint16_t str_comp(const char *a, const char *b, uint16_t index) {
	uint16_t i=0;
	uint16_t nerr = 0;
	while(i<index) {
		if (a[i] != b[i]) nerr++;
		i++;
	}
	return nerr;
}

/*
 * Copies the contents of a into b up to the RXBUFFSIZE, only meant to be used
 * for arrays of length RXBUFFSIZE. Again, this is am artifact of my first pass
 * through where I just needed stuff to work and didn't worry about modularity/robustness.
 */
void strcopy(uint8_t *a, uint8_t *b) {
	uint16_t i=0;
	while(i<RXBUFFSIZE){
		b[i] = a[i];
		i++;
	}
}

/*
 * Takes a char array pointer and its length and puts the value of the decimal number
 * the string represents into n, if it is a number. Otherwise returns 0.
 */
uint8_t str2int(volatile uint8_t *a, uint8_t str_len, int* n) {
	uint8_t j = str_len-1;
	uint8_t i;
	*n = 0;
	for (i=0; i<str_len; i++){
		if (a[i] < 0x30 || a[i] > 0x39) return 0;
		uint8_t k = j;
		int temp = a[i] - 0x30;
		while (k > 0){
			temp = temp*10;
			k--;
		}
		*n += temp;
		j--;
	}
	return 1;
}

/*
 * The character match flag callback function.
 * This function is called whenever the character that the terminal ends all its strings
 * with (0x3b, ';') is received. This means a string of less than RXBUFFSIZE characters has
 * been received and we should look at what it is.
 */
void cmf_UART_callback() {

	uint8_t str_index = lenstr(rxbuff, RXBUFFSIZE);
	if (str_index == 0) return;
	printf("\n%d ", str_index);


	// IGNORE THIS CASE
	if (!str_comp(rxbuff, (uint8_t *)"UART", 4)) {

		printf("\nUART STRESS TESTING\n");
		uint16_t ntests = 0;
		str2int(rxbuff+4, str_index-4, &ntests);
		printf("ntests: %d\n", ntests);
		uint16_t nerr = 0;
		uint16_t max_err_cnt = 0;
		uint16_t min_err_cnt = 10000;
		uint16_t i=0;
		while (i < ntests) {

			int j;
			int err_count = 0;
			uint8_t c;
			for (j=0; j<AUXBUFFSIZE; j++) {
				print(&UartAux, (uint8_t *)(lorem+j), 1);
				if(HAL_UART_Receive(&UartAux, (uint8_t *)&c, 1, 100) != HAL_OK) {
					  err_count++;
					  printf("timeout\n");
				} else if (c != lorem[j]) err_count++;
			}

			if (err_count > 0) {
				nerr++;
				if (err_count > max_err_cnt) max_err_cnt = err_count;
				if (err_count < min_err_cnt) min_err_cnt = err_count;
			}

			i++;
		}
		if (nerr > 0) {
			printf("\nNumber of failed tests: %d\n", nerr);
			printf("Error count range: %d -- %d (out of %d)\n", min_err_cnt, max_err_cnt, AUXBUFFSIZE);
		} else printf("\nNo Error.\n");
	}

	int dc; // used in case (4)

//	Check for control strings
	switch (str_index) {
	case (8): //motor
		if (!str_comp(rxbuff, "motor-on", str_index)) {
			// String received was 'motor-on', so enable each PWM
			if (motor_status == MOTOR_OFF) {
				motor_status = MOTOR_ON;
				if (HAL_TIM_PWM_Start(&TimHandleX, TIM_CHANNEL_1) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}
				if (HAL_TIM_PWM_Start(&TimHandleX, TIM_CHANNEL_2) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}
				if (HAL_TIM_PWM_Start(&TimHandleX, TIM_CHANNEL_3) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}
				if (HAL_TIM_PWM_Start(&TimHandleX, TIM_CHANNEL_4) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}

				if (HAL_TIM_PWM_Start(&TimHandleY, TIM_CHANNEL_1) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}
				if (HAL_TIM_PWM_Start(&TimHandleY, TIM_CHANNEL_2) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}
				if (HAL_TIM_PWM_Start(&TimHandleY, TIM_CHANNEL_3) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}
				if (HAL_TIM_PWM_Start(&TimHandleY, TIM_CHANNEL_4) != HAL_OK)
				{
					/* PWM Generation Error */
					Error_Handler();
				}
			}
			printf("\nreceived motor-on\n");
		}
		break;
	case (9): // motor-off
		if (!str_comp(rxbuff, "motor-off", str_index)) {
			if (motor_status == MOTOR_ON) {
			if (HAL_TIM_PWM_Stop(&TimHandleX, TIM_CHANNEL_1) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}
			if (HAL_TIM_PWM_Stop(&TimHandleX, TIM_CHANNEL_2) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}
			if (HAL_TIM_PWM_Stop(&TimHandleX, TIM_CHANNEL_3) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}
			if (HAL_TIM_PWM_Stop(&TimHandleX, TIM_CHANNEL_4) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}
			if (HAL_TIM_PWM_Stop(&TimHandleY, TIM_CHANNEL_1) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}
			if (HAL_TIM_PWM_Stop(&TimHandleY, TIM_CHANNEL_2) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}
			if (HAL_TIM_PWM_Stop(&TimHandleY, TIM_CHANNEL_3) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}
			if (HAL_TIM_PWM_Stop(&TimHandleY, TIM_CHANNEL_4) != HAL_OK)
			{
				/* PWM Generation Error */
				Error_Handler();
			}

				motor_status = MOTOR_OFF;
			}
			printf("\nreceived motor-off\n");
		}
		break;
	case (4)://PWM duty cycle value
		// If the 4 characters received were an integer, update the PWM pulse value
		if(str2int(rxbuff, str_index, &dc)) {
			update_pwm(&dc);
			printf("Received int: %d\n", dc);
		}
	}

	printf(rxbuff);
	printf("\n");
	clearstring();

}

/*
 * This is the callback used when the receive buffer rxbuff is full, meaning
 * the terminal sent at least RXBUFFSIZE characters. It echoes the string back and
 * clears the buffer for new received data.
 */
void main_UART_callback(UART_HandleTypeDef *huart) {
	sendstring();
}



/*
 * If an error flag caused an interrupt, this callback is called. For debugging purposes mainly.
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
	printf("error callback\n");
	if (huart->Instance == USARTx) {
		if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)rxbuff, RXBUFFSIZE) != HAL_OK) {
		  //Error_Handler();
			printf("Error Handler\n");
		}
	}
}

/*
 * This is the callback called by the interrupt service routine. From here, depending
 * on which Uart caused the interrupt and what type of interrupt it was, we call the
 * approproate callback function.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance->ISR & USART_ISR_CMF) {
		// Character Match Flag interrupt
		__HAL_UART_SEND_REQ(huart, UART_RXDATA_FLUSH_REQUEST);
		SET_BIT(huart->Instance->ICR, USART_ICR_CMCF);
		if (huart->Instance != USARTaux) cmf_UART_callback();
	}
	else {
		if (huart->Instance == USARTx) main_UART_callback(huart);
	}

	if (huart->Instance == USARTaux) {
		//As of 7 Dec, no longer use interrupts for UartAux
	} else {
		if(HAL_UART_Receive_IT(&UartHandle, (uint8_t *)rxbuff, RXBUFFSIZE) != HAL_OK) {
				  Error_Handler();
		}
	}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
