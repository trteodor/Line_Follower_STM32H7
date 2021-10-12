/*
 * ENKODERY.h
 *
 *  Created on: Jan 11, 2021
 *      Author: Teodor
 */

#ifndef INC_ENKODERY_H_
#define INC_ENKODERY_H_

#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "sdmmc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stm32h7xx_it.h"
#include <stdio.h>
#include "CZUJNIKI.h"
#include "R_PID.h"
#include "EEPROM.h"
#include "BLE_PC_CON.h"
#include "Komendy_BLE.h"
#include "Robot_Control.h"
#include <TSOP2236_new_T.h>
#include "ftoa_function.h"


extern void oblicz_predkosc();
extern  int flaga_ENK;
extern void pomiardoble();
extern void wykryj_znacznik();
extern void mierzprzebdr();

extern float ENK_LEWY;
extern float zENK_LEWY;
extern float ENK_PRAWY;
extern float zENK_PRAWY;
extern float zT_ENK;
extern float zT_ENK_sBLE;
extern int fl_wysl;
extern float Predkosc_L;
extern float Predkosc_P;
extern int flaga_ENK;


extern float PREDKOSC_L_W_PROBCE[4000];
extern float PREDKOSC_P_W_PROBCE[4000];
extern int nr_probki;

extern float DROGA_L;
extern float DROGA_P;
extern float DROGA_L_W_PROBCE[4000];
extern float DROGA_P_W_PROBCE[4000];
extern float PR_Srodka[4000];
extern float DR_SRODKA[4000];

extern int Dnr_probki;
extern float P_DRSR;
extern float ZN_ENKL;
extern float ZN_ENKP;

extern int D_ZENKL;
extern int D_ZENKP;
extern int wykr_znacznik;

extern float zDR_ENKL;
extern float zDR_ENKP;

extern uint32_t zT_ZNACZNIK;
extern float CZ_OKR;
extern float dlugosctrasy;

extern int mapa_dplik;
extern int zzzap_nrprobki;




#endif /* INC_ENKODERY_H_ */
