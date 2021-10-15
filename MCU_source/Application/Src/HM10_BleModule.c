#include "HM10_BleModule.h"
#include "HM_10_BleAppCommands.h"

#include "main.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "dma.h"
#include "usart.h"
#include "gpio.h"

#include "LineSensorsModule.h"
#include "PID_Reg_Module.h"
#include "ftoa_function.h"

#include "EEPROM.h"
#include "EEPROM_VarLocDef.h"

#define TimeBeetweenNextDataPart 15

HM10BLE_t HM10BLE_App;


static void HM10BLE_Tx(uint8_t *pData, uint16_t Size);
static Ble_AppStatus SendActualLineSensorDataFun();
static Ble_AppStatus SendActualErrorWeightsAndWhenLineIsDetectedFun();
static Ble_AppStatus SendActualPID_AndCalcMotor_DataFun();
static Ble_AppStatus SendActualPidSettingsFun();
static Ble_AppStatus SendActualDataFor_Adv_ScreenToM_AppFun();

void HM10BLE_Init()
{
	 //InitBle Listening
	  HAL_UARTEx_ReceiveToIdle_DMA(&huart2, HM10BLE_App.ReceiveBuffer, ReceiveBufferSize);
}

void HM10Ble_Task()
{
	if(HM10BLE_App.ActualStateCallBack != NULL  && HM10BLE_App.Ble_AppSt != Idle)
	{
		if(HM10BLE_App.ActualStateCallBack() != BLE_OK)
		{
			//for example change state
			HM10BLE_App.ActualStateCallBack = NULL;
			HM10BLE_App.Ble_AppSt=Idle;
			return;
		}
	}
}

