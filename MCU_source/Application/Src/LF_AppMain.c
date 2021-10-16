#include "main.h"
#include "string.h"
#include <stdio.h>
#include "dma.h"
#include "usart.h"
#include "gpio.h"

#include "LF_AppMain.h"
#include "TSOP2236_T.h"
#include "LineSensorsModule.h"
#include "PID_Reg_Module.h"
#include "HM10_BleModule.h"
#include "EEPROM.h"
#include "Robot_Control.h"

RC5Struct TSOP2236;
uint16_t TSOP_NormRecData;

void IR_DataRead();



void LF_App_MainConfig(void)
{
	EEPROM_WriteEnable();
	RC5_INIT(&TSOP2236);
	HM10BLE_Init();
	//	RC5100usTimer Called from stm32h7xx_it.c file
	//	RC5_IR_EXTI_GPIO_ReceiveAndDecodeFunction Called from stm32h7xx_it.c file

	SM_SensorModuleInit();
	PID_Init();

}

void LF_App_MainTask(void)
{
	HM10Ble_Task();
//	IR_DataRead();
	LF_Robot_ControlTask();
}














void IR_DataRead()
{
		RC5_ReadNormal(&TSOP2236, &TSOP_NormRecData);
		char Recval[50];
		int size = sprintf(Recval,"RecVal:0x%x\n\r",TSOP_NormRecData);

		HAL_UART_Transmit_DMA(&huart2,(uint8_t*) Recval, size);
		HAL_Delay(100);
}




