#ifndef __LINERENDERER_H__
#define __LINERENDERER_H__

#include "config.h"
#include <stddef.h>
#include <stdint.h>
#include "str.h"
#ifdef serial_console
#include "serial.h"
#endif // serial_console
#ifdef vga_console
#include "vga_console.h"
#endif // vga_console

void terminal_initialize(void);

void terminal_setcolor(uint8_t color);

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

void terminal_putc(int ch, void* stream);

void terminal_putchar(char c);

void terminal_newline(void);

void terminal_tab(void);

void terminal_backspace(void);

void terminal_write_for_char(const char data);

void terminal_write(const char* data, size_t size);

void terminal_writestring(const char* data);

void terminal_writeint(int data);

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);

void terminal_disable_cursor();

void terminal_update_cursor(int x, int y);

#endif
