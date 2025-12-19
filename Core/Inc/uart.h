#ifndef __UART_H_
#define __UART_H_
#include "main.h"
#include "usart.h"
#include <stdbool.h>
#define BUFFER_SIZE  256
typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    volatile uint8_t head;
    volatile uint8_t tail;
} RingBuffer_t;
extern RingBuffer_t buffer1;
void rb_init(RingBuffer_t *rb);
bool rb_write(RingBuffer_t*rb,uint8_t data);
bool rb_read(RingBuffer_t*rb,uint8_t *data);
#endif



