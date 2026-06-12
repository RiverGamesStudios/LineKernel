#ifndef __PANIC_H__
#define __PANIC_H__

#include "LineRenderer.h"
#include "power.h"
#include "printf.h"
#include "random.h"

char* random_error_message(void);
void panic(const char* format, ...);

#endif
