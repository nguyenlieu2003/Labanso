#include "MKL46Z4.h"


char char_to_waveform[] = {
	0x0B, 0x0E, //0
	0x0A, 0x0, 	//1
	0x07, 0x0C,	//2
	0x05, 0x0E,	//3
	0x0C, 0x06,	//4
	0x0D, 0x0A, //5
	0x0F, 0x0A,	//6
	0x0, 0x0E,  //7
	0x0F, 0x0E, //8
	0x0D, 0x0E	//9
};

int pin[] = {37,17,7,8,53,38,10,11};

void lcd_Init(){
	
	//bat clock
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_SLCD_MASK;
	
	//chon nguon dong ho
	LCD->GCR |= LCD_GCR_SOURCE_MASK;
	
	//chon duty circle (4 back plane)-> chon sd 4 bp
	LCD->GCR |= 1<<0 | 1<<1;
	
	//bat nguon dong ho
	MCG->C1 |= MCG_C1_IRCLKEN_MASK;
	
	//bat 12 chan
	LCD->PEN[0] |= 1<<19;
	LCD->PEN[0] |= 1<<18;
	LCD->PEN[0] |= 1<<17;
	LCD->PEN[0] |= 1<<7;
	LCD->PEN[0] |= 1<<8;
	LCD->PEN[0] |= 1<<10;
	LCD->PEN[0] |= 1<<11;
	
	LCD->PEN[1] |= 1<<8;
	LCD->PEN[1] |= 1<<20;
	LCD->PEN[1] |= 1<<5;
	LCD->PEN[1] |= 1<<21;
	LCD->PEN[1] |= 1<<6;
	
	//bat bp
	LCD->BPEN[0] |= 1<<19;
	LCD->BPEN[0] |= 1<<18;
	
	LCD->BPEN[1] |= 1<<8;
	LCD->BPEN[1] |= 1<<20;
	
	//bat nen
	LCD->WF8B[40] |= 1<<0; //com0
	LCD->WF8B[52] |= 1<<1; //com1
	LCD->WF8B[19] |= 1<<2; //com2
	LCD->WF8B[18] |= 1<<3; //com3
	
	//enable LCD 
	LCD->GCR |= LCD_GCR_LCDEN_MASK;
}

void char_Lcd(int position, char c){
	if (c == ' ') {
		LCD->WF8B[pin[position*2]] = 0;
		LCD->WF8B[pin[position*2+1]] = 0;
	}
	if(c < '0' || c > '9')
		return;
	if(position <0 || position >4)
		return;
	
	int index = c - 48;
	char a1 = char_to_waveform[index*2];
	char a2 = char_to_waveform[index*2+1];
	
	LCD->WF8B[pin[position*2]] = a1;
	LCD->WF8B[pin[position*2+1]] = a2;
}
	
void string_Lcd(char* c){
	int pos = 0;
	while (pos < 4 && *c) {
		char_Lcd(pos, *c++);
		pos++;
	}
	while (pos < 4)
	{
		char_Lcd(pos, ' ');
		pos++;
	}
}
	