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
#include "in_code.h"

static INSN_T in_code_call[IN_CODE_SIZE];
static INSN_T in_code_mem[IN_CODE_SIZE];
static INSN_T in_code_OOprofile[IN_CODE_SIZE];
static INSN_T in_code_bb_freq[IN_CODE_SIZE];

int entre_in_code_bb_freq_get(INSN_T ** code_array)
{
	*code_array = in_code_bb_freq;
	return IN_CODE_SIZE;
}


int entre_in_code_OOprofile_get(INSN_T ** code_array)
{
	*code_array = in_code_OOprofile;
	return IN_CODE_SIZE;
}


int entre_in_code_mem_get(INSN_T ** code_array)
{
	*code_array = in_code_mem;
	return IN_CODE_SIZE;
}


int entre_in_code_call_get(INSN_T ** code_array)
{
	*code_array = in_code_call;
	return IN_CODE_SIZE;
}

/***********************************************************************
 * this code is implanted into the function, placed before jalr and jr 
 * instruction. the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
void entre_make_in_code_call(ADDRESS context_switch_addr)
{
	in_code_call[0] = entre_make_sd(REG_SP, REG_RA, -8);
	in_code_call[1] = entre_make_sd(REG_SP, REG_SP, -16);
	in_code_call[2] = entre_make_sd(REG_SP, REG_T9, -24);
	in_code_call[3] = entre_make_lui(REG_T9, context_switch_addr>>16);
	in_code_call[4] = entre_make_inc_x(REG_T9, context_switch_addr&0xffff);
	in_code_call[5] = entre_make_jalr(REG_T9);
	in_code_call[6] = entre_make_nop();
	in_code_call[7] = entre_make_ld(REG_SP, REG_T9, -24);
	in_code_call[8] = entre_make_ld(REG_SP, REG_SP, -16);
	in_code_call[9] = entre_make_ld(REG_SP, REG_RA, -8);
}

/***********************************************************************
 * this code is implanted into the function, placed before st and ld 
 * instruction. the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
void entre_make_in_code_mem(ADDRESS context_switch_addr)
{
	in_code_mem[0] = entre_make_sd(REG_SP, REG_RA, -8);
	in_code_mem[1] = entre_make_sd(REG_SP, REG_SP, -16);
	in_code_mem[2] = entre_make_sd(REG_SP, REG_T9, -24);
	in_code_mem[3] = entre_make_lui(REG_T9, context_switch_addr>>16);
	in_code_mem[4] = entre_make_inc_x(REG_T9, context_switch_addr&0xffff);
	in_code_mem[5] = entre_make_jalr(REG_T9);
	in_code_mem[6] = entre_make_nop();
	in_code_mem[7] = entre_make_ld(REG_SP, REG_T9, -24);
	in_code_mem[8] = entre_make_ld(REG_SP, REG_SP, -16);
	in_code_mem[9] = entre_make_ld(REG_SP, REG_RA, -8);
}

/***********************************************************************
 * this code is implanted into the function, placed at function begin
 * and end, or placed at basic block begin and basic block end.
 * the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
void entre_make_in_code_OOprofile(ADDRESS context_switch_addr)
{
	in_code_OOprofile[0] = entre_make_sd(REG_SP, REG_RA, -8);
	in_code_OOprofile[1] = entre_make_sd(REG_SP, REG_SP, -16);
	in_code_OOprofile[2] = entre_make_sd(REG_SP, REG_T9, -24);
	in_code_OOprofile[3] = entre_make_lui(REG_T9, context_switch_addr>>16);
	in_code_OOprofile[4] = entre_make_inc_x(REG_T9, context_switch_addr&0xffff);
	in_code_OOprofile[5] = entre_make_jalr(REG_T9);
	in_code_OOprofile[6] = entre_make_nop();
	in_code_OOprofile[7] = entre_make_ld(REG_SP, REG_T9, -24);
	in_code_OOprofile[8] = entre_make_ld(REG_SP, REG_SP, -16);
	in_code_OOprofile[9] = entre_make_ld(REG_SP, REG_RA, -8);
}

/***********************************************************************
 * this code is implanted into the function, placed at basic block begin.
 * the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
void entre_make_in_code_bb_freq(ADDRESS bb_counter_addr)
{
//	in_code_bb_freq[0] = entre_make_sd(REG_SP, REG_T1, -8);
//	in_code_bb_freq[1] = entre_make_sd(REG_SP, REG_T2, -16);
//
//	in_code_bb_freq[2] = entre_make_lui(REG_T1, bb_counter_addr>>16);
//	in_code_bb_freq[3] = entre_make_inc_x(REG_T1, bb_counter_addr&0xffff);
//	in_code_bb_freq[4] = entre_make_ld(REG_T1, REG_T2, 0);
//	in_code_bb_freq[5] = entre_make_addiu(REG_T2, REG_T2, 1);
//	in_code_bb_freq[6] = entre_make_sd(REG_T1, REG_T2, 0);
//
//	in_code_bb_freq[7] = entre_make_ld(REG_SP, REG_T2, -16);
//	in_code_bb_freq[8] = entre_make_ld(REG_SP, REG_T1, -8);
//	in_code_bb_freq[9] = entre_make_nop();
	in_code_bb_freq[0] = entre_make_sd(REG_SP, REG_RA, -8);
	in_code_bb_freq[1] = entre_make_sd(REG_SP, REG_SP, -16);
	in_code_bb_freq[2] = entre_make_sd(REG_SP, REG_T9, -24);
	in_code_bb_freq[3] = entre_make_lui(REG_T9, bb_counter_addr>>16);
	in_code_bb_freq[4] = entre_make_inc_x(REG_T9, bb_counter_addr&0xffff);
	in_code_bb_freq[5] = entre_make_jalr(REG_T9);
	in_code_bb_freq[6] = entre_make_nop();
	in_code_bb_freq[7] = entre_make_ld(REG_SP, REG_T9, -24);
	in_code_bb_freq[8] = entre_make_ld(REG_SP, REG_SP, -16);
	in_code_bb_freq[9] = entre_make_ld(REG_SP, REG_RA, -8);
}
