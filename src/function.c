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
#include <string.h>
#include "global.h"
#include "function.h"
#include "basicblock.h"
#include "binary.h"
#include "isa.h"
#include "make_new_function.h"

struct function all_function[ALL_FUNCTION_SIZE];
int all_function_size;
int all_function_n;

int entre_lr_num(struct function * fun, ADDRESS target_addr, ADDRESS b_addr)
{
	int lr_num = 0;
	ADDRESS addr_i;
	ADDRESS start_addr;
	ADDRESS end_addr;
	ADDRESS fun_start_addr = FUNCTION_START_ADDRESS(fun);
	
	if(target_addr >= entre_function_next_address(fun) || 
	   target_addr < fun_start_addr )
	{
		entre_my_error("EE: address does not in function!");
	}

	if(target_addr > b_addr)
	{
		start_addr = b_addr;
		end_addr = target_addr;
	}
	else
	{
		start_addr = target_addr;
		end_addr = b_addr;
	}
#ifdef BB_FREQ
	for(addr_i=start_addr; addr_i<=end_addr; addr_i+=INSN_BYTES)
#else
	for(addr_i=start_addr; addr_i<end_addr; addr_i+=INSN_BYTES)
//	for(addr_i=start_addr; addr_i<=end_addr; addr_i+=INSN_BYTES)
#endif
	{
		INSN_T insn = INSN_AT(addr_i);
//		if(entre_is_instrument_instruction(insn) && 
//		   entre_is_bb_begine(addr_i))
//		{
//			printf("instrument and bb_begine. addr: 0x%x\t insn: 0x%x\n",
//					addr_i, insn);
//			entre_my_error("Cannot reach here!");
//		}
#ifdef BB_FREQ
		if((entre_is_instrument_instruction(insn) || 
			entre_is_bb_begine(addr_i)) && 
			entre_can_instrument_here(addr_i))
#else
		if(entre_is_instrument_instruction(insn) && 
		   entre_can_instrument_here(addr_i))
#endif
			lr_num ++;
	}
	return lr_num;
}

int entre_is_before_main(struct function * fun)
{
	if(strcmp(fun->f_name, "__start") == 0 ||
       strcmp(fun->f_name, "__do_global_dtors_aux") == 0 ||
       strcmp(fun->f_name, "frame_dummy") == 0 ||
       strcmp(fun->f_name, "__do_global_ctors_aux") == 0 )
		return 1;

	return 0;
}

void entre_for_all_function(void (*my_fun)(struct function *))
{
	struct function * fun;
	int i;

	for(i=0; i<all_function_n; i++)
	{
		fun = &all_function[i];
		(*my_fun)(fun);
	}
}

struct function * entre_find_function(char * name)
{
	int i;
	struct function * fun;
	
	for(i=0; i<all_function_n; i++)
	{
		fun = &all_function[i];
		if(strcmp(name, fun->f_name)==0)
			return fun;
	}
	return NULL;
}

ADDRESS entre_function_next_address(struct function * fun)
{
	struct bb * bb_p = BASIC_BLOCK(fun->f_firstBB + fun->f_numBB -1 );
	ADDRESS addr = bb_p->start + bb_p->insn_num*4;
	return addr;
}

ADDRESS entre_function_start_address(struct function * fun)
{
	struct bb * bb_p = BASIC_BLOCK(fun->f_firstBB);
	return bb_p->start;
}

int entre_function_size(struct function * fun)
{
	return entre_function_next_address(fun) - entre_function_start_address(fun);
}

void entre_call_for_all_function(void (*my_fun)(struct function *))
{
	struct function * fun;
	int i;

	for(i=0; i<all_function_n; i++)
	{
		fun = &all_function[i];
		(*my_fun)(fun);
	}
}

inline int entre_function_num()
{
    return all_function_n;
}

void entre_init_one_function(Elf32_Sym *sym, unsigned first_bb, unsigned bb_num)
{
    int i;

    i = all_function_n ++;
    all_function[i].f_name = (char *) &(Executable.pStrTab[(int)sym->st_name]);
    all_function[i].f_address = sym->st_value;
    all_function[i].f_codesize = sym->st_size;
    all_function[i].f_firstBB = first_bb;
    all_function[i].f_numBB = bb_num;
}

void entre_init_function(void)
{
    Elf32_Sym *sym;
    
    all_function_size = Executable.nSymTab;
    all_function_n = 0;

    if(all_function_size > ALL_FUNCTION_SIZE)
    {
        entre_my_error("init function error: memory out\n");
    }
}
