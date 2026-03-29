#include "config.h"
#include "LineRenderer.h"
#include "bios_tools.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#ifdef serial_console
#include "serial.h"
#endif // serial_console

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void terminal_disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void terminal_update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_setcolor(vga_entry_color(LineRenderer_DEFAULTFOREGROUND, LineRenderer_DEFAULTBACKGROUND));
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
#ifdef serial_console
	init_serial();
#endif // serial_console
#if !defined(vga_console) || !defined(console_cursor)
	terminal_disable_cursor();
#endif // !defined(vga_console) || !defined(console_cursor)
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
#ifdef vga_console
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
#endif // vga_console
}

void terminal_putchar(char c)
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
#ifdef serial_console
	write_serial(c);
#endif // serial_console
}

void terminal_newline(void)
{
	terminal_row++;
	terminal_column = 0;
#ifdef serial_console
	write_serial('\r');
	write_serial('\n');
#endif // serial_console
}

void terminal_backspace(void)
{
	const size_t index = terminal_row * VGA_WIDTH + terminal_column - 1;
	terminal_buffer[index] = vga_entry(' ', terminal_color);
	terminal_column--;
#ifdef serial_console
	write_serial('\b');
#endif // serial_console
}

void terminal_write_for_char(const char c)
{
	if (c == '\b') {
		terminal_backspace();
	}
	else if (c == '\n') {
		terminal_newline();
	}
	else if (c != 0) {
		terminal_putchar(c);
	}
	terminal_update_cursor(terminal_column, terminal_row);
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
