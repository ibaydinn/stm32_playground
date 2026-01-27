#ifndef BSP__BOARD_BUTTON_H
#define BSP__BOARD_BUTTON_H

#include "bsp/board_config.h"
#include <stdbool.h>

// Function to initialize the user button
void board_button_init(void);

// Function to check if the user button is pressed
bool board_read_button_states(void);



#endif // BSP__BOARD_BUTTON_H