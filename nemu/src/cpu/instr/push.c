#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/
make_instr_func(push_ebp){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.ebp;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_ebx){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = cpu.ebx;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_rm_v){
    OPERAND rm, m;
    
    int len = 1;
    cpu.esp -= 4;
    
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    
    operand_read(&rm);
    m.val = rm.val;
    operand_write(&m);
    
    return len;
}
