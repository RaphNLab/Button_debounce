/*
 * button.h
 *
 *  Created on: Sep 22, 2024
 *      Author: silvere
 */

#ifndef DRIVERS_BUTTON_H_
#define DRIVERS_BUTTON_H_

#include "global.h"

#define BUTTON_PIN		GPIO13 // User button PC13
#define BUTTON_GREEN	GPIO9	// Green button PA9
#define BUTTON_RED		GPIO8	// Red button PA8


enum button_type
{
	GREEN_BUTTON = 0,
	RED_BUTTON
};

void button_config(void);
bool_t button_debounce(enum button_type bt);

#endif /* DRIVERS_BUTTON_H_ */
