#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/
make_instr_func(add_i2rm_b){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = 8; 
    len += modrm_rm(eip+1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = 8;
    
    operand_read(&rm);
    operand_read(&imm);
    rm.val += imm.val;
    operand_write(&rm);
    
    return len + 1;
}
