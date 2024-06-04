#include "MKL46Z4.h"
#include "delay.h"
#include "switch.h"

volatile uint32_t msTicks = 0;
volatile uint32_t green = 0;
volatile uint32_t red = 0;

void Init_Systick(){
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk |SysTick_CTRL_ENABLE_Msk;
	SysTick->LOAD = SystemCoreClock/1000;
	NVIC_SetPriority(-1,16);
}

void Shutdown(){
	SysTick->CTRL &= ~(1<<0);
}

void SysTick_Handler (void){
	msTicks++;
	if (operation == 0) {
		PTD->PDOR |= (1<<5);
		green = 0;
		red++;
		if (red == 250) {
			PTE->PTOR |= 1 << 29;
			red = 0;
		}
	}
	else if(operation == 1){
		red = 0;
		green ++;
		PTE->PDOR |= (1<<29);
		if(green == 500){
			green = 0;
			PTD->PTOR |= 1<<5;
		}
	}
}

void Delay (uint32_t TICK) {
	while (msTicks < TICK); // Wait 500ms
	msTicks = 0; // Reset counter
	
} 