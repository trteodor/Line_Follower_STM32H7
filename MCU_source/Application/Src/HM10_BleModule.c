#include "HM10_BleModule.h"
#include "HM_10_BleAppCommands.h"

#include "main.h"
#include "string.h"
#include <stdio.h>
#include "dma.h"
#include "usart.h"
#include "gpio.h"

HM10BLE_t HM10BLE_App;

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

	break;
	}
	case DrivingStopCommand:
	{

	break;
	}
	/* @@@@@ @@@@ "Basic" Screen in Mobile App */
	case StartPIDScanning:
	{

	break;
	}
	case StopPIDScanning:
	{

	break;
	}
	case SendActualPidSettings:
	{

	break;
	}
	case SetPid_Kp:
	{

	break;
	}
	case SetPid_Kd:
	{

	break;
	}
	case SetPid_Ki:
	{

	break;
	}
	case SetBaseMotorSpeedValue:
	{

	break;
	}
		/* @@@@@ @@@@ Commands for Save data to .txt file on Phone */
	case SaveDataVal1:
	{

	break;
	}
	case SaveDataVal2:
	{

	break;
	}
	case StopSavingData:
	{

	break;
	}
	/* @@@@@ @@@@ Sensor Screen in Mobile App */
	case StartSendActualSensorData:
	{
		HM10BLE_App.Ble_AppSt=SendActualSensorData;
	break;
	}
	case StopSendActualSensorData :
	{
		HM10BLE_App.Ble_AppSt=Idle;
	break;
	}
	case StopSendActualSensorDataAndSendActualErrorWeights :
	{

	break;
	}
	/* Value from mobile App -  Weights of Error for each sensor */
	case SensorErW_1 :
	{

	break;
	}
	case SensorErW_2 :
	{

	break;
	}
	case SensorErW_3 :
	{

	break;
	}
	case SensorErW_4 :
	{

	break;
	}
	case SensorErW_5 :
	{

	break;
	}
	case SensorErW_6 :
	{

	break;
	}
	case SensorErW_7 :
	{

	break;
	}
	case SensorErWMax :
	{

	break;
	}
	/* Value from mobile App - when the line is detected*/
	case S1_LineIsDetV :
	{

	break;
	}
	case S2_LineIsDetV :
	{

	break;
	}
	case S3_LineIsDetV :
	{

	break;
	}
	case S4_LineIsDetV :
	{

	break;
	}
	case S5_LineIsDetV :
	{

	break;
	}
	case S6_LineIsDetV :
	{

	break;
	}
	case S7_LineIsDetV :
	{

	break;
	}
	case S8_LineIsDetV :
	{

	break;
	}
	/*@@@@@ @@@@  Mobile App Screen "Adv" */
	case PrintActualDataFor_Adv_ScreenToM_App:
	{

	break;
	}
	case MAX_Pid_Value:
	{

	break;
	}
	case ReverseSpeed :
	{

	break;
	}
	case MaxSumValue_forPidKi :
	{

	break;
	}
	case PID_KdProbeTime :
	{

	break;
	}
	case Motor1TestStart :
	{

	break;
	}
	case Motor1TestStop :
	{

	break;
	}
	case Reserv3 :
	{

	break;
	}
	case Reserv4 :
	{

	break;
	}
	case IrSensor ://?
	{

	break;
	}
	case LedMode :
	{
		int i=0;
		UNUSED(i);
	break;
	}
	default:
	{
		//error
	break;
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




