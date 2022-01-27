#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"

void raise_intr(uint8_t intr_no)
{
#ifdef IA32_INTR
    //Push eflags,cs,eip
    make_instr_func(push_eflags);
    make_instr_func(push_cs);
    make_instr_func(push_eip);
    //find the IDT entry using 'inrt_no'
    printf("cpu.idtr: 0x%x, itro_no: 0x%x\n",cpu.idtr.base,intr_no);
    GateDesc *entry = (GateDesc *)cpu.idtr.base + intr_no;
    printf("entry: 0x%x\n", (uint32_t)entry);
    //Clear IF if it is an interrupt
    if (intr_no >= 1000) { //there is something wrong, intr_no in do_irq.S begins with 1000, while that begins with 32 in idt.c 
        printf("it is a interrupt!\n");
        cpu.eflags.IF = 0;        
    }
    fflush(stdout);
    //Set cs:eip to the entry of interrupt handler
    cpu.cs.val = entry->selector;
    
    cpu.eip = (entry->offset_15_0 & 0xffff) + ((entry->offset_31_16 << 16) & 0xffff0000);
    printf("cs:eip = 0x%x: 0x%x\n", cpu.cs.val, cpu.eip);
    
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
