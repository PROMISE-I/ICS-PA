#include "cpu/instr.h"
/*
Put the implementations of `adc' instructions here.
*/
make_instr_func(adc_r2rm_v){
    OPERAND r, rm;
    
    int len = 1;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    rm.val = alu_adc(r.val, rm.val, data_size);
    operand_write(&rm);
    
    print_asm_2("adc", "v", len, &r, &rm);
    
    return len;
}
