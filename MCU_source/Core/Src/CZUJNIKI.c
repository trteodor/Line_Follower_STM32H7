/*
 * CZUJNIKI.c
 *
 *  Created on: Sep 17, 2020
 *      Author: Teodor
 */

#include "CZUJNIKI.h"
#include "main.h"
#include "adc.h"
#include "EEPROM.h"
#include "R_PID.h"
#include "ENKODERY.h"
//#include "stdbool.h"

uint16_t DANE_Z_CZUJNIKOW[8];
float ERR_CZ=0;
int OST_KIER_BL=0;


float er1,er2,er3,er4,er5,er6,er7,err_max; //ustawiane w apce bluetooth

int czcz1,czcz2,czcz3,czcz4,czcz5,czcz5,czcz6,czcz7,czcz8; //ustawiane w apce bluetooth

int fl_Time_PD_Reset=0;

uint32_t CzasZ_CZ=0;

float OBLICZ_BLAD()
{

	flaga_ENK=0;
	int SKRZ=0;

	for(int i=2; i<6; i++)
	{

		if (DANE_Z_CZUJNIKOW[i]>2500)
		{
			SKRZ++;
		}
		if(SKRZ==4)
		{
			ERR_CZ=0;
			SKRZ=0;
			flaga_ENK=1;
			return ERR_CZ;
		}
	}

	if(DANE_Z_CZUJNIKOW[3]>czcz4 && DANE_Z_CZUJNIKOW[4]>czcz5)	{		ERR_CZ=0;  	return ERR_CZ; 	}

	if(DANE_Z_CZUJNIKOW[0]>czcz1 && DANE_Z_CZUJNIKOW[1]>czcz2)	{		ERR_CZ=er6;  OST_KIER_BL=1;	return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[1]>czcz2 && DANE_Z_CZUJNIKOW[2]>czcz3)	{		ERR_CZ=er4;  	return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[2]>czcz3 && DANE_Z_CZUJNIKOW[3]>czcz4)	{		ERR_CZ=er2;  	return ERR_CZ; 	}


	if(DANE_Z_CZUJNIKOW[7]>czcz8 && DANE_Z_CZUJNIKOW[6]>czcz7)	{		ERR_CZ=-er6; OST_KIER_BL=-1; 	return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[6]>czcz7 && DANE_Z_CZUJNIKOW[5]>czcz6)	{		ERR_CZ=-er4; 	return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[5]>czcz6 && DANE_Z_CZUJNIKOW[4]>czcz5)	{		ERR_CZ=-er2;  	return ERR_CZ; 	}


	if(DANE_Z_CZUJNIKOW[0]>czcz1)	{		ERR_CZ=er7;   OST_KIER_BL=1; 	 return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[1]>czcz2)	{		ERR_CZ=er5;     return ERR_CZ;		}
	if(DANE_Z_CZUJNIKOW[2]>czcz3)	{		ERR_CZ=er3;  	return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[3]>czcz4)	{		ERR_CZ=er1;  	return ERR_CZ; 	}

	if(DANE_Z_CZUJNIKOW[4]>czcz5)	{		ERR_CZ=-er1;  	return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[5]>czcz6)	{		ERR_CZ=-er3;  	return ERR_CZ; 	}
	if(DANE_Z_CZUJNIKOW[6]>czcz7)	{		ERR_CZ=-er5;    return ERR_CZ;	 	}
	if(DANE_Z_CZUJNIKOW[7]>czcz8)	{		ERR_CZ=-er7;  OST_KIER_BL=-1;	return ERR_CZ;	}



	if (OST_KIER_BL==-1 )  {  ERR_CZ=-err_max; 	return ERR_CZ; }
	if (OST_KIER_BL==1  )  {  ERR_CZ=err_max;  	return ERR_CZ; }

	//ERR_CZ=99;
	return 0;
}


void CZUJNIKI_INIT()
{
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)DANE_Z_CZUJNIKOW,8); //Turn on Sensor Read
	ReadValue_CZ_EEPROM();
}


void ReadValue_CZ_EEPROM()
{

EEPROM_READ_FLOAT(70, &er1);
EEPROM_READ_FLOAT(75, &er2);
EEPROM_READ_FLOAT(80, &er3);
EEPROM_READ_FLOAT(85, &er4);
EEPROM_READ_FLOAT(90, &er5);
EEPROM_READ_FLOAT(100, &er6);
EEPROM_READ_FLOAT(105, &er7);
EEPROM_READ_FLOAT(115, &err_max);

EEPROM_READ_INT(265, &czcz1);
EEPROM_READ_INT(245, &czcz2);
EEPROM_READ_INT(210, &czcz3);
EEPROM_READ_INT(215, &czcz4);
EEPROM_READ_INT(220, &czcz5);
EEPROM_READ_INT(225, &czcz6);
EEPROM_READ_INT(230, &czcz7);
EEPROM_READ_INT(235, &czcz8);

}


