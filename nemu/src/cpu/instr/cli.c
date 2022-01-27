#include "cpu/instr.h"
/*
Put the implementations of `cli' instructions here.
*/
make_instr_func(cli)
{
    uint32_t len = 1;
    cpu.eflags.IF = 0;
    return len;
}

