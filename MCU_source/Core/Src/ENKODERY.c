/*
 * ENKODERY.c
 *
 *  Created on: Jan 11, 2021
 *      Author: Teodor
 */
#include "ENKODERY.h"
#include "math.h"

float ENK_LEWY=0;
float zENK_LEWY=0;
float ENK_PRAWY=0;
float zENK_PRAWY=0;
float zT_ENK=0;
float zT_ENK_sBLE=0;
int fl_wysl=0;
float Predkosc_L;
float Predkosc_P;
int flaga_ENK=0;
void wykryto_znacznik();
void WYSLIJMAPE_DO_BLE();
void wyznacz_xiy();
void mierzprzebdr();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

if(GPIO_Pin==ENK1_Pin)
{		ENK_PRAWY++;	}
if(GPIO_Pin==ENK2_Pin)
{		ENK_PRAWY++;	}
if(GPIO_Pin==ENK4_Pin)
{			ENK_LEWY++;	}
if(GPIO_Pin==ENK3_Pin)
{			ENK_LEWY++;	}

}

float PREDKOSC_L_W_PROBCE[4000];
float PREDKOSC_P_W_PROBCE[4000];
int nr_probki=0;

float DROGA_L;
float DROGA_P;
float DROGA_L_W_PROBCE[4000];
float DROGA_P_W_PROBCE[4000];
float PR_Srodka[4000];
float DR_SRODKA[4000];

int Dnr_probki=0;
float P_DRSR=0;
float ZN_ENKL=0;
float ZN_ENKP=0;

int D_ZENKL=0;
int D_ZENKP=0;
int wykr_znacznik=0;

float zDR_ENKL=0;
float zDR_ENKP=0;

uint32_t zT_ZNACZNIK=0;
float CZ_OKR=0;
float dlugosctrasy=0;

int mapa_dplik=0;
int zzzap_nrprobki=0;
float Sr_Predkosc=0;

void oblicz_predkosc()
{

	if(t2>zT_ENK+200)
	{
		zT_ENK=t2;

		float Droga_impulsu=0.000788; //czyli tyle mam metra na jeden impuls...



		DROGA_L= ((ENK_LEWY-zENK_LEWY)*Droga_impulsu);
		DROGA_L_W_PROBCE[nr_probki]=DROGA_L;


		DROGA_P= ((ENK_PRAWY-zENK_PRAWY)*Droga_impulsu);
		DROGA_P_W_PROBCE[nr_probki]=DROGA_P;

		Predkosc_L=((ENK_LEWY-zENK_LEWY)*Droga_impulsu)/0.02;
		PREDKOSC_L_W_PROBCE[nr_probki]=Predkosc_L;
		zENK_LEWY=ENK_LEWY;


		Predkosc_P=((ENK_PRAWY-zENK_PRAWY)*Droga_impulsu)/0.02;
		PREDKOSC_P_W_PROBCE[nr_probki]=Predkosc_P;
		zENK_PRAWY=ENK_PRAWY;
		nr_probki++;
		if(nr_probki==4001)
		{
			nr_probki=4000;
		}
	}
}

void mierzprzebdr()
{
	if(zzzap_nrprobki!=nr_probki-1)
	{
		zzzap_nrprobki=nr_probki-1;

	DR_SRODKA[nr_probki-1]=DROGA_L_W_PROBCE[nr_probki-1]+DROGA_P_W_PROBCE[nr_probki-1];
	if(DR_SRODKA[nr_probki-1]!=0)
	{
		DR_SRODKA[nr_probki-1]=DR_SRODKA[nr_probki-1]/2;
	}
	P_DRSR=P_DRSR+DR_SRODKA[nr_probki-1];
	}
}

