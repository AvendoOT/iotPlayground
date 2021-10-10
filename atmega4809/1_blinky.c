#define F_CPU 3333333
#include <avr/io.h>
#include <util/delay.h> 


// naizmjenicno paljenje LED diode, blinky
int main(void) {

    PORTF.DIR |= (1 << 5); // PF.5 as output
    while (1) {
        PORTF.OUT |= (1 << 5); // LED ON
        _delay_ms(500);
        PORTF.OUT &= ~(1 << 5); // LED OFF
        _delay_ms(500);
    }
}