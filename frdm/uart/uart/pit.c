#include "MKL46Z4.h"
#include "pit.h"
#include "tpm.h"
#include "sLCD.h"
#include "ADC.h"

/*
void PIT_IRQHandler(void){
	double sensor_value = adc_avg()/4096*3;
	double temperature = 25-(sensor_value-(240/4095*3))/1.769;
	sLCD_convert((int)temperature,1);
	
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}
*/

/*
void pit_init(void){

	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK; 
	PIT->CHANNEL[0].LDVAL = 2431385;//100ms, 24mhz clock

	NVIC_ClearPendingIRQ(PIT_Number);				
	NVIC_EnableIRQ(PIT_Number);						
	NVIC_SetPriority (PIT_Number, 3);			

	PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; //Turn on interrupts for PIT and enable whole timer	

	PIT->MCR = 0x00;

}
*/