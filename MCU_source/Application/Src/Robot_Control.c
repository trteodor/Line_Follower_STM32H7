/*
 * Uruchamianie.c
 *
 *  Created on: Sep 28, 2020
 *      Author: Teodor
 */

#include "main.h"
#include "tim.h"

#include "Robot_Control.h"
#include "PID_Reg_Module.h"
#include "Encoders_Module.h"

Robot_Cntrl_t Robot_Cntrl;
extern PID_RegModule_t PID_Module;


void Decode_PID();
static void LF_Robot_Stop();
static void Motor_PWM_Init();
static void ForwardDriving(int LeftMotorSpeed, int RightMotorSpeed);
static void RightMotorDrivingReverse(int LeftMotorSpeed, int RightMotorSpeed);
static void LeftMotorDrivingReverse(int LeftMotorSpeed, int RightMotorSpeed);

void LF_Robot_ControlInit()
{
	Motor_PWM_Init();
}

struct
{
	float X[MaxProbeNumber];
	float Y[MaxProbeNumber];
	float T[MaxProbeNumber];
}PositionOnTrack;

RobotState_t LF_Robot_ControlTask()
{
	if(Robot_Cntrl.RobotState == LF_Started)
	{
		Decode_PID();
		return LF_Started;
	}
	if(Robot_Cntrl.RobotState == LF_go_Start) //Bluetooth or Ir Rec Can Change the state
	{
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

void LF_Robot_Stop()
{
	//Robot off
    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000);
    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000);

    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000);
    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000);
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


//
//void wyznacz_xiy()
//{
//	for(int i=0;  i<nr_probki; i++)
//	{
//	T[i]=T[i-1]+(1/0.147)*(DROGA_L_W_PROBCE[i]-DROGA_P_W_PROBCE[i]);
//
//
//	X[i]=X[i-1]+(  0.5*cos(T[i-1]) * ( DROGA_L_W_PROBCE[i]+DROGA_P_W_PROBCE[i]) );
//
//	Y[i]=Y[i-1]+(  0.5*sin(T[i-1]) * ( DROGA_L_W_PROBCE[i]+DROGA_P_W_PROBCE[i]) );
//	}
//
//}
//
//
//void WYSLIJMAPE_DO_BLE()
//{
//	char SEND_DATA_IN_FILE[40];
//
//	if(DANE_DO_TEXT)
//	{
//		Z_Czas_Do_Pliku=HAL_GetTick();
//
//
//		sprintf(SEND_DATA_IN_FILE,"X,Y,DR_L,DR_P,PR,P\n\r");
//		DO_BLE(SEND_DATA_IN_FILE);
//
//		int znr_probki=nr_probki;
//		for(int i=0; i<znr_probki; i=i)
//		{
//
//		if(Z_Czas_Do_Pliku+30 <  HAL_GetTick() )
//			{
//			Z_Czas_Do_Pliku=HAL_GetTick();
//					i++;
//
//
//				sprintf(SEND_DATA_IN_FILE,"%f,%f,%f,%f\n\r",X[i],Y[i],DROGA_L_W_PROBCE[i],DROGA_P_W_PROBCE[i] );
//				DO_BLE(SEND_DATA_IN_FILE);
//			}
//		}
//	}
//	else
//	{
//		sprintf(SEND_DATA_IN_FILE,"T:%f\n\rVs:%f\n\r,D:%f\n\r",CZ_OKR,Sr_Predkosc, P_DRSR);
//					DO_BLE(SEND_DATA_IN_FILE);
//	}
//}


//void Speed_ProfileFunction()
//{
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
//	}


//#endif /* SRC_URUCHAMIANIE_C_ */
