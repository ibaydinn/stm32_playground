#include "bsp/board_led.h"
#include "bsp/board_button.h"
#include "bsp/board_usart.h"

#define UART_BAUDRATE 115200

#define APPLICATION_ADDRESS     0x08020000
#define EMPTY_MEMORY_PATTERN    0xFFFFFFFF


typedef void (*pFunction)(void);

void delay_ms(uint32_t ms)
{
    uint32_t count = ms * (SYSTEM_CLOCK_FREQUENCY_HZ / 1000 / 5);
    while (count--)
        asm volatile("nop");
}


static void jump_to_application(void)
{
    uint32_t app_msp = *(uint32_t *)APPLICATION_ADDRESS;
    uint32_t app_reset = *(uint32_t *)(APPLICATION_ADDRESS + 4);

    // Check if application is valid
    if ((app_msp == EMPTY_MEMORY_PATTERN) || (app_reset == EMPTY_MEMORY_PATTERN))
    {
        printf("No valid application found at address 0x%08X\n\r", APPLICATION_ADDRESS);
        return;
    }

    printf("Jumping to application at address 0x%08X\n\r", APPLICATION_ADDRESS);

    __disable_irq();

    // Stop SysTick (common crash source)
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;

    // Disable + clear all NVIC interrupts (bootloader leftovers)
    for (uint32_t i = 0; i < 8; i++) { // STM32F4 has up to 240 IRQs -> 8 regs
        NVIC->ICER[i] = 0xFFFFFFFFU;
        NVIC->ICPR[i] = 0xFFFFFFFFU;
    }

    // Set vector table to app
    SCB->VTOR = APPLICATION_ADDRESS;
    __DSB();
    __ISB();
    
    // Set MSP to app
    __set_MSP(app_msp);
    __DSB();
    __ISB();

    // Jump to app reset handler
    ((pFunction)app_reset)();

    // Should never reach here
    while (1);
}

int main(void)
{
    /* Initialize LEDs and Button. */
    board_led_init();
    board_button_init();

    /* Initialize USART */
    board_usart_init(UART_BAUDRATE);

    printf("Bootloader Started!\n\r");
    printf("Press button to wait for bootloader, or app will start in 3 seconds...\n\r");
    
    uint32_t timeout = 3000U;
    uint8_t button_pressed = 0;
    
    while (timeout > 0)
    {
        if (board_is_button_pressed())
        {
            button_pressed = 1;
            printf("Button pressed. Waiting for application upload...\n\r");
            break;
        }
        delay_ms(250);
        timeout -= 250;
        board_led_toggle(LED_GREEN);

        if (timeout % 1000 == 0)
        {
            
            printf("Starting application in %lu seconds...\n\r", timeout / 1000);
        }
    }
    
    if (!button_pressed)
    {
        board_led_on(LED_GREEN);
        jump_to_application();
    }
    
    while (1)
    {
        printf("Waiting in bootloader...\n\r");
        delay_ms(1000);
    }
    return 0;
}

