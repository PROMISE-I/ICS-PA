#include "cpu/instr.h"
/*
Put the implementations of `pop' instructions here.
*/
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
