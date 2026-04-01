#ifndef __KPRINTF_H__
#define __KPRINTF_H__

#define NANOPRINTF_IMPLEMENTATION
#include "third-party/nanoprintf.h"

#define kprintf(...) npf_pprintf(&terminal_putc, NULL, __VA_ARGS__)

#endif
