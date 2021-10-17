#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/
make_instr_func(push_ebp){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.ebp;
    
    operand_write(m);
    cpu.esp += 4;
    
    return 1;
}
