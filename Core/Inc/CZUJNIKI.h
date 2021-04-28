/*
 * CZUJNIKI.h
 *
 *  Created on: Sep 17, 2020
 *      Author: Teodor
 */

#ifndef INC_CZUJNIKI_H_
#define INC_CZUJNIKI_H_
#include "stm32h7xx_hal.h"

extern uint16_t DANE_Z_CZUJNIKOW[8];
extern float ERR_CZ;
extern int OST_KIER_BL1,OST_KIER_BL2,OST_KIER_BL3,OST_KIER_BL4;

extern float er1,er2,er3,er4,er5,er6,er7,err_max;
extern int czcz1,czcz2,czcz3,czcz4,czcz5,czcz5,czcz6,czcz7,czcz8;

extern void ReadValue_CZ_EEPROM();
extern float OBLICZ_BLAD();
extern void CZUJNIKI_INIT();

#endif /* INC_CZUJNIKI_H_ */
