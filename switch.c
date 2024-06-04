#include "MKL46Z4.h"
#include "switch.h"


void switch_Init(){
	operation = 0;
	//bat clock cho portC
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	//bat gpio
	PORTC->PCR[3] |= 1<<8;
	PORTC->PCR[12] |= 1<<8;
	
	//set input
	PTC->PDDR &= ~(1<<3);
	PTC->PDDR &= ~(1<<12);
	
	//set pullup
	PORTC->PCR[3] |= 1<<1 | 1<<0; //PE =1, PS =1
	PORTC->PCR[12] |= 1<<1 | 1<<0; //PE =1, PS =1
	
	//interrupt enable
	PORTC->PCR[3] |= PORT_PCR_IRQC(0xA); // 1<<19 | 1<<17
	PORTC->PCR[12] |= 1<<19 | 1<<17;

	//bat ham interrupt
	NVIC_EnableIRQ(31);
	NVIC_SetPriority(31, 15);
}

void PORTC_PORTD_IRQHandler(){
	if((PTC->PDIR & (1<<3)) == 0){
		if(operation == 0) operation = 1;
		else operation = 0;
	}
	
	PORTC->PCR[3] |= (1 << 24);
	if((PTC->PDIR & (1<<12)) == 0)
		NVIC_SystemReset();
	
	PORTC->PCR[12] |= (1 << 24);
}
