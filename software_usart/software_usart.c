/*
 * software_usart.c
 *
 * Created: 11/4/2017 8:47:40 PM
 *  Author: talho_000
 */ 
/*
#include "software_usart.h"
#include "print.h"

unsigned char BUSY = 0;
unsigned char timer_done = 0;

void setup_OCR0A_interrupts()
{
	TCCR0A |= (1 << WGM01);   // normal operation
	TIMSK0 |= (1 << OCIE0A);  // enable interutps on OCIEB
}

void start_timer()
{
	timer_done = 0;
	OCR0A = 25;							 // Period is 104us
	TCNT0 = 0x00;                        // load TCNT0 with 0
	TCCR0B |= (1 << CS01) | (1 << CS00); // normal mode, prescaler of 64, crystal oscillator as clock source, and start timer
}

void setup_sft_usart()
{
	DDRB |= (1<<TX); // TX is output (PB5, 9 on Micro), RX is input (PB6, 10 on Micro)
	PORTB |= (1<<TX); // IDLE state is high
}

void sft_send_char(unsigned char data)
{
	while(BUSY); // wait for receive to be completed
	BUSY = 1; // beginning of transmission
	
	start_timer();
	PORTB &= ~(1<<TX); // start bit
	while(timer_done == 0);
	
	for (int i = 0; i < 8; i++)
	{
		start_timer();
		if (data & (1 << i))
		PORTB |= (1<<TX);
		else
		PORTB &= ~(1<<TX);
		while(timer_done == 0); // wait for timer0 to be done
	}
	
	PORTB |= (1<<TX); // stop bit
	BUSY  = 0; // end of transmission
	
	_delay_ms(3);
}

ISR(TIMER0_COMPA_vect)
{
	timer_done = 1;
}
*/