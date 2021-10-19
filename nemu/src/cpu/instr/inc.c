#include "cpu/instr.h"
/*
Put the implementations of `inc' instructions here.
*/
make_instr_func(inc_rm_b){
    OPERAND rm;
    
    int len = 1;
    rm.data_size = 8;
    len += modrm_rm(eip+1, &rm);
    
    operand_read(&rm);
    rm.val = alu_add(1, rm.val, 8);
    operand_write(&rm);
    
    return len;
}

make_instr_func(inc_rm_v){
    OPERAND rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    operand_read(&rm);
    rm.val = alu_add(1, rm.val, data_size);
    operand_write(&rm);
    
    return len;
}

make_instr_func(inc_eax){
    cpu.eax = alu_add(1, cpu.eax, 32);
    return 1;
}

make_instr_func(inc_ecx){
    cpu.ecx = alu_add(1, cpu.ecx, 32);
    return 1;
}

make_instr_func(inc_edx){
    cpu.edx = alu_add(1, cpu.edx, 32);
    return 1;
}

make_instr_func(inc_ebx){
    cpu.ebx = alu_add(1, cpu.ebx, 32);
    return 1;
}

make_instr_func(inc_esp){
    cpu.esp = alu_add(1, cpu.esp, 32);
    return 1;
}

make_instr_func(inc_ebp){
    cpu.ebp = alu_add(1, cpu.ebp, 32);
    return 1;
}

make_instr_func(inc_esi){
    cpu.esi = alu_add(1, cpu.esi, 32);
    return 1;
}

make_instr_func(inc_edi){
    cpu.edi = alu_add(1, cpu.edi, 32);
    return 1;
}