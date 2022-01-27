#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/

make_instr_func(lgdt)
{
#ifdef IA32_SEG
        int len = 1;
        OPERAND rm, limit, base;
        
        rm.data_size = 32;
        len += modrm_rm(eip+1, &rm);

        limit.type = OPR_IMM;
        limit.data_size = 16;
        limit.addr = rm.addr;
        
        base.type = OPR_IMM;
        base.data_size = 32;
        base.addr = rm.addr + 2;
        
        operand_read(&limit);
        operand_read(&base);
        
        cpu.gdtr.limit = limit.val;
        if(data_size == 32) {
            cpu.gdtr.base = base.val;
        }
        else {
            cpu.gdtr.base = (base.val & 0xffffff);
        }
        print_asm_2("lgdt", "", 6, &limit, &base);
        //printf("base: %x, limit: %x\n", cpu.gdtr.base, cpu.gdtr.limit);
        //fflush(stdout);
#endif        
        return len;
}
