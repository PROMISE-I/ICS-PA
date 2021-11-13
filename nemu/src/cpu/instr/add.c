#include "cpu/instr.h"
/*
Put the implementations of `add' instructions here.
*/
make_instr_func(add_r2rm_b){
    OPERAND r, rm;
    
    int len = 1;
    rm.data_size = 8; 
    r.data_size = 8;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&rm);
    operand_read(&r);
    rm.val = alu_add(r.val, rm.val, 8);
    operand_write(&rm);
    
    print_asm_2("add", "b", len, &r, &rm);
    return len;
}

make_instr_func(add_r2rm_v){
    OPERAND r, rm;
    
    int len = 1;
    rm.data_size = data_size; 
    r.data_size = data_size;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&rm);
    operand_read(&r);
    rm.val = alu_add(r.val, rm.val, data_size);
    operand_write(&rm);
    
    print_asm_2("add", "v", len, &r, &rm);
    return len;
}

make_instr_func(add_i2rm_v){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size; 
    len += modrm_rm(eip+1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = data_size;
    
    operand_read(&rm);
    operand_read(&imm);
    rm.val = alu_add(imm.val, rm.val, data_size);
    operand_write(&rm);
    
    print_asm_2("add", "v", len, &imm, &rm);
    return len + data_size / 8;
}

make_instr_func(add_i2rm_bv){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size; 
    len += modrm_rm(eip+1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = 8;
    
    operand_read(&rm);
    operand_read(&imm);
    rm.val = alu_add(sign_ext(imm.val, 8), rm.val, data_size);
    operand_write(&rm);
    
    print_asm_2("add", "", len, &imm, &rm);
    return len + 1;
}

make_instr_func(add_i2a_v){
    OPERAND imm;
    
    int len = 1;
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;
    
    operand_read(&imm);
    cpu.eax = alu_add(cpu.eax, sign_ext(imm.val, data_size), 32);
    
    print_asm_1("add", "", len, &imm);
    return len + data_size / 8;
}
