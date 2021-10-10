#define F_CPU 3333333

#include <avr/io.h>

void delay(uint16_t ms) {
    while (ms--) {
        while (!(TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm)); // wait for overflow
        TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;
    }
}

void main() {
    uint16_t period;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc; // set normal mode
    period = (uint32_t)F_CPU / 1000UL;
    TCA0.SINGLE.PER = period; // set period
    TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm; // clear overflow flag
    TCA0.SINGLE.CTRLA = 0x01; // enable TCA
    PORTD.DIR |= (1 << 7); // pd.7 as output
    while (1) {
        delay(500);
        PORTD.OUTTGL = (1 << 7); // toogle led
    }
}