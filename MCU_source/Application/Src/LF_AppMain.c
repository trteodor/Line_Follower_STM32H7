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
#include "IR_Module.h"
#include "BlinkLedMod.h"


void LF_App_MainConfig(void)
{
	EEPROM_WriteEnable();

	HM10BLE_Init();
	IR_ModInit();

	BlinkLedInit();
	SM_SensorModuleInit();
	PID_Init();
	LF_Robot_ControlInit();
}

void LF_App_MainTask(void) //only one Task without any RTOS, all works fine -- for now the soultion is inaf :)
{
	HM10Ble_Task();
	IR_Task();
	PID_Task();
	LF_Robot_ControlTask();
	BlinkLedTask();
}



