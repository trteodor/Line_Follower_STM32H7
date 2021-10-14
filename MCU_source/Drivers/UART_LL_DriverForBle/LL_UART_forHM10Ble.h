/*
 * LL_UART_ECHO_DMA_IDLE.h
 *
 *  Created on: Mar 15, 2021
 *      Author: Teodor
 */

#ifndef INC_LL_UART_forHM10Ble_H_
#define INC_LL_UART_forHM10Ble_H_

#include "main.h"
#include <stdbool.h>


//#define NbDataToReceive 25
#define UART_DMA_BUFF_SIZE      256

typedef enum
{
	UART_Ok,
	UART_Error
}Uart_State;

typedef struct __UART_DMA_Handle_Td
{
	USART_TypeDef      *Instance;

	uint32_t UART_DMA_RX_CHANNEL;
	uint32_t UART_DMA_TX_CHANNEL;

	bool Uart_ready_to_TX;
	bool Uart_RX_data_ready;

	uint32_t ReceiveBufforSize;
	uint32_t NbofRecData;


	uint8_t *UART_DMA_TX_Buffer;
	uint8_t *UART_DMA_RX_Buffer;	// DMA, UART BUFF

	uint32_t LastMessageSendTimeStart;

}UART_DMA_Handle_Td;;

extern UART_DMA_Handle_Td TUART2;

extern void TUART_END_RECEIVE_CALLBACK(UART_DMA_Handle_Td *USARTX);
extern Uart_State TUART_DMA_Trasmit(UART_DMA_Handle_Td *USARTX, uint8_t *txBuf, uint16_t size,uint32_t timeout );

extern void USART_IDLE_CallBack(UART_DMA_Handle_Td *USARTX);
extern void Init_LL_USART_IDLE();

extern void StartTransfers(UART_DMA_Handle_Td *USARTX);
extern void UART_DMA_TransmitComplete_Callback(UART_DMA_Handle_Td *USARTX);
extern void UART_DMA_ReceiveComplete_Callback(UART_DMA_Handle_Td *USARTX);

extern void Configure_DMA(UART_DMA_Handle_Td *USARTX);

#endif /* INC_LL_UART_ECHO_DMA_IDLE_H_ */
