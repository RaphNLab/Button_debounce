#ifndef DELAY_DRIVER_
#define DELAY_DRIVER_

#include "global.h"


void timer_sleep_config(void);
void timer_debounce_config(void);
void sleep_us(uint16_t delay_us);
void sleep_ms(uint16_t delay_ms);


#endif
