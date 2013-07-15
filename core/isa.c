/************************************************************
 * Copyright (c) 2010-present Peng Fei.  All rights reserved.
 ************************************************************/

/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistribution and use in source and binary forms must authorized by
 * Peng Fei.
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 */


#include "global.h"
#include "isa.h"
#include "reg.h"

ADDRESS entre_mem_access_addr(ADDRESS b_reg, INT offset)
{
	return (b_reg + offset);
}

inline int entre_is_lui(INSN_T insn)
{
	if(MAIN_OP(insn) == 15)
		return 1;
	else
		return 0;
}

inline int entre_is_sdc1(INSN_T insn)
{
	if(MAIN_OP(insn) == 61)
		return 1;
	else
		return 0;
}

inline int entre_is_ldc1(INSN_T insn)
{
	if(MAIN_OP(insn) == 53)
		return 1;
	else
		return 0;
}

inline int entre_is_swc1(INSN_T insn)
{
	if(MAIN_OP(insn) == 57)
		return 1;
	else
		return 0;
}

inline int entre_is_lwc1(INSN_T insn)
{
	if(MAIN_OP(insn) == 49)
		return 1;
	else
		return 0;
}

inline int entre_is_sh(INSN_T insn)
{
	if(MAIN_OP(insn) == 41)
		return 1;
	else
		return 0;
}

inline int entre_is_lh(INSN_T insn)
{
	if(MAIN_OP(insn) == 33)
		return 1;
	else
		return 0;
}

inline int entre_is_sb(INSN_T insn)
{
	if(MAIN_OP(insn) == 40)
		return 1;
	else
		return 0;
}

inline int entre_is_lb(INSN_T insn)
{
	if(MAIN_OP(insn) == 32)
		return 1;
	else
		return 0;
}

inline int entre_is_sw(INSN_T insn)
{
	if(MAIN_OP(insn) == 43)
		return 1;
	else
		return 0;
}

inline int entre_is_lw(INSN_T insn)
{
	if(MAIN_OP(insn) == 35)
		return 1;
	else
		return 0;
}


inline int entre_is_b(INSN_T insn)
{
	if((MAIN_OP(insn) == 4  || MAIN_OP(insn) == 5  ||
	    MAIN_OP(insn) == 6  || MAIN_OP(insn) == 7  ||
	    MAIN_OP(insn) == 20 || MAIN_OP(insn) == 21 ||
	    MAIN_OP(insn) == 22 || MAIN_OP(insn) == 23) ||
		(MAIN_OP(insn) == 1	&& (T_REG(insn) == 0 ||
							    T_REG(insn) == 1 ||
							    T_REG(insn) == 2 ||
							    T_REG(insn) == 3))  ||
		(MAIN_OP(insn) == 1	&& (T_REG(insn) == 16 ||
							    T_REG(insn) == 17 ||
							    T_REG(insn) == 18 ||
							    T_REG(insn) == 19)) ||
		(MAIN_OP(insn) == 16 && S_REG(insn) == 8 &&
								(T_REG(insn) == 0 ||
							     T_REG(insn) == 1 ||
							     T_REG(insn) == 2 ||
							     T_REG(insn) == 3)) ||
		(MAIN_OP(insn) == 17 && (S_REG(insn) == 8 ||
								 S_REG(insn) == 9 ||
								 S_REG(insn) == 10)) ||
		(MAIN_OP(insn) == 18 && S_REG(insn) == 8 &&
								(T_REG(insn) == 0 ||
							     T_REG(insn) == 1 ||
							     T_REG(insn) == 2 ||
							     T_REG(insn) == 3)))
		return 1;
	else
		return 0;
}

inline int entre_is_j(INSN_T insn)
{
	if(MAIN_OP(insn)==2)
		return 1;
	else
		return 0;
}

inline int entre_is_jal(INSN_T insn)
{
	if(MAIN_OP(insn)==3)
		return 1;
	else
		return 0;
}

inline int entre_is_jalr(INSN_T insn)
{
	if((MAIN_OP(insn)==0) && (SUB_OP(insn)==9))
		return 1;
	else
		return 0;
}

inline int entre_is_jr(INSN_T insn)
{
	if((MAIN_OP(insn)==0) && (SUB_OP(insn)==8))
		return 1;
	else
		return 0;
}

inline int entre_is_jr_ra(INSN_T insn)
{
	if((MAIN_OP(insn)==0) && (SUB_OP(insn)==8) && (S_REG(insn)==REG_RA))
		return 1;
	else
		return 0;
}

inline int entre_is_jr_call(INSN_T insn)
{
	if((MAIN_OP(insn)==0) && (SUB_OP(insn)==8) && (S_REG(insn)!=REG_RA))
		return 1;
	else
		return 0;
}

inline INSN_T entre_make_b(INSN_T insn, unsigned broffset)
{
	INSN_T new_insn;
	new_insn = (insn & 0xffff0000) | (broffset & 0x0000ffff);
	return new_insn;
}

