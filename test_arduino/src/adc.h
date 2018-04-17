#include <avr/io.h>

#define ADC_START_CONVERSION (ADSC |= (1 << ADCSRA))

// ADC_CHANNEL_COUNT
#define ADC_CHANNEL_COUNT	4
#define ADC_CHANNEL_COUNT_MASK	(ADC_CHANNEL_COUNT - 1)
#define ADC_SAMPLES_COUNT	4
#define ADC_SAMPLES_COUNT_MASK	(ADC_CHANNEL_COUNT - 1)

#define ADC_HAS_NEW_SAMPLE	1
#define ADC_HAS_NOT_NEW_SAMPLE	0

typedef struct {
	uint8_t channel;
	uint16_t val_raw;
} adc_samp_typedef;


void init_adc (void);
uint8_t is_new_adc_sample (void);
void adc_get_sample (adc_samp_typedef *samp);
void adc_start (void);
