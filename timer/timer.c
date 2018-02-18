/*
 * timer.c
 *
 * Created: 10/12/2017 1:24:37 PM
 *  Author: talho_000
 */

#include "timer.h"

unsigned int ICP1_get_width()
{
    unsigned int width;
    TCCR1B = (1 << ICES1) | (1 << CS10); // no noise filtering, rising edge trigger, no prescaler
    while ((TIFR1 & (1 << ICF1)) == 0)
        ; // wait for IC flag
    width = ICR1;
    TCCR1B &= ~(1 << ICES1); // change input capture to falling edge trigger
    TIFR1 |= (1 << ICF1);    // clear IC flag
    while ((TIFR1 & (1 << ICF1)) == 0)
        ; // wait for IC flag
    width = ICR1 - width;
    TIFR1 |= (1 << ICF1); // clear IC flag

    return width;
}

void setup_pwm()
{
    TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0A1); // fast PWM, non-inverted
    TCCR0B |= (1 << CS00);                                 // no prescaler with f_osc (so 62.5KHz PWM)
}

void set_duty_cycle(int duty_cycle)
{
    duty_cycle = 2.56 * duty_cycle - 1;
    OCR0A = (char)((0x00FF) & duty_cycle);
}
