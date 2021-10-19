#include "cpu/instr.h"
/*
Put the implementations of `dec' instructions here.
*/
make_instr_func(dec_eax){
    cpu.eax = alu_sub(1, cpu.eax, 32);
    return 1;
}

make_instr_func(dec_ecx){
    cpu.ecx = alu_sub(1, cpu.ecx, 32);
    return 1;
}

make_instr_func(dec_edx){
    cpu.edx = alu_sub(1, cpu.edx, 32);
    return 1;
}

make_instr_func(dec_ebx){
    cpu.ebx = alu_sub(1, cpu.ebx, 32);
    return 1;
}

make_instr_func(dec_esp){
    cpu.esp = alu_sub(1, cpu.esp, 32);
    return 1;
}

make_instr_func(dec_ebp){
    cpu.ebp = alu_sub(1, cpu.ebp, 32);
    return 1;
}

make_instr_func(dec_esi){
    cpu.esi = alu_sub(1, cpu.esi, 32);
    return 1;
}

make_instr_func(dec_edi){
    cpu.edi = alu_sub(1, cpu.edi, 32);
    return 1;
}