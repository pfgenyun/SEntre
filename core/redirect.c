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
#include <string.h>
#include "global.h"
#include "context_switch.h"
#include "isa.h"
#include "reg.h"
#include "in_code.h"
#include "redirect.h"
#include "make_new_function.h"
#include "got.h"

unsigned  global_var =0;

/* judje whether the new target of j/jal instruction out of range.
 * new_replace_addr is the address of the j/jal instruction at new space
 * new_target_addr  is the address of the j/jal target at new space*/
int entre_out_of_j_range(ADDRESS new_replace_addr, ADDRESS new_target_addr)
{
	if(new_target_addr > new_replace_addr)	/* j/jal after*/
	{
		if((new_target_addr-new_replace_addr)/INSN_BYTES > 0x3ffffff)
		    return true;
	}
	else							/* j/jal before*/
	{
		if((new_replace_addr-new_target_addr)/INSN_BYTES > 0x3ffffff)
		    return true;
	}
	return false;
}

/* calculate new target of b instruction when redirect b instruction.
 * old_target_addr is the target address at orignal space
 * b_addr is b instruction address at orignal space
 * fun_call_num is jalr and jr instruction number between 
 * old_target_addr and b_addr */
int entre_get_b_new_target(ADDRESS old_target_addr, ADDRESS b_addr, int fun_call_num, int j_call_num, int bal_call_num)
{
	ADDRESS new_target_addr;

	if(old_target_addr > b_addr)	/* branch after*/
	{
		new_target_addr = old_target_addr + fun_call_num*IN_CODE_SIZE*INSN_BYTES + j_call_num*J_JAL_T9_NUM*INSN_BYTES + bal_call_num*BAL_T9_NUM*INSN_BYTES;
		if((new_target_addr-b_addr)/INSN_BYTES-1>0x8fff)
		{
            printf("             ************************************************************\n");
            printf("             ******       WARNING1: Branch Offset Over 2^15!       ******\n");
            printf("             ******            Suggest Not Instrument!             ******\n");
            printf("             ************************************************************\n");
		}
	}
	else							/* branch before*/
	{
		new_target_addr = old_target_addr - fun_call_num*IN_CODE_SIZE*INSN_BYTES - j_call_num*J_JAL_T9_NUM*INSN_BYTES - bal_call_num*BAL_T9_NUM*INSN_BYTES;
		if((b_addr-new_target_addr)/INSN_BYTES-1>0x8fff && (b_addr != old_target_addr))
		{
            printf("             ************************************************************\n");
            printf("             ******       WARNING2: Branch Offset Over 2^15!       ******\n");
            printf("             ******            Suggest Not Instrument!             ******\n");
            printf("             ************************************************************\n");
		}
	}

	return new_target_addr;
}

