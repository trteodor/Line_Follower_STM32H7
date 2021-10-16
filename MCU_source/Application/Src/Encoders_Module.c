/*
 * ENKODERY.c
 *
 *  Created on: Jan 11, 2021
 *      Author: Teodor
 */
#include "Encoders_Module.h"
#include "math.h"
#include "main.h"

Encoders_Module_t Enc_Module;
extern uint32_t  us100Timer;

#define OneImpulsDistance 0.000788


__inline void Enc_AddEncoderImpulsIntoImpulsSum(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==ENK1_Pin || GPIO_Pin==ENK2_Pin){
		Enc_Module.RightEncoderImpulsCount++;
	}

	if(GPIO_Pin==ENK4_Pin || GPIO_Pin==ENK3_Pin){
		Enc_Module.LeftEncoderImpulsCount++;
	}
}

void Enc_CalculateActualSpeed()
{
	static uint32_t EncodersSavedTime;

	if(us100Timer>EncodersSavedTime+200) //(20ms)
	{
		EncodersSavedTime=us100Timer;


		Enc_Module.Distance_LeftWheel=
			((Enc_Module.RightEncoderImpulsCount-Enc_Module.PreviousLeftEncoderImpulsCount)*OneImpulsDistance);
		Enc_Module.LeftWheelDistanceInProbe[Enc_Module.ProbeNumber]=Enc_Module.Distance_LeftWheel;

		Enc_Module.Distance_RightWheel=
			((Enc_Module.RightEncoderImpulsCount-Enc_Module.PreviousRightEncoderImpulsCount)*OneImpulsDistance);
		Enc_Module.RightWheelDistanceInProbe[Enc_Module.ProbeNumber]=Enc_Module.Distance_RightWheel;



		Enc_Module.LeftWheelSpeed=Enc_Module.Distance_LeftWheel/0.02;
		Enc_Module.LeftWheelSpeedInProbe[Enc_Module.ProbeNumber]=Enc_Module.LeftWheelSpeed;

		Enc_Module.RightWheelSpeed=Enc_Module.Distance_RightWheel/0.02;
		Enc_Module.RightWheelDistanceInProbe[Enc_Module.ProbeNumber]=Enc_Module.RightWheelSpeed;

		Enc_Module.PreviousLeftEncoderImpulsCount=Enc_Module.RightEncoderImpulsCount;
		Enc_Module.PreviousRightEncoderImpulsCount=Enc_Module.RightEncoderImpulsCount;
		Enc_Module.ProbeNumber++;

		if(Enc_Module.ProbeNumber > MaxProbeNumber)
		{
			Enc_Module.ProbeNumber=MaxProbeNumber;
		}
	}
}

void Enc_CalculateTraveledDistance()
{
	static uint32_t PreviousProbeNumber;

	if(PreviousProbeNumber != Enc_Module.ProbeNumber-1)
	{
		PreviousProbeNumber=Enc_Module.ProbeNumber-1;

		Enc_Module.TakenDistanceInProbe[Enc_Module.ProbeNumber-1] =
				Enc_Module.LeftWheelDistanceInProbe[Enc_Module.ProbeNumber-1] +
					Enc_Module.RightWheelDistanceInProbe[Enc_Module.ProbeNumber-1];
			if(Enc_Module.TakenDistanceInProbe[Enc_Module.ProbeNumber-1] != 0)
			{
				Enc_Module.TakenDistanceInProbe[Enc_Module.ProbeNumber-1]=Enc_Module.TakenDistanceInProbe[Enc_Module.ProbeNumber-1]/2;
			}
	Enc_Module.TakenDistance=Enc_Module.TakenDistance + Enc_Module.TakenDistanceInProbe[Enc_Module.ProbeNumber-1];
	}
}



//
//void TryDetectLapEndMark()
//{
//	wykr_znacznik=0;
//
//	if(flaga_ENK==1 && (ENK_LEWY-ZN_ENKL)!=0 )
//	{
//		ZN_ENKL=ENK_LEWY;
//		D_ZENKL++;
//	}
//	if(flaga_ENK==1 && (ENK_PRAWY-ZN_ENKP)!=0 )
//	{
//		ZN_ENKP=ENK_PRAWY;
//		D_ZENKP++;
//	}
//	if(D_ZENKL>=25 && D_ZENKP>=25)
//	{
//		//wykytro znacznik
//
//		D_ZENKP=0;
//		D_ZENKL=0;
//
//
//
//		wykryto_znacznik();
//
//		if(mapa_dplik==1)
//		{
//			mapa_dplik=0;
//			URUCHAMIANIE_ROBOTA=0; //zatrzymanie robota
//
//		   __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000);
//		    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000);
//
//		    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000);
//		    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000);
//
//			  HAL_GPIO_WritePin(LDD1_GPIO_Port, LDD1_Pin,GPIO_PIN_SET);
//			wyznacz_xiy();
//			WYSLIJMAPE_DO_BLE();
//
//			P_DRSR=0;
//			nr_probki=0;
//			return;
//		}
//
//		if(mapa_dplik==0)
//		{
//			HAL_GPIO_WritePin(LDD1_GPIO_Port, LDD1_Pin,GPIO_PIN_RESET);
//			mapa_dplik=1;
//			P_DRSR=0;
//			nr_probki=0;
//		}
//	}
//}

//
//
//
//
//void wykryto_znacznik()
//{
//
//	CZ_OKR=t2-zT_ZNACZNIK;
//	CZ_OKR=CZ_OKR/10000;
//	zT_ZNACZNIK=t2;
//
//	for(int i=0; i<nr_probki; i++)
//	{
//		PR_Srodka[i]=PREDKOSC_L_W_PROBCE[i]+PREDKOSC_P_W_PROBCE[i];
//		if(PR_Srodka[i]!=0)
//		{
//		PR_Srodka[i]=PR_Srodka[i]/2;
//		}
//	}
//
//
//	for (int i=0; i<nr_probki; i++)
//	{
//		Sr_Predkosc=Sr_Predkosc+PR_Srodka[i];
//	}
//	Sr_Predkosc=Sr_Predkosc/nr_probki;
//
//}
//
//


