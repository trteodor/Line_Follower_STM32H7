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

Robot_Cntrl_t Robot_Cntrl;
extern PID_RegModule_t PID_Module;


void Decode_PID();
static void LF_Robot_Stop();

RobotState_t LF_Robot_ControlTask()
{


	if(Robot_Cntrl.RobotState == LF_Started)
	{
		PID_Task();
		Decode_PID();

		return LF_Started;
	}
	if(Robot_Cntrl.RobotState == LF_go_Start) //Bluetooth or Ir Rec Can Change the state
	{
		Robot_Cntrl.RobotState = LF_Started;
		LF_Robot_ControlTask(); //Recurention :) frist time ever in my life :o
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

			LEWY_DO_TYLU(Pr_Silnika_Lewego, Pr_Silnika_Prawego);
			return;
		}

	if(Pr_Silnika_Prawego<0)
		{
			Pr_Silnika_Prawego=Pr_Silnika_Prawego*(-1);

			PRAWY_DO_TYLU(Pr_Silnika_Lewego, Pr_Silnika_Prawego);
			return;
		}

	JAZDA_DO_PRZODU(Pr_Silnika_Lewego, Pr_Silnika_Prawego);
}

void JAZDA_DO_PRZODU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{

  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxSpeedValue);//-->> Naprzod
  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxSpeedValue-Pr_Sil_Pr);

  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxSpeedValue);
  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxSpeedValue-Pr_Sil_Lew); //-->> Naprzod

}
void PRAWY_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxSpeedValue-Pr_Sil_Pr);
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxSpeedValue);  //-->> Do tylu


	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxSpeedValue);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxSpeedValue-Pr_Sil_Lew); //-->> Naprzod



}
void LEWY_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxSpeedValue); //-->> Do tylu
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxSpeedValue-Pr_Sil_Pr);


	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxSpeedValue-Pr_Sil_Lew); //-->> Naprzod
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxSpeedValue);



}
void JAZDA_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,MaxSpeedValue-Pr_Sil_Pr); //-->> Do tylu
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,MaxSpeedValue);

	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,MaxSpeedValue-Pr_Sil_Lew);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,MaxSpeedValue); //-->> Do tylu

}

void Motor_PWM_Init()
{
	EEPROM_PID_READ();
	EEPROM_ZAAW_READ();
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
//float X[4000];
//float Y[4000];
//float T[4000];
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



//

//void P_trasaA()
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
//}
//void P_trasaB()
//{
//	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//	if(ZMIENNA3==2) //trasa B
//	{
//	if(P_DRSR>0)
//	{
//		pr_pocz_silnikow=1.5;
//	}
//	if(P_DRSR>0.1)
//	{
//	pr_pocz_silnikow=2.5;
//	}
//
//	if(P_DRSR>0.8)
//	{
//	pr_pocz_silnikow=2.2;
//	}
//	if(P_DRSR>1)
//	{
//	pr_pocz_silnikow=2.5;
//	}
//	if(P_DRSR>1.3)
//	{
//	pr_pocz_silnikow=1.5;
//	}
//	if(P_DRSR>3.1)
//	{
//	pr_pocz_silnikow=2.2;
//	}
//	if(P_DRSR>3.6)
//	{
//	pr_pocz_silnikow=2.3;
//	}
//	if(P_DRSR>3.9)
//	{
//	pr_pocz_silnikow=2.4;
//	}
//	}
//}



//#endif /* SRC_URUCHAMIANIE_C_ */
