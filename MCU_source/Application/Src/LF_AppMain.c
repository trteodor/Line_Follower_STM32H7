#include "main.h"
#include "tim.h"
#include "string.h"
#include <stdio.h>
#include "dma.h"
#include "usart.h"
#include "gpio.h"

#include "LF_AppMain.h"
#include "TSOP2236_T.h"
#include "PID_Reg_Module.h"
#include "HM10_BleModule.h"
#include "EEPROM.h"
#include "IR_Module.h"
#include "BlinkLedMod.h"
#include "Encoders_Module.h"
#include "LineSensorsModule.h"



Robot_Cntrl_t Robot_Cntrl;
extern PID_RegModule_t PID_Module;

struct
{
	float X[MaxProbeNumber];
	float Y[MaxProbeNumber];
	float T[MaxProbeNumber];
}PositionOnTrack;

static void Decode_PID();
static void LF_Robot_Stop();
static void Motor_PWM_Init();
static void ForwardDriving(int LeftMotorSpeed, int RightMotorSpeed);
static void RightMotorDrivingReverse(int LeftMotorSpeed, int RightMotorSpeed);
static void LeftMotorDrivingReverse(int LeftMotorSpeed, int RightMotorSpeed);
static void TryDetectLapEndMark();
static void LF_Robot_ControlInit();
static RobotState_t LF_Robot_ControlTask();


void LF_App_MainConfig(void)
{
	EEPROM_WriteEnable();
	BlinkLedInit();
	HM10BLE_Init();
	IR_ModInit();
	SM_SensorModuleInit();
	PID_Init();

	//Functions definded in this file
	LF_Robot_ControlInit();
}

void LF_App_MainTask(void) //only one Task without any RTOS, all works fine -- for now the solution is inaf :)
{
	HM10Ble_Task();
	IR_Task();
	PID_Task();
	BlinkLedTask();


	//Functions definded in this file
	LF_Robot_ControlTask();
	TryDetectLapEndMark(); //for test
}


static void LF_Robot_ControlInit()
{
	Motor_PWM_Init();
}

static RobotState_t LF_Robot_ControlTask()
{
	if(Robot_Cntrl.RobotState == LF_Started) //Bluetooth or Ir Rec Can Change the state
	{
		Decode_PID();
		return LF_Started;
	}
	if(Robot_Cntrl.RobotState == LF_go_Start) //Bluetooth or Ir Rec Can Change the state
	{
		Enc_ResetModule(); //reset Encoder module to zero (all struct fields to zero)
		Robot_Cntrl.RobotState = LF_Started;
		LF_Robot_ControlTask(); //Recurention!!! :) :oo I used it :D
	}
	if(Robot_Cntrl.RobotState == LF_go_Stop)
	{
		Robot_Cntrl.RobotState = LF_Idle;
		LF_Robot_Stop();
	}
return LF_Idle;
}


static void LF_Robot_Stop()
{
    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxPWMValue);
    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxPWMValue);

    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxPWMValue);
    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxPWMValue);
}

static void TryDetectLapEndMark()
{

	int CountSensorLineDetected=0;

	static float PreviousDistance_LeftWheel;
	static float PreviousDistance_RightWheel;

	static uint16_t DistanceTakenInLineDetectStateByLeftWheel;
	static uint16_t DistanceTakenInLineDetectStateByRightWheel;

		//Sensor from 2 to 6 if is line detected...
	for(int i=2; i<6; i++)
	{
		if ( SensorModule.SensorADCValues[i] > LineIsDetectedDefValue )
		{
			CountSensorLineDetected++;
		}
		if(CountSensorLineDetected >=4)
		{
			SensorModule.PositionErrorValue=0;
		}
	}

	if(CountSensorLineDetected < 4)
	{
		DistanceTakenInLineDetectStateByRightWheel=0;
		DistanceTakenInLineDetectStateByLeftWheel=0;

		return; //@@@@@@@@@@//break, end mark not detected!1
	}


	if( CountSensorLineDetected >=4 && (Enc_Module.Distance_LeftWheel-PreviousDistance_LeftWheel) !=0 )
	{
		PreviousDistance_LeftWheel=Enc_Module.Distance_LeftWheel;
		DistanceTakenInLineDetectStateByLeftWheel++;
	}
	if( CountSensorLineDetected >=4 && (Enc_Module.Distance_RightWheel - PreviousDistance_RightWheel) !=0 )
	{
		PreviousDistance_RightWheel=Enc_Module.Distance_RightWheel;
		DistanceTakenInLineDetectStateByRightWheel++;
	}


	if(DistanceTakenInLineDetectStateByRightWheel>=CountStatesWhenLineBy4SenDetToEndLapMark
			&& DistanceTakenInLineDetectStateByLeftWheel>=CountStatesWhenLineBy4SenDetToEndLapMark)
	{
		//End Line Mark Detected

		DistanceTakenInLineDetectStateByRightWheel=0;
		DistanceTakenInLineDetectStateByLeftWheel=0;


		HAL_GPIO_TogglePin(LDD1_GPIO_Port, LDD1_Pin); //now only for tests, does it work correctly?


//		if(mapa_dplik==1)
//		{
//			//		LapEndMarkDetected();
//
//			mapa_dplik=0;
//
//			Robot_Cntrl.RobotState = LF_Idle;
//			LF_Robot_Stop();
//
//			  HAL_GPIO_WritePin(LDD1_GPIO_Port, LDD1_Pin,GPIO_PIN_SET);
//			wyznacz_xiy();
//			WYSLIJMAPE_DO_BLE();
//
//			P_DRSR=0;
//			nr_probki=0;
//			return;
//		}

	}
}





