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
#include "binary.h"

#ifdef API_MODE
#include "se_mode.h"
#endif

struct instrument_point instrument_omit[INSTRUMENT_OMIT_SIZE];
int instrument_omit_size;
int instrument_omit_num;

/* map instruction address in codecache to the function name */
ADDRESS entre_map_newAddr_2_oldInsnAddr(ADDRESS newAddr)
{
	int numPoint;
	int jump_num;
	int bal_num;
	ADDRESS oldFunAddr;
	ADDRESS newFunAddr;
	ADDRESS oldInsnAddr;

    oldFunAddr = entre_got_map_newAddr_2_oldFunAddr(newAddr);
    newFunAddr = entre_got_map_oldAddr_2_newFunAddr(oldFunAddr);
	numPoint = entre_got_find_instrument_num_from_newAddr(newAddr);
	jump_num = entre_got_find_j_num_from_newAddr(newAddr);
	bal_num = entre_got_find_bal_num_from_newAddr(newAddr);
	oldInsnAddr = oldFunAddr 
		          + (newAddr - newFunAddr) 
		          - numPoint*IN_CODE_BYTES
				  - jump_num*J_JAL_T9_NUM*INSN_BYTES
				  - bal_num*BAL_T9_NUM*INSN_BYTES
	              - LOAD_T9_BYTES;

	return oldInsnAddr;

}

/* map instruction address in codecache to the function name */
char *entre_map_newAddr_2_oldFunName(ADDRESS newAddr)
{
	ADDRESS oldFunAddr;
	char * funName;

    oldFunAddr = entre_got_map_newAddr_2_oldFunAddr(newAddr);
    funName = entre_find_funName_from_funOldAddr(oldFunAddr);

	return funName;
}

/* map instruction address in origin address space to the 
 * codecache function beginning */
ADDRESS entre_map_oldAddr_2_newFunAddr(ADDRESS oldAddr)
{
	ADDRESS newFunAddr;
    newFunAddr = entre_got_map_newAddr_2_oldFunAddr(oldAddr);

	return newFunAddr;
}

/* map instruction address in codecache to the orignal address of 
 * function beginning */
ADDRESS entre_map_newAddr_2_oldFunAddr(ADDRESS newAddr)
{
	ADDRESS oldFunAddr;
    oldFunAddr = entre_got_map_newAddr_2_oldFunAddr(newAddr);

	return oldFunAddr;
}


void entre_record_instrument_point(ADDRESS oldAddr, ADDRESS newAddr)
{
    entre_got_add_instrument_point(oldAddr, newAddr);
}

/* calculate the num of instrumentation between the address of branch/jump 
 * instruction and the target address */
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
		/*when branch down, the first and the end instruction will be omit*/
    	for(addr_i=start_addr+INSN_BYTES; addr_i<=end_addr; addr_i+=INSN_BYTES)
    	{
    		INSN_T insn = INSN_AT(addr_i);
#ifdef BB_FREQ
    		if((entre_is_instrument_instruction(insn) || 
    			entre_is_bb_begin(addr_i)) && 
    			entre_can_instrument_here(addr_i))
#else
    		if(entre_is_instrument_instruction(insn) && 
    		   entre_can_instrument_here(addr_i))
#endif
    			lr_num++;
    	}
	}
	else
	{
		start_addr = target_addr;
		end_addr = b_addr;
		/*when branch up, the first and the end instruction will be calculated*/
    	for(addr_i=start_addr; addr_i<=end_addr; addr_i+=INSN_BYTES)
    	{
    		INSN_T insn = INSN_AT(addr_i);
#ifdef BB_FREQ
    		if((entre_is_instrument_instruction(insn) || 
    			entre_is_bb_begin(addr_i)) && 
    			entre_can_instrument_here(addr_i))
#else
    		if(entre_is_instrument_instruction(insn) && 
    		   entre_can_instrument_here(addr_i))
#endif
    			lr_num++;
    	}
	}
	return lr_num;
}

/* calculate the num of instrumentation between the fun start address
 * and the target address */
