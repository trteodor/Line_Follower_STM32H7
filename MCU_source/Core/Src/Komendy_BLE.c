/*
 * KOMENDY_BLE.c
 *
 *  Created on: Sep 21, 2020
 *      Author: Teodor
 *
 *      145 / 5000
 * This application is of very poor quality, only a small refactoring has been made
 * to increase readability. However, somehow it leaves a lot to be desired.
 * Refactored 10.2021
 */

 //DANE_BLE[80];

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Robot_Control.h>
#include <String.h>
#include "main.h"

#include <stm32h7xx_it.h>
#include "Komendy_BLE.h"
#include "EEPROM.h"
#include "R_PID.h"
#include "Czujniki.h"
#include "ftoa_function.h"
#include "Robot_Control.h"
#include <TSOP2236_new_T.h>
#include "stm32h7xx_hal.h"
uint32_t AktualnyCzasK_BLE=0;
uint32_t ZapamientanyCzasK_BLE=0;
uint32_t Z_Czas_Do_Pliku=0;

uint8_t wynik=0;
uint8_t drukowanie=0;
uint8_t c=0;
uint8_t czujnikiactiv=0;
uint8_t DANE_DO_TEXT=0;

int k_wys_pom=1;


void PRZYPISYWANIEWARTOSCI();
void WyslijWartoscERR();
void ZMIENNE_ZAAW_DO_BLE();
void DRUKUJ_PID();
void PID_DO_BLE();
void DRUKUJCZUJNIKI();


