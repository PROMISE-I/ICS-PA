#include "cpu/instr.h"
/*
Put the implementations of `and' instructions here.
*/
make_instr_func(and_i2rm_bv){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    imm.type = OPR_IMM;
    imm.data_size = 8;
    imm.addr = eip + len;
    
    operand_read(&rm);
    operand_read(&imm);
    imm.val = sign_ext(imm, 8);
    rm.val = alu_and(imm.val, rm.val);
    operand_write(&rm);
    
    return len + 1;
}