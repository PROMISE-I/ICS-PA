#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/
make_instr_func(push_ebp){
    OPERAND m;
    
    cpu.esp += 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.ebp;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_ebx){
    OPERAND m;
    
    cpu.esp += 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.ebx;
    
    operand_write(&m);
    
    return 1;
}
