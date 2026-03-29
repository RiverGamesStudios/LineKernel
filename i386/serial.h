#ifndef __SERIAL_H__
#define __SERIAL_H__

#define PORT 0x3f8

int init_serial();

int serial_received();

char read_serial_right_now();

char read_serial();

char serial_sane_control_codes(const char c);

int is_transmit_empty();

void write_serial(char a);

#endif
