#include "cpu/cpu.h"

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
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imul(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_mod before testing
uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_div(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

// need to implement alu_imod before testing
int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_idiv(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_mod(uint64_t src, uint64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_mod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

int32_t alu_imod(int64_t src, int64_t dest)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_imod(src, dest);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
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
	
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_shl(src, dest, data_size);
#else
	uint32_t res = dest << ((src & (0xFFFFFFFF >> (32 - data_size))) - 1);
	
	cpu.eflags.CF = ((res >> (data_size - 1)) & 1);
	res = res << 1;
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
	uint32_t res = dest >> ((src & (0xFFFFFFFF >> (32 - data_size))) - 1);
	//uint32_t standard_res = __ref_alu_shr(src, dest, data_size);
	
	cpu.eflags.CF = ((res >> 1) & 1);
	res = res >> 1;
	set_PF(res);
	set_ZF(res, data_size);
	set_SF(res, data_size);
    printf("in shl: res: %x, src: %x, dest: %x, CF: %x\n", res, src, dest, cpu.eflags.CF);
	return res & (0xFFFFFFFF >> (32 - data_size));
#endif
}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sar(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size)
{
#ifdef NEMU_REF_ALU
	return __ref_alu_sal(src, dest, data_size);
#else
	printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	fflush(stdout);
	assert(0);
	return 0;
#endif
}

