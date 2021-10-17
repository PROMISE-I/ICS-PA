#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/

make_instr_func(cmp_i2rm_bv){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = 8;
    
    operand_read(&imm);
    imm.val = sign_ext(imm.val, data_size);
    operand_read(&rm);
    alu_sub(imm.val, rm.val, data_size);
    
    return len + 1;
}