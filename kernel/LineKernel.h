/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#ifndef __LINEKERNEL_H__
#define __LINEKERNEL_H__

#include "kernelcheck.h"
#include "version.h"
#include "syscall.h"
#include "LineRenderer.h"
#include "LineInput.h"
#include "LineColor.h"
#include "LineDrive.h"
#include "LineFilesystem.h"
#include "version.h"
#include "printf.h"
#ifdef CONFIG_PS2_KEYBOARD
#include "ps2_keyboard.h"
#endif
#ifdef CONFIG_SERIAL_CONSOLE
#include "serial.h"
#endif
#ifdef CONFIG_UART
#include "uart.h"
#endif

#ifdef ARCH_i386
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#endif
#ifdef CONFIG_FLOPPY
#include "floppy.h"
#endif

void initialize_start(void);
void kernel_main(void);
void handle_single_argument(char* arg);
void parse_cmdline(char* cmdline);

extern char cmdline_str[100];

#endif
