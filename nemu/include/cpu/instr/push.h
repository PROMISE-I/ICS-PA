#ifndef __INSTR_PUSH_H__
#define __INSTR_PUSH_H__
/*
Put the declarations of `push' instructions here.
*/
make_instr_func(push_eflags);
make_instr_func(push_eip);
make_instr_func(push_cs);
make_instr_func(pusha);
make_instr_func(push_eax);
make_instr_func(push_ecx);
make_instr_func(push_edx);
make_instr_func(push_ebx);
make_instr_func(push_esp);
make_instr_func(push_ebp);
make_instr_func(push_esi);
make_instr_func(push_edi);
make_instr_func(push_i_b);
make_instr_func(push_i_v);
make_instr_func(push_rm_v);
#endif
