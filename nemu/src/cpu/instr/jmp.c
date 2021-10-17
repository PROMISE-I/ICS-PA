#include "cpu/instr.h"

make_instr_func(jmp_near)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;

    operand_read(&rel);

    int offset = sign_ext(rel.val, data_size);
    // thank Ting Xu from CS'17 for finding this bug
    print_asm_1("jmp", "", 1 + data_size / 8, &rel);

    cpu.eip += offset;

    return 1 + data_size / 8;
}

make_instr_func(je_short){
    OPERAND imm;

    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    
    if(cpu.eflags.ZF == 1){
        operand_read(&imm);
        len += imm.val;
    }
    
    return len;
}

make_instr_func(jg_short){
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(((cpu.eflags.SF ^ cpu.eflags.OF) | cpu.eflags.ZF) == 0){
        operand_read(&imm);
        len += imm.val;
    }
    
    return len;
}

make_instr_func(jle_short){
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(((cpu.eflags.SF ^ cpu.eflags.OF) | cpu.eflags.ZF) == 1){
        operand_read(&imm);
        len += imm.val;
    }
    
    return len;
}

make_instr_func(jne_short){
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(cpu.eflags.ZF == 0){
        operand_read(&imm);
        len += imm.val;
    }
    
    return len;
}
