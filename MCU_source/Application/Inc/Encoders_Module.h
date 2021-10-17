#ifndef _Encoders_Module_H
#define _Encoders_Module_H


#include "stdint.h"

#define MaxProbeNumber 4000

typedef struct
{
	uint32_t LeftEncoderImpulsCount;
	uint32_t RightEncoderImpulsCount;

	float Distance_LeftWheel;
	float Distance_RightWheel;

	int ProbeNumber;

	uint32_t PreviousLeftEncoderImpulsCount;
	uint32_t PreviousRightEncoderImpulsCount;

	float LeftWheelDistanceInProbe[MaxProbeNumber];
	float RightWheelDistanceInProbe[MaxProbeNumber];


	float LeftWheelSpeed;
	float RightWheelSpeed;

	float LeftWheelSpeedInProbe[MaxProbeNumber];
	float RightWheelSpeedInProbe[MaxProbeNumber];


	float TakenDistanceInProbe[MaxProbeNumber];
	float TakenDistance;

}Encoders_Module_t ;

extern Encoders_Module_t Enc_Module;

void Enc_ResetModule();
void Enc_AddEncoderImpulsIntoImpulsSum(uint16_t GPIO_Pin);
void Enc_CalculateActualSpeed();
void Enc_CalculateTraveledDistance();

#endif //_Encoders_Module_H
