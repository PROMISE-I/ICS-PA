#include "cpu/instr.h"
/*
Put the implementations of `call' instructions here.
*/
make_instr_func(call_near){
    OPERAND imm;
    
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;

    operand_read(&imm);
    cpu.eip = imm.val;
    
    return 0;
}

