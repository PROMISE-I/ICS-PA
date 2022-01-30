#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `in' instructions here.
*/
make_instr_func(in_b)
{
    int len = 1;
    cpu.gpr[0]._8[0] = pio_read(cpu.gpr[2]._16, 1);
    return len;
}

make_instr_func(in_l)
{
    int len = 1;
    cpu.eax = pio_read(cpu.gpr[2]._16, 4);
    return len;
}
