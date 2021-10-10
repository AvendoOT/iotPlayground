#include <stm32f407xx.h>

extern static volatile uint32_t msTicks;

static __attribute__((interrupt)) SysTick_Handler(void);