///*
// * Uruchamianie.c
// *
// *  Created on: Sep 28, 2020
// *      Author: Teodor
// */
//
//#ifndef SRC_URUCHAMIANIE_C_
//#define SRC_URUCHAMIANIE_C_
//#include "Robot_Control.h"
//#include "tim.h"
//
//int T_SIL=0;
//int URUCHAMIANIE_ROBOTA=0;
//
//
//
//void Decode_PID();
//
//void Robot_Control()
//{
//	if(URUCHAMIANIE_ROBOTA)
//	{
//		//Robot start
//		//Poki co to tak tylko dla testow...
//
//		Decode_PID();
//
//	}
//	else
//	{
//		rz_IP=0;
//		rz_IL=0;
//
//		//Robot off
//	    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000);
//	    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000);
//
//	    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000);
//	    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000);
//	}
//}
//
//
//void Decode_PID()
//{
//	if(Pr_Silnika_Lewego<0)
//		{
//			Pr_Silnika_Lewego=Pr_Silnika_Lewego*(-1);
//
//			LEWY_DO_TYLU(Pr_Silnika_Lewego, Pr_Silnika_Prawego);
//			return;
//		}
//
//	if(Pr_Silnika_Prawego<0)
//		{
//			Pr_Silnika_Prawego=Pr_Silnika_Prawego*(-1);
//
//			PRAWY_DO_TYLU(Pr_Silnika_Lewego, Pr_Silnika_Prawego);
//			return;
//		}
//
//	JAZDA_DO_PRZODU(Pr_Silnika_Lewego, Pr_Silnika_Prawego);
//}
//
//#endif /* SRC_URUCHAMIANIE_C_ */
