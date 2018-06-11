#ifndef _SERIAL_H
#define _SERIAL_H
#include "inttypes.h"
#include "io.h"

#define  COM0_PORT  0x3f8

void init_serial();
int is_serial_received();
uint8_t read_serial();
int is_transmit_empty();
void write_serial(uint8_t c);
void test_serial();
#endif //_SERIAL_H
