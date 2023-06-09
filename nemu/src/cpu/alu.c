#include "cpu/cpu.h"
#include <stdlib.h>

int64_t sign_ext_64_my(int32_t src, size_t data_size)
{
    assert(data_size == 8 || data_size == 16 || data_size == 32);
    switch(data_size){
        case 8:
            return (int64_t)(int8_t)(src & 0xFF);
        case 16:
            return (int64_t)(int16_t)(src & 0xFFFF);
        default: 
            return (int64_t)(int32_t)(src & 0xFFFFFFFF);
    }    
}


void set_CF_add(uint32_t res, uint32_t src, size_t data_size)
{
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (res < src);
    //printf("res: %x, src: %x, CF: %x\n", res, src, cpu.eflags.CF);
}

void set_CF_adc(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (res < src) || (dest != 0 && res == src);
    //printf("in adc: res: %x src: %x, dest: %x, CF: %x\n", res, src, dest, cpu.eflags.CF);
}

void set_PF(uint32_t res)
{
    uint32_t flag = 1;
    uint32_t i = 0;
    for(; i < 8; i++)
    {
        flag = flag ^ (((res << (31 - i)) & (0x80000000)) >> 31);
    }
    cpu.eflags.PF = flag;
    //printf("res: %x, PF: %x\n", res, cpu.eflags.PF);
}

void set_ZF(uint32_t res, size_t data_size)
{
    res = res & (0xFFFFFFFF >> (32 - data_size));
    cpu.eflags.ZF = (res == 0);
}

void set_SF(uint32_t res, size_t data_size)
{
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.SF = sign(res);
}

void set_OF_add(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
    switch(data_size){
        case 8:
              res = sign_ext(res & 0xFF, 8);
              src = sign_ext(src & 0xFF, 8);
              dest = sign_ext(dest & 0xFF, 8);
              break;
        case 16:
              res = sign_ext(res & 0xFFFF, 16);
              src = sign_ext(src & 0xFFFF, 16);
              dest = sign_ext(dest & 0xFFFF, 16);
              break;
        default: break;
    }
    if(sign(src) == sign(dest)){
        if(sign(src) != sign(res))
            cpu.eflags.OF = 1;
        else
            cpu.eflags.OF = 0;
    }else{
        cpu.eflags.OF = 0;
    }
}

void set_CF_sub(uint32_t res, uint32_t dest, size_t data_size)
{
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (res > dest);
}

void set_OF_sub(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
    switch(data_size){
        case 8:
              res = sign_ext(res & 0xFF, 8);
              src = sign_ext(src & 0xFF, 8);
              dest = sign_ext(dest & 0xFF, 8);
              break;
        case 16:
              res = sign_ext(res & 0xFFFF, 16);
              src = sign_ext(src & 0xFFFF, 16);
              dest = sign_ext(dest & 0xFFFF, 16);
              break;
        default: break;
    }
    if(sign(src) != sign(dest)){
        if(sign(dest) != sign(res))
            cpu.eflags.OF = 1;
        else
            cpu.eflags.OF = 0;
    }else{
        cpu.eflags.OF = 0;
    }
}

