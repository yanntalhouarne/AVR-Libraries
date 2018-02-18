
/*
 * mc_protocol.h
 *
 * Created: 11/1/2017 12:44:47 AM
 *  Author: talho_000
 */

#ifndef MC_PROTOCOL_H_
#define MC_PROTOCOL_H_

#include <util/delay.h>

#include "print.h"
#include "usart.h"

#define LSB 0x00FF
#define MSB 0xFF00

// joystick reading and scaling
#define AVG_ELEMENTS 10
#define CMD_SCALE 1.44
#define NEUTRAL_CMD 493
#define DEADBAND_MIN 485
#define DEADBAND_MAX 505
#define OFFSET 7

// packet structure: [*][CC1][CC2][MSB][LSB][CS]
#define GO 21       // CC2 for move motor cmd
#define ROBOTEQ 'Q' // CC1 for Roboteq
#define REQUEST 'X' // CC1 for request
#define MAX_DATA_SIZE 4
#define SWING_ESTOP 2
#define LIFT_ESTOP 1
#define SWING_AMPS 11
#define LIFT1_AMPS 14
#define LIFT2_AMPS 15

char get_lsb(int integer);
char get_msb(int integer);
void send_cmd(unsigned char cc1, unsigned char cc2, int data);
void parse_and_send(unsigned char string[MAX_STRING_SIZE]);

#endif /* MC_PROTOCOL_H_ */