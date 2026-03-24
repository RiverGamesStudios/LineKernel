#include "config.h"
#include "LineRenderer.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

int strcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

// ANSI escape sequence parsing
static int ansi_state = 0;
static char ansi_buffer[16];
static int ansi_index = 0;

// Forward declarations
void terminal_clear(void);
void terminal_set_cursor_pos(const char* params);
void terminal_handle_sgr(const char* params);
void terminal_apply_sgr_code(int code);

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
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (ansi_state == 0) {
		if (c == '\x1b') {
			ansi_state = 1;
			return;
		}
	} else if (ansi_state == 1) {
		if (c == '[') {
			ansi_state = 2;
			ansi_index = 0;
			return;
		} else {
			ansi_state = 0; // Invalid escape, print ESC
			terminal_putentryat('\x1b', terminal_color, terminal_column, terminal_row);
			if (++terminal_column == VGA_WIDTH) {
				terminal_column = 0;
				if (++terminal_row == VGA_HEIGHT) {
					terminal_row = 0;
				}
			}
		}
	} else if (ansi_state == 2) {
		if ((c >= '0' && c <= '9') || c == ';') {
			if (ansi_index < sizeof(ansi_buffer) - 1) {
				ansi_buffer[ansi_index++] = c;
			}
			return;
		} else if (c == 'm') {
			// SGR (Select Graphic Rendition) - color/attribute codes
			ansi_buffer[ansi_index] = '\0';
			terminal_handle_sgr(ansi_buffer);
			ansi_state = 0;
			return;
		} else if (c == 'J') {
			// Clear screen
			ansi_buffer[ansi_index] = '\0';
			if (ansi_index == 0 || strcmp(ansi_buffer, "2") == 0) {
				terminal_clear();
			}
			ansi_state = 0;
			return;
		} else if (c == 'H') {
			// Cursor position
			ansi_buffer[ansi_index] = '\0';
			terminal_set_cursor_pos(ansi_buffer);
			ansi_state = 0;
			return;
		} else {
			// Unknown sequence, ignore
			ansi_state = 0;
			return;
		}
	}
	
	// Normal character
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		if (data[i] == '\n') {
			terminal_row++;
			terminal_column = 0;
		}
		else {
			terminal_putchar(data[i]);
		}
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

void terminal_log(const char* message, const char* status)
{
	terminal_writestring(message);
	terminal_writestring(" [");
	
	// Set color based on status
	if (strcmp(status, "OK") == 0) {
		terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREEN, LineRenderer_DEFAULTBACKGROUND));
	} else if (strcmp(status, "INFO") == 0) {
		terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREY, LineRenderer_DEFAULTBACKGROUND));
	} else if (strcmp(status, "WARN") == 0) {
		terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BROWN, LineRenderer_DEFAULTBACKGROUND));
	} else if (strcmp(status, "ERROR") == 0 || strcmp(status, "FATAL") == 0) {
		terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_RED, LineRenderer_DEFAULTBACKGROUND));
	}
	
	terminal_writestring(status);
	terminal_writestring("]\n");
	
	// Reset to default color
	terminal_setcolor(vga_entry_color(LineRenderer_DEFAULTFOREGROUND, LineRenderer_DEFAULTBACKGROUND));
}

void terminal_clear(void)
{
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	terminal_row = 0;
	terminal_column = 0;
}

void terminal_set_cursor_pos(const char* params)
{
	int row = 0, col = 0;
	
	if (*params == '\0') {
		// Default to 0,0
		terminal_row = 0;
		terminal_column = 0;
		return;
	}
	
	// Parse "row;col" format
	const char* p = params;
	while (*p && *p != ';') {
		if (*p >= '0' && *p <= '9') {
			row = row * 10 + (*p - '0');
		}
		p++;
	}
	if (*p == ';') {
		p++;
		while (*p) {
			if (*p >= '0' && *p <= '9') {
				col = col * 10 + (*p - '0');
			}
			p++;
		}
	}
	
	// Convert to 0-based indexing
	if (row > 0) row--;
	if (col > 0) col--;
	
	// Bounds check
	if (row >= VGA_HEIGHT) row = VGA_HEIGHT - 1;
	if (col >= VGA_WIDTH) col = VGA_WIDTH - 1;
	
	terminal_row = row;
	terminal_column = col;
}

void terminal_handle_sgr(const char* params)
{
	if (*params == '\0') {
		// Reset to default
		terminal_setcolor(vga_entry_color(LineRenderer_DEFAULTFOREGROUND, LineRenderer_DEFAULTBACKGROUND));
		return;
	}
	
	const char* p = params;
	int code = 0;
	
	while (*p) {
		if (*p >= '0' && *p <= '9') {
			code = code * 10 + (*p - '0');
		} else if (*p == ';') {
			// Process the code
			terminal_apply_sgr_code(code);
			code = 0;
		}
		p++;
	}
	// Process the last code
	terminal_apply_sgr_code(code);
}

void terminal_apply_sgr_code(int code)
{
	switch (code) {
		case 0: // Reset
			terminal_setcolor(vga_entry_color(LineRenderer_DEFAULTFOREGROUND, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 30: // Black foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_BLACK, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 31: // Red foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_RED, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 32: // Green foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_GREEN, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 33: // Yellow foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BROWN, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 34: // Blue foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_BLUE, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 35: // Magenta foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 36: // Cyan foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_CYAN, LineRenderer_DEFAULTBACKGROUND));
			break;
		case 37: // White foreground
			terminal_setcolor(vga_entry_color(VGA_COLOR_WHITE, LineRenderer_DEFAULTBACKGROUND));
			break;
		// Add more codes as needed
	}
}
