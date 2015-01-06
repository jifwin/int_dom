#include "MKL46Z4.h"  

#define NUM_OF_EVENTS 4
#define ACTIONS_PER_PIN 4


	
	void configure_pins();
	void handle_event(uint8_t value);