/*******************************************************************
 redirect j and jal instruction's target from orignal space to new 
 space in codecache.
*******************************************************************/
int 
entre_jump_redirect(int jump_insn_index_new, ADDRESS jump_new_start_addr, ADDRESS jump_new_target, ADDRESS jump_next_addr, INSN_T jump_insn)
{
	int insn_index_new = jump_insn_index_new;
	ADDRESS new_start_addr = jump_new_start_addr;
	ADDRESS new_target = jump_new_target;
	ADDRESS addr_next = jump_next_addr;
	ADDRESS new_replace_addr;
	INSN_T new_insn, insn_redirect, next_insn;
	INSN_T insn = jump_insn;

	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
	new_insn = INSN_AT(new_replace_addr);
	if(entre_is_nop(new_insn))
	{
		insn_redirect = entre_make_sd(REG_SP, REG_T9, -8);
		entre_cc_replace(new_replace_addr, insn_redirect);
	}
	else
		printf("error: 0x%x in not nop!\n", new_replace_addr);
	insn_index_new++;
	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
	new_insn = INSN_AT(new_replace_addr);
	if(entre_is_nop(new_insn))
	{   
		insn_redirect = entre_make_lui(REG_T9, new_target>>16);
		entre_cc_replace(new_replace_addr, insn_redirect);
	}
	else
		printf("error: 0x%x in not nop!\n", new_replace_addr);
	insn_index_new++;
	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
	new_insn = INSN_AT(new_replace_addr);
	if(entre_is_nop(new_insn))
	{
		insn_redirect = entre_make_inc_x(REG_T9, new_target&0xffff);
		entre_cc_replace(new_replace_addr, insn_redirect);
	}
	else
		printf("error: 0x%x in not nop!\n", new_replace_addr);
	insn_index_new++;
	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
	new_insn = INSN_AT(new_replace_addr);
	if(entre_is_nop(new_insn))
	{
		if(entre_is_j(insn))
			insn_redirect = entre_make_jr(REG_T9);
		else
			insn_redirect = entre_make_jalr(REG_T9);
		entre_cc_replace(new_replace_addr, insn_redirect);
	}
	else
		printf("error: 0x%x in not nop!\n", new_replace_addr);
	insn_index_new++;
	next_insn = INSN_AT(addr_next);
	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
	new_insn = INSN_AT(new_replace_addr);
	entre_cc_replace(new_replace_addr, next_insn);
	insn_index_new++;
	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
	insn_redirect = entre_make_ld(REG_SP, REG_T9, -8);
    entre_cc_replace(new_replace_addr, insn_redirect);
}

