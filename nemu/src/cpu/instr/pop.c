#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/
make_instr_func(pop_ebx){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.ebx = m.val;
    esp += 4;
    
    return 1;
}

make_instr_func(pop_ebp){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.ebp = m.val;
    esp += 4;
    
    return 1;
}
