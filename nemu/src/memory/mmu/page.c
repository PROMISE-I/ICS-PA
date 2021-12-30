#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
	paddr_t PDEpaddr = cpu.cr3.PDBR + ((laddr >> 22) & 0x2ff);
	PDE pde;
	pde.val = paddr_read(PDEpaddr, 4);
	assert(pde.present == 1);
	
	paddr_t PTEpaddr = (pde.page_frame << 12) + ((laddr >> 12) & 0x2ff);
	PTE pte;
	pte.val = paddr_read(PTEpaddr, 4);
	assert(pte.present == 1);
	
	paddr_t paddr = (pte.page_frame << 12) + (laddr & 0xfff);
	return paddr;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
