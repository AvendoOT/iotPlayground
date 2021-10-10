#include <stm32f407xx.h>
#include <stdio.h>

void init_DefaultClock(void);
void init_Clock(void);
void init_FlashAccess(void);
void init_SysTick (void);
void init_USART2 (void);
void sendchar_USART2(int32_t c);
void init_TIM7 (void);