#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

volatile static uint8_t f = 0;

ISR (TIMER1_COMPA_vect){
	
	PINB = (1 << PB5);
	
	if (f){
		printf ("%d,%d,%d,%d\r\n", f, 0,0,0);
		f = 0;
	}
	else {
		printf ("%d,%d,%d,%d\r\n", f, 0,0,0);
		f = 1;
	}
}


void init_timer (void){

	//PORTB = (1 << PB5);
	PINB = (1 << PB5);
	
    //OCR1A = 0x3D08;
    OCR1A = 250*2;

    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A

    TIMSK1 |= (1 << OCIE1A);
    //Set interrupt on compare match

    //TCCR1B |= (1 << CS12) | (1 << CS10);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // set prescaler to 64 and start the timer
	// Timmer clock source period is 4ms
	// 4ms * OCR1A = 4ms * 25 = 100ms

	
}
