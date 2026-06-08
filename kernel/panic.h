#ifndef __PANIC_H__
#define __PANIC_H__

#include "bios_tools.h"
#include "printf.h"
#include "LineRenderer.h"

char* random_error_message(void);
void panic(const char* format, ...);

#endif
