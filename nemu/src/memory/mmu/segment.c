#include "cpu/cpu.h"
#include "memory/memory.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg)
{
#ifdef IA32_SEG
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	uint32_t base = cpu.segReg[sreg].base;
	return base + offset;
#endif
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg)
{
#ifdef IA32_SEG
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	 SegReg *segReg = &cpu.segReg[sreg];
	 laddr_t addr = cpu.gdtr.base + (uint32_t)(segReg->index & 0x1fff);
	 SegDesc segDesc;
	 segDesc.val[0] = laddr_read(addr, 4);
	 segDesc.val[1] = laddr_read(addr + 4, 4);
	 
	 //load invisible part from segDesc
	 segReg->base = segDesc.base_15_0 + (segDesc.base_23_16 << 16) + (segDesc.base_31_24 << 24);
	 segReg->limit = segDesc.limit_15_0 + (segDesc.limit_19_16 << 16);
	 segReg->type = segDesc.type + (segDesc.segment_type << 4);
	 segReg->privilege_level = segDesc.privilege_level;
	 segReg->soft_use = segDesc.soft_use;
	 
	 //necessarily check
	 assert(segReg->base == 0);
	 assert(segReg->limit == 0xfffff);
	 assert(segDesc.granularity == 1);
	 assert(segDesc.present == 1);
#endif
}
