#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>

uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data)
{
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len)
{
	uint32_t ret = 0;
#ifdef CACHE_ENABLED
        if (is_mmio(paddr) == -1)
            ret = cache_read(paddr, len);
        else
            ret = mmio_read(paddr, len, is_mmio(paddr));
#else
        if (is_mmio(paddr) == -1)
    	    ret = hw_mem_read(paddr, len);
        else
            ret = mmio_read(paddr, len, is_mmio(paddr));
#endif
	return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data)
{
#ifdef CACHE_ENABLED
        if (is_mmio(paddr))
            cache_write(paddr, len, data);  
        else 
            mmio_write(paddr, len, data, is_mmio(paddr));
#else
        if (is_mmio(paddr))
    	    hw_mem_write(paddr, len, data);
        else
            mmio_write(paddr, len, data, is_mmio(paddr));
#endif
}

uint32_t laddr_read(laddr_t laddr, size_t len)
{
    //todo: pa3-3
    if (cpu.cr0.pe && cpu.cr0.pg) {
        if (((laddr + len - 1) >> 12) != (laddr >> 12)) {// data cross the page boundary
            int i = 0;
            for (; ((laddr + i) >> 12) == (laddr >> 12); i++);
            uint32_t res = paddr_read(page_translate(laddr), i);
            // printf("res1 = %x\n", res);
            return res + ((paddr_read(page_translate(laddr + i), len - i)) << (8 * i));
            // printf("res2 = %x\n", res);
            // printf("you got me in page boundary! i = %d; len = %d\n", i, len);
            // fflush(stdout);            
            // assert(0);
        } else{
           return paddr_read(page_translate(laddr), len);
        }
    }
    
    return paddr_read(laddr, len);
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data)
{
    //todo: pa3-3

    if (cpu.cr0.pe && cpu.cr0.pg) {
        if (((laddr + len - 1) >> 12) != (laddr >> 12)) {// data cross the page boundary
            int i = 0;
            for (; ((laddr + i) >> 12) == (laddr >> 12); i++);
            uint32_t dataH = data >> (8 * i);
            uint32_t dataL = data - (dataH << (8 * i));

            paddr_write(page_translate(laddr+i), len-i, dataH);
            paddr_write(page_translate(laddr), i, dataL);
            //printf("you got me in page boundary! i = %d; len = %d\n", i, len);
            //fflush(stdout);            
            //assert(0);
        } else{
           paddr_write(page_translate(laddr), len, data);
        }
    }
    else{
        paddr_write(laddr, len, data);
    }
    
}

uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
        return laddr_read(vaddr, len);
#else
        uint32_t laddr = vaddr;
        if (cpu.cr0.pe) {
            laddr = segment_translate(vaddr, sreg);
        }
        return laddr_read(laddr, len);
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data)
{
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG
        laddr_write(vaddr, len, data);
#else
	    uint32_t laddr = vaddr;
	    if (cpu.cr0.pe) {
	        laddr = segment_translate(vaddr, sreg);
	    }
	    laddr_write(laddr, len, data);
#endif
}

void init_mem()
{
	// clear the memory on initiation
	memset(hw_mem, 0, MEM_SIZE_B);

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len)
{
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t *get_mem_addr()
{
	return hw_mem;
}
