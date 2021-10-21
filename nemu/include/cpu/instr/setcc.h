#ifndef __INSTR_SETCC_H__
#define __INSTR_SETCC_H__
make_instr_func(setb_b);//0x92
make_instr_func(setne_b);//0x95
make_instr_func(seta_b);//0x97
make_instr_func(setae_b);//0x93
make_instr_func(setbe_b);//0x96
make_instr_func(setc_b);
make_instr_func(sete_b);//0x94
make_instr_func(setg_b);
make_instr_func(setge_b);
make_instr_func(setl_b);
make_instr_func(setle_b);
make_instr_func(setno_b);//0x91
make_instr_func(setnp_b);
make_instr_func(setns_b);
make_instr_func(seto_b);//0x90
make_instr_func(setp_b);
make_instr_func(sets_b);

#endif
