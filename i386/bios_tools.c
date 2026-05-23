#include "bios_tools.h"

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	__asm__ volatile ("inb %w1, %b0":"=a" (ret)
		:"Nd"(port)
		:"memory");

	return ret;
}

void outb(uint16_t port, uint8_t val)
{
	__asm__ volatile ("outb %b0, %w1"::"a" (val), "Nd"(port):"memory");
}

void io_wait(void)
{
	outb(0x80, 0);
}

void insl(int port, uint32_t addr, int cnt)
{
	asm volatile ("cld; rep insl":
		"=D" (addr), "=c"(cnt): "d"(port), "0"(addr), "1"(cnt): "memory", "cc");
}
