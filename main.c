#include "MKL46Z4.h"
#include "I2C.h"
#include "delay.h"
#include "uart.h"
#include "mag.h"
#include "lcd.h"
#include "switch.h"
#include "led.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

volatile uint8_t operation;

float calibx() {
	float minx = 30000;
	float maxx = -30000;
	for (int i = 0; i < 500; i++) {
		mag3110 data = mag_read();
		if (data.x < minx) minx = (float)data.x;
		if (data.x > maxx) maxx = (float)data.x;
		Delay(10);
	}
	return (minx + maxx) / 2.0;
}

float caliby() {
	float miny = 30000;
	float maxy = -30000;
	for (int i = 0; i < 500; i++) {
		mag3110 data = mag_read();
		if (data.y < miny) miny = (float)data.y;
		if (data.y > maxy) maxy = (float)data.y;
		Delay(10);
	}
	return (miny + maxy) / 2.0;
}


int main() {
	UART_Init();
	led_Init();
	switch_Init();
	Init_Systick();
	I2C_init();
	mag_Init();
	Delay(1);
	lcd_Init();
	UART_SendString("h");
	float calibration_x = calibx();
	float calibration_y = caliby();
	while(1){
		if (operation == 0) {
			string_Lcd(" ");
			continue;
		} else {
			mag3110 data = mag_read();
		
			float heading_float = atan2(data.y - calibration_y, data.x - calibration_x);
			heading_float = heading_float * (180.0/3.14159) + 180;
			int heading_int = (int)heading_float;
			
			char s[32];
			sprintf(s, "%d", heading_int);
			string_Lcd(s);
			Delay(100);
		}
	}
}