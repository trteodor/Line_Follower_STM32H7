#include "main.h"
#include "string.h"
#include <stdio.h>
#include "dma.h"
#include "usart.h"
#include "gpio.h"

#include "LF_AppMain.h"
#include "TSOP2236_T.h"
#include "LineSensorsModule.h"

RC5Struct TSOP2236;
uint16_t TSOP_NormRecData;

void IR_DataRead();



void LF_App_MainConfig(void)
{
	SensorModuleInit();
}

void LF_App_MainTask(void)
{
	HM10BLE_Init();
	SensorsCalculateError();
	IR_DataRead();
}














void IR_DataRead()
{
		RC5_ReadNormal(&TSOP2236, &TSOP_NormRecData);
		char Recval[50];
		int size = sprintf(Recval,"RecVal:0x%x\n\r",TSOP_NormRecData);

		HAL_UART_Transmit_DMA(&huart2,(uint8_t*) Recval, size);
		HAL_Delay(100);
}




