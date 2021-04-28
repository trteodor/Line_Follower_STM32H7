/*
 * EEPROM.h
 *
 *  Created on: Sep 21, 2020
 *      Author: Teodor
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "i2c.h"
#include "main.h"

extern int8_t EEPROM_WRITE(uint16_t MemAdr, uint8_t *regData , uint16_t len);

extern int8_t EEPROM_READ(uint16_t MemAdr, uint8_t *regData , uint16_t len);

extern float EEPROM_WRITE_FLOAT(uint16_t MemAdr, float *regData);

extern float EEPROM_READ_FLOAT(uint16_t MemAdr,float *regData);

extern int EEPROM_READ_INT(uint16_t MemAdr,int *regData);

extern int EEPROM_WRITE_INT(uint16_t MemAdr, int *regData);

#endif /* INC_EEPROM_H_ */
