# Syscalls
Remember, when adding syscalls, you need to modify:
- **[`syscall.h`](kernel/syscall.h)** (add your syscall number and function declaration)
- **all `syscall.s` files** (change max syscall to yours + 1)
    Note: you can search across files for `REPLACEMAXSYSCALL` if you have trouble finding it.
- **[`syscall.c`](kernel/syscall.c)** (add your syscall function and add your syscall to `syscall_table`)

<!--
SPDX-License-Identifier: CC0-1.0
SPDX-FileCopyrightText: Copyright (C) 2026 River Games
-->
