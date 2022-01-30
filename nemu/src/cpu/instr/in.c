#include "cpu/instr.h"
#include "device/port_io.h"
/*
Put the implementations of `in' instructions here.
*/
make_instr_func(in_b)
{
    int len = 1;
    cpu.gpr[0]._8[0] = read_io_port(cpu.gpr[2]._16, 2);
    return len;
}
