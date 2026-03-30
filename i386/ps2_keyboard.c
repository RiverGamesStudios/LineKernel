// phoenixcoe got eaten by a grue
// or he got mauled by a bear, idk
// it could also possibly be SAM, he seems suspiciously quiet
#include "config.h"
#ifdef ps2_keyboard
#include "ps2_keyboard.h"
#include "bios_tools.h"

static int is_shift_pressed = 0;

void wait_kbd_write()
{
	while (inb(PS2_STATUS_PORT) & PS2_STATUS_INPUT_FULL);
}

int is_kbd_ready_to_read()
{
	return (!(inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_FULL));
}

void wait_kbd_read()
{
	while (!(inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_FULL));
}

// i think phoenix also found a way to get eaten by a troll, but that seems less likely than the other two options
// best regards,

void keyboard_init()
{
	wait_kbd_write();
	outb(PS2_DATA_PORT, KBD_CMD_SCAN_ON);
}

uint8_t keyboard_read_scancode()
{
	wait_kbd_read();
	return inb(PS2_DATA_PORT);
}

uint8_t keyboard_read_scancode_right_now()
{
	return inb(PS2_DATA_PORT);
}

static const char ascii_table[] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static const char shift_ascii_table[] =
{
	0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0,
	'|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' '
};

char keyboard_to_ascii(uint8_t scancode)
{
	if (scancode == 0x2A || scancode == 0x36) {
		is_shift_pressed = 1;
		return 0;
	}

	if (scancode == 0xAA || scancode == 0xB6) {
		is_shift_pressed = 0;
		return 0;
	}

	if (scancode & 0x80) {
		return 0; 
	}
	
	if (scancode < sizeof(ascii_table)) {
		return is_shift_pressed ? shift_ascii_table[scancode] : ascii_table[scancode];
	}
	
	return 0;
}

char keyboard_read_scancode_to_ascii_right_now()
{
	uint8_t scancode = keyboard_read_scancode_right_now();
	char c = keyboard_to_ascii(scancode);
	return c;
}

char keyboard_read_scancode_to_ascii()
{
	uint8_t scancode = keyboard_read_scancode();
	char c = keyboard_to_ascii(scancode);
	return c;
}

#endif // ps2_keyboard
