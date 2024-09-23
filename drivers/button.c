/**
 * Comment block
 *
*/

/*
 * button.c
 *
 *  Created on: Sep 22, 2024
 *      Author: silvere
 */

/**
 * Include statements
 *
*/
#include "button.h"
#include "timer_drv.h"
#include <libopencm3/stm32/exti.h>


/**
 * Data type, Constant and macro definitions
 *
*/

/**
 * Static data declaration
 *
*/
bool_t button_state = FALSE;
bool_t debounce_delay_elapsed = FALSE;
enum button_type bt_type;
/**
 * Private function prototypes
 *
*/

/**
 * Public functions
 *
*/
void button_config(void)
{
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, BUTTON_PIN);
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, (BUTTON_GREEN | BUTTON_RED));
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);


	nvic_enable_irq(NVIC_EXTI9_5_IRQ);
	exti_select_source (EXTI9, GPIOA);
	exti_select_source (EXTI8, GPIOA);
	exti_set_trigger((EXTI8 | EXTI9), EXTI_TRIGGER_FALLING);
	exti_enable_request(EXTI8 | EXTI9);
}

bool_t button_debounce(enum button_type bt)
{
	bool_t ret_val = FALSE;
	if(debounce_delay_elapsed && (bt == RED_BUTTON))
	{
		debounce_delay_elapsed = FALSE;
		ret_val = TRUE;
	}
	else if(debounce_delay_elapsed && (bt == GREEN_BUTTON))
	{
		debounce_delay_elapsed = FALSE;
		ret_val = TRUE;
	}
	return ret_val;
}


/**
 * Private functions
 *
*/
void exti9_5_isr(void)
{
	/* EXTI8 turns OFF, EXTI9 turns ON */
	if (exti_get_flag_status(EXTI8) == EXTI8)
	{
		exti_reset_request(EXTI8);
		timer_enable_counter(TIM3);
		debounce_delay_elapsed = FALSE;
		button_state = TRUE;
		bt_type = RED_BUTTON;
	}
	else if (exti_get_flag_status(EXTI9) == EXTI9)
	{
		exti_reset_request(EXTI9);
		timer_enable_counter(TIM3);
		debounce_delay_elapsed = FALSE;
		button_state = FALSE;
		bt_type = GREEN_BUTTON;
	}
	else
	{
		__asm__("nop");
	}
}


void tim3_isr(void)
{
	if (timer_get_flag(TIM3, TIM_SR_UIF))
	{
		timer_clear_flag(TIM3, TIM_SR_UIF);

		switch(bt_type)
		{
		case RED_BUTTON:
			// Check if the button has been released
			if (gpio_get(GPIOA, BUTTON_RED))
			{
				debounce_delay_elapsed = TRUE;

				/* Disable timer for next trigger*/
				timer_disable_counter(TIM3);
				//timer_disable_irq(TIM3, TIM_DIER_UIE);
			}
			break;
		case GREEN_BUTTON:
			// Check if the button has been released
			if (gpio_get(GPIOA, BUTTON_GREEN))
			{
				debounce_delay_elapsed = TRUE;

				/* Disable timer for next trigger*/
				timer_disable_counter(TIM3);
				//timer_disable_irq(TIM3, TIM_DIER_UIE);
			}
			break;
		default:
			break;
		}
	}
}


