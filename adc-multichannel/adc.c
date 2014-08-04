#include <msp430.h>
#include "stdint.h"
#include "adc.h"

void ADC_init_intref_multichannel(uint16_t *buffer,uint16_t samples_cnt) // Init ADC single channel oneshot with internal reference 2.5V
{
    ADC10CTL0 &= ~ENC;
    ADC10CTL0 = MSC + // multiple samples
                SREF_1 +  // internal reference
                ADC10SHT_2 + // sample and hold time
		REF2_5V + // VREF = 2.5V
		REFON + // internal reference on
		ADC10ON + // ADC on
		ADC10IE;
    	
    ADC10CTL1 = INCH_7 + // scan all ADC inputs from A0 to A7
                SHS_0 +
		ADC10SSEL_0 + // ADC clock source = SMCLK
		ADC10DIV_0 + // No prescaler (1:1)
		CONSEQ_3; // repeating multichannel channel mode
    ADC10AE0 = BIT4+BIT5+BIT7; // Enable P1.5 as analog input
    ADC10DTC0 = ADC10CT; // Contioniously transfer
    ADC10DTC1 = samples_cnt; // Number of conversion = channels_count * samples_count
    //while (ADC10CTL1&BUSY);
    ADC10SA = (int) buffer; // Start address of buffer
    ADC10CTL0 |=ENC + ADC10SC; // Enable conversion
}



