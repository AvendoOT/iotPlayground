#define F_CPU 3333333
#include <avr/io.h>
#include <util/delay.h> 

int main() {
    PORTA.DIR |= (1 << 7); // pd.7 as output
    while (1) {
        if (PORTA.IN & (1 << 7) == 0) { // key pressed
            PORTA.OUT |= (1 << 7); // led on
        } else {
            PORTA.OUT &= ~(1 << 7); // led off
        }
    }
}