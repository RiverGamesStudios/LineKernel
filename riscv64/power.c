#include "power.h"

void poweroff(void)
{
	*(uint32_t *) SYSCON_ADDR = 0x5555;
}

void reboot(void)
{
	*(uint32_t *) SYSCON_ADDR = 0x7777;
}
