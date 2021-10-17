#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
make_instr_func(inc_rm_v){
    OPERAND rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    operand_read(&rm);
    rm.val++;
    operand_write(&rm);
    
    return len;
}
