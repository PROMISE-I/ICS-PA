#include "cpu/instr.h"
/*
Put the implementations of `ret' instructions here.
*/
make_instr_func(ret_near){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.eip = m.val;
    cpu.esp += 4;
    
    return 0;
}
