#include "cpu/instr.h"
/*
Put the implementations of `sti' instructions here.
*/
make_instr_func(std){
    cpu.eflags.DF = 1;
    return 1;
}

make_instr_func(sti){
    cpu.eflags.IF = 1;
    return 1;
}
