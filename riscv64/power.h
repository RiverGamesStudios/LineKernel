#ifndef __POWER_H__
#define __POWER_H__

#define SYSCON_ADDR 0x100000
#include <stdint.h>
void poweroff(void);
void reboot(void);

#endif
