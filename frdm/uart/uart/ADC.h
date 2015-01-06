#include "MKL46Z4.h"
#define ADC0_Number ADC0_IRQn

int ADC_calibrate(void);
void ADC_init(void);
void avg_ADCresult(void);
void ADC0_IRQHandler(void);
int ADCresult(void);
void print_avg_ADCresult(void);
void print_ADCresult(void);
uint32_t getValue();
