#include <msp430.h>
#include "stdint.h"
#include "adc.h"

void ADC_init_intref(void) // Init ADC single channel oneshot with internal reference 2.5V
{
    ADC10CTL0 &= ~ENC;
    ADC10CTL0 = SREF_1 +  // internal reference
                ADC10SHT_2 + // sample and hold time
		REF2_5V + // VREF = 2.5V
		REFON + // internal reference on
		ADC10ON; // ADC on
    ADC10CTL1 = INCH_5 + // channel 5 = P1.5
                SHS_0 +
		ADC10SSEL_0 + // ADC clock source = SMCLK
		ADC10DIV_0 + // No prescaler (1:1)
		CONSEQ_0; // single channel mode
    ADC10AE0 = BIT5; // Enable P1.5 as analog input
    ADC10CTL0 |=ENC; // Enable conversion
}

uint16_t getADC(void)
{
    ADC10CTL0 |= ADC10SC; // Strat conversion
    while (ADC10CTL1&ADC10BUSY); // Wait while ADc is not ready
    return ADC10MEM; // return ADC result
}

