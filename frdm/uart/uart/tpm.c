#include "MKL46Z4.h"
#include "tpm.h"
#include "sonar.h"
#include "sLCD.h"
#include "ADC.h"

#define RedLED 1

void tpm_init(void){
	
		PORTD->PCR[5] = PORT_PCR_MUX(4);  //TPM0_CH5
		PORTE->PCR[29] = PORT_PCR_MUX(3); //TPM0_CH2 
	
		SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; //dolaczenie sygnalu taktujacego do modulu TMP

		SIM->SCGC5 |=  (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK); //dolaczenie sygnalu taktujacego do portu D i E, zrobione tez w leds initializze
	
	
		SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); // MCGFLLCLK clock or MCGPLLCLK/2
		SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; //MCGPLLCLK clock with fixed divide by two
	
		TPM0->MOD = TPM_MOD_MOD(4095); 
		TPM0->CNT |=  TPM_CNT_COUNT_SHIFT; //reset counter

		//edge aligned pwm
		
		TPM0->CONTROLS[2].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; //high true pulses
		TPM0->CONTROLS[5].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK; //low true pulses
		
		//edge aligned pwm end
		
		//center aligned PWM
		/*
		TPM0->CONTROLS[2].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; //high-true pulses
		TPM0->CONTROLS[5].CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; //low true pulses
		*/
		//center aligned PWM end
	
		TPM0->CONTROLS[2].CnV = TPM_CnV_VAL(0); //poczatkowa wartosc wspolczyynika wypelninia	
		TPM0->CONTROLS[5].CnV = TPM_CnV_VAL(0); //poczatkowa wartosc wspolczyynika wypelninia


		TPM0->SC = TPM_SC_PS(0x07) | TPM_SC_CPWMS_MASK | TPM_SC_CMOD(0x01); 
		//divide by 128 !!
		//upcounting
	  //increment every counter clock
}

