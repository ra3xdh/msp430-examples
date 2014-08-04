/*
 * This file is part of the MSP430 hardware UART example.
 *
 * Copyright (C) 2014 Vadim Kuznetsov<ra3xdh@gmail.com> 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* ADC single channel mode demo program
   Echos to UART voltage in mV on P1.5 pin
   if "3" is sent */

#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "adc.h"

#define LED_RED BIT0
#define LED_GREEN BIT6

#define SAMPLES_CNT 4
#define CHANNELS_CNT 8

uint16_t adc[SAMPLES_CNT][CHANNELS_CNT];

void uart_rx_isr(unsigned char c) 
{
    uint16_t mV=0; // Volatge in mV
    uint32_t adc_avg=0; // ADC average
    int i=0;

    switch (c) {
    case '1': P1OUT ^=LED_RED;
              uart_puts("Red led toggled\n");
              break;
    case '2': P1OUT ^= LED_GREEN;
              uart_puts("Green led toggled\n");
              break;
    case '3': adc_avg=0;
              for (i=0;i<SAMPLES_CNT;i++) { // Perform averaging
                 adc_avg += adc[i][((CHANNELS_CNT-1)-5)]; 
              }
	      adc_avg /= SAMPLES_CNT;
              mV = (adc_avg*2500)/1024;
	      //for (i=0;i<7;i++) printf("ADC[%d]=%d\n",i,adc[i]);
              printf("P1.5 pin voltage = %d mV\n",mV);
	      break;
    default:  uart_putc(c);
              break;
    }
}
 
/**
 * Main routine
 */
int main(void)
{
    WDTCTL  = WDTPW + WDTHOLD; 	// Stop WDT
    BCSCTL1 = CALBC1_1MHZ;      // Set DCO
    DCOCTL  = CALDCO_1MHZ;
 
    P1DIR  = BIT0 + BIT6; 		// P1.0 and P1.6 are the red+green LEDs	
    P1OUT  = BIT0 + BIT6; 		// All LEDs off

    uart_init();

	// register ISR called when data was received
    uart_set_rx_isr_ptr(uart_rx_isr);

    __bis_SR_register(GIE);

    uart_puts("\n***************\n");
    uart_puts("MSP430 harduart\n");
    uart_puts("***************\n");

    ADC_init_intref_multichannel((uint16_t *)adc,SAMPLES_CNT*CHANNELS_CNT); // Init ADC

    __bis_SR_register(LPM0_bits+GIE); // Go to sleep

    for(;;); // For debug

}

