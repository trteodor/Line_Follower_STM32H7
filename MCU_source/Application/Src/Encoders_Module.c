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

void Enc_ResetModule()
{
	//this is rly wrong solution but work! :)
//	static const Encoders_Module_t EmptyStruct;
//	Enc_Module=EmptyStruct;
	//finally better solution:
	Enc_Module.LeftEncoderImpulsCount = 0;
	Enc_Module.RightEncoderImpulsCount = 0;
	Enc_Module.Distance_LeftWheel = 0;
	Enc_Module.Distance_RightWheel = 0;
	Enc_Module.ProbeNumber = 0;
	Enc_Module.PreviousLeftEncoderImpulsCount = 0;
	Enc_Module.PreviousRightEncoderImpulsCount = 0;
	Enc_Module.LeftWheelSpeed = 0;
	Enc_Module.RightWheelSpeed = 0;
	Enc_Module.TakenDistance = 0;
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

static void CalculatAverageSpeed()
{

//
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

}




