#include "MKL46Z4.h"

#define PIT_Number PIT_IRQn

void pit_init(void);
void PIT_IRQHandler(void);
void faster(void);
void slower(void);
void pit_change(void);