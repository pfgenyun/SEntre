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
#include "context_switch.h"
#include "in_code.h"
#include "isa.h"
#include "make_new_function.h"

void entre_bb_freq_record(struct context * context)
{
	ADDRESS old_addr, new_addr, counter_addr;

	new_addr = context->ra + IN_CODE_LW_NUM;
	old_addr = entre_map_newAddr_2_oldInsnAddr(new_addr);
	counter_addr = entre_get_bb_counter_addr(old_addr);
	ATOMIC_INC(int, *(ADDRESS *)counter_addr);
}
