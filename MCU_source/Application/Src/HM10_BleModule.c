#include "HM10_BleModule.h"
#include "HM_10_BleAppCommands.h"

#include "main.h"
#include "string.h"
#include <stdio.h>
#include "dma.h"
#include "usart.h"
#include "gpio.h"



uint8_t ReceiveBuffer[ReceiveBufferSize]; // Receive from UART Buffer
uint8_t Message[TransmitBufferSize]; // Message to transfer by UART
uint8_t Length; // Message length

void HM10BLE_Init()
{
	 //InitBle Listening
	  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, ReceiveBuffer, ReceiveBufferSize);
}

__inline void HM10Ble_Task()
{

}

void HM10Ble_ExecuteCommand(HM10BleCommand_t HM10BLE_Command)
{
	switch(HM10BLE_Command)
	{
	//General App view
	case DrivingStartCommand :
	{
		int i=0;
		UNUSED(i);
	}
	case DrivingStopCommand:
	{

	}
	/* @@@@@ @@@@ "Basic" Screen in Mobile App */
	case StartPIDScanning:
	case StopPIDScanning:
	case SendActualPidSettings:
	case SetPid_Kp:
	case SetPid_Kd:
	case SetPid_Ki:
	case SetBaseMotorSpeedValue:
		/* @@@@@ @@@@ Commands for Save data to .txt file on Phone */
	case SaveDataVal1:
	case SaveDataVal2:
	case StopSavingData:
	/* @@@@@ @@@@ Sensor Screen in Mobile App */
	case StartSendActualSensorData:
	case StopSendActualSensorData :
	case StopSendActualSensorDataAndSendActualErrorWeights :
	/* Value from mobile App -  Weights of Error for each sensor */
	case SensorErW_1 :
	case SensorErW_2 :
	case SensorErW_3 :
	case SensorErW_4 :
	case SensorErW_5 :
	case SensorErW_6 :
	case SensorErW_7 :
	case SensorErWMax :
	/* Value from mobile App - when the line is detected*/
	case S1_LineIsDetV :
	case S2_LineIsDetV :
	case S3_LineIsDetV :
	case S4_LineIsDetV :
	case S5_LineIsDetV :
	case S6_LineIsDetV :
	case S7_LineIsDetV :
	case S8_LineIsDetV :
	/*@@@@@ @@@@  Mobile App Screen "Adv" */
	case PrintActualDataFor_Adv_ScreenToM_App:
	{

	}
	case MAX_Pid_Value:
	case ReverseSpeed :
	case MaxSumValue_forPidKi :
	case PID_KdProbeTime :
	case Motor1TestStart :
	case Motor1TestStop :
	case Reserv3 :
	case Reserv4 :
	case IrSensor ://?
	case LedMode :
	{
		int i=0;
		UNUSED(i);
	}
	default:
	{
		//error
	}
	}
}


uint8_t GetCommandFromBleMessage(uint16_t RecDataSize)
{
	//dk why 2 :/ (Behavior Mobile App)
	return ReceiveBuffer[RecDataSize-2];
}

void HM10BLE_RxEventCallback(uint16_t RecDataSize)
{
	HM10BleCommand_t HM10BLE_Command = GetCommandFromBleMessage(RecDataSize);
	HM10Ble_ExecuteCommand(HM10BLE_Command);
	UNUSED(HM10BLE_Command);
}

void HM10BLE_TxCmpltEventCallback()
{
//Do Something
}