int entre_jump_num(struct function * fun, ADDRESS target_addr, ADDRESS b_addr)
{
	int lr_num = 0;
	ADDRESS addr_i;
	ADDRESS start_addr;
	ADDRESS end_addr;
	ADDRESS fun_start_addr = FUNCTION_START_ADDRESS(fun);
	
	if(target_addr >= entre_function_next_address(fun) || 
	   target_addr < fun_start_addr )
	{
		entre_my_error("JUMP EE: address does not in function!");
	}

	if(target_addr > b_addr)
	{
		start_addr = b_addr;
		end_addr = target_addr;
		/*when branch down, the first and the end instruction will be omit*/
    	for(addr_i=start_addr+INSN_BYTES; addr_i<=end_addr; addr_i+=INSN_BYTES)
    	{
    		INSN_T insn = INSN_AT(addr_i);
			if(entre_is_jal(insn) || entre_is_j(insn))
    			lr_num++;
    	}
	}
	else
	{
		start_addr = target_addr;
		end_addr = b_addr;
		/*when branch up, the first and the end instruction will be calculated*/
    	for(addr_i=start_addr; addr_i<=end_addr; addr_i+=INSN_BYTES)
    	{
    		INSN_T insn = INSN_AT(addr_i);
			if(entre_is_jal(insn) || entre_is_j(insn))
    			lr_num++;
    	}
	}
	return lr_num;
}

/* calculate the num of instrumentation between the fun start address
 * and the target address */
int entre_bal_num(struct function * fun, ADDRESS target_addr, ADDRESS b_addr)
{
   int lr_num = 0;
   ADDRESS addr_i;
   ADDRESS start_addr;
   ADDRESS end_addr;
   ADDRESS fun_start_addr = FUNCTION_START_ADDRESS(fun);
   
   if(target_addr >= entre_function_next_address(fun) || 
      target_addr < fun_start_addr )
   {
       entre_my_error("JUMP EE: address does not in function!");
   }

   if(target_addr > b_addr)
   {
       start_addr = b_addr;
       end_addr = target_addr;
       /*when branch down, the first and the end instruction will be omit*/
       for(addr_i=start_addr+INSN_BYTES; addr_i<=end_addr; addr_i+=INSN_BYTES)
       {
           INSN_T insn = INSN_AT(addr_i);
           if(entre_is_bal(insn))
               lr_num++;
       }
   }
   else
   {
       start_addr = target_addr;
       end_addr = b_addr;
       /*when branch up, the first and the end instruction will be calculated*/
       for(addr_i=start_addr; addr_i<=end_addr; addr_i+=INSN_BYTES)
       {
           INSN_T insn = INSN_AT(addr_i);
           if(entre_is_bal(insn))
               lr_num++;
       }
   }
   return lr_num;
}

/* when a instrument instruction(lw or sw) lies in a 
 * branch delay slot, it cannot be instrumented */
int entre_can_instrument_here(ADDRESS instrument_addr)
{
	INSN_T insn = INSN_AT(instrument_addr - INSN_BYTES);
	if(entre_is_b(insn) || entre_is_call_instruction(insn) ||
	   entre_is_return_instruction(insn) || entre_is_jal(insn) ||
	   entre_is_j(insn) || entre_is_jr_ra(insn))
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
#ifdef API_MODE
	INSN_T* incode_mode;
	int incode_mode_size = entre_in_code_mode_get(&incode_mode);
#endif

	INSN_T load_t9[LOAD_T9_NUM];
#ifdef N64
    load_t9[0] = entre_make_lui(REG_T9, fun_start_addr>>48);
    load_t9[1] = entre_make_inc_x(REG_T9, ((fun_start_addr>>32)&0xffff));
    load_t9[2] = entre_make_dsll(REG_T9, REG_T9, 16);
    load_t9[3] = entre_make_inc_x(REG_T9, ((fun_start_addr>>16)&0xffff));
    load_t9[4] = entre_make_dsll(REG_T9, REG_T9, 16);
    load_t9[5] = entre_make_inc_x(REG_T9, (fun_start_addr&0xffff));
#else
	load_t9[0] = entre_make_lui(REG_T9, fun_start_addr>>16);
	load_t9[1] = entre_make_inc_x(REG_T9, fun_start_addr&0xffff);
#endif
	entre_cc_add_code(load_t9, LOAD_T9_NUM);

	
	ADDRESS addr_i;
	ADDRESS addr_end;
	ADDRESS addr_start = fun_start_addr;
	ADDRESS fun_next_addr = fun_start_addr + fun_size;
	ADDRESS ccAddr_i;

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
			if(entre_can_instrument_here(addr_end))
			{
				entre_cc_add_code(incode_call, incode_call_size);
#ifdef MAP
				ccAddr_i = entre_cc_get_top_address();
				entre_record_instrument_point(addr_end, ccAddr_i);
#endif
			}
			else
			{
				printf("EE: jalr instuction cannot be instrumented here.\n");
				exit(0);
			}
			addr_start = addr_end;
		}
