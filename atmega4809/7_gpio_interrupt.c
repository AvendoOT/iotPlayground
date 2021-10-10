#define F_CPU 3333333

#include <avr/io.h>

#define PA7_LOW !(PORTA.IN & PIN7_bm)
#define PA7_INTERRUPT PORTA.INTFLAGS & PIN7_bm;
#define PA7_CLEAR_INTERRUPT_FLAG PORTA.INTFLAGS |= PIN7_bm;

volatile uint8_t pa7flag;

ISR(PORTA_PORT_vect) { // macro for interrupt function
    if (PA7_INTERRUPT) {
        pa7flag = 1;
        PA7_CLEAR_INTERRUPT_FLAG;
    }
}

void isrExampleGPIO1() {
    PORTD.DIR |= (1 << 7); // PD.7 output
    pa7flag = 0;
    PORTA.DIR &= ~PIN7_bm;
    PORTA.PIN7CTRL |= PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc; // enable interrupts
    sei(); // global enable interrupts
    while (1) {
        if (pa7flag) {
            if (PA7_LOW) {
                PORTD.OUT |= (1 << 7);
            } else {
                PORTD.OUT &= ~(1 << 7);
            }
            pa7flag = 0;
        }
    }
}