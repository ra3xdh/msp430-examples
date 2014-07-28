#include <msp430.h>
#include "stdint.h"
#include "adc.h"

void ADC_init_intref_repeating(uint16_t *buffer,uint16_t samples_cnt) // Init ADC single channel oneshot with internal reference 2.5V
{
    ADC10CTL0 &= ~ENC;
    ADC10CTL0 = MSC + // multiple samples
                SREF_1 +  // internal reference
                ADC10SHT_2 + // sample and hold time
		REF2_5V + // VREF = 2.5V
		REFON + // internal reference on
		ADC10ON; // ADC on
    ADC10CTL1 = INCH_5 + // channel 5 = P1.5
                SHS_0 +
		ADC10SSEL_0 + // ADC clock source = SMCLK
		ADC10DIV_0 + // No prescaler (1:1)
		CONSEQ_2; // repeating single channel mode
    ADC10AE0 = BIT5; // Enable P1.5 as analog input
    ADC10DTC0 = ADC10CT; // Contioniously transfer
    ADC10DTC1 = samples_cnt; // Number of conversion
    while (ADC10CTL1&BUSY);
    ADC10SA = (int) buffer; // Start address of buffer
    ADC10CTL0 |=ENC + ADC10SC; // Enable conversion
}



