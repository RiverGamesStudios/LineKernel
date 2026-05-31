#ifndef __PANIC_H__
#define __PANIC_H__

#include "bios_tools.h"
#include "printf.h"
#include "LineRenderer.h"

void panic(const char* format, ...);

#endif
