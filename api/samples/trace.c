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

#include "se_api.h"
//#include <stdio.h>
#include <stdlib.h>

//#include "trace.h"
//#include "context_switch.h"
//#include "isa.h"
//#include "in_code.h"

void entre_init_trace(void)
{
	int i;

	trace_n = 0;
	for(i = 0; i < TRACE_SIZE; i++)
	{
		all_trace[i].counter = 0;
		all_trace[i].insn_addr = 0;
		all_trace[i].access_addr = 0;
		all_trace[i].mem_access_insn = 0;
		all_trace[i].fun_name = '\0';
	}
}

int entre_get_trace_index(ADDRESS addr)
{
    int low, high, mid;

    low = 0;
    high = trace_n - 1;
    mid = 0;

    if(addr == all_trace[low].insn_addr)
        return low;
    if(addr == all_trace[high].insn_addr)
        return high;
    
    while(low <= high)
    {   
        mid = low + (high - low)/2;
        if(addr == all_trace[mid].insn_addr)
            return mid;
    
        if(all_trace[mid].insn_addr > addr)
            high = mid - 1;
        else
            low = mid + 1;
    }   

    if(low > high)
        return -1; 
}

ADDRESS entre_get_mem_access_addr(struct context * context)
{
	ADDRESS insn_addr = context->ra + IN_CODE_LW_NUM;
	ADDRESS access_addr;
	UINT64 b_reg_value;
	INSN_T mem_access_insn = INSN_AT(insn_addr);
	
	INT offset = entre_offset_cvt(OFFSET(mem_access_insn));
	REG_T b_reg = S_REG(mem_access_insn);

	if((b_reg < 0) || (b_reg > 36))
	{
	  printf("EE: b_reg out of range!\n");
	  exit(0);
	}

	if(b_reg == 29)
	{
		b_reg_value = context->old_sp;
	}
	else if(b_reg == 31)
	{
		b_reg_value = context->old_ra;
	}
	else if(b_reg == 25)
	{
		b_reg_value = context->old_t9;
	}
	else
	{
//		int* p_context = ((int *)context);
		UINT64* p_context = ((UINT64 *)context);
		p_context++;
		b_reg_value = p_context[b_reg]; /* +1 is for context->stack */
//		b_reg_value = p_context[(b_reg+1)*2]; /* +1 is for context->stack */
	}
	access_addr = entre_mem_access_addr((ADDRESS)b_reg_value, offset);

//#ifdef DEBUG
//	entre_dump_context(context);
//#endif

#ifdef DEBUG
//	printf("b_reg: %d\tb_reg_value: %d 0x%x\toffset: %d 0x%x\taccess_addr: %d 0x%x\t\n",
//			b_reg, b_reg_value, b_reg_value, offset, offset, access_addr, access_addr);
	printf("b_reg: %d\tb_reg_value: 0x%x\toffset: 0x%x\taccess_addr: 0x%x\t\n",
			b_reg, b_reg_value, b_reg_value, offset, access_addr);
#endif

	return access_addr;
}

void entre_trace_add(ADDRESS addr, INSN_T insn, ADDRESS access_addr)
{
	int cur;

	cur = entre_get_trace_index(addr);
	if(cur == -1) {
		all_trace[trace_n].counter = 1;
		all_trace[trace_n].insn_addr = entre_map_newAddr_2_oldInsnAddr(addr);
		all_trace[trace_n].mem_access_insn = insn;
		all_trace[trace_n].access_addr = access_addr;
		all_trace[trace_n].fun_name = entre_map_newAddr_2_oldFunName(addr);
		trace_n++;
	}   
	else
      	all_trace[cur].counter++;
}

#ifdef TRACE
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
int XPos = 100, YPos = 1000, Old_XPos = 0, Old_YPos = 0;
int svg_mark = 0;
int svg_count = 0;
ADDRESS temp_addr = 0;

