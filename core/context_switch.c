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
#include "codecache.h"
#include "redirect.h"

//extern void entre_call_redirect(struct context * context);

ADDRESS entre_make_context_switch_code(ADDRESS target_addr)
{
    int i;
    int insn_i;
    INSN_T scode[SCODE_SIZE];
    ADDRESS context_addr;
//    ADDRESS addr = (ADDRESS) entre_call_redirect;

    insn_i = 0;

	/* 36 position was used 33 in fact. the remaining 3 was used in in_code function. */
    scode[insn_i++] = entre_make_addiu(REG_SP, REG_SP, (-(36*8)));	/* stack space */
    for(i=0; i<32; i++)
    {
        scode[insn_i++] = entre_make_sd(REG_SP, (REG_T)i, (i+1)*8);		/* record context on stack */
    }
    scode[insn_i++] = entre_make_move(REG_A0, REG_SP);				/* parameter pass to entre_main_entry */
    scode[insn_i++] = entre_make_sd(REG_SP, REG_SP, 0);				/* parameter stored into stack */
	scode[insn_i++] = entre_make_lui(REG_T9,target_addr>>16);
	scode[insn_i++] = entre_make_inc_x(REG_T9, target_addr&0xffff);
	scode[insn_i++] = entre_make_jalr(REG_T9);
	scode[insn_i++] = entre_make_nop();
	for(i=0; i<32; i++)
	{
	    scode[insn_i++] = entre_make_ld(REG_SP, (REG_T)i, (i+1)*8);
	}
	scode[insn_i++] = entre_make_jr(REG_RA);
	scode[insn_i++] = entre_make_addiu(REG_SP, REG_SP, (36*8));		/* exe before jr */
//	scode[insn_i++] = entre_make_nop();

    context_addr = entre_cc_get_top_address();		/* copy this code to cc */
	entre_cc_add_code(scode, insn_i);
#ifdef DEBUG
	printf("codecache start address:0x%x in context switch code\n\n", context_addr);
#endif

	return context_addr;
}


/*************************************************************
 * ****************************debug*************************
 * ***********************************************************/
/*
void entre_dump_context(struct context * context)
{
	printf("\t\t\t\tstack: %-8x\tzero: %-8x\tat: %-8x\tv0: %-8x\tv1: %-8x\t\n	\
			a0: %-8x\ta1: %-8x\ta2: %-8x\ta3: %-8x\t\n	\
			t0: %-8x\tt1: %-8x\tt2: %-8x\tt3: %-8x\t\n	\
			t4: %-8x\tt5: %-8x\tt6: %-8x\tt7: %-8x\t\n	\
			s0: %-8x\ts1: %-8x\ts2: %-8x\ts3: %-8x\t\n	\
			s4: %-8x\ts5: %-8x\ts6: %-8x\ts7: %-8x\t\n	\
			t8: %-8x\tt9: %-8x\tk0: %-8x\tk1: %-8x\t\n	\
			gp: %-8x\tsp: %-8x\tfp: %-8x\tra: %-8x\t\n	\
			old_t9: %-x\told_ra: %-x\t\n",
		context->stack, context->zero, context->at, context->v0, context->v1,
		context->a0, context->a1, context->a2, context->a3,
		context->t0, context->t1, context->t2, context->t3,
		context->t4, context->t5, context->t6, context->t7,
		context->s0, context->s1, context->s2, context->s3,
		context->s4, context->s5, context->s6, context->s7,
		context->t8, context->t9, context->k0, context->k1,
		context->gp, context->sp, context->fp, context->ra,
		context->old_t9, context->old_ra);
}
*/


void entre_dump_context(struct context * context)
{
	printf("\t\t\t\tstack: %-16llx\tzero: %-16llx\t\n	\
			at: %-16llx\tv0: %-16llx\tv1: %-16llx\t\n	\
			a0: %-16llx\ta1: %-16llx\ta2: %-16llx\t\n	\
			a3: %-16llx\tt0: %-16llx\tt1: %-16llx\t\n	\
			t2: %-16llx\tt3: %-16llx\tt4: %-16llx\t\n	\
			t5: %-16llx\tt6: %-16llx\tt7: %-16llx\t\n	\
			s0: %-16llx\ts1: %-16llx\ts2: %-16llx\t\n	\
			s3: %-16llx\ts4: %-16llx\ts5: %-16llx\t\n	\
			s6: %-16llx\ts7: %-16llx\tt8: %-16llx\t\n	\
			t9: %-16llx\tk0: %-16llx\tk1: %-16llx\t\n	\
			gp: %-16llx\tsp: %-16llx\tfp: %-16llx\t\n	\
			ra: %-16llx\told_t9: %-llx\told_sp: %-llx\told_ra: %-llx\n",
		context->stack, context->zero, context->at, context->v0, context->v1,
		context->a0, context->a1, context->a2, context->a3,
		context->t0, context->t1, context->t2, context->t3,
		context->t4, context->t5, context->t6, context->t7,
		context->s0, context->s1, context->s2, context->s3,
		context->s4, context->s5, context->s6, context->s7,
		context->t8, context->t9, context->k0, context->k1,
		context->gp, context->sp, context->fp, context->ra,
		context->old_t9, context->sp, context->old_ra);
}



