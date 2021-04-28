/*
 * Komendy_BLE.h
 *
 *  Created on: Sep 21, 2020
 *      Author: Teodor
 */

#ifndef SRC_KOMENDY_BLE_H_
#define SRC_KOMENDY_BLE_H_

#include "stm32h7xx_hal.h"


extern uint32_t AktualnyCzasK_BLE;
extern uint32_t ZapamientanyCzasK_BLE;
extern uint32_t Z_Czas_Do_Pliku;

extern uint8_t wynik;
extern uint8_t drukowanie;
extern uint8_t c;
extern uint8_t DANE_DO_TEXT;


extern int k_wys_pom;
extern uint8_t czujnikiactiv;
extern 	float PID_value;

extern void KOMENDY_BLE();
extern void DRUKUJCZUJNIKI();
extern void WyslijWartoscERR();
extern void DRUKUJ_PID();
extern void PID_DO_BLE();
extern void DANE_DO_APLIKACJI_MOBILNEJ();
extern void ZMIENNE_ZAAW_DO_BLE();

extern void WYSLIJ_AKTUALNE_DANE_CZUJNIKOW_I_CZAS_DO_BLE();
extern void Wyslij_PojedynczyCzujnik(uint16_t nr_czujnika);

#endif /* SRC_KOMENDY_BLE_H_ */
