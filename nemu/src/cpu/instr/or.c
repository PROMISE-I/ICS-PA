#include "cpu/instr.h"
/*
Put the implementations of `or' instructions here.
*/
make_instr_func(or_r2rm_b){
    OPERAND r, rm;
    
    int len = 1;
    r.data_size = 8;
    rm.data_size = 8;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    rm.val = alu_or(r.val, rm.val, 8);
    operand_write(&rm);
    
    return len;
}

make_instr_func(or_r2rm_v){
    OPERAND r, rm;
    
    int len = 1;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    rm.val = alu_or(r.val, rm.val, data_size);
    operand_write(&rm);
    
    return len;
}

make_instr_func(or_rm2r_b){
    OPERAND r, rm;
    
    int len = 1;
    r.data_size = 8;
    rm.data_size = 8;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    r.val = alu_or(r.val, rm.val, 8);
    operand_write(&r);
    
    return len;
}

make_instr_func(or_rm2r_v){
    OPERAND r, rm;
    
    int len = 1;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    r.val = alu_or(r.val, rm.val, data_size);
    operand_write(&r);
    
    return len;
}
