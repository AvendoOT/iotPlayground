#define F_CPU 3333333
#define BAUD_RATE 19200

#include <avr/io.h>
#include <stdio.h>

void UsartExample4() {
    char c;
    PORTB.DIR |= PIN0_bm;
    USART3.BAUD = ((uint32_t)F_CPU * 64) / (16 * (uint32_t)BAUD_RATE);
    USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm; // TX and RX enable
    while (1) {
        while (!(USART3.STATUS & USART_RXCIF_bm)); // cekaj znak, blokirajuci poziv
        c = USART3.RXDATAL;
        while (!(USART3.STATUS & USART_DREIF_bm));
        USART3.TXDATAL = c;
    }
}