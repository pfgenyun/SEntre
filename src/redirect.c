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


#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "context_switch.h"
#include "isa.h"
#include "reg.h"
#include "in_code.h"
#include "redirect.h"
#include "make_new_function.h"

/* calculate new target of b instruction when redirect b instruction.
 * old_target_addr is orignal address at orignal space
 * b_addr is b target address at orignal space
 * fun_call_num is jalr and jr instruction number between 
 * old_target_addr and b_addr */
int entre_get_b_new_target(ADDRESS old_target_addr, ADDRESS b_addr, int fun_call_num)
{
	ADDRESS new_target_addr;

	if(old_target_addr > b_addr)	/* branch after*/
	{
		new_target_addr = old_target_addr + fun_call_num*IN_CODE_SIZE*INSN_BYTES;
		if((new_target_addr-b_addr)>65535)
		{
            printf("             ************************************************************\n");
            printf("             ******       WARNING1: Branch Offset Over 2^16!       ******\n");
            printf("             ******                Can't Instrument!               ******\n");
            printf("             ************************************************************\n");
		}
	}
	else							/* branch before*/
	{
		new_target_addr = old_target_addr - fun_call_num*IN_CODE_SIZE*INSN_BYTES;
		if((b_addr-new_target_addr)>65535)
		{
            printf("             ************************************************************\n");
            printf("             ******       WARNING2: Branch Offset Over 2^16!       ******\n");
            printf("             ******                 Can't Instrument!              ******\n");
            printf("             ************************************************************\n");
		}
	}

	return new_target_addr;
}


/*******************************************************************
 redirect jal and b instruction's target from orignal space to new 
 space in codecache.
*******************************************************************/
void entre_jal_b_redirect(struct function * fun)
{
	ADDRESS fun_start_addr = FUNCTION_START_ADDRESS(fun);
	ADDRESS new_start_addr;
    int fun_size = FUNCTION_SIZE(fun);
    ADDRESS fun_next_addr = fun_start_addr + fun_size;
	int insn_index_old=0;
	int insn_index_new=0;
	ADDRESS addr_i;

	new_start_addr = entre_got_find_orig(fun_start_addr);
	if(new_start_addr == 0)
		entre_my_error("EE: redirect error!");

	for(addr_i=fun_start_addr; addr_i<fun_next_addr; addr_i+=INSN_BYTES)
    {
		ADDRESS old_target=0;
		ADDRESS new_target=0;
		ADDRESS old_replace_addr;
		ADDRESS new_replace_addr;
        INSN_T insn = INSN_AT(addr_i);
		INSN_T insn_redirect;

		insn_index_old++;
		insn_index_new++;
	
		/* in_code instruction number */
#ifdef BB_FREQ
		if((entre_is_instrument_instruction(insn) || 
			entre_is_bb_begine(addr_i)) &&
			entre_can_instrument_here(addr_i))
#else	
		if(entre_is_instrument_instruction(insn) &&
		   entre_can_instrument_here(addr_i))
#endif
		{
			insn_index_new += IN_CODE_SIZE;
		}

        if(entre_is_jal(insn) || entre_is_j(insn))
        {
			old_target = TARGET(insn)<<2;
			new_target = entre_got_find_final(old_target);
			if(entre_is_jal(insn))
				insn_redirect = entre_make_jal(new_target);
			else if(entre_is_j(insn))
				insn_redirect = entre_make_j(new_target);
#ifdef DEBUG
			printf("old_jal_j_target:0x%x\tnew_jal_j_target:0x%x\tfunction name:%-20s\n",
                   old_target, new_target, fun->f_name);
#endif
			old_replace_addr = fun_start_addr + (insn_index_old-1)*INSN_BYTES;
			new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
			entre_cc_replace(new_replace_addr, insn_redirect);
#ifdef DEBUG
            printf("old_jal_j_addr:0x%x\tnew_jal_j_addr:0x%x\tfunction name:%-20s\n\n",
                   old_replace_addr, new_replace_addr, fun->f_name);
#endif
        }

		if(entre_is_b(insn))
		{
			old_target = entre_branch_target(addr_i, insn);
#ifdef DEBUG
			printf("old_b_insn: 0x%x\told_b_target: 0x%x\tfunction name: %-20s\n",
					insn, old_target, fun->f_name);
#endif
			int fun_call_num = entre_lr_num(fun, old_target, addr_i);
			new_target = entre_get_b_new_target(old_target, addr_i, fun_call_num);
			insn_redirect = entre_make_b(insn, (new_target-addr_i-1)/INSN_BYTES);
#ifdef DEBUG
	        printf("new_b_insn: 0x%x\told_b_target: 0x%x\tnew_b_target: 0x%x\tlr_num: %d\t function name: %-20s\n",
					insn_redirect, old_target, new_target, fun_call_num, fun->f_name);
#endif

			old_replace_addr = fun_start_addr + (insn_index_old-1)*INSN_BYTES;
			new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
			entre_cc_replace(new_replace_addr, insn_redirect);
#ifdef DEBUG
            printf("addr_i: 0x%x\told_b_addr: 0x%x\tnew_b_addr: 0x%x\tfunction name: %-20s\n\n",
                   addr_i, old_replace_addr, new_replace_addr, fun->f_name);
#endif
		}
    }   
}