void KOMENDY_BLE()
{
size_BLE--;
size_BLE--;
c=DANE_BLE[size_BLE];
if(c==226) //? wtf
{
	size_BLE--;
}
c=DANE_BLE[size_BLE];


if(c==147 || c==134)
{
	drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=1;//SAVE_DATA
}
if(c==146)
{
	drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;//STOP_DATA
}


				//Dobrze byłoby to zrobic na switchu no ale bd tak


	if(c=='I'){wynik=222; URUCHAMIANIE_ROBOTA=1; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //jedz ( uruchamianie robota)

	else if(c=='U'){wynik=223; URUCHAMIANIE_ROBOTA=0;} //stop ( wyłączanie robota )

	//ERKAN "PODST"
	else if(c=='P'){wynik =220; drukowanie=3; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //scanowanie pid
	else if(c=='O'){wynik =221; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //wylaczanie scanowania pid
	else if(c=='>'){wynik =205; drukowanie=1; k_wys_pom=1; DANE_DO_TEXT=0;}//aktualne dane PID


	else if(c=='+'){wynik =1;}  //Kp

    else if(c=='-'){wynik =2;}  //KD
    else if(c==')'){wynik =103;}  //Predkosc silnikow to intiger
    else if(c=='('){wynik =4;} //Ki

	    //@@@
	    //EKRAN "CZUJNIKI"
	      else if(c=='B')  {wynik =206;  czujnikiactiv=1; k_wys_pom=1; drukowanie=0; DANE_DO_TEXT=0;} //Wysylaj aktualne dane z czujnikow
	      else if(c=='V'){wynik =207;   czujnikiactiv=0; k_wys_pom=1; drukowanie=0; DANE_DO_TEXT=0;} //wyłączam wysylanie danych z czujników
	      else if(c=='~'){wynik =208;   drukowanie=2; czujnikiactiv=0;  k_wys_pom=1; DANE_DO_TEXT=0;}
	       											//wyłączam wysylanie danych z czujników i wysylam aktualne wartosci ER
	      else if(c=='*'){wynik=10; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //ER1
	      else if(c=='&'){wynik=11; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //ER2
	      else if(c=='^'){wynik=12; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}
	      else if(c=='%'){wynik=13; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}
	      else if(c=='$'){wynik=14; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}
	      else if(c=='#'){wynik=15; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}
	      else if(c=='@'){wynik=16; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //ER7
	      else if(c=='!'){wynik=17; czujnikiactiv  =0; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //ERMAX

	      else if(c==167){wynik=40; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //CZCZ1 //alt+21 nadaje apka  - § <<ten znaczek //bylo "G" nie wiem skad problem
	      else if(c=='H'){wynik=41; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //CZCZ2
	      else if(c=='Q'){wynik=42; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //CZCZ3
	      else if(c=='W'){wynik=43; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //CZCZ4
	      else if(c=='?'){wynik=44; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //CZCZ5
	      else if(c=='L'){wynik=45; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //CZCZ6
	      else if(c=='T'){wynik=46; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //CZCZ7
	      else if(c=='Y'){wynik=47; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //CZCZ8

	    	//@@@

    //EKRAN "ZAAW"
	    if(c=='X'){drukowanie=4; } //drukuj aktualnie zapisane dane :)

    else if(c=='g'){wynik=30; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //MAX_PID_WARTOSC
    else if(c=='h'){wynik=131; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //pr_tyl
    else if(c=='q'){wynik=32; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //SUMAMAX
    else if(c=='w'){wynik=33; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;}  //PID_KdProbeTime


    else if(c=='e'){wynik=134; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0; } //test silnika   //zmienna 1
    else if(c=='`'){wynik=135; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //test silnika stop //zmienna 2

    else if(c=='t'){wynik=36; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //zmienna 3
    else if(c=='y'){wynik=37; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //zmienna 4
    else if(c=='j'){wynik=38; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //zmienna 5
    else if(c=='J'){wynik=39; drukowanie=0; czujnikiactiv=0; k_wys_pom=1; DANE_DO_TEXT=0;} //zmienna 6




    if(wynik!=0)
    {
    	PRZYPISYWANIEWARTOSCI ();
    }
      wynik=0;
 }

void DANE_DO_APLIKACJI_MOBILNEJ()
{
	  DRUKUJCZUJNIKI();
	  WyslijWartoscERR();
	  DRUKUJ_PID();
	  PID_DO_BLE();
	  ZMIENNE_ZAAW_DO_BLE();

}

void DRUKUJ_PID()
{
	if(drukowanie==3)
	 {

		 char after_con_val[32]={0};

	 // Serial.println("jestem tutaj");

	    drukowanie=3;
	  if ( k_wys_pom==1 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   ftoa(PID_value,after_con_val ,2);
	   strcat(after_con_val, "a");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	  }
	  if ( k_wys_pom==2 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(Pr_Silnika_Lewego,after_con_val ,10);
	   strcat(after_con_val, "s");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	  }
	    if ( k_wys_pom==3 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(Pr_Silnika_Prawego,after_con_val ,10);
	   strcat(after_con_val, "d");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	   }
	       if ( k_wys_pom==4 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   char helper[20]={0};
	   ftoa(ERR_CZ,helper ,2);

	   strcat(after_con_val, "ERROR:");

	   strcat(after_con_val, helper);
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	   }
	       if ( k_wys_pom==5 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(KI_SUMA,after_con_val ,10);
	   strcat(after_con_val, "f");
	   DO_BLE(after_con_val);
	   k_wys_pom=1;
	   //drukowanie=0; //ciągle wysyla
	    }

	  }


}

void PID_DO_BLE()
{
	  if(drukowanie==1)
	 {
		  char after_con_val[32]={0};

	  if (k_wys_pom==1 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
		  ZapamientanyCzasK_BLE = HAL_GetTick();

	    ftoa(Kp,after_con_val ,2);
		   strcat(after_con_val, "l");
		  DO_BLE(after_con_val);
		k_wys_pom++;
	  }
	  if (k_wys_pom==2 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	    ftoa(Kd,after_con_val ,2);
		   strcat(after_con_val, "k");
		  DO_BLE(after_con_val);
		k_wys_pom++;
	  }
	    if (k_wys_pom==3 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	    ftoa(pr_pocz_silnikow,after_con_val ,2);
			   strcat(after_con_val, "m");
			  DO_BLE(after_con_val);
			k_wys_pom++;
	   }
	       if (k_wys_pom==4 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();
	 //Serial.println("jestem tutaj");
	    itoa(CzasProbkowania_CZ_Rozniczkujacego,after_con_val ,10);
			   strcat(after_con_val, "w");
			  DO_BLE(after_con_val);
			k_wys_pom=1;
	   drukowanie=0; //tylko jeden raz
	    }
	  }
}
//literka n jest wolna!!

void DRUKUJCZUJNIKI()
{
  if(czujnikiactiv==1)
{
	  char Pom_String[20]={0};
	  char after_con_int[32]={0};
  drukowanie=0;
    if ( HAL_GetTick() - ZapamientanyCzasK_BLE >= 15) {
    	ZapamientanyCzasK_BLE = HAL_GetTick();

          if(k_wys_pom==1)  { itoa(DANE_Z_CZUJNIKOW[0],after_con_int,10); strcat(Pom_String, "CZ1:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;	}
          if(k_wys_pom==2)  { itoa(DANE_Z_CZUJNIKOW[1],after_con_int,10); strcat(Pom_String, "CZ2:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;  }
          if(k_wys_pom==3)  { itoa(DANE_Z_CZUJNIKOW[2],after_con_int,10); strcat(Pom_String, "CZ3:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;  }
          if(k_wys_pom==4)  { itoa(DANE_Z_CZUJNIKOW[3],after_con_int,10); strcat(Pom_String, "CZ4:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;  }
          if(k_wys_pom==5)  { itoa(DANE_Z_CZUJNIKOW[4],after_con_int,10); strcat(Pom_String, "CZ5:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;  }
          if(k_wys_pom==6)  { itoa(DANE_Z_CZUJNIKOW[5],after_con_int,10); strcat(Pom_String, "CZ6:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;  }
          if(k_wys_pom==7)  { itoa(DANE_Z_CZUJNIKOW[6],after_con_int,10); strcat(Pom_String, "CZ7:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;  }
          if(k_wys_pom==8)  { itoa(DANE_Z_CZUJNIKOW[7],after_con_int,10); strcat(Pom_String, "CZ8:"); strcat(Pom_String,after_con_int );  k_wys_pom++; DO_BLE(Pom_String); return;  }
          if(k_wys_pom==9)  { ftoa(ERR_CZ,after_con_int ,2);  strcat(Pom_String, "ERROR:"); strcat(Pom_String,after_con_int );  k_wys_pom=1; DO_BLE(Pom_String); return;  }
          }
    }
}

void WyslijWartoscERR()
{
	   if(drukowanie==2) //to cale jest do napisania
	 {
		  	  char after_con_val[32]={0};


	 //   drukowanie=2;


	  if (k_wys_pom==1 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   ftoa(er1,after_con_val ,2);
	   strcat(after_con_val, "*");
	  DO_BLE(after_con_val);
	k_wys_pom++;
	  }
	  if (k_wys_pom==2 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();
	   ftoa(er2,after_con_val ,2);
	   strcat(after_con_val, "&");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	  }
	    if (k_wys_pom==3 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();
	   ftoa(er3,after_con_val ,2);
	   strcat(after_con_val, "^");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	   }
	       if (k_wys_pom==4 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   ftoa(er4,after_con_val ,2);
	   strcat(after_con_val, "_");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	          if (k_wys_pom==5 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   ftoa(er5,after_con_val ,2);
	   strcat(after_con_val, "$");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	          if (k_wys_pom==6 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   ftoa(er6,after_con_val ,2);
	   strcat(after_con_val, "#");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	          if (k_wys_pom==7 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   ftoa(er7,after_con_val ,2);
	   strcat(after_con_val, "@");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	          if (k_wys_pom==8 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   ftoa(err_max,after_con_val ,2);
	   strcat(after_con_val, "!");
	   DO_BLE(after_con_val);
	  // drukowanie=0;
	   //wynik=0;
	   k_wys_pom++;

	    }
              if (k_wys_pom==9 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(czcz1,after_con_val ,10);
	   strcat(after_con_val, "§"); //alt+21
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	                  if (k_wys_pom==10 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(czcz2,after_con_val ,10);
	   strcat(after_con_val, "H");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	                  if (k_wys_pom==11 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(czcz3,after_con_val ,10);
	   strcat(after_con_val, "Q");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	                  if (k_wys_pom==12 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(czcz4,after_con_val ,10);
	   strcat(after_con_val, "W");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	                  if (k_wys_pom==13 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();


	   itoa(czcz5,after_con_val ,10);
	   strcat(after_con_val, "?");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	                  if (k_wys_pom==14 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(czcz6,after_con_val ,10);
	   strcat(after_con_val, "L");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	                  if (k_wys_pom==15 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(czcz7,after_con_val ,10);
	   strcat(after_con_val, "T");
	   DO_BLE(after_con_val);
	   k_wys_pom++;
	    }
	                  if (k_wys_pom==16 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	   ZapamientanyCzasK_BLE = HAL_GetTick();

	   itoa(czcz8,after_con_val ,10);
	   strcat(after_con_val, "Y");
	   DO_BLE(after_con_val);
	   k_wys_pom=1;
	    drukowanie=0;
	 	  wynik=0;

	    }

	  }
}

void PRZYPISYWANIEWARTOSCI()
{

	//Z Ekranu "PODST"
  if(wynik==1){
	  Kp=atof(DANE_BLE);
	  EEPROM_WRITE_FLOAT(50,&Kp);

    }
  if(wynik==2){
    Kd=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(55,&Kd);
  }
  if(wynik==103){
    pr_pocz_silnikow=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(60,&pr_pocz_silnikow);
}
  if(wynik==4) {
    Ki=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(65,&Ki);
  }



  //Z Ekranu "CZUJNIKI"

  if(wynik==10) {
    er1=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(70,&er1);

  }
    if(wynik==11) {
    er2=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(75,&er2);

  }
    if(wynik==12) {
    er3=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(80,&er3);

  }
    if(wynik==13) {
    er4=atof(DANE_BLE);
    EEPROM_WRITE_FLOAT(85,&er4);

  }
    if(wynik==14) {
    er5=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(90,&er5);

  }
    if(wynik==15) {
    er6=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(100,&er6); //adres 95 uszkodzony? :/

  }
    if(wynik==16) {
    er7=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(105,&er7);

  }
    if(wynik==17) {
    	err_max=atof(DANE_BLE); EEPROM_WRITE_FLOAT(115,&err_max); //adres 110 uszkodzony? :/

  }




					if(wynik==40) {
						czcz1=atoi(DANE_BLE);  EEPROM_WRITE_INT(265,&czcz1); //adres 200 uszkodzony? tak
						}
					  if(wynik==41) {
						  czcz2=atoi(DANE_BLE);  EEPROM_WRITE_INT(245,&czcz2); //adres 205 uszkodzony? tak nwm o co kmn anyway
						  }
					  if(wynik==42) {
						  czcz3=atoi(DANE_BLE);  EEPROM_WRITE_INT(210,&czcz3);
						  }
					  if(wynik==43) {
						  czcz4=atoi(DANE_BLE);  EEPROM_WRITE_INT(215,&czcz4);
						  }
					  if(wynik==44) {
						  czcz5=atoi(DANE_BLE);  EEPROM_WRITE_INT(220,&czcz5);
						  }
						  if(wynik==45) {
							  czcz6=atoi(DANE_BLE);  EEPROM_WRITE_INT(225,&czcz6);
						  }
					  if(wynik==46) {
						  czcz7=atoi(DANE_BLE);  EEPROM_WRITE_INT(230,&czcz7);
					  }
						if(wynik==47) {
							czcz8=atoi(DANE_BLE);  EEPROM_WRITE_INT(235,&czcz8);
						}




        //@@@@@@@@@@@@@@@
//Z Ekranu "ZAAW"

				if(wynik==30) {
					MAX_PID=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(400,&MAX_PID);

			  }
				  if(wynik==131) {
				pr_tyl=atoi(DANE_BLE);  EEPROM_WRITE_INT(405,&pr_tyl);

			  }
				  if(wynik==32) {
					  SUMA_MAX=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(410,&SUMA_MAX);

			  }
				  if(wynik==33) {
				CzasProbkowania_CZ_Rozniczkujacego=atoi(DANE_BLE);

			   EEPROM_WRITE_INT(420,&CzasProbkowania_CZ_Rozniczkujacego);

			  }

				  if(wynik==134) { //test silnika wl
					  T_SIL=1;
			  }
				  if(wynik==135) { //tesy silnika wyl
					  T_SIL=0;
			  }

				  if(wynik==36) {
					  ZMIENNA3=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(440,&ZMIENNA3);

			   }

				  if(wynik==37) {
					  ZMIENNA4=atof(DANE_BLE);  EEPROM_WRITE_FLOAT(445,&ZMIENNA4);
					  HAL_NVIC_SystemReset();
			  }

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ IR STATE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      if(wynik==38) {
    	  IR_READY=atoi(DANE_BLE);  EEPROM_WRITE_INT(450,&IR_READY);

  }
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ IR STATE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        if(wynik==39) {
        	LED_BLINK=atoi(DANE_BLE);;  EEPROM_WRITE_INT(455,&LED_BLINK);
      }
  //@@@@@@@@@@@@@@@@
}


void ZMIENNE_ZAAW_DO_BLE()
{

      if(drukowanie==4)
 {
    	  char after_con_val[32]={0};
    drukowanie=4;

  if (k_wys_pom==1 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
	  ZapamientanyCzasK_BLE = HAL_GetTick();

   ftoa(MAX_PID,after_con_val ,2);
   strcat(after_con_val, "g");
  DO_BLE(after_con_val);
k_wys_pom++;
  }
  if (k_wys_pom==2 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15)  {
   ZapamientanyCzasK_BLE = HAL_GetTick();

   itoa(pr_tyl,after_con_val ,10);
   strcat(after_con_val, "h");
  DO_BLE(after_con_val);
k_wys_pom++;
  }
    if (k_wys_pom==3 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15)  {
   ZapamientanyCzasK_BLE = HAL_GetTick();

   ftoa(SUMA_MAX,after_con_val ,2);
   strcat(after_con_val, "q");
  DO_BLE(after_con_val);
k_wys_pom++;
   }
       if (k_wys_pom==4 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15)  {
   ZapamientanyCzasK_BLE = HAL_GetTick();

   itoa(CzasProbkowania_CZ_Rozniczkujacego,after_con_val ,10);
   strcat(after_con_val, "w");
  DO_BLE(after_con_val);
k_wys_pom++;
    }

          if (k_wys_pom==5 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15)  {
   ZapamientanyCzasK_BLE = HAL_GetTick();

   ftoa(ZMIENNA3,after_con_val ,2);
   strcat(after_con_val, "t");
  DO_BLE(after_con_val);
k_wys_pom++;
    }
              if (k_wys_pom==6 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15)  {
   ZapamientanyCzasK_BLE = HAL_GetTick();

   itoa(IR_READY,after_con_val ,10);
     strcat(after_con_val, "j");
    DO_BLE(after_con_val);
  k_wys_pom++;
    }
              if (k_wys_pom==7 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15)  {
   ZapamientanyCzasK_BLE = HAL_GetTick();

   itoa(LED_BLINK,after_con_val ,10);
     strcat(after_con_val, "J");
    DO_BLE(after_con_val);
  k_wys_pom++;
    }
          if (k_wys_pom==8 && (HAL_GetTick() - ZapamientanyCzasK_BLE) >= 15) {
   ZapamientanyCzasK_BLE = HAL_GetTick();

   ftoa(ZMIENNA4,after_con_val ,2);
     strcat(after_con_val, "y");
    DO_BLE(after_con_val);
  k_wys_pom=1;
   drukowanie=0; //tylko jeden raz
    }
  }
}


//Called in "void TIM2_IRQHandler(void)" check file stm32fxxx_it.c





