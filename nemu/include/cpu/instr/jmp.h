#ifndef __INSTR_JMP_H__
#define __INSTR_JMP_H__

make_instr_func(jmp_near);
make_instr_func(jmp_b);
make_instr_func(jo_short);
make_instr_func(jno_short);
make_instr_func(jb_short);
make_instr_func(jnb_short);
make_instr_func(jz_short);
make_instr_func(jnz_short);
make_instr_func(jbe_short);
make_instr_func(jnbe_short);
make_instr_func(js_short);
make_instr_func(jns_short);
make_instr_func(jp_short);
make_instr_func(jnp_short);
make_instr_func(jl_short);
make_instr_func(jnl_short);
make_instr_func(jle_short);
make_instr_func(jnle_short);

make_instr_func(jo_v);
make_instr_func(jno_v);
make_instr_func(jb_v);
make_instr_func(jnb_v);
make_instr_func(jz_v);
make_instr_func(jnz_v);
make_instr_func(jbe_v);
make_instr_func(jnbe_v);
make_instr_func(js_v);
make_instr_func(jns_v);
make_instr_func(jp_v);
make_instr_func(jnp_v);
make_instr_func(jl_v);
make_instr_func(jnl_v);
make_instr_func(jle_v);
make_instr_func(jnle_v);
#endif