//static void LapEndMarkDetected()
//{
//
////	CZ_OKR=t2-zT_ZNACZNIK;
////	CZ_OKR=CZ_OKR/10000;
////	zT_ZNACZNIK=t2;
////
////	for(int i=0; i<nr_probki; i++)
////	{
////		PR_Srodka[i]=PREDKOSC_L_W_PROBCE[i]+PREDKOSC_P_W_PROBCE[i];
////		if(PR_Srodka[i]!=0)
////		{
////		PR_Srodka[i]=PR_Srodka[i]/2;
////		}
////	}
////
////
////	for (int i=0; i<nr_probki; i++)
////	{
////		Sr_Predkosc=Sr_Predkosc+PR_Srodka[i];
////	}
////	Sr_Predkosc=Sr_Predkosc/nr_probki;
//
//}

void Speed_ProfileFunction()
{
//	if(ZMIENNA3==1) //trasa A
//	{
//	if(P_DRSR>0)
//	{
//		pr_pocz_silnikow=2.0;
//	}
//
//	if(P_DRSR>0.2)
//	{
//	pr_pocz_silnikow=1.7;
//	}
//	if(P_DRSR>1.1)
//	{
//	pr_pocz_silnikow=2.2;
//	}
//	if(P_DRSR>2.3)
//	{
//	pr_pocz_silnikow=1.7;
//	}
//	if(P_DRSR>3.8)
//	{
//	pr_pocz_silnikow=2.0;
//	}
}


void Create_XY_PositionMap()
{
	for(int i=0;  i<Enc_Module.ProbeNumber; i++)
	{
		PositionOnTrack.T[i]=PositionOnTrack.T[i-1] + (1/0.147)
				*(Enc_Module.LeftWheelDistanceInProbe[i] - Enc_Module.RightWheelDistanceInProbe[i]);


		PositionOnTrack.X[i]=PositionOnTrack.X[i-1]+(  0.5*cos(PositionOnTrack.T[i-1]) *
				( Enc_Module.LeftWheelDistanceInProbe[i]+Enc_Module.RightWheelDistanceInProbe[i]) );

		PositionOnTrack.Y[i]=PositionOnTrack.Y[i-1]+(  0.5*sin(PositionOnTrack.T[i-1]) *
				( Enc_Module.LeftWheelDistanceInProbe[i]+Enc_Module.RightWheelDistanceInProbe[i]) );
	}
}


void SendCratedTrackMapToMobileApp()
{
	uint8_t SEND_DATA_IN_FILE[40];

	if(0) //another parts of the App must be defided to use it! :)
	{
		static uint32_t  SavedTimeToFile=0;


		sprintf((char *) SEND_DATA_IN_FILE,"X,Y,D_LM,D_RM\n\r");
		 HM10BLE_Tx(SEND_DATA_IN_FILE, sizeof(SEND_DATA_IN_FILE));

		for(int i=0; i<Enc_Module.ProbeNumber; i=i) //BLOCKING SENDING DATA!!!!
		{

		if(SavedTimeToFile+30 <  HAL_GetTick() )
			{
			SavedTimeToFile=HAL_GetTick();
					i++;

				sprintf((char *) SEND_DATA_IN_FILE,"%f,%f,%f,%f\n\r",PositionOnTrack.X[i],PositionOnTrack.Y[i],
							Enc_Module.LeftWheelDistanceInProbe[i],Enc_Module.RightWheelDistanceInProbe[i] );
				 HM10BLE_Tx(SEND_DATA_IN_FILE, sizeof(SEND_DATA_IN_FILE));
			}
		}
	}
}


void Decode_PID()
{
	if(PID_Module.CalculatedLeftMotorSpeed<0)
		{

			int _CalculatedLeftMotorSpeed=PID_Module.CalculatedLeftMotorSpeed*(-1);

			LeftMotorDrivingReverse(_CalculatedLeftMotorSpeed, PID_Module.CalculatedRightMotorSpeed);
			return;
		}
	if(PID_Module.CalculatedRightMotorSpeed < 0)
		{
		int _CalculatedRightMotorSpeed=PID_Module.CalculatedRightMotorSpeed*(-1);

			RightMotorDrivingReverse(PID_Module.CalculatedLeftMotorSpeed, _CalculatedRightMotorSpeed);

			return;
		}

	ForwardDriving(PID_Module.CalculatedLeftMotorSpeed, PID_Module.CalculatedRightMotorSpeed);
	return;
}



static void ForwardDriving(int LeftMotorSpeed, int RightMotorSpeed)
{

  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxPWMValue);//-->> Forward
  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxPWMValue - RightMotorSpeed);

  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxPWMValue);
  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxPWMValue - LeftMotorSpeed); //-->> Forward

}

static void RightMotorDrivingReverse(int LeftMotorSpeed, int RightMotorSpeed)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxPWMValue - RightMotorSpeed);
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxPWMValue);  //-->> Reverse tylu
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxPWMValue);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxPWMValue - LeftMotorSpeed); //-->> Forward
}
static void LeftMotorDrivingReverse(int LeftMotorSpeed, int RightMotorSpeed)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxPWMValue); //-->> Forward
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxPWMValue - RightMotorSpeed);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxPWMValue - LeftMotorSpeed); //-->> Reverse
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxPWMValue);
}

void Motor_PWM_Init()
{
    HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);

    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,0);
    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,0);

    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);
    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);
}




