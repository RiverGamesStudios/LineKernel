/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "version.h"

void we_are_running(void)
{
	// Todo: bring this back
	// terminal_writestring("Flags: ");
	// terminal_writestring("\n");
	terminal_writestring("Target: " ARCH);
	terminal_writestring("\n\n");
}
