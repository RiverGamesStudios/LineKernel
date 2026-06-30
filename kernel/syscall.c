/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "LineKernel/syscall/syscall_ids.h"
#include <stdint.h>
#include "LineRenderer.h"
#include "LineColor.h"

#define COMMAND2TABLE(name) [SYS_##name] = sys_##name

#define DEFINECALL(name, ...) int sys_##name(__VA_ARGS__); \
	int sys_##name(__VA_ARGS__)

typedef int (*syscall_t)(long, long, long, long, long, long);

DEFINECALL(print2, uintptr_t read)
{
	terminal_writestring((char*)read);
	return 0;
}

DEFINECALL(termcolor, linecolor_t fg_color, linecolor_t bg_color)
{
	terminal_setcolor(fg_color, bg_color);
	return 0;
}

DEFINECALL(termscolor, void)
{
	terminal_resetcolor();
	return 0;
}

DEFINECALL(termclear, void)
{
	terminal_cls();
	return 0;
}

DEFINECALL(termcursor, int x, int y)
{
	terminal_update_cursor(x, y);
	return 0;
}

void* syscall_table[] = {
	COMMAND2TABLE(print2),
	COMMAND2TABLE(termcolor),
	COMMAND2TABLE(termscolor),
	COMMAND2TABLE(termclear),
	COMMAND2TABLE(termcursor),
};
