#include "MKL46Z4.h"  
#include "intdom.h"
#include "leds.h"

//using PORTD!

unsigned int pin_states[3] = {1, 1, 1}; //temporary?

void handle_event(uint8_t value) {
	
	uint8_t function_number = 0;
	uint8_t device_number = 0;
	unsigned int shift = 0;
	unsigned int delay = 0;
	uint8_t index = 0;
	
	if(value == 128) { //128 == refresh all
		
			send_refresh();
		
	}
	else if(value != '\n') {
	value = value - 'A'; //start conuting from 0
	function_number = value % 4; // 4 - liczba funkcji  
	index = device_number = value/4; // przesuniecie w prawo (pominiecie dwoch ostatnich bitow) = numer pinu
	
	//convert to port numbers
	device_number = (device_number+1)*2;
	
	shift = 1UL << device_number;
	
	switch(function_number) {
		case 0: 
			FPTD->PTOR |= shift;
			for(delay=0; delay<3600000; delay++);
			FPTD->PTOR |= shift;
			break;
		
		case 1:
			FPTD->PCOR |= shift;
			pin_states[index] = 0;
			break;
		
		case 2:
			FPTD->PSOR |= shift;
			pin_states[index] = 1;
			break;
		
		case 3:
			FPTD->PTOR |= shift;
			pin_states[index] = ((pin_states[index] == 1) ? 0 : 1); // invert
			break;
	}
	
	//00 - MRUG
	//01 - ON
	//10 - OFF
	//11 - TOGGLE
	
	send_ack();
	}	
}
	

void send_refresh() {
	uint8_t i = 0;
	uart2_transmit('R');
	for(i = 0; i < sizeof(pin_states); i++) {
		uart2_transmit(pin_states[i]);
	}
	uart2_transmit('\n');
}

void send_ack() {
	uart2_transmit('X');
}	




void configure_pins() {
	unsigned delay = 0;
	SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK;      
  PORTD->PCR[2] = PORT_PCR_MUX(1);                       
	PORTD->PCR[4] = PORT_PCR_MUX(1);                       /* Pin PTA5 is GPIO */
	PORTD->PCR[6] = PORT_PCR_MUX(1);                       /* Pin PTA5 is GPIO */
	
	FPTD->PDDR |= (1UL << 2 | 1UL << 4 | 1UL << 6);        //output
	FPTD->PSOR |= (1UL << 2 | 1UL << 4 | 1UL << 6);

	
}