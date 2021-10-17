#include "cpu/instr.h"
/*
Put the implementations of `lea' instructions here.
*/
make_instr_func(lea){
    OPERAND m, r;
    
    int len = 1;
    m.data_size = 32;
    r.data_size = data_size;
    len += modrm_r_rm(eip + 1, &r, &m);
    
    r.val = m.addr;
    operand_write(&r);
    
    return len;
}
