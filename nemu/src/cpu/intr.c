#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"
   

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
    //Push eflags,cs,eip
    push_eflags(0,0);
    push_cs(0,0);
    push_eip(0,0);

    //find the IDT entry using 'inrt_no'
    vaddr_t entry = cpu.idtr.base + intr_no * 8;

    //Clear IF if it is an interrupt
    if (intr_no >= 1000) { //there is something wrong, intr_no in do_irq.S begins with 1000, while that begins with 32 in idt.c 
        printf("it is a interrupt!\n");
        cpu.eflags.IF = 0;        
    }
    
    //Set cs:eip to the entry of interrupt handler
    cpu.eip = (vaddr_read(entry, SREG_DS, 2) & 0xffff) + ((vaddr_read(entry+6, SREG_DS, 2) << 16) & 0xffff0000);
    cpu.cs.val = vaddr_read(entry+2, SREG_DS, 2);
    //Reload cs with load_sreg()
    load_sreg(1);
#endif
}

void raise_sw_intr(uint8_t intr_no)
{
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
