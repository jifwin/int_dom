#include "MKL46Z4.h"     
#include "pit.h"
#include "tpm.h"
#include "sLCD.h"
#include "ADC.h"

uint32_t adc_value = 0;

void ADC0_IRQHandler(void)
{
		int value = (int)(ADC0->R[0]);
		sLCD_convert(value,1);
		adc_value = value;
		ADC0->SC1[0] |= ADC_SC1_ADCH(3);
			
}
		
uint32_t getValue() {
	return adc_value;
}
	

int ADC_calibrate(void){

	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; //dolaczenie sygnalu taktujacego do modulu A/C
	
	ADC0->CFG1 |= ADC_CFG1_ADICLK(0); //zrodlo sygnalu zegarowego - Bus Clock
	ADC0->CFG1 |= ADC_CFG1_ADIV(3);   //wartosc dzielnika The divide ratio is 8 and the clock rate is (input clock)/8.
	ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK; //dlugi czas probkowania
	
	ADC0->CFG2 |= ADC_CFG2_ADHSC_MASK; //High-speed conversion sequence selected with 2 additional ADCK cycles to total conversion time.
	ADC0->CFG2 |= ADC_CFG2_ADLSTS(3); //2 extra ADCK cycles; 6 ADCK cycles total sample time.
	
	ADC0->SC2 |= ADC_SC2_REFSEL(0); //zewnetrzne zrodlo referencyjne
	ADC0->SC3 |= ADC_SC3_AVGE_MASK; //usrednianie sprzetowe
	ADC0->SC3 |= ADC_SC3_AVGS(3); //wartosc maksymalna
	ADC0->SC3 |= ADC_SC3_CAL_MASK; //rozpoczecie kalibracji
	
	
	while((ADC0->SC3 & ADC_SC3_CAL_MASK) != 0); //wait for CAL to be 0
	if ((ADC0->SC3 & ADC_SC3_CALF_MASK) == 0) return 0; //sucessfull
	return 1; //error
}

void ADC_init(void)
{

	uint16_t sum = 0;
	if(!ADC_calibrate()){ //success
		
		sum = ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4 + ADC0->CLPS + ADC0->CLPD; // czy 32 bity czy 16 czy 9
		sum /= 2;
		sum |= 1 << 15u; 
		ADC0->PG = ADC_PG_PG(sum);  
		

		sum = ADC0->CLMD + ADC0->CLMS + ADC0->CLM4 + ADC0->CLM3 + ADC0->CLM2 + ADC0->CLM1 + ADC0->CLM0;
		sum /= 2;
		sum |= 1 << 15u; 		
		ADC0->MG = ADC_MG_MG(sum);
		
		ADC0->CFG1 |= ADC_CFG1_ADICLK(1); 		//BusClock/2
		ADC0->CFG1 |= ADC_CFG1_ADIV(0); 			//divide 1
		ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK; 	//Long sampling
		ADC0->CFG1 = ADC_CFG1_MODE(1); 				//When DIFF=0:It is single-ended 12-bit conversion
		ADC0->SC1[0] &= ~ADC_SC1_DIFF_MASK; 	//DIFF=0
		
		ADC0->SC1[0] = ADC_SC1_ADCH(3)| ADC_SC1_AIEN_MASK;	 //przerwanie aktywne DADP3 is selected as input;
		
		NVIC_ClearPendingIRQ(ADC0_Number); //Enable interrupt
		NVIC_EnableIRQ(ADC0_Number);			 //Enable interrupt
	}
	
}

	