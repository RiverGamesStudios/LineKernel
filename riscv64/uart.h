#ifndef __UART_H__
#define __UART_H__

#include "kconfig.h"
#ifdef CONFIG_UART

#define UART_ADDR 0x10000000

#include <stdint.h>
#include <stddef.h>
void uart_putchar(char c);
void uart_init();

#endif
#endif