void HM10Ble_ExecuteCommand(HM10BleCommand_t HM10BLE_Command)
{
	switch(HM10BLE_Command)
	{
	//General App view
	case DrivingStartCommand :
	{
			//
	break;
	}
	case DrivingStopCommand:
	{
			//
	break;
	}
	/* @@@@@ @@@@ "Basic" Screen in Mobile App */
	case StartSendActualPID_AndCalcMotor_Data:
	{
		HM10BLE_App.Ble_AppSt=ContinuousCyclicSendingData;
		HM10BLE_App.ActualStateCallBack = SendActualPID_AndCalcMotor_DataFun;
	break;
	}
	case StopSendActualPID_AndCalcMotor_Data:
	{
		HM10BLE_App.Ble_AppSt=Idle;
	break;
	}
	case SendActualPidSettings:
	{
		HM10BLE_App.Ble_AppSt = SendingDataToMobAppOneTime;
		HM10BLE_App.ActualStateCallBack = SendActualPidSettingsFun;
	break;
	}
	case SetPid_Kp:
	{
		PID_Module.Kp = atof((char *)HM10BLE_App.ReceiveBuffer);
		EEPROM_WRITE_FLOAT(EEPROM_Addr_PID_Kp,&PID_Module.Kp);
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
		HM10BLE_App.Ble_AppSt=ContinuousCyclicSendingData;
		HM10BLE_App.ActualStateCallBack = SendActualLineSensorDataFun;
	break;
	}
	case StopSendActualSensorData :
	{
		HM10BLE_App.Ble_AppSt=Idle;
	break;
	}
	case StopSendActualSensorDataAndSendActualErrorWeights :
	{
		HM10BLE_App.Ble_AppSt = SendingDataToMobAppOneTime;
		HM10BLE_App.ActualStateCallBack = SendActualErrorWeightsAndWhenLineIsDetectedFun;
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
		HM10BLE_App.Ble_AppSt = SendingDataToMobAppOneTime;
		HM10BLE_App.ActualStateCallBack = SendActualDataFor_Adv_ScreenToM_AppFun;
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

static Ble_AppStatus SendActualDataFor_Adv_ScreenToM_AppFun()
{
	static int DataToSendQueue=1;
	static uint32_t SaveTime_BLE;
	static char BuffToBLE[20];
	static char after_con_val[20];
	if(HM10BLE_App.BleTxState==BLE_TX_Busy)
	{
		return BLE_OK; //wait for ready
	}
	if ( HAL_GetTick() - SaveTime_BLE >= TimeBeetweenNextDataPart)
	{
		SaveTime_BLE = HAL_GetTick();

		 for (int i=0; i<20; i++)
		 {
			 BuffToBLE[i]=0;
			 after_con_val[i]=0;
		 }


		  if (DataToSendQueue==1){
		  ftoa(PID_Module.MAX_PID_value,after_con_val ,2);
		  strcat(after_con_val, MAX_Pid_Value_d);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==2){
		  ftoa(PID_Module.ReverseSpeed,after_con_val ,2);
		  strcat(after_con_val, ReverseSpeed_d);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==3){
		  ftoa(PID_Module.Ki_Sum_MaxVal,after_con_val ,2);
		  strcat(after_con_val, MaxSumValue_forPidKi_d);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==4){
		  ftoa(PID_Module.PID_DerivativeTime,after_con_val ,2);
		  strcat(after_con_val, PID_KdProbeTime_dd);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==5){
//		  ftoa(  ,after_con_val ,2);
//		  strcat(after_con_val, Motor1TestStart_d);
//		  strcat(BuffToBLE,after_con_val );
//		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==6){
//		  ftoa(  ,after_con_val ,2);
//		  strcat(after_con_val, Motor1TestStop_d);
//		  strcat(BuffToBLE,after_con_val );
//		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==7){
//		  ftoa(  ,after_con_val ,2);
//		  strcat(after_con_val, Reserv3_d);
//		  strcat(BuffToBLE,after_con_val );
//		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==8){
//		  ftoa(  ,after_con_val ,2);
//		  strcat(after_con_val, Reserv4_d);
//		  strcat(BuffToBLE,after_con_val );
//		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==9){
//		  ftoa(  ,after_con_val ,2);
//		  strcat(after_con_val, IrSensor_d);
//		  strcat(BuffToBLE,after_con_val );
//		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==10){
//		  ftoa(  ,after_con_val ,2);
//		  strcat(after_con_val, LedMode_d);
//		  strcat(BuffToBLE,after_con_val );
//		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue=1;
		  return GoToIdle;
		  }
	}
	return BLE_OK;
}

static Ble_AppStatus SendActualPidSettingsFun()
{
	static int DataToSendQueue=1;
	static uint32_t SaveTime_BLE;
	static char BuffToBLE[20];
	static char after_con_val[20];
	if(HM10BLE_App.BleTxState==BLE_TX_Busy)
	{
		return BLE_OK; //wait for ready
	}
	if ( HAL_GetTick() - SaveTime_BLE >= TimeBeetweenNextDataPart)
	{
		SaveTime_BLE = HAL_GetTick();

		 for (int i=0; i<20; i++)
		 {
			 BuffToBLE[i]=0;
			 after_con_val[i]=0;
		 }


		  if (DataToSendQueue==1){
		  ftoa(PID_Module.Kp,after_con_val ,2);
		  strcat(after_con_val, PID_KpComm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==2){
		  ftoa(PID_Module.Kd,after_con_val ,2);
		  strcat(after_con_val, PID_KdComm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==3){
		  ftoa(PID_Module.BaseMotorSpeed,after_con_val ,2);
		  strcat(after_con_val, BaseMotorSpeed_d);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==4){
		  ftoa(PID_Module.PID_DerivativeTime,after_con_val ,2);
		  strcat(after_con_val, PID_KdProbeTime_d);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue=1; //reset function
		  return GoToIdle;
		  }
	}
	 return BLE_OK;
}

static Ble_AppStatus SendActualPID_AndCalcMotor_DataFun()
{
	static int DataToSendQueue=1;
	static uint32_t SaveTime_BLE;
	static char BuffToBLE[20];
	static char after_con_val[20];
	if(HM10BLE_App.BleTxState==BLE_TX_Busy)
	{
		return BLE_OK; //wait for ready
	}
	if ( HAL_GetTick() - SaveTime_BLE >= TimeBeetweenNextDataPart)
	{
		SaveTime_BLE = HAL_GetTick();

		 for (int i=0; i<20; i++)
		 {
			 BuffToBLE[i]=0;
			 after_con_val[i]=0;
		 }


		  if (DataToSendQueue==1){
		  ftoa(PID_Module.PID_value,after_con_val ,2);
		  strcat(after_con_val, PID_ActualValue);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==2){
		  ftoa(PID_Module.CalculatedLeftMotorSpeed,after_con_val ,2);
		  strcat(after_con_val, LeftMotorSpeed);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==3){
		  ftoa(PID_Module.CalculatedRightMotorSpeed,after_con_val ,2);
		  strcat(after_con_val, RightMotorSpeed);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==4){
		  ftoa(SensorModule.PositionErrorValue,after_con_val ,2);
		  strcat(after_con_val, ActualPositionError);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==5){
		  ftoa(PID_Module.Ki_Sum,after_con_val ,2);
		  strcat(after_con_val, PID_Ki_Sum);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue=1; //Reset Function
		  return BLE_OK;
		  }
	}
	return BLE_OK;
}

static Ble_AppStatus SendActualErrorWeightsAndWhenLineIsDetectedFun()
{
	static int DataToSendQueue=1;
	static uint32_t SaveTime_BLE;
	static char BuffToBLE[20];
	static char after_con_val[20];
	if(HM10BLE_App.BleTxState==BLE_TX_Busy)
	{
		return BLE_OK; //wait for ready
	}
	if ( HAL_GetTick() - SaveTime_BLE >= TimeBeetweenNextDataPart)
	{
		SaveTime_BLE = HAL_GetTick();

		 for (int i=0; i<20; i++)
		 {
			 BuffToBLE[i]=0;
			 after_con_val[i]=0;
		 }


		  if (DataToSendQueue==1){
		  ftoa(SensorModule.SensorErrorValue[0],after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_1);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==2){
		  ftoa(SensorModule.SensorErrorValue[1],after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_2);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==3){
		  ftoa(SensorModule.SensorErrorValue[2],after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_3);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==4){
		  ftoa(SensorModule.SensorErrorValue[3],after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_4);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==5){
		  ftoa(SensorModule.SensorErrorValue[4],after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_5);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==6){
		  ftoa(SensorModule.SensorErrorValue[5],after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_6);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==7){
		  ftoa(SensorModule.SensorErrorValue[6],after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_7);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==8){
		  ftoa(SensorModule.SensorErrorMaxValue,after_con_val ,2);
		  strcat(after_con_val, S_LineErWToM_App_Max);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==9){
		  itoa(SensorModule.LineDetectValue[0],after_con_val ,10);
		  strcat(after_con_val, S_Line_1_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==10){
		  itoa(SensorModule.LineDetectValue[1],after_con_val ,10);
		  strcat(after_con_val, S_Line_2_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==11){
		  itoa(SensorModule.LineDetectValue[2],after_con_val ,10);
		  strcat(after_con_val, S_Line_3_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==12){
		  itoa(SensorModule.LineDetectValue[3],after_con_val ,10);
		  strcat(after_con_val, S_Line_4_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==13){
		  itoa(SensorModule.LineDetectValue[4],after_con_val ,10);
		  strcat(after_con_val, S_Line_5_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==14){
		  itoa(SensorModule.LineDetectValue[5],after_con_val ,10);
		  strcat(after_con_val, S_Line_6_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==15){
		  itoa(SensorModule.LineDetectValue[6],after_con_val ,10);
		  strcat(after_con_val, S_Line_7_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
		  }
		  if (DataToSendQueue==16){
		  itoa(SensorModule.LineDetectValue[7],after_con_val ,10);
		  strcat(after_con_val, S_Line_8_DetectValueToMobileAPP);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue=1; //Reset function
		  return GoToIdle; //Transmision End
		  }
	}
	return BLE_OK;
}

static Ble_AppStatus SendActualLineSensorDataFun()
{
	static int DataToSendQueue=1;
	static uint32_t SaveTime_BLE;
	static char BuffToBLE[20];
	static char after_con_val[20];

	if(HM10BLE_App.BleTxState==BLE_TX_Busy)
	{
		return BLE_OK; //wait for ready
	}


	if ( HAL_GetTick() - SaveTime_BLE >= TimeBeetweenNextDataPart)
	{
		SaveTime_BLE = HAL_GetTick();

		 for (int i=0; i<20; i++)
		 {
			 BuffToBLE[i]=0;
			 after_con_val[i]=0;
		 }

	  if(DataToSendQueue==1){
		  itoa(SensorModule.SensorADCValues[0],after_con_val,10);
		  strcat(BuffToBLE, S_Line_1_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==2){
		  itoa(SensorModule.SensorADCValues[1],after_con_val,10);
		  strcat(BuffToBLE, S_Line_2_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==3){
		  itoa(SensorModule.SensorADCValues[2],after_con_val,10);
		  strcat(BuffToBLE, S_Line_3_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==4){
		  itoa(SensorModule.SensorADCValues[3],after_con_val,10);
		  strcat(BuffToBLE, S_Line_4_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==5){
		  itoa(SensorModule.SensorADCValues[4],after_con_val,10);
		  strcat(BuffToBLE, S_Line_5_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==6){
		  itoa(SensorModule.SensorADCValues[5],after_con_val,10);
		  strcat(BuffToBLE, S_Line_6_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==7){
		  itoa(SensorModule.SensorADCValues[6],after_con_val,10);
		  strcat(BuffToBLE, S_Line_7_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==8){
		  itoa(SensorModule.SensorADCValues[7],after_con_val,10);
		  strcat(BuffToBLE, S_Line_8_Data_ToM_App_Comm);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue++;
		  return BLE_OK;
	  }
	  if(DataToSendQueue==9){
		  ftoa(SensorModule.PositionErrorValue,after_con_val ,2);
		  strcat(BuffToBLE, ActualPositionError_SS);
		  strcat(BuffToBLE,after_con_val );
		  HM10BLE_App.BleTxState=BLE_TX_Busy;
		  HM10BLE_Tx((uint8_t *)BuffToBLE, sizeof(BuffToBLE));
		  DataToSendQueue=1; //ResetFunction
		  return BLE_OK;
	  }
	}
	return BLE_OK;
}

static uint8_t GetCommandFromBleMessage(uint16_t RecDataSize)
{
	//dk why 2 :/ (Behavior Mobile App)
	return HM10BLE_App.ReceiveBuffer[RecDataSize-2];
}

static void PrepareBleAppModuleToNewCommand()
{
	HM10BLE_App.Ble_AppSt = Idle;
	HM10BLE_App.ActualStateCallBack = NULL;
}

void HM10BLE_RxEventCallback(uint16_t RecDataSize)
{
	PrepareBleAppModuleToNewCommand();
	HM10BleCommand_t HM10BLE_Command = GetCommandFromBleMessage(RecDataSize);
	HM10Ble_ExecuteCommand(HM10BLE_Command);

}

void HM10BLE_TxCmpltEventCallback()
{
//Do Something
	HM10BLE_App.BleTxState=BLE_TX_Ready;
}

void HM10BLE_Tx(uint8_t *pData, uint16_t Size)
{
	HAL_UART_Transmit_DMA(&huart2, pData, Size);
//	HAL_Delay(10);
}


