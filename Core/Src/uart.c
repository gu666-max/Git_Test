#include "uart.h"
#include <stdio.h>
RingBuffer_t buffer1;
uint8_t rx_data;
// 1. 初始化
void rb_init(RingBuffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
	  __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
		HAL_UART_Receive_DMA(&huart1,&rb->buffer[rb->tail],BUFFER_SIZE);
}

bool rb_write(RingBuffer_t*rb,uint8_t data)
{
	if((rb->tail+1)%BUFFER_SIZE==rb->head)
	{
		return false;
	}
	rb->buffer[rb->tail]=data;
	rb->tail=(rb->tail+1)%BUFFER_SIZE;
	
	return true;
	
}

bool rb_read(RingBuffer_t*rb,uint8_t *data)
{
	if(rb->head==rb->tail)
	{
		return false;
	}
	*data=rb->buffer[rb->head];
	rb->head=(rb->head+1)%BUFFER_SIZE;
	
	return true;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)
	{
//		rb_write(&buffer1,rx_data);
		HAL_UART_Receive_IT(&huart1,&rx_data,1);
	}
}


int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
	return ch;
}