void entre_svg_out(ADDRESS access)
{
#ifdef OUT_TRACE_STACK
    if(svg_mark == 1 && access > 0x70000000) {
#endif
#ifdef OUT_TRACE_HEAP
    if(svg_mark == 1 && access > 0x20000000 && access < 0x70000000) {
#endif
        if(Old_XPos == 0 && Old_YPos == 0) {
            Old_XPos = XPos;
            Old_YPos = YPos;
        }
        else {
            fprintf(stdtrace, "<path d=\"M %d %d L %d %d\" fill=\"blue\" stroke=\"red\" stroke-width=\"3\" />\n", Old_XPos, Old_YPos, XPos, YPos - (access - temp_addr));
			if(svg_count == 5) {
        		fprintf(stdtrace, "<text style=\"font-size:30;stroke:none;fill:rgb(0,0,0);\" x=\"%d\" y=\"%d\">\n", XPos, YPos - (access - temp_addr) - 10);
		        fprintf(stdtrace, "0x%x\n", access);
				fprintf(stdtrace, "</text>\n");
				svg_count = 0;
			}
            Old_XPos = XPos;
            Old_YPos = YPos - (access - temp_addr);
        }
		svg_count++;
        XPos += 20;
    }
}
#endif

#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
void entre_get_svg(ADDRESS access)
{
	if(svg_mark == 1)
		return;
#ifdef OUT_TRACE_STACK
    if(svg_mark == 0 && access > 0x70000000) {
#endif
#ifdef OUT_TRACE_HEAP
    if(svg_mark == 0 && access > 0x20000000 && access < 0x70000000) {
#endif
        temp_addr = access;
        svg_mark = 1;
        fprintf(stdtrace, "<text style=\"font-size:30;stroke:none;fill:rgb(0,0,0);\" x=\"%d\" y=\"%d\">\n", XPos - 100, YPos);
        fprintf(stdtrace, "0x%x\n", temp_addr);
        fprintf(stdtrace, "</text>\n");
    }
}
#endif

void entre_trace_record(struct context * context)
{
	ADDRESS insn_addr = context->ra + IN_CODE_LW_NUM;
	INSN_T mem_access_insn = INSN_AT(insn_addr);
	ADDRESS access_addr;

	if(!entre_is_mem_instruction(mem_access_insn))
	{
		printf("error insn\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
		entre_my_error("entre_trace_record insn error 1!");
	}

	if(entre_is_lw(mem_access_insn))
	{
		access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
        entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "lw   4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
	}
	else if(entre_is_sw(mem_access_insn))
	{
		access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "sw   4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
	}
	else if(entre_is_lh(mem_access_insn))
	{
		access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "lh   2\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
	}
	else if(entre_is_sh(mem_access_insn))
	{
		access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "sh   2\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
  	}
  	else if(entre_is_lb(mem_access_insn))
  	{
	  	access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "lb   1\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
  	}
  	else if(entre_is_sb(mem_access_insn))
  	{
	  	access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "sb   1\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
  	}
  	else if(entre_is_lwc1(mem_access_insn))
  	{
	  	access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "lwc1   4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
  	}
  	else if(entre_is_swc1(mem_access_insn))
  	{
  		access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "swc1   4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
  	}
  	else if(entre_is_ldc1(mem_access_insn))
  	{
  		access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "ldc1   8\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
  	}
  	else if(entre_is_sdc1(mem_access_insn))
  	{
  		access_addr = entre_get_mem_access_addr(context);
#ifdef OUT_SVG
#if defined(OUT_TRACE_STACK) || defined(OUT_TRACE_HEAP)
		entre_get_svg(access_addr);
        entre_svg_out(access_addr);
#else
		entre_trace_add(insn_addr, mem_access_insn, access_addr);
#endif
#else
		fprintf(stdtrace, "sdc1   8\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
#endif
	}
	else
	{
		entre_my_error("entre_trace_record insn error! 2");
	}
}
#else
void entre_trace_record(struct context * context)
{
}
#endif

