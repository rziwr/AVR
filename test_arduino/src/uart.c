
#include <avr/io.h>
#include <util/delay.h>
#include "stdio.h"


#define BAUD 57600UL // Скорость обмена данными
//#define BAUD 1000000UL // Скорость обмена данными
#define UBRRL_value (F_CPU/(BAUD*16)-1) //Согластно заданной скорости подсчитываем значение для регистра UBRR

static FILE mystdout;

void init_uart (void){
	UBRR0L = UBRRL_value;       //Младшие 8 бит UBRRL_value
	UBRR0H = UBRRL_value >> 8;  //Старшие 8 бит UBRRL_value
	UCSR0B |=(1<<TXEN0);         //Бит разрешения передачи
	UCSR0C |=(1<< UCSZ01)|(1<< UCSZ00); //Устанавливем формат 8 бит данных	
	
	stdout = &mystdout;
	
}

void send_UART(char value) {
	while(!( UCSR0A & (1 << UDRE0)));   // Ожидаем когда очистится буфер передачи
	UDR0 = value; // Помещаем данные в буфер, начинаем передачу
}

static int my_putchar(char c, FILE *stream){
	send_UART(c);
	return 0;
}


// определяем дескриптор для стандартного вывода
static FILE mystdout = FDEV_SETUP_STREAM(
                send_UART,     // функция вывода символа
                NULL,           // функция ввода символа, нам сейчас не нужна
                _FDEV_SETUP_WRITE // флаги потока - только вывод
);

//__attribute((OS_main))