/*******************************************************************
 redirect jal and b instruction's target from orignal space to new 
 space in codecache.
*******************************************************************/
void entre_jal_b_redirect(struct function * fun)
{
	ADDRESS new_start_addr, addr_i, addr_t, old_replace_addr, new_replace_addr;
	ADDRESS fun_start_addr = FUNCTION_START_ADDRESS(fun);
    int fun_size = FUNCTION_SIZE(fun);
    ADDRESS fun_next_addr = fun_start_addr + fun_size;
	int insn_index_old= 0, insn_index_new = 0;
	int fun_call_num, jump_num, jump_call_num;

	new_start_addr = entre_got_find_orig(fun_start_addr);
	if(new_start_addr == 0)
		entre_my_error("EE: redirect error!");

	for(addr_i=fun_start_addr; addr_i<fun_next_addr; addr_i+=INSN_BYTES)
    {
		ADDRESS old_target=0, new_target = 0, offset = 0;
		INSN_T insn_redirect, new_insn, old_insn;
        INSN_T insn = INSN_AT(addr_i);

		insn_index_old++;
		insn_index_new++;
	
		/* in_code instruction number */
#ifdef BB_FREQ
		if((entre_is_instrument_instruction(insn) || 
			entre_is_bb_begin(addr_i)) &&
			entre_can_instrument_here(addr_i))
#else	
		if(entre_is_instrument_instruction(insn) &&
		   entre_can_instrument_here(addr_i))
#endif
			insn_index_new += IN_CODE_SIZE;

        if(entre_is_jal(insn) || entre_is_j(insn))
        {
			old_target = ((TARGET(insn)<<2) | ((addr_i) & 0xf0000000));
			if(old_target >= entre_function_next_address(fun) || old_target < fun_start_addr )
			{
				new_target = entre_got_find_final(old_target);
				if(new_target == 0)			/*for gcc-4.6 jal to .plt */
					new_target = old_target;
				new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
				if(entre_out_of_j_range(new_replace_addr, new_target))
				{
					addr_i += INSN_BYTES;
					entre_jump_redirect(insn_index_new, new_start_addr, new_target, addr_i, insn);
					insn_index_new += 5;
					insn_index_old += 2;
					continue;
				}
			}
			else
			{
                fun_call_num = 0;
                jump_num = 0;
				int bal_num = 0;
                for(addr_t = fun_start_addr; addr_t <= old_target; addr_t+=INSN_BYTES)
                {
                    new_insn = INSN_AT(addr_t);
#ifdef BB_FREQ
                    if((entre_is_instrument_instruction(new_insn) || entre_is_bb_begin(addr_t)) && entre_can_instrument_here(addr_t))
                        fun_call_num++;
#else
                    if(entre_is_instrument_instruction(new_insn) && entre_can_instrument_here(addr_t))
                        fun_call_num++;
#endif
                    if(entre_is_jal(new_insn) || entre_is_j(new_insn))
                        jump_num++;
                    if(entre_is_bal(new_insn))
                        bal_num++;
                }
                offset = old_target - fun_start_addr;
                new_target = new_start_addr + offset + fun_call_num*IN_CODE_SIZE*INSN_BYTES + jump_num*J_JAL_T9_NUM*INSN_BYTES + bal_num*BAL_T9_NUM*INSN_BYTES;
			}
			if(entre_is_jal(insn))
				insn_redirect = entre_make_jal(new_target);
			else if(entre_is_j(insn))
				insn_redirect = entre_make_j(new_target);
#ifdef DEBUG
			printf("old_jal_j_target:0x%x\tnew_jal_j_target:0x%x\tfunction name:%-20s\n",
                   old_target, new_target, fun->f_name);
#endif
			insn_index_new += J_JAL_T9_NUM;
			old_replace_addr = fun_start_addr + (insn_index_old-1)*INSN_BYTES;
			new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
			entre_cc_replace(new_replace_addr, insn_redirect);
            insn_index_new++;
            insn_index_old++;
            addr_i += INSN_BYTES;
#ifdef DEBUG
            printf("old_jal_j_addr:0x%x\tnew_jal_j_addr:0x%x\tfunction name:%-20s\n\n",
                   old_replace_addr, new_replace_addr, fun->f_name);
#endif
			continue;
        }
		if(entre_is_b(insn))
		{
			old_target = entre_branch_target(addr_i, insn);
#ifdef DEBUG
			printf("old_b_insn: 0x%x\told_b_target: 0x%x\tfunction name: %-20s\n",
					insn, old_target, fun->f_name);
#endif
           	if(old_target >= fun_next_addr || old_target < fun_start_addr)
           	{
               	new_target = entre_got_find_final(old_target);
               	if(entre_is_bal(insn))
               	{
                   	if((S_REG(insn) > 0) || (S_REG(insn) == 0))
                   	{
#ifdef N64
                       	insn_redirect = entre_make_sd(REG_SP, REG_T9, -8);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_lui(REG_T9, new_target>>48);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_inc_x(REG_T9, ((new_target>>32)&0xffff));
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_dsll(REG_T9, REG_T9, 16);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_inc_x(REG_T9, ((new_target>>16)&0xffff));
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_dsll(REG_T9, REG_T9, 16);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_inc_x(REG_T9, (new_target&0xffff));
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_jalr(REG_T9);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_index_old++;
                       	addr_i += INSN_BYTES;
                       	INSN_T next_insn = INSN_AT(addr_i);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, next_insn);
                       	insn_index_new++;
                       	insn_redirect = entre_make_ld(REG_SP, REG_T9, -8);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
#else
                       	insn_redirect = entre_make_sw(REG_SP, REG_T9, -8);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_lui(REG_T9, new_target>>16);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_inc_x(REG_T9, (new_target&0xffff));
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_redirect = entre_make_jalr(REG_T9);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
                       	insn_index_new++;
                       	insn_index_old++;
                       	addr_i += INSN_BYTES;
                       	INSN_T next_insn = INSN_AT(addr_i);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, next_insn);
                       	insn_index_new++;
                       	insn_redirect = entre_make_ld(REG_SP, REG_T9, -8);
                       	new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
                       	entre_cc_replace(new_replace_addr, insn_redirect);
						continue;
                   	}
               	}
               	else
               	{
					new_replace_addr = new_start_addr + (insn_index_new-1)*INSN_BYTES;
					insn_redirect = entre_make_b(insn, (new_target-new_replace_addr)/INSN_BYTES-1); /* -1 is for broffset*/
				}
			}
			else
			{
#endif
				fun_call_num = entre_lr_num(fun, old_target, addr_i);
				jump_call_num = entre_jump_num(fun, old_target, addr_i);
				int bal_call_num = entre_bal_num(fun, old_target, addr_i);
				new_target = entre_get_b_new_target(old_target, addr_i, fun_call_num, jump_call_num, bal_call_num);
				insn_redirect = entre_make_b(insn, (new_target-addr_i)/INSN_BYTES-1); /* -1 is for broffset*/
			}
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
		old_addr = (ADDRESS)context->old_t9;
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
	char *str;
#ifdef DEBUG
	if(global_var++%10000 == 0)
	{
	  printf("In jalr !!!!!\n");
	}
#endif

    //when the parameter is a function pointer
    ADDRESS new_addr;

	/* spec-cpu2000 168 can not pass with runspec: segmentation fault */
    new_addr = entre_got_find_final((ADDRESS)context->a0);
	if (new_addr != 0)
        context->a0 = new_addr;
    new_addr = entre_got_find_final((ADDRESS)context->a1);
	if (new_addr != 0)
	{
//#ifdef MAP /*168 pass, chromium cann't pass*/	
//		str = entre_map_newAddr_2_oldFunName((ADDRESS)context->a1);
//		if(str != NULL)
//		{
//			if(strstr(str, "PerlIO_arg_fetch") == NULL)
//        		context->a1 = new_addr;
//		}
//#else	/*168 cann't pass, chromuim pass*/
        context->a1 = new_addr;
//#endif
	}
    new_addr = entre_got_find_final((ADDRESS)context->a2);
	if (new_addr != 0)
	{
//#ifdef MAP /*168 pass, chromium cann't pass*/	
//		str = entre_map_newAddr_2_oldFunName((ADDRESS)context->a2);
//		if(str != NULL)
//		{
//			if(strstr(str, "uinith_") == NULL && strstr(str, "muldoe_") == NULL && strstr(str, "zdotc_") == NULL)
//        		context->a2 = new_addr;
//		}
//#else	/*168 cann't pass, chromuim pass*/
        context->a2 = new_addr;
//#endif
	}
    new_addr = entre_got_find_final((ADDRESS)context->a3);
	if (new_addr != 0)
        context->a3 = new_addr;

	ADDRESS jalr_addr = context->ra + IN_CODE_LW_NUM;
	INSN_T jalr_insn = INSN_AT(jalr_addr);

	if(MAIN_OP(jalr_insn) != 0 || SUB_OP(jalr_insn) != 9)
		entre_my_error("entre_redirect_jalr insn error!");

	REG_T s_reg = S_REG(jalr_insn);
	REG_T d_reg = D_REG(jalr_insn);

	if(d_reg != REG_RA)
		entre_my_error("entre_redirect_jalr reg error!");

	ADDRESS old_addr;
//	ADDRESS new_addr;

	if(s_reg == REG_T9)
	{
		old_addr = (ADDRESS)context->old_t9;
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
//when the parameter is a function pointer
    ADDRESS new_addr;

#ifdef DUMP_CONTEXT
	entre_dump_context(context);
#endif

	ADDRESS dirty_addr = context->ra + IN_CODE_LW_NUM;
	INSN_T dirty_insn = INSN_AT(dirty_addr);

	int main_op = MAIN_OP(dirty_insn);
	int sub_op = SUB_OP(dirty_insn);
	REG_T s_reg = S_REG(dirty_insn);

#ifdef DUMP_DIRTY_CALL
	ADDRESS map_funAddr = entre_map_newAddr_2_oldFunAddr(dirty_addr);
	ADDRESS map_InsnAddr = entre_map_newAddr_2_oldInsnAddr(dirty_addr);
	char* funName = entre_map_newAddr_2_oldFunName(dirty_addr);

	printf("in call_redirect\n");
	printf("fun_name: %s  dirty_addr: %x  old_InsnAddr: %x  old_funAddr: %x  \
dirty_insn: %x  main_op: %d  sub_op: %d s_reg: %d\n",
			funName, dirty_addr, map_InsnAddr, map_funAddr, 
			dirty_insn, main_op, sub_op, s_reg);
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

