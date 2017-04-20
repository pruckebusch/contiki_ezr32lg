#ifndef __ADC_H__
#define __ADC_H__

#include "em_adc.h"

void adc_init(void);

int16_t adc_get_inttemp(void);

uint16_t adc_get_value_mv(uint8_t u8_adc_channel);
uint32_t adc_get_battery(void);


/** @} */
#endif /* __ADC_H__ */
