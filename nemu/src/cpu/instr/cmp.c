#include "cpu/instr.h"
/*
Put the implementations of `cmp' instructions here.
*/
make_instr_func(cmp_i2al_b){
    OPERAND imm;
    
    int len = 1;
    imm.type = OPR_IMM;
    imm.data_size = 8;
    imm.addr = eip + 1;
    len++;
    
    operand_read(&imm);
    alu_sub(imm.val, cpu.eax, 8);
    
    return len;
}

make_instr_func(cmp_i2eax_v){
    OPERAND imm;
    
    int len = 1;
    imm.type = OPR_IMM;
    imm.data_size = data_size;
    imm.addr = eip + 1;
    len =+ data_size/8;
    
    operand_read(&imm);
    alu_sub(imm.val, cpu.eax, data_size);
    
    return len;
}

make_instr_func(cmp_i2rm_b){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = 8;
    len += modrm_rm(eip + 1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = 8;
    
    operand_read(&imm);
    imm.val = sign_ext(imm.val, data_size);
    operand_read(&rm);
    alu_sub(imm.val, rm.val, data_size);
    
    return len + 1;
}

make_instr_func(cmp_i2rm_v){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = data_size;
    
    operand_read(&imm);
    imm.val = sign_ext(imm.val, data_size);
    operand_read(&rm);
    alu_sub(imm.val, rm.val, data_size);
    
    return len + data_size/8;
}

make_instr_func(cmp_i2rm_bv){
    OPERAND imm, rm;
    
    int len = 1;
    rm.data_size = data_size;
    len += modrm_rm(eip + 1, &rm);
    
    imm.type = OPR_IMM;
    imm.addr = eip + len;
    imm.data_size = 8;
    
    operand_read(&imm);
    imm.val = sign_ext(imm.val, data_size);
    operand_read(&rm);
    alu_sub(imm.val, rm.val, data_size);
    
    return len + 1;
}

make_instr_func(cmp_r2rm_b){
    OPERAND r, rm;

    int len = 1;
    r.data_size = 8;
    rm.data_size = 8;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    alu_sub(r.val ,rm.val, 8);
    
    return len;
}

make_instr_func(cmp_r2rm_v){
    OPERAND r, rm;

    int len = 1;
    r.data_size = data_size;
    rm.data_size = data_size;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&r);
    operand_read(&rm);
    alu_sub(r.val ,rm.val, data_size);
    
    return len;
}

make_instr_func(cmp_rm2r_b){
    OPERAND rm, r;
    
    int len = 1;
    rm.data_size = 8;
    r.data_size = 8;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&rm);
    operand_read(&r);
    alu_sub(rm.val, r.val, 8);
    
    return len;
}

make_instr_func(cmp_rm2r_v){
    OPERAND rm, r;
    
    int len = 1;
    rm.data_size = data_size;
    r.data_size = data_size;
    len += modrm_r_rm(eip+1, &r, &rm);
    
    operand_read(&rm);
    operand_read(&r);
    alu_sub(rm.val, r.val, data_size);
    
    return len;
}