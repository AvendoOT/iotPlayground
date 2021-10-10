#include <stm32f407xx.h>
#include "handlers.h"

static volatile uint32_t msTicks;

// prekidna fja
// na stog se pohranjuju xPSR(APSR, IPSR, EPSR), PC(R15), LR(R14), R12, R3, R2, R1, R0
void __attribute__((interrupt)) SysTick_Handler(void) { 
    msTicks++;
}