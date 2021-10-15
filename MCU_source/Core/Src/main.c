/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "sdmmc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HM10_BleModule.h"
#include "LF_AppMain.h"



#include <stdio.h>
//#include "CZUJNIKI.h"
//#include "R_PID.h"
#include "EEPROM.h"
//#include "Komendy_BLE.h"
#include "Robot_Control.h"
//#include <TSOP2236_new_T.h>
//#include "ENKODERY.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
void LED_BLINKING();
void ProfilPredkosci();
void zrob_charakterystki_siln();

//uint32_t aktCzas=0;
//uint32_t zapCzas=0;
//
//
//uint32_t aktCzaspPWM=0;
//uint32_t zapCzaspPWM=0;
//int zm_pPWM=0;
//float bufor_zpomiar_prpwm[20];
//int valueofpwm=1000;
//
//int LED_BLINK=1,LED_Helper=0;
//int Sys_Reset=0;

void EEPROM_LED_BLINK_READ()
{
	EEPROM_READ_INT(455, &LED_BLINK);
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//uint16_t DANE_Z_CZUJNIKOW[8];
/*
void my_i2c_scanner(uint8_t adress)
{
	  if(HAL_I2C_IsDeviceReady(&hi2c1, (adress << 1 ) , 1, 100) == HAL_OK)
	  {

		 // HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
	  }
	  HAL_Delay(10);
}*/

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SDMMC1_SD_Init();
  MX_ADC1_Init();
  MX_TIM15_Init();
  MX_TIM4_Init();
  MX_I2C4_Init();
  MX_USART2_UART_Init();
  MX_UART5_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  //Activate 100usTimer
  LL_TIM_EnableIT_CC1(TIM2);
  LL_TIM_EnableCounter(TIM2);
  //just for information (it is set by default in CubeMX
  //  HAL_GPIO_WritePin(EEPROM_WC_GPIO_Port, EEPROM_WC_Pin, GPIO_PIN_RESET);


  LF_App_MainConfig();


//  EEPROM_LED_BLINK_READ(); //defined in this file above
//  CZUJNIKI_INIT(); //Init the sensors,reference to file "CZUJNIKI.c"
//  Motor_PWM_Init(); //Init the PWM on Motor Drivers,reference to file "R_PID.c"
//  IR_INIT(); //Init the IR detector, reference to file "IR_TSOP2236_byTeor.c"




	/*float CZ_B1,CZ_B2,CZ_B3;
  unsigned long l=0;*/

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  LF_App_MainTask();

	 // zrob_charakterystki_siln();

//	  oblicz_predkosc();
//	  mierzprzebdr();
//
//	  ProfilPredkosci();
//
//	  OBLICZ_BLAD(); //reference to file "CZUJNIKI.c"
//	  calculatePID(); //reference to file "R_PID.c"
//	  Robot_Control(); //reference to file "Robot_Control.c"
//	  DANE_DO_APLIKACJI_MOBILNEJ(); ////reference to file "Komendy_BLE.h"
//	  LED_BLINKING(); //defined in this file below
//	  IR_READER();
//
//	 wykryj_znacznik();
	// pomiardoble();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 8;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
  PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	// Check if UART2 trigger the Callback
	if(huart->Instance == USART2)
	{
		// Start listening again
		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, HM10BLE_App.ReceiveBuffer, ReceiveBufferSize);
		HM10BLE_RxEventCallback(Size);
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	// Check if UART2 triggered the Callback
	if(huart->Instance == USART2)
	{
		HM10BLE_TxCmpltEventCallback();
	}
}





void LED_BLINKING()
{
#define LED_TOGGLE_TIME 500

//	if(LED_BLINK)
//	{
//
//	  aktCzas=HAL_GetTick();
//
//	  if( zapCzas+LED_TOGGLE_TIME < aktCzas)
//	  {
//
//
//	  if(LED_Helper)
//		  {
//		  	  // HAL_GPIO_WritePin(LDD1_GPIO_Port, LDD1_Pin,GPIO_PIN_SET);
//			  //  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_SET);
//			  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin,GPIO_PIN_SET);
//			  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin,GPIO_PIN_SET);
//			  LED_Helper=0;
//		  }
//
//
//	  else
//	  {
//			//  HAL_GPIO_WritePin(LDD1_GPIO_Port, LDD1_Pin,GPIO_PIN_RESET);
//			//  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,GPIO_PIN_RESET);
//			  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin,GPIO_PIN_RESET);
//			  HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin,GPIO_PIN_RESET);
//			  LED_Helper=1;
//	  }
//		  zapCzas= HAL_GetTick();
//		  		  zapCzas=aktCzas;
//	  }
//	}

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
