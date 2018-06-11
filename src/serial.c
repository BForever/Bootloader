#include "serial.h"

void init_serial()
{
	oportb(COM0_PORT + 1, 0x00);
	/* enable to set divisor of bauds */
	oportb(COM0_PORT + 3, 0x80);
	/* 0x0c means bands rate is 9600 */
	oportb(COM0_PORT + 0, 0x0c);
	oportb(COM0_PORT + 1, 0x00);
	/* 8 bits, 1 stop, no parity */
	oportb(COM0_PORT + 3, 0x03);
	/* enable fifo, clear them, with 14-byte threshold */
	oportb(COM0_PORT + 2, 0xC7);
	/* if want to enable interrupt, add here, COM0_PORT + 4 */
}

/* check whether receive data */
int is_serial_received()
{
	return iportb(COM0_PORT + 5) & 0x01;
}

uint8_t read_serial()
{
	while(is_serial_received() == 0)
		;
	
	return iportb(COM0_PORT + 0);
}

int is_transmit_empty()
{
	return iportb(COM0_PORT + 5) & 0x20;
}

void write_serial(uint8_t c)
{
	while(is_transmit_empty() == 0)
		;
	
	oportb(COM0_PORT + 0, c);
}

void print(uint8_t *string)
{
	while (*string){
		write_serial(*string);
		string++;
	}
}

void println(uint8_t *string)
{
	print(string);
	write_serial(0x0A);
	write_serial(0x0D);
}


void test_serial()
{
	init_serial();
	char c;
	
	while(1){
		c = read_serial();
		if(c == '\r')write_serial('\n');
		write_serial(c);
	}
}