inline INSN_T entre_make_addiu(REG_T d, REG_T s, int j)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(9) | INSN_S_REG(s) | INSN_T_REG(d) | (0x0000ffff&j);
	return insn;
}

inline INSN_T entre_make_or(REG_T d, REG_T s, REG_T t)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(0) | INSN_S_REG(s) | INSN_T_REG(t) | INSN_D_REG(d) | 37;
	return insn;
}

inline INSN_T entre_make_lui(REG_T d, unsigned c)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(15) | INSN_T_REG(d) | (0x0000ffff&c);
	return insn;
}

inline INSN_T entre_make_inc_x(REG_T s, unsigned x)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(13) | INSN_S_REG(s) | INSN_T_REG(s) | (0x0000ffff&x);
	return insn;
}

inline INSN_T entre_make_j(INSN_T t)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(2) | INSN_TARGET(t);
	return insn;
}

inline INSN_T entre_make_jal(INSN_T t)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(3) | INSN_TARGET(t);
	return insn;
}

inline INSN_T entre_make_jalr(REG_T s)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(0) | INSN_S_REG(s) | INSN_D_REG(31) | INSN_SUB_OP(9);
	return insn;
}

inline INSN_T entre_make_jr(REG_T s)
{
	INSN_T insn;
	insn = INSN_MAIN_OP(0) | INSN_S_REG(s) | INSN_SUB_OP(8);
	return insn;
}

inline INSN_T entre_make_ld(REG_T b, REG_T t, unsigned offset)
{
	INSN_T insn;
//	insn = INSN_MAIN_OP(55) | INSN_S_REG(b) | INSN_T_REG(t) | (0x0000ffff&offset);
	insn = INSN_MAIN_OP(35) | INSN_S_REG(b) | INSN_T_REG(t) | (0x0000ffff&offset);
	return insn;
}

inline INSN_T entre_make_sd(REG_T b, REG_T t, unsigned offset)
{
	INSN_T insn;
//	insn = INSN_MAIN_OP(63) | INSN_S_REG(b) | INSN_T_REG(t) | (0x0000ffff&offset);
	insn = INSN_MAIN_OP(43) | INSN_S_REG(b) | INSN_T_REG(t) | (0x0000ffff&offset);
	return insn;
}

inline INSN_T entre_make_l_d(REG_T b, REG_T ft, unsigned offset)
{
	INSN_T insn;
//	insn = INSN_MAIN_OP(55) | INSN_S_REG(b) | INSN_T_REG(t) | (0x0000ffff&offset);
	insn = INSN_MAIN_OP(53) | INSN_S_REG(b) | INSN_T_REG(ft) | (0x0000ffff&offset);
	return insn;
}

inline INSN_T entre_make_s_d(REG_T b, REG_T ft, unsigned offset)
{
	INSN_T insn;
//	insn = INSN_MAIN_OP(63) | INSN_S_REG(b) | INSN_T_REG(t) | (0x0000ffff&offset);
	insn = INSN_MAIN_OP(61) | INSN_S_REG(b) | INSN_T_REG(ft) | (0x0000ffff&offset);
	return insn;
}

inline INSN_T entre_make_mfhi(REG_T d)
{
	INSN_T insn;
	insn =  INSN_MAIN_OP(0) | INSN_D_REG(d) | INSN_SUB_OP(16);
	return insn;
}

inline INSN_T entre_make_mflo(REG_T d)
{
	INSN_T insn;
	insn =  INSN_MAIN_OP(0) | INSN_D_REG(d) | INSN_SUB_OP(18);
	return insn;
}

inline INSN_T entre_make_mthi(REG_T s)
{
	INSN_T insn;
	insn =  INSN_MAIN_OP(0) | INSN_S_REG(s) | INSN_SUB_OP(17);
	return insn;
}

inline INSN_T entre_make_mtlo(REG_T s)
{
	INSN_T insn;
	insn =  INSN_MAIN_OP(0) | INSN_S_REG(s) | INSN_SUB_OP(19);
	return insn;
}

inline INSN_T entre_make_nop()
{
	return 0;
}

ADDRESS entre_offset_cvt(ADDRESS offset)
{
    ADDRESS mask = 0xffff0000;
    ADDRESS ad;

    if((offset>>15) == 1)
        offset = offset | mask;

	
    return offset;
}


ADDRESS entre_broffset_cvt(ADDRESS broffset)
{
    ADDRESS mask = 0xffff0000;
    ADDRESS ad;

    if((broffset>>15) == 1)
        broffset = broffset | mask;

	broffset++;
	ad = broffset * 4;

    return ad;
}

ADDRESS entre_branch_target(ADDRESS pc, INSN_T br)
{
    return (pc + entre_broffset_cvt(br & 0xffff) );
}


ADDRESS entre_branch_offset_cvt(ADDRESS pc, ADDRESS target)
{
	ADDRESS broffset = 0;

	if(target - pc < 0)
	{
		
	}
	else
	{
		broffset = target - pc;
	}
	return broffset;
}
