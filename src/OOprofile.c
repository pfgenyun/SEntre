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
#include "in_code.h"
#include "OOprofile.h"

void entre_OOprofile_init()
{
	putenv("LD_PRELOAD=");
	system(OPCONTROL_INIT);
}

void entre_OOprofile_fini()
{
	system(OPCONTROL_FINI);
}

void entre_func_begine_OOprofile(struct context * context)
{
	system(OPCONTROL_SETUP);
}

void entre_func_end_OOprofile(struct context * context)
{
	system(OPCONTROL_REPORT);
}

void entre_OOprofile_record(struct context * context)
{	
	ADDRESS insn_addr = context->ra + IN_CODE_LW_NUM;
	INSN_T OOprofile_insn = INSN_AT(insn_addr);
	ADDRESS access_addr;
#ifdef DEBUG
	printf("hellooooooooooooprofile!\n");
#endif
	if(entre_is_return_instruction(OOprofile_insn))
	{
		entre_func_end_OOprofile(context);
	}
	else if(entre_is_t9_instruction(OOprofile_insn))
	{
		entre_func_begine_OOprofile(context);
	}
	else
	{
		entre_my_error("entre_OOprofile_record insn error!");
	}
}
