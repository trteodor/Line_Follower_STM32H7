#ifndef _HM10_BleModule_H
#define _HM10_BleModule_H
#include "stdint.h"

#define ReceiveBufferSize 128
#define TransmitBufferSize 128

extern uint8_t ReceiveBuffer[ReceiveBufferSize]; // Receive from UART Buffer
extern uint8_t TransmitBuffer[TransmitBufferSize]; // Message to transfer by UART
extern uint8_t Length; // Message length

void HM10BLE_Init();
void HM10BLE_RxEventCallback(uint16_t RecDataSize);
void HM10BLE_TxCmpltEventCallback();

#endif //_HM10_BleModule_H
