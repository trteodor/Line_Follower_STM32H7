/*
 * TSOP2236_new_T.h
 *
 *  Created on: 2 gru 2020
 *      Author: Teodor
 */

#ifndef INC_TSOP2236_NEW_T_H_
#define INC_TSOP2236_NEW_T_H_

#include <stdbool.h>

extern void delay_100us(uint32_t delay_100us);
extern void OBSLUGAPILOTA();
extern void IR_INIT();
extern void EEPROM_IR_STATE_READ();

extern uint8_t irdata[33];   //Used to record the time between two falling edges
extern bool receiveComplete; //Receive Complete Flag Bits
extern uint8_t idx;          //Number received for indexing
extern bool startflag;       //Indicates start of reception
extern uint32_t pr_IR;
extern  int IR_READY;
extern uint32_t receiver_codet;

extern uint32_t remote_code[32];

extern void IR_IT_Dec();

extern uint8_t Ir_Server();
extern void IR_READER();


#endif /* INC_TSOP2236_NEW_T_H_ */
