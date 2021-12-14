#include "cpu/instr.h"
/*
Put the implementations of `sub' instructions here.
*/
static void instr_execute_2op(){
    operand_read(&opr_src);
    operand_read(&opr_dest);
    opr_dest.val = alu_sub(opr_src.val, opr_dest.val, opr_src.data_size);
    operand_write(&opr_dest);
}

make_instr_impl_2op(sub, i, rm, v)
make_instr_impl_2op(sub, i, rm, b)
make_instr_impl_2op(sub, r, rm, b)
make_instr_impl_2op(sub, r, rm, v)
make_instr_impl_2op(sub, rm, r, b)
make_instr_impl_2op(sub, rm, r, v)

make_instr_func(sub_i2rm_bv){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    imm.type = OPR_IMM;
    imm.data_size = 8;
    imm.sreg = SERG_CS;
    imm.addr = eip + len;
    len += 1;
    
    operand_read(&rm);
    operand_read(&imm);
    rm.val = alu_sub(sign_ext(imm.val, 8), rm.val, data_size);
    operand_write(&rm);
    
    return len;
}




// make_instr_func(sub_r2rm_b){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = 8;
//     rm.data_size = 8;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     rm.val = alu_sub(r.val, rm.val, 8);
//     operand_write(&rm);
    
//     return len;
// }

// make_instr_func(sub_r2rm_v){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = data_size;
//     rm.data_size = data_size;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     rm.val = alu_sub(r.val, rm.val, data_size);
//     operand_write(&rm);
    
//     return len;
// }

// make_instr_func(sub_rm2r_b){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = 8;
//     rm.data_size = 8;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     r.val = alu_sub(rm.val, r.val, 8);
//     operand_write(&r);
    
//     return len;
// }

// make_instr_func(sub_rm2r_v){
//     OPERAND r, rm;
    
//     int len = 1;
//     r.data_size = data_size;
//     rm.data_size = data_size;
//     len += modrm_r_rm(eip+1, &r, &rm);
    
//     operand_read(&r);
//     operand_read(&rm);
//     r.val = alu_sub(rm.val, r.val, data_size);
//     operand_write(&r);
    
//     return len;
// }