void set_CF_sbb(uint32_t res, uint32_t src, uint32_t dest, size_t data_size)
{
    res = sign_ext(res & (0xFFFFFFFF >> (32 - data_size)), data_size);
    src = sign_ext(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
    dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
    cpu.eflags.CF = (res > dest) || (src != 0 && res == dest);
}

/**************************************分割线*******************************************/

uint32_t alu_add(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_add(src, dest, data_size);
#else
	uint32_t res = 0;
	res = src + dest;
	
	//printf("in add: res: %x, src: %x, dest: %x, CF: %x\n", res, src, dest, cpu.eflags.CF);
	set_CF_add(res, src, data_size);
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_add(res, src, dest, data_size);
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_adc(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_adc(src, dest, data_size);
#else
    //printf("pre-CF: %x\n", cpu.eflags.CF);
	uint32_t res = src + dest + cpu.eflags.CF;
	
	set_CF_adc(res, src, dest, data_size);
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_add(res, src, dest, data_size);
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sub(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sub(src, dest, data_size);
#else
	uint32_t res = dest - src;
	
	set_CF_sub(res, dest, data_size);
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_sub(res, src, dest, data_size);
	//printf("in sub: res: %x, src: %x, dest: %x, OF: %x\n", res, src, dest, cpu.eflags.OF);
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sbb(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sbb(src, dest, data_size);
#else
	uint32_t res = dest - src - cpu.eflags.CF;
	
	set_CF_sbb(res, src, dest, data_size);
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	set_OF_sub(res, src, dest, data_size);
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mul(src, dest, data_size);
#else
	uint64_t src_ext = src;
	uint64_t dest_ext = dest;
	
	src_ext = src_ext & (0xFFFFFFFFFFFFFFFF >> (64 - data_size));
	dest_ext = dest_ext & (0xFFFFFFFFFFFFFFFF >> (64 - data_size));
	
	uint64_t res = src_ext * dest_ext;
	cpu.eflags.OF = ((res >> data_size) != 0);
	cpu.eflags.CF = cpu.eflags.OF;
	
	return res & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));//测试用例在这里都是32位；
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
    //if(data_size == 32) printf("pre: src: %x, dest: %x\n", src, dest);
	int64_t src_ext = sign_ext_64_my(src & (0xFFFFFFFF >> (32 - data_size)), data_size);
	int64_t dest_ext = sign_ext_64_my(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
	int64_t res;
	
	src_ext = src_ext & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));
	dest_ext = dest_ext & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));
	
	res = dest_ext * src_ext;
	if(data_size != 32) 
	{
	    res = (int64_t)sign_ext(res & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size)), 2 * data_size);   
	}
	
    //if(data_size == 32) printf("in imul: data_size: %d, res: %llx, src_64: %llx, dest_64: %llx, std_res: %llx\n", data_size, res, src_ext, dest_ext, __ref_alu_imul(src, dest, data_size));
    return res;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
    if(src == 0) exit(-1);//为什么我去掉这行还是对的？
    //printf("in div: src: %llx, dest: %llx\n", src, dest);
	src = src & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));
	dest = dest & (0xFFFFFFFFFFFFFFFF >> (64 - 2 * data_size));
	
	uint32_t res = dest / src;
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	if(src == 0) exit(-1);
	if(data_size != 32)//为什么不符号扩展也可以过？
	{
	    dest = sign_ext_64_my(dest, data_size * 2);
	}
	src = sign_ext_64_my(src, data_size);
	
	return (dest / src) & (0xFFFFFFFF >> (32 - data_size));
	
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	uint32_t res = dest % src;
	return res;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	return dest % src;
#endif
}

uint32_t alu_and(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_and(src, dest, data_size);
#else
	uint32_t res = (src & dest);
	//printf("in and: res: %x, src: %x, dest: %x\n", res, src, dest);
	set_SF(res, data_size);
	set_ZF(res, data_size);
	set_PF(res);
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_xor(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_xor(src, dest, data_size);
#else
    uint32_t res = (src ^ dest);
	
	set_SF(res, data_size);
	set_ZF(res, data_size);
	set_PF(res);
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_or(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_or(src, dest, data_size);
#else
	uint32_t res = (src | dest);
	
	set_SF(res, data_size);
	set_ZF(res, data_size);
	set_PF(res);
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
    uint32_t res;
    if(src == 0){
        res = dest;
        cpu.eflags.CF = 0;
    }
	else{
	    res = dest << ((src & (0xFFFFFFFF >> (32 - data_size))) - 1);
	    cpu.eflags.CF = ((res >> (data_size - 1)) & 1);
	    res = res << 1;
	} 
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
	//printf("in shl: res: %x, src: %x, dest: %x, CF: %x\n", res, src, dest, cpu.eflags.CF);
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shr(src, dest, data_size);
#else
    dest = dest & (0xFFFFFFFF >> (32 - data_size));
    uint32_t res;
    if(src == 0){
        res = dest;
        cpu.eflags.CF = 0;
    }
    else{
        res = dest >> ((src & (0xFFFFFFFF >> (32 - data_size))) - 1);    
        cpu.eflags.CF = (res & 1);
	    res = res >> 1;
    }
	
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
    //printf("in shl: res: %x, src: %x, dest: %x, CF: %x\n", res, src, dest, cpu.eflags.CF);
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	int32_t signed_dest = sign_ext(dest & (0xFFFFFFFF >> (32 - data_size)), data_size);
	int32_t signed_res;
	uint32_t res;
	if(src == 0){
	    res = signed_dest;
	    cpu.eflags.CF = 0;
	}
	else{
	    signed_res = signed_dest >> ((src & (0xFFFFFFFF >> (32 - data_size))) - 1);
        cpu.eflags.CF = (signed_res & 1);
	    res = signed_res >> 1;
	}
	   
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
    //printf("in shl: res: %x, src: %x, dest: %x, CF: %x\n", res, src, dest, cpu.eflags.CF);
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	return alu_shl(src, dest, data_size);
#endif
}

uint32_t alu_neg(uint32_t src, size_t data_size)
{
    cpu.eflags.CF = (src != 0);
    return -src;
}

