/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "power.h"

void reboot(void)
{
	__asm__ volatile ("jmp 0xFFFF");
}

void poweroff(void)
{
	/* TODO: ACPI */
}

void halt(void)
{
	__asm__ volatile ("cli");

	while (1) {
		__asm__ volatile ("hlt");
	}
}
