#include "bsp/board_led.h"
#include "bsp/board_usart.h"

#define UART_BAUDRATE 115200

int main(void)
{
    /* Set BLUE LED on at startup. So I can see that code is started to run. */
    board_led_init();
    board_led_on(LED_GREEN);

    /* Initialize USART */
    board_usart_init(UART_BAUDRATE);
    printf("USART Initialized at %d baudrate.\n\r", UART_BAUDRATE);

    while (1)
    {
        printf("Send a character: \n\r");
        char received = board_uart_read();
        printf("Received: %c\n\r", received);
    }


    return 0;
}

