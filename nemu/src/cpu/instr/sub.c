#include "cpu/instr.h"
/*
Put the implementations of `sub' instructions here.
*/
make_instr_func(sub_i2rm_bv){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    imm.type = OPR_IMM;
    imm.data_size = 8;
    imm.addr = eip + len;
    len += 1;
    
    operand_read(&rm);
    operand_read(&imm);
    rm.val = alu.sub(sign_ext(imm.val, 8), rm.val, data_size);
    operand_write(&rm);
    
    return len;
}
