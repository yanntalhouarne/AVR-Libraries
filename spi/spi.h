/*
 * spi.h
 *
 * Created: 10/16/2017 7:12:34 PM
 *  Author: talho_000
 */

#include <avr/io.h>

#ifndef SPI_H_
#define SPI_H_

//SPI pins
#define MISO 3
#define MOSI 2
#define SCLK 1
#define SS   0

// setup
	void spi_master_initialize();
// char (one byte)
	void send_char(char data); // send a single char (one byte)
	char spi_exchange_char(char data); // exchange single char (one byte)
// array of char (multiple bytes)
	void spi_send_bytes(char *pdata,char bytes); // send array of char of size "bytes"
	void spi_exchange_bytes(char *mosi, char *miso, char bytes); // exchange array of char of size "bytes"
// int (single int)
	void spi_send_int(unsigned int mosi); // send a int value LSB first
	unsigned int spi_exchange_int(unsigned int mosi); // exchange int value


#endif /* SPI_H_ */