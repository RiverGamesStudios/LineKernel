#include "power.h"

void reboot(void)
{
    __asm__ volatile ("JMP 0xFFFF");
}

void poweroff(void)
{
}
