#define F_CPU 3333333

#include <avr/io.h>
#include <util/delay.h>

// s1,s2,s3,s4 tipke (pa7 - pa4)
// h1,h2,h3,h4 led diode (pd7-pd4)

void main() {

    PORTD.DIR |= PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm; // led outputs
    PORTA.DIR &= ~(PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm); // key inputs

    while(1) {
        if (PORTA.IN & (1 << 7) == 0) {
            PORTD.OUT &= ~(PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm);
            PORTD.OUT |= (1 << 7);
        }

        else if (PORTA.IN & (1 << 6) == 0) {
            PORTD.OUT &= ~(PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm);
            PORTD.OUT |= (1 << 6);
        }

        else if (PORTA.IN & (1 << 5) == 0) {
            PORTD.OUT &= ~(PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm);
            PORTD.OUT |= (1 << 5);
        }

        else if (PORTA.IN & (1 << 4) == 0) {
            PORTD.OUT &= ~(PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm);
            PORTD.OUT |= (1 << 4);
        }

    }

}
