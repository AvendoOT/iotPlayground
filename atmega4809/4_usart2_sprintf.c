#define F_CPU 3333333
#define BAUD_RATE 19200

#include <avr/io.h>
#include <stdio.h>

void sendSingleCharacter(char data) { // blokirajuce slanje jednog znaka
    while (!(USART3.STATUS & USART3_DREIF_bm));
    USART3.TXDATAL = data;
}

void print_usart(char *msg) {
    while (*msg) {
        sendSingleCharacter(*msg);
        msg++;
    }
}

void UsartExample2() {
    char msg[64];
    char *pChar;
    int i;
    
    PORTB.DIR |= PIN0_bm;
    USART3.BAUD = ((uint32_t)F_CPU * 64) / (16 * (uint32_t)BAUD_RATE);
    USART3.CTRLB |= USART_TXEN_bm;
    i = 1;
    pChar = msg;
    while (1) {
        sprintf(msg, "cnt = %d\r\n", i);
        print_usart(msg);
        i++;
    }
}