#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "global.h"
#include "timer_drv.h"

#define GREEN_LED	GPIO12
#define ORANGE_LED	GPIO13
#define RED_LED		GPIO14
#define BLUE_LED	GPIO15


typedef enum
{
	LED_LEFT = 0,
	LED_RIGTH
}blink_dir_t;

void led_config(void);
void led_ring(uint16_t delay, blink_dir_t direction);
void led_heart_beat(uint16_t delay);


#endif