void wykryj_znacznik()
{
	wykr_znacznik=0;

	if(flaga_ENK==1 && (ENK_LEWY-ZN_ENKL)!=0 )
	{
		ZN_ENKL=ENK_LEWY;
		D_ZENKL++;
	}
	if(flaga_ENK==1 && (ENK_PRAWY-ZN_ENKP)!=0 )
	{
		ZN_ENKP=ENK_PRAWY;
		D_ZENKP++;
	}
	if(D_ZENKL>=25 && D_ZENKP>=25)
	{
		//wykytro znacznik

		D_ZENKP=0;
		D_ZENKL=0;



		wykryto_znacznik();

		if(mapa_dplik==1)
		{
			mapa_dplik=0;
			URUCHAMIANIE_ROBOTA=0; //zatrzymanie robota

		   __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,1000);
		    __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_2,1000);

		    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000);
		    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,1000);

			  HAL_GPIO_WritePin(LDD1_GPIO_Port, LDD1_Pin,GPIO_PIN_SET);
			wyznacz_xiy();
			WYSLIJMAPE_DO_BLE();

			P_DRSR=0;
			nr_probki=0;
			return;
		}

		if(mapa_dplik==0)
		{
			HAL_GPIO_WritePin(LDD1_GPIO_Port, LDD1_Pin,GPIO_PIN_RESET);
			mapa_dplik=1;
			P_DRSR=0;
			nr_probki=0;
		}



	}

	if(flaga_ENK==0) //referebce ti file "CZUJNIKI.c"
	{
		 D_ZENKL=0;
		 D_ZENKP=0;
	}
}




void wykryto_znacznik()
{

	CZ_OKR=t2-zT_ZNACZNIK;
	CZ_OKR=CZ_OKR/10000;
	zT_ZNACZNIK=t2;

	for(int i=0; i<nr_probki; i++)
	{
		PR_Srodka[i]=PREDKOSC_L_W_PROBCE[i]+PREDKOSC_P_W_PROBCE[i];
		if(PR_Srodka[i]!=0)
		{
		PR_Srodka[i]=PR_Srodka[i]/2;
		}
	}


	for (int i=0; i<nr_probki; i++)
	{
		Sr_Predkosc=Sr_Predkosc+PR_Srodka[i];
	}
	Sr_Predkosc=Sr_Predkosc/nr_probki;

}



float X[4000];
float Y[4000];
float T[4000];
void wyznacz_xiy()
{
	for(int i=0;  i<nr_probki; i++)
	{
	T[i]=T[i-1]+(1/0.147)*(DROGA_L_W_PROBCE[i]-DROGA_P_W_PROBCE[i]);


	X[i]=X[i-1]+(  0.5*cos(T[i-1]) * ( DROGA_L_W_PROBCE[i]+DROGA_P_W_PROBCE[i]) );

	Y[i]=Y[i-1]+(  0.5*sin(T[i-1]) * ( DROGA_L_W_PROBCE[i]+DROGA_P_W_PROBCE[i]) );
	}

}


void WYSLIJMAPE_DO_BLE()
{
	char SEND_DATA_IN_FILE[40];

	if(DANE_DO_TEXT)
	{
		Z_Czas_Do_Pliku=HAL_GetTick();


		sprintf(SEND_DATA_IN_FILE,"X,Y,DR_L,DR_P,PR,P\n\r");
		DO_BLE(SEND_DATA_IN_FILE);

		int znr_probki=nr_probki;
		for(int i=0; i<znr_probki; i=i)
		{

		if(Z_Czas_Do_Pliku+30 <  HAL_GetTick() )
			{
			Z_Czas_Do_Pliku=HAL_GetTick();
					i++;


				sprintf(SEND_DATA_IN_FILE,"%f,%f,%f,%f\n\r",X[i],Y[i],DROGA_L_W_PROBCE[i],DROGA_P_W_PROBCE[i] );
				DO_BLE(SEND_DATA_IN_FILE);
			}
		}
	}
	else
	{
		sprintf(SEND_DATA_IN_FILE,"T:%f\n\rVs:%f\n\r,D:%f\n\r",CZ_OKR,Sr_Predkosc, P_DRSR);
					DO_BLE(SEND_DATA_IN_FILE);
	}
}

void pomiardoble(char *dane)
{

}



