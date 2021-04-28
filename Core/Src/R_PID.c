/*
 * R_PID.c
 *
 *  Created on: Sep 17, 2020
 *      Author: Teodor
 */

#include "CZUJNIKI.h"
#include "R_PID.h"
#include "stm32h7xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "EEPROM.h"
#include<stdlib.h>
#include "main.h"
#include "ENKODERY.h"
#include "math.h"

float Kp = 100,Kd = 0,Ki = 0, Kii=0,PID_value=0,KI_SUMA=0,P,Pr_PID_value=0;

float D=0,P=0,I=0,I_SUMA=0,P_ERR_CZ=0; //D rozniczkowo P - Proporcjonalnie , I suma

float MAX_PID=0,SUMA_MAX=0,ZMIENNA3=0,ZMIENNA4=0;

int pr_tyl=0;
int z_npr_s_sil=0;
float rz_IP=0;
float rz_IL=0;



int Pr_Silnika_Prawego=0;
int Pr_Silnika_Lewego=0;
float pr_pocz_silnikow=50;
void EEPROM_ZAAW_READ();
void EEPROM_PID_READ();
void JAZDA_DO_PRZODU();
void PRAWY_DO_TYLU();
void LEWY_DO_TYLU();
void JAZDA_DO_TYLU();
float rz_predkoscfb();


float rz_predkosc(float pr_zadanaL, float pr_zadanaP);

void max_speed();

int CzasProbkowania_CZ_Rozniczkujacego=0;
uint32_t zCzas_PID=0;

float calculatePID()
{

P=ERR_CZ;

uint32_t Cz_Pr_Cz_Rozn=CzasProbkowania_CZ_Rozniczkujacego;
if(Cz_Pr_Cz_Rozn>190)
{
	Cz_Pr_Cz_Rozn=190;
}

if(zCzas_PID + Cz_Pr_Cz_Rozn < HAL_GetTick())
{
D= ERR_CZ - P_ERR_CZ;
P_ERR_CZ=ERR_CZ;
zCzas_PID=HAL_GetTick();

}

PID_value = (Kp * P)+(Kd*D);


#define feedback

#ifdef feedback
rz_predkoscfb();
#else
	Pr_Silnika_Lewego = pr_pocz_silnikow + PID_value;
	Pr_Silnika_Prawego = pr_pocz_silnikow - PID_value;
#endif

max_speed();
return 0;

}



float rz_predkoscfb()
{
	 float pr_zadana=pr_pocz_silnikow;

	 float PR_zP;
	 float PR_zL;

	 	 PR_zL=pr_zadana+PID_value;
	 	 PR_zP=pr_zadana-PID_value;



		 if(PR_zP>Predkosc_P)
		 {
			 float delta_pr=PR_zP-Predkosc_P;
			 PR_zP=PR_zP+(delta_pr);
		 }

		 if(PR_zP<Predkosc_P)
		 {
			 float delta_pr=PR_zP-Predkosc_P;
			 PR_zP=PR_zP+(delta_pr);
		 }




		 if(PR_zL>Predkosc_L)
		 {
			 float delta_pr=PR_zL-Predkosc_L;
			 PR_zL=PR_zL+(delta_pr);
		 }

		 if(PR_zL<Predkosc_L)
		 {
			 float delta_pr=PR_zL-Predkosc_L;
			 PR_zL=PR_zL+(delta_pr);
		 }

			 PR_zP= (220*PR_zP)+50 - (220*PID_value);
			 PR_zL= (220*PR_zL)+50 + (220*PID_value);

 Pr_Silnika_Lewego  = PR_zL;
 Pr_Silnika_Prawego = PR_zP;


return 0;
}

void max_speed()
{
	if(Pr_Silnika_Lewego>1000)
	{
		Pr_Silnika_Lewego=1000;
	}


	//Mniejsza od -1000!!!!!!!!!@@@@@@@@
	if(Pr_Silnika_Lewego<-1000)
	{
		Pr_Silnika_Lewego=-1000;
	}

	if(Pr_Silnika_Prawego>1000)
	{
		Pr_Silnika_Prawego=1000;
	}
	//Mniejsza od -1000!!!!!!!!!@@@@@@@@
	if(Pr_Silnika_Prawego<-1000)
	{
		Pr_Silnika_Prawego=-1000;
	}
}



void JAZDA_DO_PRZODU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{

  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000);//-->> Naprzod
  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000-Pr_Sil_Pr);

  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000);
  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000-Pr_Sil_Lew); //-->> Naprzod

}
void PRAWY_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000-Pr_Sil_Pr);
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000);  //-->> Do tylu


	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000-Pr_Sil_Lew); //-->> Naprzod



}
void LEWY_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000); //-->> Do tylu
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000-Pr_Sil_Pr);


	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000-Pr_Sil_Lew); //-->> Naprzod
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000);



}
void JAZDA_DO_TYLU(int Pr_Sil_Lew, int Pr_Sil_Pr)
{
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000-Pr_Sil_Pr); //-->> Do tylu
	  __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000);

	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000-Pr_Sil_Lew);
	  __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000); //-->> Do tylu

}
void EEPROM_ZAAW_READ()
{
	EEPROM_READ_FLOAT(400, &MAX_PID);
	EEPROM_READ_FLOAT(410, &SUMA_MAX);

	EEPROM_READ_FLOAT(440, &ZMIENNA3); //@@@@@@@@@@@@@@@@@@@@

	EEPROM_READ_FLOAT(445, &ZMIENNA4);

	EEPROM_READ_INT(405, &pr_tyl);
	EEPROM_READ_INT(420, &CzasProbkowania_CZ_Rozniczkujacego);
}
void EEPROM_PID_READ()
{
	EEPROM_READ_FLOAT(50, &Kp);
	EEPROM_READ_FLOAT(55, &Kd);
	EEPROM_READ_FLOAT(60, &pr_pocz_silnikow);
	EEPROM_READ_FLOAT(65, &Ki);
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
