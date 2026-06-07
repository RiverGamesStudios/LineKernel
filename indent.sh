lineindent()
{
    indent -bad -bap -br -ce -cdw -npcs -ncs -nbc -npsl -brs -blf -ut -l100 -ngts -fca -fnc -nlps -ncdw -i4 -ts4 -nlp -pal $1/*.c $1/*.h
}

lineindent i386
lineindent x86
lineindent x86_64
lineindent riscv64
