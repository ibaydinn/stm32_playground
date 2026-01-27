#include "bsp/board_led.h"


void board_led_init(void)
{
    // Enable GPIOB clock
    BOARD_LED_PERIPHERAL_BUS |= BOARD_LED_GPIO_CLOCK_EN;

    // Configure PB0 as output (LED_GREEN)
    BOARD_LED_GPIO_PORT->MODER |= 0x1U << (BOARD_LED_GREEN_PIN * 2);
    BOARD_LED_GPIO_PORT->MODER &= ~(0x2U << (BOARD_LED_GREEN_PIN * 2));

    // Configure PB7 as output (LED_BLUE)
    BOARD_LED_GPIO_PORT->MODER |= 0x1U << (BOARD_LED_BLUE_PIN * 2);
    BOARD_LED_GPIO_PORT->MODER &= ~(0x2U << (BOARD_LED_BLUE_PIN * 2));


    // Configure PB14 as output (LED_RED)
    BOARD_LED_GPIO_PORT->MODER |= 0x1U << (BOARD_LED_RED_PIN * 2);
    BOARD_LED_GPIO_PORT->MODER &= ~(0x2U << (BOARD_LED_RED_PIN * 2));
}

void board_led_on(led_color_t color)
{
    switch (color)
    {
        case LED_GREEN:
            BOARD_LED_GPIO_PORT->BSRR = 0x1U << BOARD_LED_GREEN_PIN;   // Set PB0
            break;
        case LED_BLUE:
            BOARD_LED_GPIO_PORT->BSRR = 0x1U << BOARD_LED_BLUE_PIN;   // Set PB7
            break;
        case LED_RED:
            BOARD_LED_GPIO_PORT->BSRR = 0x1U << BOARD_LED_RED_PIN;  // Set PB14
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
            BOARD_LED_GPIO_PORT->BSRR = 0x1U << (BOARD_LED_GREEN_PIN + 16);   // Reset PB0
            break;
        case LED_BLUE:
            BOARD_LED_GPIO_PORT->BSRR = 0x1U << (BOARD_LED_BLUE_PIN + 16);   // Reset PB7
            break;
        case LED_RED:
            BOARD_LED_GPIO_PORT->BSRR = 0x1U << (BOARD_LED_RED_PIN + 16);  // Reset PB14
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
            BOARD_LED_GPIO_PORT->ODR ^= 0x1U << BOARD_LED_GREEN_PIN;    // Toggle PB0
            break;
        case LED_BLUE:
            BOARD_LED_GPIO_PORT->ODR ^= 0x1U << BOARD_LED_BLUE_PIN;    // Toggle PB7
            break;
        case LED_RED:
            BOARD_LED_GPIO_PORT->ODR ^= 0x1U << BOARD_LED_RED_PIN;   // Toggle PB14
            break;
        default:
            break;
    }
}