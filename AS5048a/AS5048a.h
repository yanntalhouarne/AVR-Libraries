/*
 * AS5048a.h
 *
 * Created: 1/13/2018 5:59:28 PM
 *  Author: Yann
 */ 


#ifndef AS5048A_H_
#define AS5048A_H_

#include <math.h>

#define CS 1
#define ANGLE_TO_DEGREES 0.2197

// ADRESSES
#define READ_ANGLE 0x3FFF
#define NO_OP 0x0000
#define CLEAR_ERROR_FLAG 0x0001
#define OTP_HI 0x0016
#define OTP_LOW 0x0017

#define SS_HIGH PORTD |= (1 << CS);
#define SS_LOW PORTD &= ~(1 << CS);
#define LED_ON PORTB |=  (1 << LED );
#define LED_OFF PORTB &=  ~(1 << LED );

// MASKS
#define READ 0x4000
#define WRITE 0x0000
#define ERROR_FLAG_BIT 14
#define FRAME_ERROR_BIT 0
#define COMMAND_ERROR_BIT 1
#define PARITY_ERROR_BIT 2
#define OTP_HI_mask 0x00FF;
#define OTP_LOW_mask 0x002F;

// FUNCTION DECLARATIONS
unsigned int AS5048a_compute_parity(unsigned int word);
unsigned int AS5048a_send_cmd(unsigned int READ_WRITE, unsigned int ADDRESS);
void AS5048a_check_parity(unsigned int word);
void AS5048a_clear_and_read_errors();
int angle_to_degrees(unsigned int angle);
void zero_angle();
unsigned int AS5048a_send_data(unsigned int data);
int AS5048a_get_angle();



#endif /* AS5048A_H_ */