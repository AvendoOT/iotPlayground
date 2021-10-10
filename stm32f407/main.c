#include <stm32f407xx.h>
#include "handlers.h"
#include "init.h"



void Delay(uint32_t NoOfTicks);

void Delay(uint32_t NoOfTicks) {
	uint32_t curTicks;
	curTicks = msTicks;
	while ((msTicks - curTicks) < NoOfTicks);
}

int main(void) {
    volatile uint32_t tmp;
    init_SysTick();
    RCC->AHB1ENR |= 0x1UL << 3; // enable led1-led4 (GPIOD)
    tmp = RCC->AHB1ENR; // dummy read


    // RGB loop
    // PB13 Red, PB14 Blue, PB15 Green
    GPIOB->MODER &= ~((0x3UL << 26) | (0x3UL << 28) | (0x3UL << 30)); // brisanje vrijednosti
    GPIOB->MODER |= (0x3UL << 26) | (0x3UL << 28) | (0x3UL << 30); // postavljanje rgb outputa

    for (int i = 0; i < 3; i++) {
        GPIOB->ODR &= ~((0x1UL << 13U) | (0x1UL << 14U) | (0x1UL << 15U)); // RGB OFF
        GPIOB->ODR |= (0x1UL << 13U); // Red ON
        Delay(1000);
        GPIOB->ODR &= ~(0x1UL << 13U); // Red OFF
        GPIOB->ODR |= (0x1UL << 14U); // Blue ON
        Delay(1000);
        GPIOB->ODR &= ~(0x1UL << 14U); // Blue OFF
        GPIOB->ODR |= (0x1UL << 15U); // Green ON
        Delay(1000);
        GPIOB->ODR &= ~(0x1UL << 15U); // Green OFF
    }
}