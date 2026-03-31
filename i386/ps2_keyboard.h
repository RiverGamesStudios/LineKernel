#ifndef __PS2_KEYBOARD_H__
#define __PS2_KEYBOARD_H__

#include "bios_tools.h"
#include <stdint.h>

#define PS2_DATA_PORT 0x60
#define PS2_STATUS_PORT 0x64
#define PS2_COMMAND_PORT 0x64

#define KBD_CMD_SET_LED 0xED
#define KBD_CMD_ECHO 0xEE
#define KBD_CMD_SCAN_ON 0xF4
#define KBD_CMD_SCAN_OFF 0xF5
#define KBD_CMD_RESET 0xFF

#define PS2_STATUS_OUTPUT_FULL 0x01
#define PS2_STATUS_INPUT_FULL 0x02

void keyboard_init();
uint8_t keyboard_read_scancode();
uint8_t keyboard_read_scancode_right_now();
char keyboard_to_ascii(uint8_t scancode);
char keyboard_read_scancode_to_ascii();
char keyboard_read_scancode_to_ascii_right_now();
int is_kbd_ready_to_read();

#endif
