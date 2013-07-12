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
static INSN_T in_code_mode[IN_CODE_SIZE];

int entre_in_code_mode_get(INSN_T ** code_array)
{
	*code_array = in_code_mode;
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
 * this code is implanted into the function, placed before jalr and jr 
 * instruction. the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
void entre_make_in_code_mode(ADDRESS context_switch_addr)
{
	in_code_mode[0] = entre_make_sd(REG_SP, REG_RA, -8);
	in_code_mode[1] = entre_make_sd(REG_SP, REG_SP, -16);
	in_code_mode[2] = entre_make_sd(REG_SP, REG_T9, -24);
	in_code_mode[3] = entre_make_lui(REG_T9, context_switch_addr>>16);
	in_code_mode[4] = entre_make_inc_x(REG_T9, context_switch_addr&0xffff);
	in_code_mode[5] = entre_make_jalr(REG_T9);
	in_code_mode[6] = entre_make_nop();
	in_code_mode[7] = entre_make_ld(REG_SP, REG_T9, -24);
	in_code_mode[8] = entre_make_ld(REG_SP, REG_SP, -16);
	in_code_mode[9] = entre_make_ld(REG_SP, REG_RA, -8);
}
