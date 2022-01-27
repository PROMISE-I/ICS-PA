#include "cpu/instr.h"
/*
Put the implementations of `iret' instructions here.
*/
make_instr_func(iret)
{
    pop_cs(0,0);
    pop_eip(0,0);
    pop_eflags(0,0);
    
    return 1;
}
