#include "spi.h"
#include "AS5048a.h"
#include "print.h"

// AS5048a functions

unsigned int AS5048a_send_cmd(unsigned int READ_WRITE, unsigned int ADDRESS)
{
	unsigned int mosi = 0;
	unsigned int miso = 0;
	unsigned int parity = 0;

	mosi |= (READ_WRITE | ADDRESS); // setup MOSI for a READ command (READ_ANGLE)
	parity = AS5048a_compute_parity(mosi); // compute parity on MOSI
	mosi |= (parity<<15); // add the parity bit to mosi
	
	SS_LOW;
		miso = spi_exchange_int(mosi);
	SS_HIGH;
	
	return miso;
}

unsigned int AS5048a_compute_parity(unsigned int word)
{
	unsigned int cnt = 0;
	unsigned char i;

	for (i = 0; i < 15; i++)
	{
		if (word & 0x0001)
			cnt++;
		word >>= 1;
	}

	return (0x0001) & cnt;
}

void AS5048a_check_parity(unsigned int word)
{
	unsigned int computed_parity = 0;
	unsigned int received_parity = 0;
	
	computed_parity = AS5048a_compute_parity(word); // compute parity on MISO
	received_parity = ( ((0x8000)&word) >> 15 ); // get bit 15 of miso

	if (computed_parity != received_parity)
	{
		println("Computed parity does not match received parity;");
	}
}

void AS5048a_clear_and_read_errors()
{
	unsigned int miso = 0;
	
	// send CLEAR_ERROR_FLAG command
	AS5048a_send_cmd(READ, CLEAR_ERROR_FLAG);
	
	//get error register content
	SS_LOW;
		miso = spi_exchange_int(NO_OP); // get error register content
	SS_HIGH;
	
	// check which error occurred
	if ( (1<<FRAME_ERROR_BIT) & miso )
		println("Framing error;");
	if ( (1<<COMMAND_ERROR_BIT) & miso )
		println("Invalid command;");
	if ( (1<<PARITY_ERROR_BIT) & miso )
		println("Parity error;");
	else
		println("Could not resolve error;");
	print_char(NL);
}

int angle_to_degrees(unsigned int angle)
{
	angle &= 0x3FFF; // mask parity and error flag bits
	angle *= ANGLE_TO_DEGREES;
	angle /= 10;
	
	return angle;;
}

unsigned int AS5048a_send_data(unsigned int data)
{
	unsigned int miso = 0;
	unsigned int parity = 0;

	parity = AS5048a_compute_parity(data); // compute parity on data
	data |= (parity<<15); // add the parity bit to data
	
	SS_LOW;
		miso = spi_exchange_int(data); // send data
	SS_HIGH;
	
	return miso;
}

void zero_angle()
{
	int position = 0;
	unsigned int OTP_HI_position = 0;
	unsigned int OTP_LOW_position = 0;
	
	AS5048a_send_cmd(WRITE,OTP_HI); // select the OTP HI register
	AS5048a_send_data(0x0000);	// write zero to it to clear it
	AS5048a_send_cmd(WRITE,OTP_LOW); // select the OTP LOW register
	AS5048a_send_data(0x0000); // write zero to it to clear it
	
	position = AS5048a_get_angle();
	
	OTP_HI_position = (position>>6) & OTP_HI_mask;
	OTP_LOW_position = position & OTP_LOW_mask;
	
	AS5048a_send_cmd(WRITE,OTP_HI); // select the OTP HI register
	AS5048a_send_data(OTP_HI_position);	// write zero to it
	AS5048a_send_cmd(WRITE,OTP_LOW); // select the OTP LOW register
	AS5048a_send_data(OTP_LOW_position); // write zero to it
}

int AS5048a_get_angle()
{
	AS5048a_send_cmd(READ,READ_ANGLE);
	AS5048a_send_data(NO_OP);
}