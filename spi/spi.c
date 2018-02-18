#include "spi.h"

void send_char(char data)
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)))
	; // wait for transmission to complete
}

char spi_exchange_char(char data)
{
	SPDR = data; // start transmission
	
	while (!(SPSR & (1 << SPIF)))
	; // wait for transmission complete
	
	return SPDR;
}

void spi_send_bytes(char *pdata, char bytes)
{
	int i;

	for (i = 0; i < bytes; i++)
	{
		SPDR = pdata[i]; // start transmission
		while (!(SPSR & (1 << SPIF)))
		; // wait for transmission complete
	}
}

void spi_exchange_bytes(char *mosi, char *miso, char bytes)
{
	int i;

	for (i = 0; i < bytes; i++)
	{
		SPDR = mosi[i]; // start transmission

		while (!(SPSR & (1 << SPIF)))
		; // wait for transmission complete
		miso[i] = SPDR;
	}
}

void spi_master_initialize()
{
	DDRB |= (1 << MOSI) | (1 << SCLK) | (1 << SS);               // outputs                                      // input
	//PORTB |= (1 << SS);                                          // set SS high
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1)| (1 << SPR0) | (1 << CPHA); // Enable SPI, Master, set clock rate fck/128, SPI_MODE1, MSB first
}

unsigned int spi_exchange_int(unsigned int mosi) // not tested
{
	unsigned int miso = 0;
	
	// first send MSB
	SPDR = (char)(mosi >> 8); // start transmission by sending MSB of MOSI

	while (!(SPSR & (1 << SPIF))); // wait for transmission complete
	miso |= (0xFF00) & (SPDR << 8); // store MSB of MISO

	SPDR = (char)mosi; // send LSB of MOSI
	while (!(SPSR & (1 << SPIF))); // wait for transmission complete
	miso |= (0xFF00) & (SPDR); // store LSB of MISO

	return miso;
}

void spi_send_int(unsigned int mosi) // not tested
{
	while (!(SPSR & (1 << SPIF)));
	SPDR = (char)(mosi >> 8); // start transmission by sending MSB of MOSI

	while (!(SPSR & (1 << SPIF)));
	SPDR = (char)mosi; // send LSB of MOSI
}