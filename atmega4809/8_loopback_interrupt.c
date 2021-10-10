#define F_CPU 3333333
#define BAUD_RATE 19200

#include <avr/io.h>


#define USART3_RXC_INTERRUPT USART3.STATUS & USART_RXCIF_bm
#define USART3_RXC_CLEAR_INTERRUPT_FLAG USART3.STATUS |= USART_RXCIF_bm

ISR(USART3_RXC_vect) {
    uint8_t c;
    if (USART3_RXC_INTERRUPT) {
        c = USART3.RXDATAL;
        USART3_RXC_CLEAR_INTERRUPT_FLAG;
        USART3.TXDATAL = c;
    }
}

void main() {
    PORTB.DIR |= PIN0_bm;
    USART3.BAUD = ((uint32_t)F_CPU) / (16 * (uint32_t)BAUD_RATE);
    USART3.CTRLA |= USART_RXCIE_bm; // enable ISR for USART.RX event
    USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
    sei();
    while (1);
}