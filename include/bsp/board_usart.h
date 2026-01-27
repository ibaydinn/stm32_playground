#ifndef BSP__BOARD_USART_H_
#define BSP__BOARD_USART_H_

#include "bsp/board_config.h"

// For printf redirection
#include <stdio.h>

void board_usart_init(uint32_t baudrate);
void board_uart_write(char data);
char board_uart_read(void);

#endif // BSP__BOARD_USART_H_