#include "leds.h"

void uart2_init(void);
void uart2_transmit(uint8_t value);
void uart_leds(uint8_t blue);
void UART2_IRQHandler();
void display_on_lcd();