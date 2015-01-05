#include "MKL46Z4.h"  
#include "intdom.h"
#include "leds.h"

extern const uint8_t events[NUM_OF_EVENTS] =  {'A', 'B', 'C', 'D' };
extern const FGPIO_Type * PORTS[NUM_OF_EVENTS] =  {FPTA_BASE, FPTA_BASE, FPTA_BASE, FPTA_BASE };
extern const uint32_t pin_number[NUM_OF_EVENTS] =  {1, 1, 1, 1};	


void handle_event(uint8_t value) {
	

	ledsInitialize();
	
	
}

void configure_pins() {
	unsigned delay = 0;
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK;      /* Enable Clock to Port A */
  PORTA->PCR[1] = PORT_PCR_MUX(1);                       /* Pin PTA5 is GPIO */
	FPTA->PDDR = 1UL << 1;        //output
	FPTA->PSOR = 1UL << 1; 
	
	while(1) {
		for(delay=0; delay<12000; delay++);
		FPTA->PTOR = 1UL << 1; 
	}
	

	
	
}