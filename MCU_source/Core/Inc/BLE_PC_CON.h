/*
 * DANE_Z_BLE.h
 *
 *  Created on: Sep 21, 2020
 *      Author: Teodor
 */

#ifndef INC_BLE_PC_CON_H_
#define INC_BLE_PC_CON_H_

#include "stm32h7xx_hal.h"

extern uint8_t Received;
extern uint8_t REC_DANE_PC[30];
extern uint8_t DANE_PCE[30];
extern uint8_t DOWYSLANIA[80];
extern uint8_t ToSendAPP[30];
extern int znacznik;
extern int znacznik2;

extern uint8_t size_BLE;
extern uint8_t size_PC;

extern unsigned long Aktualnyczas;
extern unsigned long ZapamientanyCzas;

extern char REC_D_BLE[30];
extern char DANE_BLE[30];
extern uint8_t DOWYSLANIA2[80];
extern int znacznik3;
extern int znacznik4;
extern unsigned long ZapamientanyCzas3;
extern uint32_t ZapamientanyCzasTR;
extern uint32_t t5;

extern void BLE_INIT();
extern void BUFOR();
extern void BUFOR2();
extern void DOPAMIECI2();
extern void DOPAMIECI();
extern void DRUKOWANIE();
extern void PC_BLE_TRANSMIT();
extern void DO_BLE(char *String);

#endif /* INC_BLE_PC_CON_H_ */
