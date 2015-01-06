#include "MKL46Z4.h"
#include "sonar.h"
#include "tpm.h"
#include "sLCD.h"



void sonar_init(void){
	
		SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK; // podanie zegara na PIT
		//SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; // podanie zegara na portB
		SIM->SOPT2 |= SIM_SOPT2_TPMSRC(0x3); // 2.4 multipurpose clock 
	
		PORTC->PCR[0] |= PORT_PCR_MUX(3);   // echo
		PORTC->PCR[1] |= PORT_PCR_MUX(3); 	// trigger
	
		NVIC_ClearPendingIRQ(TPM_Number);
		NVIC_EnableIRQ(TPM_Number);
		
	
		MCG->C1 |= MCG_C1_IRCLKEN_MASK; // 2.5
		MCG->C1 |= MCG_C1_IREFS_MASK; // 2.5
	
		// External reference clock is selected. f = 4 MHz
		MCG->C2 |= MCG_C2_IRCS_MASK;
	
	
				// Clock prescale
////		0 Divide by 1
////		1 Divide by 2
////		2 Divide by 4
////		3 Divide by 8
////		4 Divide by 16
////		5 Divide by 32
////		6 Divide by 64
////		7 Divide by 128
		TPM1->SC = TPM_SC_PS(0x04); 
				 
	
		TPM1->SC |= TPM_SC_CMOD(0x01) ;// TPM counter increments on every TPM counter clock
		TPM1->SC &= ~TPM_SC_CPWMS_MASK ; // upcounting mode
	
		// counter MOD value
		TPM1->MOD = TPM_MOD_MOD(20000); // 
	
		TPM1->CNT |=  TPM_CNT_COUNT_SHIFT ; //  clear register
		
		TPM1->CONTROLS[0].CnSC &= ~TPM_CnSC_MSA_MASK; // capture on falling and raising edge
		TPM1->CONTROLS[0].CnSC &= ~TPM_CnSC_MSB_MASK; // 
		TPM1->CONTROLS[0].CnSC |= TPM_CnSC_ELSB_MASK; // 
		TPM1->CONTROLS[0].CnSC |= TPM_CnSC_ELSA_MASK; // 
		TPM1->CONTROLS[0].CnSC |= TPM_CnSC_CHIE_MASK ;
	
		TPM1->CONTROLS[1].CnSC |= TPM_CnSC_MSA_MASK; // Pulse Output high on match
		TPM1->CONTROLS[1].CnSC |= TPM_CnSC_MSB_MASK; // Pulse Output high on match
		TPM1->CONTROLS[1].CnSC &= ~TPM_CnSC_ELSB_MASK; // Pulse Output high on match p. 569
		TPM1->CONTROLS[1].CnSC |= TPM_CnSC_ELSA_MASK; // Pulse Output high on match
		TPM1->CONTROLS[1].CnSC |= TPM_CnSC_CHIE_MASK ;
		
		// output pulse time = 10 us
		TPM1->CONTROLS[1].CnV = TPM_CnV_VAL(10);  
		
		TPM1->CONF |= TPM_CONF_TRGSEL(0x0000); /// External trigger pin input (EXTRG_IN)
	
}


