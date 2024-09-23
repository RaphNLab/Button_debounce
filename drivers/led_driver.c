#include "led_driver.h"


/**
 * Data type, Constant and macro definitions
 *
*/

/**
 * Static data declaration
 *
*/

/**
 * Private function prototypes
 *
*/

/**
 * Public functions
 *
*/
void led_config(void)
{
	rcc_periph_clock_enable(RCC_GPIOD);
	/* Set GPIO6 (in GPIO port B) to 'output push-pull'. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, (GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED));
}

/**
 * @brief This function toggles an group of four LED in a ring form
 * @param delay unsigned int16 the delay time in ms
 * @return
*/
void led_ring(uint16_t delay, blink_dir_t direction)
{
	uint16_t led_num;
	for(uint8_t i = 0; i < 8; i++)
	{
		switch(direction)
		{
			case LED_LEFT:
			{
				led_num = GREEN_LED;
				for(uint8_t j = 0; j < 4; j++)
				{
					gpio_toggle(GPIOD, (led_num));
					sleep_ms(delay);
					led_num = (led_num * 2);
				}
			}
			break;
			//case LED_RIGTH:
			default:
			{
				led_num = BLUE_LED;
				for(uint8_t j = 0; j < 4; j++)
				{
					gpio_toggle(GPIOD, (led_num));
					sleep_ms(delay);
					led_num = (led_num / 2);
				}
			}
		}
	}
}

/**
 * @brief This function toggles an group of four LED in a heart beat frequency
 * @param delay unsigned int16 the delay time in ms
 * @return
*/
void led_heart_beat(uint16_t delay)
{
	gpio_toggle(GPIOD, (GREEN_LED | ORANGE_LED | RED_LED | BLUE_LED));
	sleep_ms(delay);
}


/**
 * Private functions
 *
*/

