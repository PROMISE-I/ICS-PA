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

make_instr_func(ret_near_w){
    OPERAND m, imm;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    
    imm.type = OPR_IMM;
    imm.data_size = 16;
    imm.addr = eip + 1;
    
    operand_read(&m);
    operand_read(&imm);
    cpu.eip = m.val;
    cpu.esp += 4;
    cpu.esp += sign_ext(imm.val, 16);
    
    return 0;
}
