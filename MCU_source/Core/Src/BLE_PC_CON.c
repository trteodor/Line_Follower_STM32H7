//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//#define SEND_DATA_TO_PC // To on echo data uncomment this line
						//to off echo between BLE and PC comment this
						//called in interrupt from timer
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//Ostatecznie at+baud8 daje 115200kBits.s w dokumentacji at+baud4 to 115200 gdzie w rzeczywistosci sie okazuje 9600
//bledy bledy bledy wszedzie bledy ehh

//at+baud1 - 1200

//at baud4 - 9600

//at+baud6 38400
//at+baud7 57600
//at+baud8 - 115200
//niestety 230kbits/s nie da rady


#include <BLE_PC_CON.h>
#include "stm32h7xx_hal.h"
#include "usart.h"
#include <stdio.h>
#include "tim.h"
#include "Komendy_BLE.h"

uint8_t Received;
uint8_t REC_DANE_PC[30];
uint8_t DANE_PCE[30]; //<< W tym Buforze Otrzymane Dane z PC
uint8_t ToSendAPP[30];

int znacznik=0;
int znacznik2=0;


uint8_t size_BLE=0;
uint8_t size_PC=0;

unsigned long Aktualnyczas=0;
unsigned long ZapamientanyCzas=0;

char REC_D_BLE[30];
char DANE_BLE[30]; // << W tym Buforze Otrzymane Dane z BLE

int znacznik3=0;
int znacznik4=0;
unsigned long ZapamientanyCzas3=0;
uint32_t ZapamientanyCzasTR=0;

uint8_t DL_NAPISU_BLE=0;


uint8_t DOWYSLANIA[80];
uint8_t DOWYSLANIA2[80];

uint8_t Recivedd[10];

uint8_t Data[40] = {0};  // Tablica przechowujaca wysylana wiadomosc.
uint16_t sizee = 0; // Rozmiar wysylanej wiadomosci

uint32_t t5=0;

/*
 * Initialize the Timer 4 to Call the CallBack after evry 500ms elapsed
 * Turn on the interuppt in main
 *  HAL_TIM_Base_Start_IT(&htim4);
 *  If you want other remeber to change some variables in function below
 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

if(htim->Instance == TIM5)
{

	if(t5>=50) //inkrement co 10ms 14i29min
	{
		t5=0;
		PC_BLE_TRANSMIT();	//Komunikacja pod komendy at aktywna gdy zdefiniuje SEND_DATA_TO_PC tak naprawde
	}

  	DOPAMIECI();
	DOPAMIECI2();

	t5++;

}

}

void BLE_INIT()
{
	 HAL_TIM_Base_Start_IT(&htim5);

	  HAL_UART_Receive_IT(&huart2,&Received,1);
	  HAL_UART_Receive_IT(&huart5,&Received,1);
}


int __io_putchar(int ch)
{

	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 1);
	//ITM_SendChar(ch);
			return ch;
}


/*
 * Initialize the UART1 - 115200 and UART3 115200
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart->Instance== USART2)
	{

		HAL_UART_Receive_IT(&huart2, &Received, 1); // Ponowne wlaczenie nasluchiwania
		BUFOR2();

	}


		if(huart->Instance== UART5)
	{
		HAL_UART_Receive_IT(&huart5, &Received, 1); // Ponowne wlaczenie nasluchiwania
	BUFOR();
	}
}

void BUFOR()

{
	REC_DANE_PC[znacznik]=Received;
	znacznik++;

	ZapamientanyCzas=HAL_GetTick();
	znacznik2=1;
}
void BUFOR2()
{
	REC_D_BLE[znacznik3]=Received;
	znacznik3++;
	ZapamientanyCzas3=HAL_GetTick();
	znacznik4=1;
}


void DOPAMIECI2()
{
	if(znacznik4==1)
	{

		//Copying data to second buffer
Aktualnyczas=HAL_GetTick();

if((Aktualnyczas-ZapamientanyCzas3)>30)
{
	znacznik4=0;
	int i=0;
	while(i<80)
	{
		DANE_BLE[i]=0;
		i++;
	}
	i=0;

	while(i<znacznik3)
	{
	DANE_BLE[i]=REC_D_BLE[i];
		i++;
	}
	size_BLE=i;
	znacznik3=0;
	Received=0;

	//@@@@@@@@@@@@@@@@@@@@@@@
	KOMENDY_BLE();
	//@@@@@@@@@@@@@@@@@@@@@@@

	ZapamientanyCzas3=Aktualnyczas;
}
	}
}

void DOPAMIECI()
{
	if(znacznik2==1)
	{



//Copying data to second buffer
Aktualnyczas=HAL_GetTick();
if((Aktualnyczas-ZapamientanyCzas)>30)
{
	znacznik2=0;
	int i=0;
	while(i<80)
	{
		DANE_PCE[i]=0;
		i++;
	}
	i=0;

	while(i<znacznik)
	{
	DANE_PCE[i]=REC_DANE_PC[i];
		i++;
	}
	//DANE_PCE[i]='\r';
	//DANE_PCE[i+1]='\n';
	size_PC=i;
	znacznik=0;
	Received=0;

	ZapamientanyCzas=Aktualnyczas;
		}
	}
}


void DO_BLE(char *String)
{
	for(int i=0; i<40; i++)
	{
		ToSendAPP[i]=0;
	}

	int size=sprintf(  (char*)ToSendAPP,(char*)String);
	HAL_UART_Transmit_IT(&huart2, ToSendAPP, size);
}

void DRUKOWANIE()
{

	int sizee=0;
	int sizee2=0;

	uint8_t DD[10]="HH";
	uint8_t DD2[10]="HH";

	sprintf((char*)&DOWYSLANIA, "DUPA %s \r\n DD \n\r %s",DD,DD2);


	sizee=	sprintf((char*)&DOWYSLANIA,"PC:%s\r\nBLE:%s\r\n ",DANE_PCE,DANE_BLE);

	sizee2= sprintf((char*)&DOWYSLANIA2,"BLE:%s\r\nPC:%s\r\n",DANE_BLE,DANE_PCE);

	//Modified without test :/
	// sprintf( (char*)&DOWYSLANIA ,"%s",DOWYSLANIA);
	//sprintf( (char*)&DOWYSLANIA2,"%s",DOWYSLANIA2);

	HAL_UART_Transmit_IT(&huart5,DOWYSLANIA2, sizee2); // Rozpoczecie nadawania danych z wykorzystaniem przerwan
	HAL_UART_Transmit_IT(&huart2,DOWYSLANIA, sizee); // Rozpoczecie nadawania danych z wykorzystaniem przerwan
}

#ifdef SEND_DATA_TO_PC

void PC_BLE_TRANSMIT()
{
	if(ZapamientanyCzasTR+500 < HAL_GetTick() )
	{
		ZapamientanyCzasTR=HAL_GetTick();
		DRUKOWANIE();
	}

}

#else

void PC_BLE_TRANSMIT()
{

}
#endif



