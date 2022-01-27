#include "cpu/intr.h"
#include "cpu/instr.h"

/*
Put the implementations of `int' instructions here.

Special note for `int': please use the instruction name `int_' instead of `int'.
*/
make_instr_func(int_)
{
    OPERAND imm;

    imm.type = OPR_IMM;
    imm.data_size = 8;
    imm.addr = eip + 1;
    
    operand_read(&imm);
    
    raise_sw_intr(0x80);
    
    print_asm_0("int_", "b", 2);
    return 0;
}
