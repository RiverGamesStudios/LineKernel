# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: Copyright (C) 2026 River Games

lineindent()
{
    indent -bad -bap -br -ce -cdw -npcs -ncs -nbc -npsl -brs -blf -ut -l100 -ngts -fca -fnc -nlps -ncdw -i4 -ts4 -nlp -pal $1/*.c $1/*.h
    rm $1/*.c~ $1/*.h~
}

lineindent i386
lineindent x86
lineindent x86_64
lineindent riscv64
