/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "LineRenderer.h"

size_t terminal_column;

void terminal_enable_cursor(void)
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_enable_cursor(
#if defined(CONFIG_CURSOR_SMALL)
		14,
#elif defined(CONFIG_CURSOR_FULL)
		0,
#endif
		15
	);
#endif
}

void terminal_initialize(void)
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_initialize();
#endif
#ifdef CONFIG_SERIAL_CONSOLE
	init_serial();
#endif
#ifdef CONFIG_UART
	uart_init();
#endif
	terminal_enable_cursor();
}

void terminal_putchar(char c)
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_putchar(c);
#endif
#ifdef CONFIG_SERIAL_CONSOLE
	write_serial(c);
#endif
#ifdef CONFIG_UART
	uart_putchar(c);
#endif
}

void terminal_newline(void)
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_newline();
#endif
#ifdef CONFIG_SERIAL_CONSOLE
	write_serial('\r');
	write_serial('\n');
#endif
#ifdef CONFIG_UART
	uart_putchar('\r');
	uart_putchar('\n');
#endif
}

void terminal_backspace(void)
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_backspace();
#endif
#ifdef CONFIG_SERIAL_CONSOLE
	write_serial('\b');
	write_serial(' ');
	write_serial('\b');
#endif
#ifdef CONFIG_UART
	uart_putchar('\b');
	uart_putchar(' ');
	uart_putchar('\b');
#endif
}

void terminal_tab(void)
{
	terminal_putchar(' ');
	terminal_putchar(' ');
	terminal_putchar(' ');
	terminal_putchar(' ');
}

void terminal_write_for_char(const char c)
{
	if (c == '\b')
		terminal_backspace();
	else if (c == '\n')
		terminal_newline();
	else if (c == '\t')
		terminal_tab();
	else if (c != 0)
		terminal_putchar(c);
}

// needed for printf
void _putchar(char character)
{
	terminal_write_for_char(character);
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_write_for_char(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

void terminal_writeint(int data)
{
	if (data < 0) {
		terminal_write_for_char('-');
		data = -data;
	}
	if (data / 10) {
		terminal_writeint(data / 10);
	}
	terminal_write_for_char((data % 10) + '0');
}
