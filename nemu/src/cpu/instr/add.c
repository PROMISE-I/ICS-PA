#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/
make_instr_func(add_i2rm_v){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size; 
    len += modrm_rm(eip+1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = data_size;
    
    operand_read(&rm);
    operand_read(&imm);
    rm.val += imm.val;
    operand_write(&rm);
    
    return len + data_size/8;
}

make_instr_func(add_i2a_v){
    OPERAND imm;
    
    int len = 1;
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;
    
    operand_read(&imm);
    cpu.eax = alu_add(cpu.eax, sign_ext(imm.val, data_size));
    
    return len + data_size/8;
}
