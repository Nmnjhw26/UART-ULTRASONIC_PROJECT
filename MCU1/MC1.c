/*
 * MC1.c
 *
 *  Created on: Nov 5, 2023
 *      Author: Mayar Waleed
 */


#include "ultrasonic.h"
#include "uart.h"
#include "std_types.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/delay.h>


int main()
{

	UART_init(9600);
	Ultrasonic_init();
	SREG |=(1<<7);

	while(1)
	{
		Ultrasonic_Trigger();
		uint16 distance = Ultrasonic_readDistance();
		UART_sendByte(distance);
		_delay_ms(100);

	}
}
