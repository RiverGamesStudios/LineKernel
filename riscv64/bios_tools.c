#include "bios_tools.h"

void halt(void)
{
	__asm__ volatile ("wfi");
}
