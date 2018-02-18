/*
 * timer.h
 *
 * Created: 10/12/2017 1:25:26 PM
 *  Author: talho_000
 */

#include <avr/io.h>

#ifndef TIMER_H_
#define TIMER_H_


//void delay(long unsigned int ms);
unsigned int ICP1_get_width(); // sets up ICP1 for single pulse width measurement for Atmega32U4
void set_duty_cycle(int duty_cycle);
void setup_pwm();
#endif /* TIMER_H_ */