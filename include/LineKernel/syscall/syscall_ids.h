/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#ifndef _LineKernel___SYSCALL_IDS_H__
#define _LineKernel___SYSCALL_IDS_H__

#if !defined(_LineKernel___SYSCALL_H__) && defined(__LineCore__)
#error "Don't include this, include <LineKernel/syscall.h>!"
#endif

/* Easy to read? */
#define SYS_print2      0
#define SYS_termcolor   1
#define SYS_termscolor  2
#define SYS_termclear   3
#define SYS_termcursor  4

#endif
