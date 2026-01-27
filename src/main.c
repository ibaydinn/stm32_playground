#include "bsp/board_led.h"



int main(void)
{
    /* Set BLUE LED on at startup. So I can see that code is started to run. */
    board_led_init();
    board_led_on(LED_GREEN);

    while (1)
    {

    }


    return 0;
}

