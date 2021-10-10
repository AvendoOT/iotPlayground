#include <stm32f407xx.h>
#include <stdio.h>
#include "init.h"

void init_DefaultClock(void) {
	RCC->CR |= (uint32_t)0x00000001; // HSION=1
	RCC->CFGR = 0x00000000; // Reset CFGR register
	RCC->CR &= (uint32_t)0xFEF6FFFF; // HSEON, CSSON, PLLON =0
	RCC->PLLCFGR = 0x24003010; // Reset PLLCFGR register
	RCC->CR &= (uint32_t)0xFFFBFFFF; // HSEBYP=0
	RCC->CIR = 0x00000000; // Dissable all clock interrupts
}

void init_CLOCK(void) {
    RCC->CR |= 0x1UL << 16U; // ukljuci vanjski oscilator (RCC_CR_HSEON)
    while (!(RCC->CR & 0x1UL << 17U)); // cekaj dok je spreman (stacionaran) (HSERDY)
    RCC->PLLCFGR = 0x24413208UL; // setup pll registara
    RCC->CR |= 0x1UL << 24; // ukljucivanje pll sklopa (PLLON)
    while (!(RCC->CR & 0x1UL << 25U)); // (PLLRDY)
    // upravljanje djelilima takta za sabirnice
    RCC->CFGR |= 0x0UL << 4U; // setup HPRE, divide by 1
    RCC->CFGR |= 0x7UL << 10U; // APB1 na najvecu vrijednost, ppre1 111b
    RCC->CFGR |= 0x7UL << 13U; // APB2 na najvecu vrijednost, ppre2 111b
    // upravljanje multipleksorom za odabir sistemskog takta
    // Selection of PLLCLK as SYSCLK
	RCC->CFGR |= 0x2UL; // SW=2;
	while( (RCC->CFGR & 0xCUL)>>2 != (RCC->CFGR & 0x3UL) ); // while(SWS!=SW);
    // Desired frequencies for APB1 and APB2 clocks
	RCC->CFGR &= ~(0x7UL<<10U); // PPRE1: div. 4
	RCC->CFGR |= (0x5UL<<10U);
	RCC->CFGR &= ~(0x7UL<<13U); // PPRE2: div. 2
	RCC->CFGR |= (0x4UL<<13U);
}

void init_FlashAccess(void) {
	uint32_t WS = 5UL;	//broj stanja cekanja 5 za 168MHz na 3V
	FLASH->ACR |= WS // latency
	| (0x1UL<< 8U) // FLASH_ACR_PRFTEN
	| (0x1UL<< 9U) // FLASH_ACR_ICEN
	| (0x1UL<<10U); // FLASH_ACR_DCEN
	while( ((FLASH->ACR)&(0x7UL)) != WS ); // wait acception
}

void SystemInit(void) {
    SCB->VTOR = FLASH_BASE; // vector table realocated to flash memory
    SCB->CPACR |= ((3UL << 20) | (3UL << 22)); // full access to FPU

    init_FlashAccess();
    init_Clock();
}

void init_SysTick(void) { // sistemski prekid
    // init prekide sistemskog brojila
    // System control block SCB (19 registara)
    SCB->SHP[11] = 0x2 << 4; // sysTick priority = 2
    SCB->AIRCR = (SCB->AIRCR & 0xF8FFUL) | 0x05FA0000UL;
    // init sistemsko brojilo
    SysTick->LOAD = 0x5207UL; // reload = N -1 = (Fsystick / fc) = 21000 = 20999 = 0x5207; Fc = 1ms (Tsystick)
    SysTick->VAL = 0x0UL; // current = 0
    SysTick->CTRL |= 0x3UL; // tickint = 1, ticken = 1
}

void init_USART2(void) {
    volatile uint32_t tmp;
    RCC->AHB1ENR |= (1UL << 3); // enable GPIOD clock
    RCC->APB1ENR |= (1UL << 17); // ENABLE USART2 CLOCK
    tmp = RCC->APB1ENR; // dummy read
    GPIOD->AFR[0] |= (7UL << 20); // TX to PD5
    GPIOD->AFR[0] |= (7UL << 24); // to PD6
    GPIOD->MODER &= ~(3UL << 10); // clear bits 10 & 11
    GPIOD->MODER |= 2UL << 10; // 10 alternate function mode

    // USART2: 9600 baud, 8 bits, 1 stop bit, no parity
	// fAPB1 = 25 MHz
	
	USART2->CR1 = 0x0UL;
	USART2->CR2 = 0x0UL;
	USART2->CR3 = 0x0UL;
	
	USART2->CR1 |= 	(1UL << 13); // UE => USART enable
	USART2->CR1 |= 	(0UL << 12); // M => 8 bits
	USART2->CR1 |= 	(0UL << 10); // PCE => No parity
	USART2->CR2 |= 	(0UL << 12); // STOP => 1 stop bit
	USART2->BRR = 	0x0A2CUL; // BR => 9600 bit/s
	USART2->CR1 |= 	(1UL << 3); // TE => TX enable
}