#include "vga_console.h"
#ifdef vga_console

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

#define VGA_MEMORY  0xB8000

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
uint16_t* vga_terminal_buffer = (uint16_t *) VGA_MEMORY;

void vga_terminal_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void vga_terminal_disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void vga_terminal_update_cursor(int x, int y)
{
	uint16_t pos = y * TERM_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

extern void terminal_setcolor(uint8_t);

void vga_terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_setcolor(vga_entry_color(TERM_DEFAULTFOREGROUND,
			TERM_DEFAULTBACKGROUND));

	for (size_t y = 0; y < TERM_HEIGHT; y++) {
		for (size_t x = 0; x < TERM_WIDTH; x++) {
			const size_t index = y * TERM_WIDTH + x;

			vga_terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void vga_terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * TERM_WIDTH + x;

	vga_terminal_buffer[index] = vga_entry(c, color);
}

void vga_terminal_putchar(char c)
{
	vga_terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == TERM_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == TERM_HEIGHT) {
			terminal_row = 0;
		}
	}
}

void vga_terminal_newline(void)
{
	terminal_row++;
	terminal_column = 0;
}

void vga_terminal_backspace(void)
{
	const size_t index = terminal_row * TERM_WIDTH + terminal_column - 1;

	vga_terminal_buffer[index] = vga_entry(' ', terminal_color);
	terminal_column--;
}

#endif
