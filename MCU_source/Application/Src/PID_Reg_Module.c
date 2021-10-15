
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include <stdlib.h>
#include "math.h"


#include "EEPROM.h"
#include "PID_Reg_Module.h"
#include "LineSensorsModule.h"

PID_RegModule_t PID_Module;
/*Few field of the structure above are also modified by HM10Ble App Module*/

void CheckDoesNotExceedTheMaximumSpeedValue();
float calculatePID();
void EEPROM_PID_Data_Read();

void PID_Init()
{
	EEPROM_PID_Data_Read();
}

void PID_Task()
{
	calculatePID();
	CheckDoesNotExceedTheMaximumSpeedValue();
	//		rz_predkoscfb();
}

float calculatePID()
{
		static uint32_t SavedTime_PID_Reg;
		static float PreviousPositionErrorValue;

		PID_Module.P=SensorModule.PositionErrorValue;

		if(PID_Module.PID_DerivativeTime>MaxPID_DerivativeTime){
			PID_Module.PID_DerivativeTime=200;
		}

		if(SavedTime_PID_Reg + PID_Module.PID_DerivativeTime < HAL_GetTick()){
			PID_Module.D= SensorModule.PositionErrorValue - PreviousPositionErrorValue;
			PreviousPositionErrorValue=SensorModule.PositionErrorValue;
			SavedTime_PID_Reg=HAL_GetTick();

		}
		PID_Module.PID_value = (PID_Module.Kp * PID_Module.P)+(PID_Module.Kd * PID_Module.D);
		PID_Module.CalculatedLeftMotorSpeed = PID_Module.BaseMotorSpeed + PID_Module.PID_value;
		PID_Module.CalculatedRightMotorSpeed = PID_Module.BaseMotorSpeed - PID_Module.PID_value;

	return 0;
}

void CheckDoesNotExceedTheMaximumSpeedValue()
{
	if(PID_Module.CalculatedLeftMotorSpeed>MaxSpeedValue)
	{
		PID_Module.CalculatedLeftMotorSpeed=MaxSpeedValue;
	}


	//Mniejsza od -MaxSpeedValue!!!!!!!!!@@@@@@@@
	if(PID_Module.CalculatedLeftMotorSpeed < -MaxSpeedValue)
	{
		PID_Module.CalculatedLeftMotorSpeed = -MaxSpeedValue;
	}

	if(PID_Module.CalculatedRightMotorSpeed > MaxSpeedValue)
	{
		PID_Module.CalculatedRightMotorSpeed = MaxSpeedValue;
	}
	//Mniejsza od -MaxSpeedValue!!!!!!!!!@@@@@@@@
	if(PID_Module.CalculatedRightMotorSpeed < -MaxSpeedValue)
	{
		PID_Module.CalculatedRightMotorSpeed = -MaxSpeedValue;
	}
}


void EEPROM_PID_Data_Read()
{
	EEPROM_READ_FLOAT(400, &PID_Module.MAX_PID_value);
	EEPROM_READ_FLOAT(410, &PID_Module.Ki_Sum_MaxVal);
	EEPROM_READ_INT(405, &PID_Module.ReverseSpeed);
	EEPROM_READ_INT(420, &PID_Module.PID_DerivativeTime);
	EEPROM_READ_FLOAT(50, &PID_Module.Kp);
	EEPROM_READ_FLOAT(55, &PID_Module.Kd);
	EEPROM_READ_FLOAT(60, &PID_Module.BaseMotorSpeed);
	EEPROM_READ_FLOAT(65, &PID_Module.Ki);
}

