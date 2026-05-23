#include "LineRenderer.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;

void terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_enable_cursor(cursor_start, cursor_end);
#endif
}

void terminal_disable_cursor()
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_disable_cursor();
#endif
}

void terminal_update_cursor(int x, int y)
{
#ifdef CONFIG_VGA_CONSOLE
	vga_terminal_update_cursor(x, y);
#endif
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
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
#endif
}

void terminal_write_for_char(const char c)
{
	if (c == '\b')
		terminal_backspace();
	else if (c == '\n')
		terminal_newline();
	else if (c != 0)
		terminal_putchar(c);
	terminal_update_cursor(terminal_column, terminal_row);
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
