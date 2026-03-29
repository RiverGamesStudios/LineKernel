// phoenixcoe got eaten by a grue
// or he got mauled by a bear, idk
// it could also possibly be SAM, he seems suspiciously quiet
#include "config.h"
#ifdef ps2_keyboard
#include "ps2_keyboard.h"
#include "bios_tools.h"

void wait_kbd_write()
{
	while (inb(PS2_STATUS_PORT) & PS2_STATUS_INPUT_FULL);
}

void wait_kbd_read()
{
	while (!(inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_FULL));
}

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

static const char ascii_table[] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char keyboard_to_ascii(uint8_t scancode)
{
	if (scancode & 0x80) {
		return 0; 
	}
	
	if (scancode < sizeof(ascii_table)) {
		return ascii_table[scancode];
	}
	
	return 0;
}

char keyboard_read_scancode_to_ascii()
{
	uint8_t scancode = keyboard_read_scancode();
	char c = keyboard_to_ascii(scancode);
	return c;
}

#endif // ps2_keyboard
