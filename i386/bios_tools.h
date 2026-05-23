#ifndef __BIOS_TOOLS_H__
#define __BIOS_TOOLS_H__
#include <stdint.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
void io_wait(void);
void insl(int port, uint32_t addr, int cnt);

#endif
