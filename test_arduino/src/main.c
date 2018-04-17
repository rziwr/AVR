#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "timer.h"
#include "measurements.h"
//#include "adc.h"


int main () {
	
	uint16_t i = 0;
	uint8_t up_count_flag = 1;
	
	
	DDRB = 0xFF;
	//PORTB = (1 << PB5);
	
	init_uart ();
	init_timer ();
	init_measurements ();
	//init_adc ();
	sei();
	
	printf ("Start\r\n");

	while (1){
		//PORTB |= (1 << PB5);
		_delay_ms (5);
		//PORTB &= ~(1 << PB5);
		//PORTB ^= (1 << PB5);
		_delay_ms (5);
/*		send_UART('1');
		send_UART('2');
		send_UART('3');
		send_UART('\r');
		send_UART('\n');
		*/
		//printf ("%d,%d,%d,%d\r\n", i, 100 - i, i/2 + 25 , i%10 + 50);
		
		if (up_count_flag){
			i++;
			if (i > 100){
				up_count_flag = 0;
				i -= 2;
			}
		} else {
			i--;
			if (i < 1){
				up_count_flag = 1;
				i += 2;
			}
		}
		measure_tick ();	
	}
	
	return 0;
}
