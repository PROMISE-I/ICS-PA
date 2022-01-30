#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `out' instructions here.
*/
make_instr_func(out_b)
{
    int len = 1;
    write_io_port(cpu.gpr[2]._16, 1, cpu.gpr[0]._8[0]);
    return len;
}
