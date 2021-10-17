#include "cpu/instr.h"
/*
Put the implementations of `test' instructions here.
*/
make_instr_func(test_r2rm_v){
    OPERAND r, rm;
    
    int len = 1;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip + 1, &r, &rm);
    
    alu_and(r.val, rm.val);
    
    return len;
}