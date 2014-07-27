#ifndef ADC_H
#define ADC_H

void ADC_init_intref(void); // Init ADC single channel oneshot with internal reference 2.5V
uint16_t getADC(void);

#endif

