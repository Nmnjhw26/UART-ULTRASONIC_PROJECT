/*
 * MC@.h
 *
 *  Created on: Nov 5, 2023
 *      Author: Mayar Waleed
 */

#include "uart.h"
#include "lcd.h"
#include <avr/delay.h>



int main(void)
{
	uint8 distance;

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600);

	/* Initialize the LCD Driver */
	LCD_init();

	LCD_displayString("Distance=");



    while(1)
    {
    	distance = UART_recieveByte();
    	_delay_ms(100);
    	LCD_moveCursor(0,11);
    	LCD_intgerToString(distance);
    	LCD_moveCursor(0, 14);
    	LCD_displayString("cm");

    }
}
