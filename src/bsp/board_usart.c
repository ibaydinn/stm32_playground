#include "bsp/board_usart.h"

/* Static Internal Functions */
uint16_t __calculate_usart_div(uint32_t peripheral_clock, uint32_t baudrate)
{
    // USARTDIV = Fck / (16 * Baudrate)
    uint32_t usartdiv_mul16 = (peripheral_clock + (baudrate/2U)) / baudrate; // ~= 16*USARTDIV with rounding
    return (uint16_t)usartdiv_mul16;
}

/* Public Functions */
void board_usart_init(uint32_t baudrate)
{
    // Enable GPIO clock
    BOARD_USART_GPIO_ERIPHERAL_BUS |= BOARD_USART_GPIO_CLOCK_EN;

    // Configure TX Pin as Alternate Function
    BOARD_USART_TX_GPIO_PORT->MODER &= ~(0x3U << (BOARD_USART_TX_GPIO_PIN * 2)); // Clear mode bits
    BOARD_USART_TX_GPIO_PORT->MODER |= (0x2U << (BOARD_USART_TX_GPIO_PIN * 2));  // Set to Alternate Function mode

    // Configure RX Pin as Alternate Function
    BOARD_USART_RX_GPIO_PORT->MODER &= ~(0x3U << (BOARD_USART_RX_GPIO_PIN * 2)); // Clear mode bits
    BOARD_USART_RX_GPIO_PORT->MODER |= (0x2U << (BOARD_USART_RX_GPIO_PIN * 2));  // Set to Alternate Function mode 

    // Set Alternate Function to for RX and TX pins
    BOARD_USART_TX_GPIO_PORT->AFR[BOARD_USART_TX_GPIO_PIN >> 3] &= ~(0xFU << ((BOARD_USART_TX_GPIO_PIN & 0x7U) * 4));
    BOARD_USART_TX_GPIO_PORT->AFR[BOARD_USART_TX_GPIO_PIN >> 3] |= (BOARD_USART_AF << ((BOARD_USART_TX_GPIO_PIN & 0x7U) * 4));
    
    BOARD_USART_RX_GPIO_PORT->AFR[BOARD_USART_RX_GPIO_PIN >> 3] &= ~(0xFU << ((BOARD_USART_RX_GPIO_PIN & 0x7U) * 4));
    BOARD_USART_RX_GPIO_PORT->AFR[BOARD_USART_RX_GPIO_PIN >> 3] |= (BOARD_USART_AF << ((BOARD_USART_RX_GPIO_PIN & 0x7U) * 4));

    // Enable USART clock
    BOARD_USART_PERIPHERAL_BUS |= BOARD_USART_UART_CLOCK_EN;

    // Configure USART parameters
    BOARD_USART->CR1 = 0; // Clear control register

    // Set baud rate
    uint32_t peripheral_clock = BOARD_USART_BUS_CLOCK_HZ; // Assuming APB1 runs at system clock frequency
    uint16_t usartdiv = __calculate_usart_div(peripheral_clock, baudrate);

    BOARD_USART->BRR = usartdiv;

    // Enable Transmitter and Receiver
    BOARD_USART->CR1 |= USART_CR1_TE | USART_CR1_RE;

    // Enable USART
    BOARD_USART->CR1 |= USART_CR1_UE;
}

void board_uart_write(char data)
{
    // Wait until transmit data register is empty
    while (!(BOARD_USART->SR & USART_SR_TXE));

    // Send data
    BOARD_USART->DR = (data & 0xFF);
}

char board_uart_read(void)
{
    // Wait until receive data register is not empty
    while (!(BOARD_USART->SR & USART_SR_RXNE));

    // Read data
    return (char)(BOARD_USART->DR & 0xFF);
}

// Retargeting printf to USART
int __io_putchar(int ch)
{
    board_uart_write((char)ch);
    return ch;
}

int __io_getchar(void)
{
    return (int)board_uart_read();
}