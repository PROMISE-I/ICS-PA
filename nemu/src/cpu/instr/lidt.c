#include "cpu/instr.h"
/*
Put the implementations of `lidt' instructions here.
*/
make_instr_func(lidt)
{
    uint32_t len = 1;
    OPERAND mem, base, limit;
    
    mem.data_size = 32;
    len += modrm_rm(eip+1, &mem);

    limit.type = OPR_MEM;
    limit.data_size = 16;
    limit.addr = mem.addr;
    
    base.type = OPR_MEM;
    base.data_size = 32;
    base.addr = mem.addr + 2;

    operand_read(&limit);
    operand_read(&base);

    cpu.idtr.limit = limit.val;
    if(data_size == 32) {
            cpu.idtr.base = base.val;
        }
    else {
        cpu.idtr.base = (base.val & 0xffffff);
    }
    print_asm_0("lidt", "l", 3);
    return len;
}
