#define F_CPU 3333333

#include <avr/io.h>

void main() {
    int16_t period; 
    int16_t step; // step of brightness
    int16_t value; 

    PORTD.DIR |= (1 << 2); // LED
    
    // TCA SETUP
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    TCA0.SINGLE.CTRLB |= 0x01000000;
    period = (uint32_t)F_CPU / 1000UL;
    TCA0.SINGLE.PERIOD = period;
    step = period / 10;
    value = 0;
    TCA0.SINGLE.CMP2 = value; // duty circle
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc; // save waveform output on PORT D via PORTMUX
    TCA0.SINGLE.CTRLA |= 0x01; // run timer
    while (1) {
        _delay_ms(500);
        value += step;
        if (value > period) value = 0;
        TCA0.SINGLE.CMP2 = value;
    }
}