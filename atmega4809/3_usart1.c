#define F_CPU 3333333
#define BAUD_RATE 19200
#include <avr/io.h>

void Usart1() {
    uint16_t baud_rate_value;
    char msg[] = "Hello world!\r\n";
    char *pChar;
    PORTB.DIR |= PIN0_bm; // (1 << 0); PORTB.0 = '1';
    baud_rate_value = (64 * (uint32_t)F_CPU) / (16 * (uint32_t)BAUD_RATE);
    USART3.BAUD = baud_rate_value;
    USART3.CTRLB |= USART3_TXEN_bm; // tx-only enable

    while(1) {
        pChar = msg;
        while (*pChar != 0) {
            while (!(USART3.STATUS & USART_DREIF_bm)); // wait for empty pipeline, polling, blocking transfer (not effective)
            USART3.TXDATAL = *pChar;
            pChar++;
        }

    }
}