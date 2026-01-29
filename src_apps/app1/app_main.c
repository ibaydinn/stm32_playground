#include "bsp/board_led.h"
#include "bsp/board_button.h"
#include "bsp/board_usart.h"

#define UART_BAUDRATE 115200
#define VECT_TAB_BASE_ADDRESS 0x08010000U
#define VEC_TAB_OFFSET  0x8000U

void delay_ms(uint32_t ms)
{
    uint32_t count = ms * (SYSTEM_CLOCK_FREQUENCY_HZ / 1000 / 5);
    while (count--)
        asm volatile("nop");
}


int main(void)
{
    /* Initialize LEDs and Buttons */
    board_led_init();
    board_button_init();

    /* Initialize USART */
    board_usart_init(UART_BAUDRATE);

    printf("Application 1 Started!\n\r");

    while (1)
    {
        board_led_toggle(LED_RED);
        printf("Application 1 is running...\n\r");
        delay_ms(500);
        
    }

    return 0;
}

void SystemInit(void)
{
    // SystemInit implementation if needed
    SCB->VTOR = VECT_TAB_BASE_ADDRESS | VEC_TAB_OFFSET;
}