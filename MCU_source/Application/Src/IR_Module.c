#include "main.h"

#include "TSOP2236_T.h"
#include "Robot_Control.h"
#include "IR_Module.h"
#include "EEPROM.h"
#include "EEPROM_VarLocDef.h"

IrModule_t IrModule;

RC5Struct TSOP2236;
uint16_t TSOP_NormRecData;

static void EEPROM_IR_STATE_READ();
static void IR_Decode_RemoteControlPilot();


void IR_ModInit()
{
	EEPROM_IR_STATE_READ();
	RC5_INIT(&TSOP2236);
	//	RC5100usTimer Called from stm32h7xx_it.c file
	//	RC5_IR_EXTI_GPIO_ReceiveAndDecodeFunction Called from stm32h7xx_it.c file
}



void IR_Task()
{
	if(IrModule.Ir_State == Ir_Working)
	{
		if(RC5_ReadNormal(&TSOP2236, &TSOP_NormRecData) == RC5_OK)
			{
				//new data avaible
				IR_Decode_RemoteControlPilot();
			}
	}
}

int znakwylaczdiode=0;


static void IR_Decode_RemoteControlPilot()
{

	if(TSOP_NormRecData==DVD_RobotStart_But)
	{
		Robot_Cntrl.RobotState = LF_go_Start;
	}

	if(TSOP_NormRecData==TV_RobotStop_But)
	{
		Robot_Cntrl.RobotState = LF_go_Stop;
	}
}


static void EEPROM_IR_STATE_READ()
{
	uint32_t tmpIrState;
	EEPROM_READ_INT(EEPROM_IrSensorState_Addr, (int *)&tmpIrState);
	IrModule.Ir_State=tmpIrState;
}
