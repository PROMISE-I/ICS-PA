#include "cpu/instr.h"
/*
Put the implementations of `dec' instructions here.
*/
static void instr_execute_1op()
{
    operand_read(&opr_src);
    opr_src.val = alu_sub(1, opr_src, opr_src.data_size);
    operand_write(&opr_src);
}

make_instr_impl_1op(dec, a, l)
make_instr_impl_1op(dec, c, l)
make_instr_impl_1op(dec, d ,l)
make_instr_impl_1op(dec, b, l)
make_instr_impl_1op(dec, rm, b)
make_instr_impl_1op(dec, rm, v)

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

// make_instr_func(dec_eax){
//     cpu.eax = alu_sub(1, cpu.eax, 32);
//     return 1;
// }

// make_instr_func(dec_ecx){
//     cpu.ecx = alu_sub(1, cpu.ecx, 32);
//     return 1;
// }

// make_instr_func(dec_edx){
//     cpu.edx = alu_sub(1, cpu.edx, 32);
//     return 1;
// }

// make_instr_func(dec_ebx){
//     cpu.ebx = alu_sub(1, cpu.ebx, 32);
//     return 1;
// }

// make_instr_func(dec_rm_b){
//     OPERAND rm;
    
//     int len = 1;
//     rm.data_size = 8;
//     len += modrm_rm(eip+1, &rm);
    
//     operand_read(&rm);
//     rm.val = alu_sub(1, rm.val, 8);
//     operand_write(&rm);
    
//     return len;
// }

// make_instr_func(dec_rm_v){
//     OPERAND rm;
    
//     int len = 1;
//     rm.data_size = data_size;
//     len += modrm_rm(eip+1, &rm);
    
//     operand_read(&rm);
//     rm.val = alu_sub(1, rm.val, data_size);
//     operand_write(&rm);
    
//     return len;
// }