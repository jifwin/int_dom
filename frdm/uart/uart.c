#include "MKL46Z4.h"
#include "uart.h"
#include "leds.h"
#include "sLCD.h"
#include "intdom.h"

uint16_t display = 0;



void uart2_init(void){
	
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK ; 
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;  
	
	PORTE->PCR[16] = PORT_PCR_MUX(3);                    
	PORTE->PCR[17] = PORT_PCR_MUX(3);										

	UART2->C2 &= ~UART_C2_RE_MASK; // Receiver off
	UART2->C2 &= ~UART_C2_TE_MASK; // Transmitter off
	
	UART2->BDH |= UART_BDH_SBR(0);
	UART2->BDL |= UART_BDL_SBR(156); //BSR = 156
	
	UART2->BDH &= ~UART_BDH_SBNS_MASK; // One stop bit.
	
	UART2->C1 &= ~UART_C1_M_MASK; // Normal - start + 8 data bits (lsb first) + stop.
	UART2->C1 &= ~UART_C1_PE_MASK; // No hardware parity generation or checking.
	
	
	UART2->C2 |= UART_C2_RE_MASK; // Receiver on
	UART2->C2 |= UART_C2_TE_MASK; // Transmitter on
}


/* deprecated - instead receiving used in irq 
uint8_t uart2_receive(void)
{
	uint8_t  value;
	while(!(UART2->S1 & UART_S1_RDRF_MASK)) {}
	
	value = UART2->D;
	
	return value;
	
}
*/


void uart2_transmit(uint8_t value)
{
	while(!(UART2->S1 & UART_S1_TDRE_MASK)) {}
	
	UART2->D = value;
	
}

void UART2_IRQHandler() {
	uint8_t value = 0;

	while(!(UART2->S1 & UART_S1_RDRF_MASK)) {}
	value = UART2->D;
	
	if(value == 10) { // "\n" - end 
		
		//todo:
		
	}
	handle_event(value);
	//uart2_transmit(value);
	//10 - send ACK?
		
	
	
}

void display_on_lcd() {
	if(display_number(display,2) != 0) {
		display_error();
	}
}