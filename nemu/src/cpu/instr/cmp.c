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

make_instr_func(cmp_r2rm_v){
    OPERAND r, rm;

    int len = 1;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    alu_sub(r.val ,rm.val, data_size);
    
    return len;
}