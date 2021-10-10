#define F_CPU 3333333
#define BAUD_RATE 19200

#include <avr/io.h>
#include <stdio.h>

int usart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

int usart_putchar(char c, FILE *stream) {
    while (!(USART3.STATUS & USART_DREIF_bm));
    USART3.TXDATAL = c;
    return 0;
}

void main() {

    uint16_t ADC0_RESULT, mV_RESULT;
    float mV;
    // usart init
    stdout = &mystdout;
    PORTB.DIR |= PIN0_bm;
    USART3.BAUD = ((uint32_t)F_CPU * 64) / (16 * (uint32_t)BAUD_RATE);
    USART3.CTRLB |= USART_TXEN_bm;

    // adc init
    ADC0.CTRLC |= ADC_REFSEL_VDDREF_gc;	    // select VDD as VREF (3.3 V)
    ADC0.MUXPOS |= ADC_MUXPOST_AIN0_gc;     // select ADC channel 0 (PORTD.0)
    ADC0.CTRLA | = ADC_ENABLE_bm;           // enable ADC0, single conversion mode
    
    while(1) {
        ADC0.COMMAND = ADC_STCONV_bm;               // start adc conversion
        while (!(ADC.INTFLAGS & ADC_RESDRY_bm));    // wait until adc conversion
        ADC0.INTFLAGS = ADC_RESDRY_bm;              // clear flag
        mV = (float) ADC0.RES / 1023.f * 3.3f;
        mV_RESULT = (uint16_t)(mV * 1000);
        printf("%d, %d", ADC0.RES, mV_RESULT);
        _delay_ms(1000);
    }

}