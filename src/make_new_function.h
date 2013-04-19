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


#ifndef MAKE_NEW_FUNCTION_H
#define MAKE_NEW_FUNCTION_H

#include "function.h"
#include "global.h"

#define LOAD_T9_NUM  2
#define LOAD_T9_BYTES  LOAD_T9_NUM*INSN_BYTES
#define INSTRUMENT_OMIT_SIZE  1000

enum instrument_type
{
	B_INSN,
	FUN_CALL,
	MEM_ACCESS
};

struct instrument_point
{
	enum instrument_type type;
	ADDRESS addr;
};

void entre_instrument_omit_init();
int entre_can_instrument_here(ADDRESS );
void entre_instrument_omit_record(ADDRESS );
void entre_make_new_functions();
void entre_make_a_new_function(struct function *);
int entre_lr_num(struct function * fun, ADDRESS target_addr, ADDRESS b_addr);

#endif
