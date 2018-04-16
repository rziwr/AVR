#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

/*
	ADC0:	PC0
	ADC1:	PC1
	ADC2:	PC2
	ADC3:	PC3
*/

static volatile uint8_t have_new_sample;
static volatile adc_samp_typedef sample_to_write;
static volatile adc_samp_typedef sample_current;

uint8_t is_new_adc_sample (void) {
	return have_new_sample;
}

void adc_get_sample (adc_samp_typedef *samp){
	sample_current = sample_to_write;
	
	if (sample_current.channel >= ADC_CHANNEL_COUNT){
		sample_to_write.channel = 0;
	} else {
		sample_to_write.channel++;
	}	
}

ISR (ADC_vect) {
	//uint8_t i;
	//uint8_t j;
	
	cli();
	
	if (have_new_sample == ADC_HAS_NEW_SAMPLE){
		// Error situation...
		sei();
		return;
	}
	have_new_sample = ADC_HAS_NEW_SAMPLE;
	

	
	ADMUX &= 0xf0;
	ADMUX |= sample_current.channel;
	
	sample_to_write.val_raw = ADC;
	
	/*adc_data [cur_chan] [sample_number [cur_chan]] = (ADCH << 8) | ADCL;
	
	ADCSRA = (1 << ADEN);
	
	cur_chan++;
	if (cur_chan >= ADC_CHANNEL_COUNT){
		cur_chan = 0;
		// Calculate average
		for (i = 0; i < ADC_CHANNEL_COUNT; i++){
			adc_average [i] = 0;
			for (j = 0; j < ADC_SAMPLES_COUNT; j++){
				adc_average [i] += adc_data [i] [j];
			}
			adc_average [i] >>=2;
		}
		calc_done = 1;
	}*/
	
	ADMUX &= 0b1111;
	ADMUX |= sample_to_write.channel;
	sei();
}


void init_adc (void) {
	//uint8_t i;
	//uint8_t j;
	// initialize arrays for measurements
	/*for (i = 0; i < ADC_SAMPLES_COUNT; i++){
		sample_number [i] = 0;
		for (j = 0; j < ADC_CHANNEL_COUNT; j++){
			adc_data [j] [i] = 0;
		}
	}*/
	
	// initialize ADC
	ADMUX |= (1 << REFS0) | (1 << REFS1);	// AREF = AVcc
	ADMUX &= (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0) | (1 << ADLAR);	// Set 1st ADC channel 0
	ADMUX &= ADLAR;
	ADCSRA = //(1<<ADEN) |		// Enable ADC
		(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// Set prescaler to 128
		
	// Start conversation	
	ADCSRA = (1 << ADEN);	
	// switch to next channel
	//cur_chan++;
	
	sei();
}


