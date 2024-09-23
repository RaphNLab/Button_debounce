#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#define ARR_SIZE(arr)	(sizeof(arr)/sizeof(arr[0]))

#define STM32L1_NUCLEO

typedef enum
{
	FALSE = 0,
	TRUE
}bool_t;


typedef enum
{
	GLOBAL_OK,
	GLOBAL_ERROR,
	GLOBAL_TIMEOUT_ERROR
}status_t;


#endif
