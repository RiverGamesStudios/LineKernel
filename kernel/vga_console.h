#ifndef __VGA_CONSOLE_H__
#define __VGA_CONSOLE_H__
#include "config.h"
#ifdef vga_console

#include <stdint.h>
#include <stddef.h>
#include "bios_tools.h"

void vga_terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void vga_terminal_disable_cursor();
void vga_terminal_update_cursor(int x, int y);
void vga_terminal_setcolor(uint8_t color);
void vga_terminal_initialize(void);
void vga_terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void vga_terminal_putchar(char c);
void vga_terminal_newline(void);
void vga_terminal_backspace(void);

#endif
#endif
