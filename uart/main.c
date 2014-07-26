/*
 * This file is part of the MSP430 hardware UART example.
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 * Adapted by Vadim Kuznetsov<ra3xdh@gmail.com> in July 2014
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

/******************************************************************************
 * Hardware UART example for MSP430.
 *
 * Stefan Wendler
 * sw@kaltpost.de
 * http://gpio.kaltpost.de
 *
 * Echos back each character received. Blinks green LED in main loop. Toggles
 * red LED on RX.
 *
 * Use /dev/ttyACM0 at 9600 Bauds (and 8,N,1).
 *
 * Note: RX-TX must be swaped when using the MSPg2553 with the Launchpad! 
 *       You could easliy do so by crossing RX/TX on the jumpers of the 
 *       Launchpad.
 ******************************************************************************/

#include <msp430.h>
#include "uart.h"

#define LED_RED BIT0
#define LED_GREEN BIT6

void uart_rx_isr(unsigned char c) 
{
    switch (c) {
    case '1': P1OUT ^=LED_RED;
              uart_puts("Red led toggled\n");
              break;
    case '2': P1OUT ^= LED_GREEN;
              uart_puts("Green led toggled\n");
              break;
    default: break;
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

    for(;;);

}

