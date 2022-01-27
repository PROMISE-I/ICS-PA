#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/
make_instr_func(pop_eflags){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.eflags.val = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_eip){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.eip = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_cs){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.cs.val = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(popa){
    pop_edi(0,0);
    pop_esi(0,0);
    pop_ebp(0,0);
    pop_esp(0,0);
    pop_ebx(0,0);
    pop_edx(0,0);
    pop_ecx(0,0);
    pop_eax(0,0);
    
    return 1;
}

make_instr_func(pop_eax){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.eax = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_ecx){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.ecx = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_edx){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.edx = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_ebx){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.ebx = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_esp){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.esp = m.val;
    //pop esp 后还要esp+=4？
    
    return 1;
}

make_instr_func(pop_ebp){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.ebp = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_esi){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.esi = m.val;
    cpu.esp += 4;
    
    return 1;
}

make_instr_func(pop_edi){
    OPERAND m;
    
    m.type = OPR_MEM;
    m.data_size = 32;
    m.sreg = SREG_DS;
    m.addr = cpu.esp;
    
    operand_read(&m);
    cpu.edi = m.val;
    cpu.esp += 4;
    
    return 1;
}
