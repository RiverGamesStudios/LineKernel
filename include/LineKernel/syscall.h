/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#ifndef _LineKernel___SYSCALL_H__
#define _LineKernel___SYSCALL_H__

#include <LineKernel/syscall/syscall_ids.h>

#ifdef ARCH_i386
static inline long syscall3(long num, long arg1, long arg2, long arg3)
{
	long ret;
	__asm__ volatile (
		"int $0x80"
		: "=a"(ret)
		: "a"(num), "b"(arg1), "c"(arg2), "d"(arg3)
		: "memory"
	);
	return ret;
}
#else
#error "This arch doesn't support syscalls!"
#endif

#endif
