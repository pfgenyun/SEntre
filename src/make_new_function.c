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
#include "function.h"
#include "isa.h"
#include "codecache.h"
#include "reg.h"
#include "make_new_function.h"
#include "in_code.h"

struct instrument_point instrument_omit[INSTRUMENT_OMIT_SIZE];
int instrument_omit_size;
int instrument_omit_num;

/* when a instrument instruction(lw or sw) lies in a 
 * branch delay slot, it cannot be instrumented */
int entre_can_instrument_here(ADDRESS instrument_addr)
{
	INSN_T insn = INSN_AT(instrument_addr - INSN_BYTES);
	if(entre_is_b(insn) || entre_is_call_instruction(insn) ||
	   entre_is_return_instruction(insn) || entre_is_jal(insn) ||
	   entre_is_j(insn))
		return 0;
	else
		return 1;
}

/* record all instrument point when it was not instrumented*/
void entre_instrument_omit_record(ADDRESS omit_addr)
{
	INSN_T insn = INSN_AT(omit_addr);
	if(entre_is_mem_instruction(insn))
	{
		instrument_omit[instrument_omit_num].type = MEM_ACCESS;
		instrument_omit[instrument_omit_num].addr = omit_addr;
		instrument_omit_num ++;
	}
}

/***************************************************************
 copy instruction from orignal space to codecache and insert 
 in_code before jalr jr and jal instruction in a function.
***************************************************************/
void entre_make_a_new_function(struct function * fun)
{
	ADDRESS fun_start_addr = FUNCTION_START_ADDRESS(fun);
	int fun_size = FUNCTION_SIZE(fun);
	
	ADDRESS fun_new_addr = entre_cc_get_top_address();
	entre_got_add_entry(fun_start_addr, fun_new_addr);
#ifdef DEBUG
	printf("old start address:0x%x\tnew start address:0x%x\tfunction name:%-20s\n",
           fun_start_addr, fun_new_addr, fun->f_name);
#endif


	INSN_T* incode_call;
	int incode_call_size = entre_in_code_call_get(&incode_call);
#ifdef TRACE
	INSN_T* incode_mem;
	int incode_mem_size = entre_in_code_mem_get(&incode_mem);
#endif
#ifdef OOprofile
	INSN_T* incode_OOprofile;
	int incode_OOprofile_size = entre_in_code_OOprofile_get(&incode_OOprofile);
#endif
#ifdef OOprofile
	entre_cc_add_code(incode_OOprofile, IN_CODE_SIZE);
#endif
#ifdef BB_FREQ
	INSN_T* incode_bb_freq;
	int incode_bb_freq_size = entre_in_code_bb_freq_get(&incode_bb_freq);
#endif

	INSN_T load_t9[LOAD_T9_NUM];
	load_t9[0] = entre_make_lui(REG_T9, fun_start_addr>>16);
	load_t9[1] = entre_make_inc_x(REG_T9, fun_start_addr&0xffff);
	entre_cc_add_code(load_t9, LOAD_T9_NUM);

	
	ADDRESS addr_i;
	ADDRESS addr_end;
	ADDRESS addr_start = fun_start_addr;
	ADDRESS fun_next_addr = fun_start_addr + fun_size;
	for(addr_i=fun_start_addr; addr_i<fun_next_addr; addr_i+=INSN_BYTES)
	{
		addr_end = addr_i;
		INSN_T insn = INSN_AT(addr_i);

		if(entre_is_call_instruction(insn))
		{
#ifdef DEBUG
			printf("jalr or jr insn:0x%x\tin function:%s\n", addr_end, fun->f_name);
#endif
			entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
			entre_cc_add_code(incode_call, incode_call_size);
			addr_start = addr_end;
		}
#ifdef TRACE
		else if(entre_is_mem_instruction(insn))
		{
#ifdef DEBUG
			printf("memory access insn:0x%x\tin function:%s\n", addr_end, fun->f_name);
#endif
			entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
			if(entre_can_instrument_here(addr_end))
				entre_cc_add_code(incode_mem, incode_mem_size);
			else
				entre_instrument_omit_record(addr_end);
			addr_start = addr_end;
		}
#endif
#ifdef OOprofile
		else if(entre_is_return_instruction(insn))
		{
#ifdef DEBUG
			printf("return insn:0x%x\tin function:%s\n", addr_end, fun->f_name);
#endif
			entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
			if(entre_can_instrument_here(addr_end))
			{
				entre_cc_add_code(incode_OOprofile, incode_OOprofile_size);
			}
			else
			{
				entre_instrument_omit_record(addr_end);
				entre_my_error("OOprofile can not stop!\n");
			}
			addr_start = addr_end;
		}
#endif
#ifdef BB_FREQ
		else if(entre_is_bb_begine(addr_end))
		{
#ifdef DEBUG
			printf("bb begine addr:0x%x\tin function:%s\n", addr_end, fun->f_name);
#endif
			entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
			if(entre_can_instrument_here(addr_end) && !entre_is_instrument_instruction(insn))
			{	
				ADDRESS counter_addr = entre_get_bb_counter_addr(addr_end);
				entre_make_in_code_bb_freq(counter_addr);
				entre_cc_add_code(incode_bb_freq, incode_bb_freq_size);
			}
			else
			{
				entre_instrument_omit_record(addr_end);
				entre_my_error("bb_freq insn vill not reach here!\n");
			}
			addr_start = addr_end;
		}
#endif

	}
	entre_cc_add_code((INSN_T*)addr_start, (fun_next_addr - addr_start) / INSN_BYTES);
#ifdef DEBUG
	printf("old start address:0x%x\tfuncton size:%d\t\t\tfunction name:%-20s\n\n",
	       fun_start_addr, fun_size/INSN_BYTES, fun->f_name);
#endif
}

void entre_make_new_functions()
{
	entre_for_all_function(entre_make_a_new_function);
}

void entre_instrument_omit_init()
{
	instrument_omit_size = INSTRUMENT_OMIT_SIZE;
	instrument_omit_num = 0;
}
