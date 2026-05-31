#ifndef __POWER_H__
#define __POWER_H__

#include <stdint.h>

#define SYSCON_ADDR 0x100000
void poweroff(void);
void reboot(void);

#endif
