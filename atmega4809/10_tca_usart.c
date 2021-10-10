#define F_CPU 3333333
#define BAUD_RATE 19200

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int usart_putchar(char c, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

int usart_putchar(char c, FILE *stream) {
    while(!(USART3.STATUS & USART_DREIF_bm));
    USART3.TXDATAL = c;
    return 0;
}

void main() {
    uint16_t rnd, period, keyPressed;
    uint32_t ms;
    float us;

    PORTD.DIR |= (1 << 7); // LED
    PORTA.PIN7CTRL |= 0b00001000; // enable pullup for key
    // USART setup
    stdout = &mystdout;
    PORTB.DIR |= PIN0_bm;
    USART3.BAUD = ((uint32_t)F_CPU * 64) / (16 * (uint32_t)BAUD_RATE);
    USART3.CTRLB |= USART_TXEN_bm;
    // TCA setup
    period = (uint32_t)F_CPU / 1000UL;
    TCA0.SINGLE.PERIOD = period;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
    TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm; // clear overflow
    srand();
    rnd = 1000 + rand() % 4000
    _delay_ms(rnd);
    PORTD.OUT |= (1 << 7); // turn on LED
    TCA0.SINGLE.CTRLA = 0x01; // start timer
    ms = 0;
    keyPressed = 0;
    while(1) {
        while (!(TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)) { // until overflow
            if (PORTA.IN & (1 << 7)) { // key pressed (PA7)
                TCA0.SINGLE.CTRLA = 0x00; // stop timer
                keyPressed = 1;
                break;
            }
        }
        TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm; // clear overflow flag
        if (keyPressed) {
            us = ((float)(TCA0.SINGLE.CNT)/0.3f) + (1000.0f * (float)ms);
            printf("Reaction time %ld us\n\r", (uint32_t)us);
            while(1);
        } else {
            ms++;
        }
    }

}