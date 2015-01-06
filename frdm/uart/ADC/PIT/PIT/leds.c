#include "MKL46Z4.h"                    //Device header
#include "leds.h"

const uint32_t green_mask= 1UL<<5;				//Red led is Port D bit 5
const uint32_t red_mask= 1UL<<29;			//Green led is Port E bit 29/
const uint32_t one_mask= 1UL<<1;			//Green led is Port E bit 29/

void ledsInitialize(void) {
volatile int delay;
	
//Initialize registers	
  SIM->SCGC5 |=  (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);      /* Enable Clock to Port D & E */ 
  PORTD->PCR[5] = PORT_PCR_MUX(1);                       /* Pin PTD5 is GPIO */
  PORTE->PCR[29] = PORT_PCR_MUX(1);                      /* Pin PTE29 is GPIO */

  
	FPTD->PSOR = green_mask	;          /* switch Red LED off - dioda sie WLACZA gdy na porcie jest 0*/
	FPTE->PSOR = red_mask	;        /* switch Green LED off */

	
	FPTD->PDDR = green_mask	;          /* enable PTB18/19 as Output */
	FPTE->PDDR = red_mask	;        /* enable PTB18/19 as Output */ //konfiguracja portu E, pin 29 jako wyjscie

	


////Welcome sequence
	for(delay=0; delay<1200000; delay++);
	FPTD->PCOR = green_mask	;          /* switch Red LED on = aktywacja diody wpisaniem 0 do pinow diod */
	FPTE->PCOR = red_mask	;        /* switch Green LED on */
	for(delay=0; delay<1200000; delay++);
	FPTD->PSOR = green_mask	;          /* switch Red LED off */
	FPTE->PSOR = red_mask	;        /* switch Green LED off */
	for(delay=0; delay<1200000; delay++);
	FPTD->PCOR = green_mask	;          /* switch Red LED on */
	FPTE->PCOR = red_mask	;        /* switch Green LED on */
	for(delay=0; delay<1200000; delay++);
	FPTD->PSOR = green_mask	;          /* switch Red LED off */
	FPTE->PSOR = red_mask	;        /* switch Green LED off */

}
