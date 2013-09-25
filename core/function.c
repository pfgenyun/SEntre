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

struct function all_function[ALL_FUNCTION_SIZE];
int all_function_size;
int all_function_n;

char * entre_find_funName_from_funOldAddr(ADDRESS oldAddr)
{
	int i;
	struct function * fun;
	
	for(i=0; i<all_function_n; i++)
	{
		fun = &all_function[i];
		if(oldAddr == fun->f_address)
			return fun->f_name;
	}
	return NULL;
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
	ADDRESS addr_i;
	INSN_T insn;
	int plt_fun_num = 0;

	for(addr_i = Executable.PltStart + INSN_BYTES; addr_i < Executable.PltEnd; addr_i += INSN_BYTES)
	{
		insn = INSN_AT(addr_i);
    	if(((insn >> 24) & 0x000000ff) == 0x3c)
			plt_fun_num++;
	}
    return (all_function_n + plt_fun_num);
}

#ifdef N64
void entre_init_one_function_for_share_pic(Elf64_Sym *sym)
#else
void entre_init_one_function_for_share_pic(Elf32_Sym *sym)
#endif
{
    int i;

    i = all_function_n ;
    all_function[i].f_name = (char *) &(Executable.pStrTab[(int)sym->st_name]);
    all_function[i].f_address = sym->st_value;
    all_function[i].f_codesize = sym->st_size;

// 	all_function_n = 0;
}

#ifdef N64
void entre_init_one_function(Elf64_Sym *sym, unsigned first_bb, unsigned bb_num)
#else
void entre_init_one_function(Elf32_Sym *sym, unsigned first_bb, unsigned bb_num)
#endif
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
#ifdef N64
    Elf64_Sym *sym;
#else
    Elf32_Sym *sym;
#endif
    
    all_function_size = Executable.nSymTab;
    all_function_n = 0;

    if(all_function_size > ALL_FUNCTION_SIZE)
    {
        entre_my_error("init function error: memory out\n");
    }
}
