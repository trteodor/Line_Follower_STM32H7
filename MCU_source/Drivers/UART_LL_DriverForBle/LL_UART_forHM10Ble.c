/*
 * LL_UART_ECHO_DMA_IDLE.c
 *
 *  Created on: Mar 15, 2021
 *      Author: Teodor
 */

#include "LL_UART_forHM10Ble.h"

#define MinimumTimeBeetweenNextMessages 20

char InitMessage[] = "\n\rHello Uart  115200kb/s \n\rTap Your Message:";


void Init_LL_USART_IDLE(UART_DMA_Handle_Td *USARTX)
{
	Configure_DMA(USARTX);
	StartTransfers(USARTX);
	uint16_t sizeInitMessage = sizeof(InitMessage)-1;
	USARTX->Uart_ready_to_TX = false;
	LL_DMA_DisableChannel(DMA1, USARTX->UART_DMA_TX_CHANNEL);
	/* It should be */
	  LL_DMA_ConfigAddresses(DMA1, USARTX->UART_DMA_TX_CHANNEL,
							(uint32_t) InitMessage,
							 LL_USART_DMA_GetRegAddr(USARTX->Instance),
							 LL_DMA_GetDataTransferDirection(DMA1,USARTX->UART_DMA_TX_CHANNEL));
	LL_DMA_SetDataLength(DMA1, USARTX->UART_DMA_TX_CHANNEL, sizeInitMessage);
	LL_DMA_EnableChannel(DMA1, USARTX->UART_DMA_TX_CHANNEL);
}

Uart_State TUART_DMA_Trasmit(UART_DMA_Handle_Td *USARTX, uint8_t *txBuf, uint16_t size, uint32_t timeout)
{
	timeout=HAL_GetTick()+timeout;

	while(USARTX->Uart_ready_to_TX != true)
	{
		if(HAL_GetTick() > timeout )
			{
				break;
			}
		else
			{
				continue;
			}
	}
	if(HAL_GetTick() < USARTX->LastMessageSendTimeStart+MinimumTimeBeetweenNextMessages)
	{
		return UART_Error; //error
	}
	USARTX->LastMessageSendTimeStart = HAL_GetTick();

	if(USARTX->Uart_ready_to_TX == true)
	{
		USARTX->Uart_ready_to_TX = false;

		LL_DMA_DisableChannel(DMA1, USARTX->UART_DMA_TX_CHANNEL);

	  /* It should be */
		  LL_DMA_ConfigAddresses(DMA1, USARTX->UART_DMA_TX_CHANNEL,
		                        (uint32_t) txBuf,
		                         LL_USART_DMA_GetRegAddr(USARTX->Instance),
		                         LL_DMA_GetDataTransferDirection(DMA1,USARTX->UART_DMA_TX_CHANNEL));

		LL_DMA_SetDataLength(DMA1, USARTX->UART_DMA_TX_CHANNEL, size);

		LL_DMA_EnableChannel(DMA1, USARTX->UART_DMA_TX_CHANNEL);
	}
return UART_Ok; //alls ok
}

void StartTransfers(UART_DMA_Handle_Td *USARTX)
{
	LL_USART_EnableDMAReq_RX(USARTX->Instance);
	LL_USART_EnableDMAReq_TX(USARTX->Instance);
	LL_DMA_EnableChannel(DMA1, USARTX->UART_DMA_RX_CHANNEL);
	LL_DMA_EnableChannel(DMA1, USARTX->UART_DMA_TX_CHANNEL);
	LL_USART_EnableIT_IDLE(USARTX->Instance);
}


void Configure_DMA(UART_DMA_Handle_Td *USARTX)
{

  LL_DMA_ConfigTransfer(DMA1, USARTX->UART_DMA_TX_CHANNEL,
                        LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
                        LL_DMA_PRIORITY_HIGH              |
                        LL_DMA_MODE_NORMAL                |
                        LL_DMA_PERIPH_NOINCREMENT         |
                        LL_DMA_MEMORY_INCREMENT           |
                        LL_DMA_PDATAALIGN_BYTE            |
                        LL_DMA_MDATAALIGN_BYTE);

  LL_DMA_ConfigAddresses(DMA1, USARTX->UART_DMA_TX_CHANNEL,
                         (uint32_t)USARTX->UART_DMA_TX_Buffer,
                         LL_USART_DMA_GetRegAddr(USARTX->Instance),
                         LL_DMA_GetDataTransferDirection(DMA1, USARTX->UART_DMA_TX_CHANNEL));

  LL_DMA_ConfigTransfer(DMA1, USARTX->UART_DMA_RX_CHANNEL,
                        LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
                        LL_DMA_PRIORITY_HIGH              |
                        LL_DMA_MODE_NORMAL                |
                        LL_DMA_PERIPH_NOINCREMENT         |
                        LL_DMA_MEMORY_INCREMENT           |
                        LL_DMA_PDATAALIGN_BYTE            |
                        LL_DMA_MDATAALIGN_BYTE);
  LL_DMA_ConfigAddresses(DMA1, USARTX->UART_DMA_RX_CHANNEL,
                         LL_USART_DMA_GetRegAddr(USARTX->Instance),
						 (uint32_t) USARTX->UART_DMA_RX_Buffer,
                         LL_DMA_GetDataTransferDirection(DMA1, USARTX->UART_DMA_RX_CHANNEL));
  LL_DMA_SetDataLength(DMA1, USARTX->UART_DMA_RX_CHANNEL, USARTX->ReceiveBufforSize);

  /* (5) Enable DMA transfer complete*/
  LL_DMA_EnableIT_TC(DMA1, USARTX->UART_DMA_TX_CHANNEL);
  LL_DMA_EnableIT_TC(DMA1, USARTX->UART_DMA_RX_CHANNEL);
}

void USART_IDLE_CallBack(UART_DMA_Handle_Td *USARTX)
{
		 if(LL_USART_IsActiveFlag_IDLE(USARTX->Instance) )
		{
			LL_USART_ClearFlag_IDLE(USARTX->Instance);
			UART_DMA_ReceiveComplete_Callback(USARTX);
		}
}



void UART_DMA_ReceiveComplete_Callback(UART_DMA_Handle_Td *USARTX)
{
	LL_DMA_DisableChannel(DMA1, USARTX->UART_DMA_RX_CHANNEL);
 	USARTX->Uart_RX_data_ready = true;
  	USARTX->NbofRecData=USARTX->ReceiveBufforSize - LL_DMA_GetDataLength(DMA1, USARTX->UART_DMA_RX_CHANNEL);
  	LL_DMA_SetDataLength(DMA1, USARTX->UART_DMA_RX_CHANNEL, USARTX->ReceiveBufforSize);
 	LL_DMA_EnableChannel(DMA1, USARTX->UART_DMA_RX_CHANNEL);
}

void UART_DMA_TransmitComplete_Callback(UART_DMA_Handle_Td *USARTX)
{
 USARTX->Uart_ready_to_TX = true;
}
