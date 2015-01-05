#include "MKL46Z4.h"     
#include "leds.h"
#include "uart.h"
#include "sLCD.h"


/* zad 1 */
/*int main (void) {
	char a;
	uart2_init();

	
	while(1){

		a = uart2_receive();
		uart2_transmit(a);
		
	};

}
*/
/* zad 2 */

int main (void) {
	
	uart2_init();

	sLCD_Init();
	ledsInitialize();
	
	UART2->C2 |= UART_C2_RIE_MASK;
	
	NVIC_ClearPendingIRQ(UART2_IRQn);				
		NVIC_EnableIRQ(UART2_IRQn);						
		NVIC_SetPriority (UART2_IRQn, 3);			
	
	while(1){

		
	};

}
