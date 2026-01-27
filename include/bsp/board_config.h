#ifndef BSP__BOARD_CONFIG_H_
#define BSP__BOARD_CONFIG_H_

// Include board-specific configurations here
#ifndef STM32F429xx
    #error "This board configuration is for STM32F429xx series only."
#endif

#include "stm32f4xx.h"

// Define system clock frequency
#define SYSTEM_CLOCK_FREQUENCY_HZ    16000000  // 16 MHz for STM32F429ZI

/************************ LED configuration ************************/
// Nucleo F429ZI onboard LEDs are connected to GPIOB pins 0, 7, and 14
#define BOARD_LED_GPIO_PORT             GPIOB
#define BOARD_LED_GREEN_PIN             0
#define BOARD_LED_BLUE_PIN              7
#define BOARD_LED_RED_PIN               14
#define BOARD_LED_GPIO_CLOCK_EN         RCC_AHB1ENR_GPIOBEN
#define BOARD_LED_PERIPHERAL_BUS        RCC->AHB1ENR
/***************************************************************/


/************************ USART configuration ************************/
// Nucleo F429ZI onboard usart is usart3 with TX on PD8 and RX on PD9
#define BOARD_USART                     USART3
#define BOARD_USART_TX_GPIO_PORT        GPIOD
#define BOARD_USART_TX_GPIO_PIN         8
#define BOARD_USART_RX_GPIO_PORT        GPIOD
#define BOARD_USART_RX_GPIO_PIN         9

#define BOARD_USART_GPIO_CLOCK_EN       RCC_AHB1ENR_GPIODEN
#define BOARD_USART_UART_CLOCK_EN       RCC_APB1ENR_USART3EN 

#define BOARD_USART_AF                  7  // AF7 for USART3 on PD8 and PD9
#define BOARD_USART_BUS_CLOCK_HZ        SYSTEM_CLOCK_FREQUENCY_HZ  // Assuming APB1 runs at system clock frequency
#define BOARD_USART_GPIO_ERIPHERAL_BUS  RCC->AHB1ENR
#define BOARD_USART_PERIPHERAL_BUS      RCC->APB1ENR
/***************************************************************/


#endif // BSP__BOARD_CONFIG_H_