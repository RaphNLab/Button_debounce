/*
 * systick.h
 *
 *  Created on: 28 Apr 2020
 *      Author: silvere
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


void systick_ms_setup(void);
void msleep(uint32_t delay);
void sys_tick_handler(void);


#endif /* SYSTICK_H_ */
