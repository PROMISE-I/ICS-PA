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
    
    return len + data_size/8s;
}
