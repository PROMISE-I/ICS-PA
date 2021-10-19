#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/
make_instr_func(leave){
    cpu.esp = cpu.ebp;
    pop_ebp();
    return 1;
}
