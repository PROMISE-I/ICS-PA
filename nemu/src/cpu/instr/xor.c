#include "cpu/instr.h"
/*
Put the implementations of `xor' instructions here.
*/
static void instr_execute_2op()
{
    oeprand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_xor(opr_src.val, opr_dest.val, opr_src.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(xor, r, rm, b)
make_instr_impl_2op(xor, r, rm, v)
make_instr_impl_2op(xor, rm, r, b)
make_instr_impl_2op(xor, rm, r, v)

// make_instr_func(xor_r2rm_b){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = 8;
//     rm.data_size = 8;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     rm.val = alu_xor(r.val, rm.val, 8);
//     operand_write(&rm);
    
//     return len;
// }

// make_instr_func(xor_r2rm_v){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = data_size;
//     rm.data_size = data_size;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     rm.val = alu_xor(r.val, rm.val, data_size);
//     operand_write(&rm);
    
//     return len;
// }

// make_instr_func(xor_rm2r_b){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = 8;
//     rm.data_size = 8;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     r.val = alu_xor(r.val, rm.val, 8);
//     operand_write(&r);
    
//     return len;
// }

// make_instr_func(xor_rm2r_v){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = data_size;
//     rm.data_size = data_size;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     r.val = alu_xor(r.val, rm.val, data_size);
//     operand_write(&r);
    
//     return len;
// }
