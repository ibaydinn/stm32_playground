#include "bsp/board_button.h"

void board_button_init(void) 
{
    // Enable GPIOC clock
    BOARD_BUTTON_PERIPHERAL_BUS |= BOARD_BUTTON_GPIO_CLOCK_EN;

    // Configure PC13 as input (User Button)
    BOARD_BUTTON_GPIO_PORT->MODER &= ~(0x3U << (BOARD_BUTTON_PIN * 2)); // Set to input mode
}

bool board_read_button_states(void) 
{
    // Read the state of the button pin
    // return (BOARD_BUTTON_GPIO_PORT->IDR & (1U << BOARD_BUTTON_PIN)) == 0; // Active low

    if ((BOARD_BUTTON_GPIO_PORT->IDR & (1U << BOARD_BUTTON_PIN)) == 0) {
        return false; // Button is not pressed
    } else {
        return true; // Button is pressed
    }
}