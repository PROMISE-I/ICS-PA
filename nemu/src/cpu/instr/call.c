#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_near){
    OPERAND imm,m;
    
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;

    cpu.esp += 4;
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = eip + 1 + data_size/8;
    
    operand_write(&m);
    operand_read(&imm);
    
    cpu.eip = imm.val;
    
    return 0;
}

