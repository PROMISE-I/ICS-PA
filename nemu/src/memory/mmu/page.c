#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr)
{
#ifndef TLB_ENABLED
    //laddr = laddr + 0xc0000000;
    printf("cpu.cr3: %x; laddr: %x\n", cpu.cr3.page_directory_base << 12, laddr);
	paddr_t PDEpaddr = (cpu.cr3.page_directory_base << 12) + ((laddr >> 22) & 0x3ff) * 4;
	//printf("PDEpaddr: %x\n", PDEpaddr);
	//printf("eip: %x\n", cpu.eip);
	PDE pde;
	pde.val = paddr_read(PDEpaddr, 4);
	assert(pde.present == 1);
	
	paddr_t PTEpaddr = (pde.page_frame << 12) + ((laddr >> 12) & 0x3ff) * 4;
	printf("PTEpaddr: %x, pde.page_frame: %x\n", PTEpaddr, pde.page_frame);
	PTE pte;
	pte.val = paddr_read(PTEpaddr, 4);
	assert(pte.present == 1);
	
	paddr_t paddr = (pte.page_frame << 12) + (laddr & 0xfff);
	printf("paddr: %x\n", paddr);
	fflush(stdout);
	return paddr;
#else
	return tlb_read(laddr) | (laddr & PAGE_MASK);
#endif
}
