/*
 * software_usart.h
 *
 * Created: 11/4/2017 8:49:23 PM
 *  Author: talho_000
 */ 

/*
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef SOFTWARE_USART_H_
#define SOFTWARE_USART_H_

#define BR 104 // Baud rate in microsecond
#define TX 5
#define RX 6

void setup_OCR0A_interrupts();
void start_timer();
void setup_sft_usart();
void sft_send_char(unsigned char data);

#endif /* SOFTWARE_USART_H_ */
