#include "MKL46Z4.h"
#include "uart.h"
#include "leds.h"
#include "sLCD.h"

uint16_t display = 0;



void uart2_init(void){
	
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK ; // clock
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;  // clock
	
	PORTE->PCR[16] = PORT_PCR_MUX(3);                      /// ustawic !!
	PORTE->PCR[17] = PORT_PCR_MUX(3);											////
	
	//SPRAWDZIC TO!!
	
	
	
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

uint8_t uart2_receive(void)
{
	uint8_t  value;
	while(!(UART2->S1 & UART_S1_RDRF_MASK)) {}
	
	value = UART2->D;
	
	return value;
	
}

void uart2_transmit(uint8_t value)
{
	while(!(UART2->S1 & UART_S1_TDRE_MASK)) {}
	
	UART2->D = value;
	
}

void uart_leds(uint8_t blue){
	//if(blue=='G' || blue == 'g') ledsInitialize();
	//else if(blue=='R' || blue == 'r') ledsInitialize();
	ledsInitialize();

	
}

void UART2_IRQHandler() {
	uint8_t value = 0;

	while(!(UART2->S1 & UART_S1_RDRF_MASK)) {}
	value = UART2->D;
	
	uart2_transmit('5');
	
		
	if((value >= '0' && value <= '9') || value == 10) {
		if(value == 10) { //10 - new line in ASCII (will be treated as termination char)
			display_on_lcd();
			display = 0;
			
		}
		else {
			display = display*10+(value-'0'); //'0' - 48 ascii 
		}
}
	else {
		display = 10000; //error if incorrect char
	}
	
	//dopisac jeszce sprawdzenie czy jest liczba!

		
	if(value == '1') {
	FPTD->PTOR = 1UL<<5;

	}
	
	if(value == '0') {
	FPTE->PTOR = 1UL<<29;
	}
	
}

void display_on_lcd() {
	if(display_number(display,2) != 0) {
		display_error();
	}

}