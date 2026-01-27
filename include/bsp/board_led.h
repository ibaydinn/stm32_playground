#ifndef BSP__BOARD_LED_H__
#define BSP__BOARD_LED_H__

#include "bsp/board_config.h"


// LED Colors
typedef enum
{
    LED_GREEN = 0,          // PB0
    LED_BLUE,               // PB7
    LED_RED,                // PB14
} led_color_t;


void board_led_init(void);
void board_led_on(led_color_t color);
void board_led_off(led_color_t color);
void board_led_toggle(led_color_t color);


#endif // BSP__BOARD_LED_H__