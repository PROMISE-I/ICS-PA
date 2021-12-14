#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/
make_instr_func(lgdt)
{
    OPERAND limit, base;
    
    limit.type = OPR_IMM;
    limit.data_size = 16;
    limit.addr = eip;
    
    base.type = OPR_IMM;
    base.data_size = 32;
    base.addr = eip + 2;
    
    operand_read(&limit);
    operand_read(&base);
    
    cpu.gdtr.limit = limit.val;
    if(data_size == 32) {
        cpu.gdtr.base = base.val;
    }
    else {
        cpu.gdtr.base = (base.val & 0xffffff);
    }
    printf("base: %x, limit: %x\n", cpu.gdtr.base, cpu.gdtr.limit);
    ffush(stdout);
    
    return 6;
}