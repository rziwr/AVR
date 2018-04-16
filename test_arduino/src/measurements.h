#include <avr/io.h>

#define ADC_CHANNEL_COUNT	4
#define ADC_SAMPLES_COUNT	4

uint8_t calc_done;
uint16_t adc_average [ADC_CHANNEL_COUNT];


void init_measurements (void);
void measure_tick (void);