/* scan all function and redirect all jal and b* instructions */
void entre_transfer_redirect()
{
	entre_for_all_function(entre_jal_b_redirect);
}

/* redirect jr_call instruction*/
void entre_redirect_jr_call(struct context * context)
{
	ADDRESS jr_call_addr = context->ra + IN_CODE_LW_NUM;
	INSN_T jr_call_insn = INSN_AT(jr_call_addr);
	REG_T s_reg = S_REG(jr_call_insn);

	if(MAIN_OP(jr_call_insn) != 0 || SUB_OP(jr_call_insn) != 8 
		|| S_REG(jr_call_insn) == REG_RA)
		entre_my_error("entre_redirect_jr_call insn error!");

	ADDRESS old_addr;
	ADDRESS new_addr;

	if(s_reg == REG_T9)
	{
		old_addr = (UINT32)context->old_t9;
		new_addr = entre_got_find_final(old_addr);
#ifdef DUMP_DIRTY_CALL
	printf("T9: jr_call_addr: 0x%x\told_t9: 0x%x\tnew_t9: 0x%x\t\n", 
			jr_call_addr, old_addr, new_addr);
#endif
		if(new_addr == 0)
			return;
		context->old_t9 = new_addr;
	}
	else
	{
		old_addr = GET_CONTEXT(s_reg, context);
		new_addr = entre_got_find_final(old_addr);
		if(new_addr == 0)
			return;

#ifdef DUMP_DIRTY_CALL
	printf("jr_call_addr: 0x%x\told: 0x%x\tnew: 0x%x\t\n", 
			jr_call_addr, old_addr, new_addr);
#endif
		if(new_addr == 0)
			PUT_CONTEXT(s_reg,context,new_addr);

#ifdef DUMP_DIRTY_CALL
	printf("jr_call_addr: 0x%x\told: 0x%x\tnew: 0x%x\t\n", 
			jr_call_addr, old_addr, new_addr);
#endif
	}
}


/* redirect jalr instruction*/
void entre_redirect_jalr(struct context * context)
{
	ADDRESS jalr_addr = context->ra + IN_CODE_LW_NUM;
	INSN_T jalr_insn = INSN_AT(jalr_addr);

	if(MAIN_OP(jalr_insn) != 0 || SUB_OP(jalr_insn) != 9)
		entre_my_error("entre_redirect_jalr insn error!");

	REG_T s_reg = S_REG(jalr_insn);
	REG_T d_reg = D_REG(jalr_insn);

	if(d_reg != REG_RA)
		entre_my_error("entre_redirect_jalr reg error!");

	ADDRESS old_addr;
	ADDRESS new_addr;

	if(s_reg == REG_T9)
	{
		old_addr = (UINT32)context->old_t9;
		new_addr = entre_got_find_final(old_addr);
#ifdef DUMP_DIRTY_CALL
	printf("T9: jalr_addr: 0x%x\told_t9: 0x%x\tnew_t9: 0x%x\t\n", 
			jalr_addr, old_addr, new_addr);
#endif
		if(new_addr == 0)
			return;
		context->old_t9 = new_addr;
	}
	else
	{
		old_addr = GET_CONTEXT(s_reg, context);
		new_addr = entre_got_find_final(old_addr);
		if(new_addr == 0)
			return;
		PUT_CONTEXT(s_reg,context,new_addr);
	}
}


/* redirect jalr and jr instruction */
void entre_call_redirect(struct context * context)
{

#ifdef DUMP_CONTEXT
	entre_dump_context(context);
#endif

	ADDRESS dirty_addr = context->ra + IN_CODE_LW_NUM;
	INSN_T dirty_insn = INSN_AT(dirty_addr);

	int main_op = MAIN_OP(dirty_insn);
	int sub_op = SUB_OP(dirty_insn);
	REG_T s_reg = S_REG(dirty_insn);

#ifdef DUMP_DIRTY_CALL
	printf("in call_redirect\n");
	printf("dirty_addr: %x  dirty_insn: %x  main_op: %d  sub_op: %d s_reg: %d\n",
			dirty_addr, dirty_insn, main_op, sub_op, s_reg);
#endif

	if(main_op==0 && sub_op==9)
	{
		entre_redirect_jalr(context);
	}
	else if(main_op==0 && sub_op==8 && s_reg!=REG_RA)
	{
		entre_redirect_jr_call(context);
	}
}

