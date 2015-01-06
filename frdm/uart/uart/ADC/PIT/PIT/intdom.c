#include "MKL46Z4.h"  
#include "intdom.h"
#include "leds.h"

//using PORTD!
//00 - CHECK
//01 - ON
//10 - OFF
//11 - TOGGLE


void handle_event(uint8_t value) {
	
	uint8_t function_number = 0;
	uint8_t device_number = 0;
	
	value = value - 'A'; //start conuting from 0
	function_number = value % 4; // 4 - liczba funkcji  
	device_number = value/4; // przesuniecie w prawo (pominiecie dwoch ostatnich bitow) = numer pinu
	
	//convert to port numbers
	device_number = (device_number+1)*2;
	
	FPTD->PTOR = 1UL << device_number;

	
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