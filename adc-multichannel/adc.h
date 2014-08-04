#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ADC_init_intref_multichannel(uint16_t *buffer,uint16_t samples_cnt); // Init ADC single channel repeating with internal reference 2.5V

#endif

