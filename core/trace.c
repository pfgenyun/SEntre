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
#include "trace.h"
#include "context_switch.h"
#include "isa.h"
#include "in_code.h"


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

#ifdef TRACE
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
//		printf("lw   4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "lw   4\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
//		fflush(stdtrace);
  }
	else if(entre_is_sw(mem_access_insn))
	{
		access_addr = entre_get_mem_access_addr(context);
//		printf("sw   4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "sw   4\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
		fflush(stdtrace);
	}
	else if(entre_is_lh(mem_access_insn))
	{
		access_addr = entre_get_mem_access_addr(context);
//		printf("lh   2\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "lh   2\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
	}
	else if(entre_is_sh(mem_access_insn))
	{
		access_addr = entre_get_mem_access_addr(context);
//		printf("sh   2\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "sh   2\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
  }
  else if(entre_is_lb(mem_access_insn))
  {
	  	access_addr = entre_get_mem_access_addr(context);
//		printf("lb   1\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "lb   1\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
  }
  else if(entre_is_sb(mem_access_insn))
  {
	  	access_addr = entre_get_mem_access_addr(context);
//		printf("sb   1\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "sb   1\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
  }
  else if(entre_is_lwc1(mem_access_insn))
  {
	  	access_addr = entre_get_mem_access_addr(context);
//		printf("lwc1 4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "lwc1 4\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
  			mem_access_insn, insn_addr, access_addr);
  }
  else if(entre_is_swc1(mem_access_insn))
  {
  	access_addr = entre_get_mem_access_addr(context);
//		printf("swc1 4\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "swc1 4\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
  }
  else if(entre_is_ldc1(mem_access_insn))
  {
  	access_addr = entre_get_mem_access_addr(context);
//		printf("ldc1 8\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "ldc1 8\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
  }
  else if(entre_is_sdc1(mem_access_insn))
  {
  	access_addr = entre_get_mem_access_addr(context);
//		printf("sdc1 8\t\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
//				mem_access_insn, insn_addr, access_addr);
		fprintf(stdtrace, "sdc1 8\tinsn: 0x%x\tinsn_addr: 0x%x\taccess_addr: 0x%x\t\n",
				mem_access_insn, insn_addr, access_addr);
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
