#include "MKL46Z4.h"
#include "led.h"
#include "delay.h"

void led_Init(){
	//enable clock port D,E
	SIM->SCGC5 |= 1<<13;
	SIM->SCGC5 |= 1<<12;
	
	//bat gpio
	PORTE->PCR[29] |= 1<<8;
	PORTD->PCR[5] |= 1<<8;
	
	//set dau ra 
	//0 - input
	//1 - output
	PTE->PDDR |= 1<<29;
	PTD->PDDR |= 1<<5;
	
	//tat di luc dau
	PTD->PDOR |= (1<<5);
	PTE->PDOR |= (1<<29);
}
