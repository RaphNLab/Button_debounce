#include "drivers/timer_drv.h"
#include "drivers/uart_drv.h"
#include "drivers/led_driver.h"
#include "drivers/button.h"

int main(void)
{
	timer_sleep_config();
	timer_debounce_config();

	button_config();
	led_config();

	while (1)
	{
		if(button_debounce(RED_BUTTON))
		{
			//gpio_set(GPIOA, GPIO5);
			gpio_clear(GPIOA, GPIO5);
			//gpio_toggle(GPIOA, GPIO5);
		}
		else if (button_debounce(GREEN_BUTTON))
		{
			//gpio_clear(GPIOA, GPIO5);
			gpio_set(GPIOA, GPIO5);
		}
	}
	return 0;
}
