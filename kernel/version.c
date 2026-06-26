/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "version.h"

void we_are_running(void)
{
	terminal_writestring("Target: " ARCH);
	terminal_writestring("\n\n");
}
