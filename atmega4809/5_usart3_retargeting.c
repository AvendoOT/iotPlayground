#define F_CPU 3333333
#define BAUD_RATE 19200

#include <avr/io.h>
#include <stdio.h>

int usart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

int usart_putchar(char c, FILE *stream) { // retarget funkcija
    while (!(USART3.STATUS & USART_DREIF_bm));
    USART3.TXDATAL = c;
    return 0;
}

void UsartExample3() {
    int i;
    stdout = &mystdout;
    PORTB.DIR |= PIN0_bm;
    USART3.BAUD = ((uint32_t)F_CPU * 64) / (16 * (uint32_t)BAUD_RATE);
    USART3.CTRLB |= USART_TXEN_bm;
    i = 1;
    while (1) {
        printf("cnt = %d\r\n", i); // stdout je usart_putchar
        i++;
    }
}