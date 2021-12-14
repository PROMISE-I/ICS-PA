#include "cpu/instr.h"
/*
Put the implementations of `leave' instructions here.
*/
make_instr_func(leave){
    OPERAND m;
    m.type = OPR_MEM;
    m.sreg = SERG_DS;
    m.data_size = 32;
    m.addr = cpu.ebp;
    
    operand_read(&m);
    cpu.esp = cpu.ebp;
    cpu.ebp = m.val;
    cpu.esp += 4;
    
    return 1;
}
