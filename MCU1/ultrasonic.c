/*
 * ultrasonic.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Mayar Waleed
 */
#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include "std_types.h"
#include<avr/delay.h>
#include "common_macros.h"


static volatile uint16 g_time;
static volatile uint8 g_edges_counter;

void Ultrasonic_init(void){

	ICU_ConfigType icu_type={F_CPU_8,RISING};
	ICU_init(&icu_type);
	/*call back by passing the address of the edge processing function
	 *  (name of the function = address of the function )*/
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	/* setup the direction of the trigger to be output pin */
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID ,ULTRASONIC_TRIGGER_PIN_ID ,PIN_OUTPUT);
}


void Ultrasonic_Trigger(void){
	/*give the trigger logic high (1) to start send signal */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	/*delay for sending signal*/
	_delay_ms(10);
	/*give the trigger logic low (0) to stop send signal */
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void){
	/* sending pulses by the trigger*/
	Ultrasonic_Trigger();
	if(g_edges_counter>=2){ //raising & falling -> 1 cycle
		g_edges_counter=0; //reset the counter of the edges
		/* equation to convert from time to distance*/
	}
	return (g_time*0.017);
}



void Ultrasonic_edgeProcessing(void){
	/*increment the edge by one */
	g_edges_counter++;
	if(g_edges_counter==1){
		/*clear the timer register to start the timer when the rising edge is detected*/
		ICU_clearTimerValue();
		/*change the edge select to the falling edge to know the time of the pulse*/
		ICU_setEdgeDetectionType(FALLING);
	}
	/*this condition will be true when the falling edge is detected*/
	else if(g_edges_counter==2){
		/*we will read the input capture register and save it inside the g_timeHigh*/
		g_time = ICU_getInputCaptureValue();

		/*clear the input capture register to start detect again*/
		ICU_clearTimerValue();

		/*To start detecting from the rising edge*/
		ICU_setEdgeDetectionType(RISING);
	}
}
