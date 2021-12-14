#include "cpu/instr.h"
/*
Put the implementations of `push' instructions here.
*/
make_instr_func(push_eax){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.eax;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_ecx){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.ecx;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_edx){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.edx;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_ebx){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.ebx;
    
    operand_write(&m);
    
    return 1;
}


make_instr_func(push_esp){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.esp + 4;//此处是之前的esp的值
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_ebp){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.ebp;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_esi){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.esi;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_edi){
    OPERAND m;
    
    cpu.esp -= 4;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    m.val = cpu.edi;
    
    operand_write(&m);
    
    return 1;
}

make_instr_func(push_i_b){
    OPERAND imm, m;
    
    int len = 1;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    imm.sreg = SERG_CS;
    imm.data_size = 8;
    len++;
    
    cpu.esp -= 4;
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    
    operand_read(&imm);
    m.val = sign_ext(imm.val, 8);
    operand_write(&m);
    
    return len;
}

make_instr_func(push_i_v){
    OPERAND imm, m;
    
    int len = 1;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    imm.sreg = SERG_CS;
    imm.data_size = data_size;
    len += data_size / 8;
    
    cpu.esp -= 4;
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    
    operand_read(&imm);
    m.val = sign_ext(imm.val, data_size);
    operand_write(&m);
    
    return len;
}

make_instr_func(push_rm_v){
    OPERAND rm, m;
    
    int len = 1;
    cpu.esp -= 4;
    
    rm.data_size = data_size;
    len += modrm_rm(eip+1, &rm);
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SERG_DS;
    m.addr = cpu.esp;
    
    operand_read(&rm);
    m.val = sign_ext(rm.val, data_size);
    operand_write(&m);
    
    return len;
}
