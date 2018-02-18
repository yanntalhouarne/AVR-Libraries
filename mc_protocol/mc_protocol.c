/*
 * mc_protocol.c
 *
 * Created: 11/1/2017 12:44:03 AM
 *  Author: talho_000
 */

#include "mc_protocol.h"

char get_lsb(int integer)
{
    return (char)(LSB & integer); // #define LSB 0x00FF
}

char get_msb(int integer)
{
    return (char)((MSB & integer) >> 8); // #define MSB 0xFF00
}

void send_cmd(unsigned char cc1, unsigned char cc2, int data)
{
    char packet[6] = {'*', cc1, cc2, 0, 0, 0}; // [*][CC1][CC2][MSB][LSB][CS]
    int checksum = 0;

    // put 'value' in the packet
    packet[4] = get_lsb(data); // put LSB of 'value' to 4th byte
    packet[3] = get_msb(data); // put MSB of 'value' to 3rd byte

    // compute check sum and put in the packet
    for (int j = 1; j < 5; j++)
    {
        checksum += (int)(packet[j]);
    }
    packet[5] = (char)(LSB & checksum);

    // send packet to USART
    for (int i = 0; i < 6; i++)
    {
        usart1_send_char(packet[i]);
        _delay_ms(2);
    }
}

void parse_and_send(unsigned char string[MAX_STRING_SIZE])
{
    unsigned char cc1 = 0;
    int cc2 = 0;
    int data = 0;
    char data_ascii[MAX_DATA_SIZE];
    unsigned char i = 0;
    unsigned char j = 0;

    if (string[0] == '*') // check control character
    {
        if (string[1] == ',') // check format
        {
            cc1 = string[2]; // update cc1

            if (string[3] == ',') // check format

                while (string[4 + i] != ',')
                {
                    data_ascii[i] = string[4 + i];
                    i++;
                }
            data_ascii[i + 1] = NL;
            i += 5;
            cc2 = atoi(data_ascii);

            while (string[i] != NL)
            {
                data_ascii[j] = string[i];
                i++;
                j++;
            }

            data_ascii[j + 1] = NL;
            data = atoi(data_ascii);

            send_cmd(cc1, cc2, data);
			//println(data);
        }
    }
}