#ifdef API_MODE
		if(SEntre_mode)
		{
#ifdef DEBUG
			printf("insn addr:0x%x\tin function:%s\n", addr_end, fun->f_name);
#endif
			entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
#ifdef BB_FREQ
			if(entre_can_instrument_here(addr_end) && !entre_is_instrument_instruction(insn))
#else
			if(entre_can_instrument_here(addr_end))
#endif
			{	
				entre_cc_add_code(incode_mode, incode_mode_size);
#ifdef MAP
              	ccAddr_i = entre_cc_get_top_address();
				entre_record_instrument_point(addr_end, ccAddr_i);
#endif
			}
			else
				entre_instrument_omit_record(addr_end);
			addr_start = addr_end;
		}
#endif
		if(entre_is_j(insn) || entre_is_jal(insn))
		{
#ifdef DEBUG
			printf("insn addr:0x%x\tin function:%s\n", addr_end, fun->f_name);
#endif
            entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
            INSN_T j_jal_t9[J_JAL_T9_NUM];
            j_jal_t9[0] = entre_make_nop();
            j_jal_t9[1] = entre_make_nop();
            j_jal_t9[2] = entre_make_nop();
            j_jal_t9[3] = entre_make_nop();
            entre_cc_add_code((INSN_T *)j_jal_t9, J_JAL_T9_NUM);
#ifdef MAP 
            ccAddr_i = entre_cc_get_top_address();
            entre_got_add_jump_point(addr_end, ccAddr_i);
#endif
			addr_start = addr_end;
		}
       	if(entre_is_bal(insn))
       	{
#ifdef DEBUG
            printf("bal insn addr:0x%x\tin function:%s\n", addr_end, fun->f_name);
#endif
            entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
            INSN_T bal_t9[BAL_T9_NUM];
            bal_t9[0] = entre_make_nop();
            bal_t9[1] = entre_make_nop();
            bal_t9[2] = entre_make_nop();
            bal_t9[3] = entre_make_nop();
#ifdef N64
            bal_t9[4] = entre_make_nop();
            bal_t9[5] = entre_make_nop();
            bal_t9[6] = entre_make_nop();
            bal_t9[7] = entre_make_nop();
#endif
            entre_cc_add_code((INSN_T *)bal_t9, BAL_T9_NUM);
#ifdef MAP 
            ccAddr_i = entre_cc_get_top_address();
            entre_got_add_bal_point(addr_end, ccAddr_i);
#endif
            addr_start = addr_end;
       	}
        if((addr_end > Executable.PltStart) && (addr_end <= Executable.PltEnd))
        {   
			entre_cc_add_code((INSN_T*)addr_start, (addr_end - addr_start) / INSN_BYTES);
            if(((insn >> 24) & 0x000000ff) == 0x3c)
            {   
				if(addr_end != fun_start_addr)
				{
              		ccAddr_i = entre_cc_get_top_address();
					entre_got_add_entry(addr_end, ccAddr_i);
				}
            }   
			addr_start = addr_end;
        } 
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
