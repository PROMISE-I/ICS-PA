#include "cpu/instr.h"

make_instr_func(jmp_near)
{
    OPERAND rel;
    rel.type = OPR_IMM;
    rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;

    operand_read(&rel);

    int offset = sign_ext(rel.val, data_size);
    // thank Ting Xu from CS'17 for finding this bug
    print_asm_1("jmp", "", 1 + data_size / 8, &rel);

    cpu.eip += offset;

    return 1 + data_size / 8;
}

make_instr_func(jo_short)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    
    if(cpu.eflags.OF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jno_short)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    
    if(cpu.eflags.OF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jb_short)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    
    if(cpu.eflags.CF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jnb_short)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    
    if(cpu.eflags.CF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jz_short)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    
    if(cpu.eflags.ZF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jnz_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(cpu.eflags.ZF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jbe_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if((cpu.eflags.CF | cpu.eflags.ZF) == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jnbe_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if((cpu.eflags.CF | cpu.eflags.ZF) == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(js_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(cpu.eflags.SF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jns_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(cpu.eflags.SF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jp_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(cpu.eflags.PF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jnp_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(cpu.eflags.PF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jl_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if((cpu.eflags.SF ^ cpu.eflags.OF) == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jnl_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if((cpu.eflags.SF ^ cpu.eflags.OF) == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;  
}

make_instr_func(jle_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(((cpu.eflags.SF ^ cpu.eflags.OF) | cpu.eflags.ZF) == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}

make_instr_func(jnle_short)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = 8;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += 1;
    if(((cpu.eflags.SF ^ cpu.eflags.OF) | cpu.eflags.ZF) == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, 8);
    }
    
    return len;
}


//two opcodes

make_instr_func(jo_v)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    
    if(cpu.eflags.OF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jno_v)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    
    if(cpu.eflags.OF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jb_v)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    
    if(cpu.eflags.CF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jnb_v)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    
    if(cpu.eflags.CF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jz_v)
{
    OPERAND imm;

    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    
    if(cpu.eflags.ZF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jnz_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if(cpu.eflags.ZF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jbe_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if((cpu.eflags.CF | cpu.eflags.ZF) == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jnbe_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if((cpu.eflags.CF | cpu.eflags.ZF) == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(js_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if(cpu.eflags.SF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jns_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if(cpu.eflags.SF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jp_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if(cpu.eflags.PF == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jnp_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if(cpu.eflags.PF == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jl_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if((cpu.eflags.SF ^ cpu.eflags.OF) == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jnl_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if((cpu.eflags.SF ^ cpu.eflags.OF) == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;  
}

make_instr_func(jle_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if(((cpu.eflags.SF ^ cpu.eflags.OF) | cpu.eflags.ZF) == 1){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}

make_instr_func(jnle_v)
{
    OPERAND imm;
    
    int len = 1;
    imm.data_size = data_size;
    imm.type = OPR_IMM;
    imm.addr = eip + 1;
    len += data_size/8;
    if(((cpu.eflags.SF ^ cpu.eflags.OF) | cpu.eflags.ZF) == 0){
        operand_read(&imm);
        len += sign_ext(imm.val, data_size);
    }
    
    return len;
}