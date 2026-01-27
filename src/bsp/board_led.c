#include "bsp/board_led.h"


void board_led_init(void)
{
    // Enable GPIOB clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Configure PB0 as output (LED_GREEN)
    GPIOB->MODER |= GPIO_MODER_MODER0_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER0_1;

    // Configure PB7 as output (LED_BLUE)
    GPIOB->MODER |= GPIO_MODER_MODER7_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER7_1;

    // Configure PB14 as output (LED_RED)
    GPIOB->MODER |= GPIO_MODER_MODER14_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER14_1;
}

void board_led_on(led_color_t color)
{
    switch (color)
    {
        case LED_GREEN:
            GPIOB->BSRR = GPIO_BSRR_BS0;   // Set PB0
            break;
        case LED_BLUE:
            GPIOB->BSRR = GPIO_BSRR_BS7;   // Set PB7
            break;
        case LED_RED:
            GPIOB->BSRR = GPIO_BSRR_BS14;  // Set PB14
            break;
        default:
            break;
    }
}

void board_led_off(led_color_t color)
{
    switch (color)
    {
        case LED_GREEN:
            GPIOB->BSRR = GPIO_BSRR_BR0;   // Reset PB0
            break;
        case LED_BLUE:
            GPIOB->BSRR = GPIO_BSRR_BR7;   // Reset PB7
            break;
        case LED_RED:
            GPIOB->BSRR = GPIO_BSRR_BR14;  // Reset PB14
            break;
        default:
            break;
    }
}

void board_led_toggle(led_color_t color)
{
    switch (color)
    {
        case LED_GREEN:
            GPIOB->ODR ^= GPIO_ODR_OD0;    // Toggle PB0
            break;
        case LED_BLUE:
            GPIOB->ODR ^= GPIO_ODR_OD7;    // Toggle PB7
            break;
        case LED_RED:
            GPIOB->ODR ^= GPIO_ODR_OD14;   // Toggle PB14
            break;
        default:
            break;
    }
}