#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_near_indirect)
{
    OPERAND rm, m;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    cpu.esp -= 4;
    m.data_size = 32;
    m.type = OPR_MEM;
    m.addr = cpu.esp;
    
    m.val = cpu.eip + len;
    operand_write(&m);
    
    operand_read(&rm);
    cpu.eip = rm.val;
    
    return 0;
}

make_instr_func(call_near){
    OPERAND imm,m;
    
    int len = 1;
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + len;

    cpu.esp -= 4;
    m.type = OPR_MEM;
    m.data_size = 32;
    m.addr = cpu.esp;
    m.val = eip + 1 + data_size / 8;
    
    operand_write(&m);
    operand_read(&imm);
    
    return len + data_size / 8 + imm.val;
}

