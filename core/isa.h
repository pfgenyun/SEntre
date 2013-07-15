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


#ifndef ISA_H
#define ISA_H

#include "global.h"

typedef enum
{
    GENERAL,     /* normal instruction */
    JR_LINK,     /* jump and link , jalr */
    JR_NO_LINK,  /* jump , jr */
    B_LINK,      /* branch and link, bal */
    B_NO_LINK,   /* normal branch instruction , bne */
    J_LINK,      /* jal */
    J_NO_LINK,   /* jump , j */
}INSN_CLASS;

#define MAIN_OP(insn)   ((insn) >> 26)  
#define SUB_OP(insn)    ((insn) & 0x3f) 
#define EXT_OP(insn)    (((insn) >> 21) & 0x1f) 
#define S_REG(insn)     (((insn) >> 21) & 0x1f) 
#define T_REG(insn)     (((insn) >> 16) & 0x1f) 
#define D_REG(insn)     (((insn) >> 11) & 0x1f) 
#define SHIFT(insn)     (((insn) >> 6) & 0x1f)
#define BROFFSET(insn)  ((insn) &0xffff)
#define OFFSET(insn)    ((insn) &0xffff)
#define TARGET(insn)    ((insn) &0x3ffffff)  

#define INSN_AT(addr) (*((unsigned *)(addr)))

#define INSN_MAIN_OP(op)	((op)<<26)
#define INSN_S_REG(s)		((s)<<21)
#define INSN_T_REG(t)		((t)<<16)
#define INSN_D_REG(d)		((d)<<11)
#define INSN_SUB_OP(op)		((op)&0x3f)
#define INSN_TARGET(t)		(((t)>>2)&0x3ffffff)

ADDRESS entre_offset_cvt(ADDRESS offset);
ADDRESS entre_branch_target(ADDRESS pc, INSN_T br);
ADDRESS entre_branch_offset_cvt(ADDRESS pc, ADDRESS target);
inline INSN_T entre_make_addiu(REG_T d, REG_T s, int j);
inline INSN_T entre_make_move(REG_T d, REG_T s);
inline INSN_T entre_make_lui(REG_T d, unsigned c);
inline INSN_T entre_make_inc_x(REG_T s, unsigned x);
inline INSN_T entre_make_j(INSN_T t);
inline INSN_T entre_make_jal(INSN_T t);
inline INSN_T entre_make_jalr(REG_T s);
inline INSN_T entre_make_jr(REG_T s);
inline INSN_T entre_make_ld(REG_T b, REG_T t, unsigned offset);
inline INSN_T entre_make_sd(REG_T b, REG_T t, unsigned offset);
inline INSN_T entre_make_b(INSN_T insn, unsigned broffset);
inline INSN_T entre_make_addiu(REG_T d, REG_T s, int j);
inline int entre_is_jr(INSN_T insn);
inline int entre_is_jr_ra(INSN_T insn);
inline int entre_is_jr_call(INSN_T insn);
inline int entre_is_jalr(INSN_T insn);
inline int entre_is_b(INSN_T insn);
inline int entre_is_lw(INSN_T insn);
inline int entre_is_sw(INSN_T insn);
inline int entre_is_lh(INSN_T insn);
inline int entre_is_sh(INSN_T insn);
inline int entre_is_lb(INSN_T insn);
inline int entre_is_sb(INSN_T insn);
inline int entre_is_lwc1(INSN_T insn);
inline int entre_is_swc1(INSN_T insn);
inline int entre_is_ldc1(INSN_T insn);
inline int entre_is_sdc1(INSN_T insn);
inline int entre_is_lui(INSN_T insn);
ADDRESS entre_mem_access_addr(ADDRESS b_reg, INT offset);

#define entre_make_move(d, s)	entre_make_or(d, REG_ZERO, s)

//#define entre_is_call_instruction(insn)			\
	(entre_is_jalr(insn) || entre_is_jr(insn))

/* jr ra instruction is used for function return. 
 * does not need to be redirected*/
#define entre_is_call_instruction(insn)			\
	(entre_is_jalr(insn) || entre_is_jr_call(insn))

#define entre_is_return_instruction(insn)		\
	(entre_is_jr_ra(insn))

#define entre_is_t9_instruction(insn)		\
	(entre_is_lui(insn))

#define entre_is_mem_instruction(insn)			\
	(entre_is_lw(insn) || entre_is_sw(insn)	||	\
	 entre_is_lb(insn) || entre_is_sb(insn)	||	\
	 entre_is_lh(insn) || entre_is_sh(insn) ||	\
	 entre_is_lwc1(insn) || entre_is_swc1(insn) ||	\
	 entre_is_ldc1(insn) || entre_is_sdc1(insn))

#ifdef TRACE
#ifdef OOprofile
#define entre_is_instrument_instruction(insn)	\
	(entre_is_call_instruction(insn) || entre_is_mem_instruction(insn) \
	 entre_is_return_insn(insn))
#endif
#endif

#ifdef TRACE
#ifndef OOprofile
#define entre_is_instrument_instruction(insn)	\
	(entre_is_call_instruction(insn) || entre_is_mem_instruction(insn))
#endif
#endif

#ifdef OOprofile
#ifndef TRACE
#define entre_is_instrument_instruction(insn)	\
	(entre_is_call_instruction(insn) || entre_is_return_instruction(insn))
#endif
#endif

#ifndef TRACE
#ifndef OOprofile
#define entre_is_instrument_instruction(insn)	\
	(entre_is_call_instruction(insn))
#endif
#endif

#endif
