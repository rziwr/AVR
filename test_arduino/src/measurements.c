#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "uart.h"
#include <stdio.h>



//static uint8_t cur_chan = 0;

uint16_t adc_data [ADC_CHANNEL_COUNT] [ADC_SAMPLES_COUNT];
uint8_t sample_number [ADC_SAMPLES_COUNT];
uint16_t adc_average [ADC_CHANNEL_COUNT];
uint8_t calc_done = 0;

void init_measurements (void) {
	init_adc ();
}


void measure_tick (void){
	adc_samp_typedef sample;
	//printf ("1\r\n");
	//PINB = (1 << PB5);
	if (is_new_adc_sample() == ADC_HAS_NEW_SAMPLE){
		PINB = (1 << PB5);
		adc_get_sample (&sample);
		printf ("%d\r\n", sample.val_raw);
	}
}


uint16_t adc_read (uint8_t ch){
	
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8) | ch; // clears the bottom 3 bits before ORing
 
  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1 << ADSC);
 
  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while (ADCSRA & (1 << ADSC));
  
  return (ADC);
}


typedef struct {
	uint16_t sma;
	uint16_t samp_counter;
	uint16_t samp_buf [ADC_SAMPLES_COUNT];
} sma_struct_typedef;

sma_struct_typedef sma_data [ADC_CHANNEL_COUNT];

void put_sample (uint16_t samp, uint8_t ch){
	/*
	 SMA[n] = SMA[n - 1] + (x[n] - x[n-ADC_SAMPLES_COUNT])/ADC_SAMPLES_COUNT
	 x[n] -> samp
	*/

	uint16_t samp_to_sub;
	
	// Get sample x[n - ADC_SAMPLES_COUNT]
	if (sma_data[ch].samp_counter == ADC_SAMPLES_COUNT)
		samp_to_sub = sma_data[ch].samp_buf[0];
	else 
		samp_to_sub = sma_data[ch].samp_buf[sma_data [ch].samp_counter + 1];
	
	//sma_data [ch].sma = sma_data[ch].sma + (samp - samp_to_sub) >> 2;
	sma_data [ch].sma = sma_data[ch].sma + (samp - samp_to_sub)/ADC_SAMPLES_COUNT;
	
	// Store sample into samples buffer
	sma_data [ch].samp_buf[sma_data [ch].samp_counter] = samp;
	
	// increment samples counter
	sma_data[ch].samp_counter++;
	if (sma_data [ch].samp_counter >= ADC_SAMPLES_COUNT)
		sma_data[ch].samp_counter = 0;
	
	//sma_data[ch].samp_counter++;
	//sma_data[ch].samp_counter &= ADC_SAMPLES_COUNT_MASK;
}

