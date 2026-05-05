#include "LineRenderer.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
#ifdef vga_console
	vga_terminal_enable_cursor(cursor_start, cursor_end);
#endif // vga_console
}

void terminal_disable_cursor()
{
#ifdef vga_console
	vga_terminal_disable_cursor();
#endif // vga_console
}

void terminal_update_cursor(int x, int y)
{
#ifdef vga_console
	vga_terminal_update_cursor(x, y);
#endif // vga_console
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_initialize(void)
{
#ifdef vga_console
	vga_terminal_initialize();
#endif // vga_console
#ifdef serial_console
	init_serial();
#endif // serial_console
#if !defined(vga_console) || !defined(console_cursor)
	terminal_disable_cursor();
#endif // !defined(vga_console) || !defined(console_cursor)
}

void terminal_putchar(char c)
{
#ifdef vga_console
	vga_terminal_putchar(c);
#endif // vga_console
#ifdef serial_console
	write_serial(c);
#endif // serial_console
}

void terminal_newline(void)
{
#ifdef vga_console
	vga_terminal_newline();
#endif // vga_console
#ifdef serial_console
	write_serial('\r');
	write_serial('\n');
#endif // serial_console
}

void terminal_backspace(void)
{
#ifdef vga_console
	vga_terminal_backspace();
#endif // vga_console
#ifdef serial_console
	write_serial('\b');
	write_serial(' ');
	write_serial('\b');
	if (terminal_column == (size_t)-1) {
		// ^[1A - Move cursor one line up
		write_serial('\033');
		write_serial('[');
		write_serial('1');
		write_serial('A');
		// ^[999C - Move cursor 999 characters right
		write_serial('\033');
		write_serial('[');
		write_serial('9');
		write_serial('9');
		write_serial('9');
		write_serial('C');
	}
#endif // serial_console
}

void terminal_write_for_char(const char c)
{
	if (c == '\b')
		terminal_backspace();
	else if (c == '\n')
		terminal_newline();
	else if (c != 0)
		terminal_putchar(c);
#ifdef console_cursor
	terminal_update_cursor(terminal_column, terminal_row);
#endif
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
