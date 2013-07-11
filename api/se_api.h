/************************************************************
 * Copyright (c) 2013-present MeiWenBin.  All rights reserved.
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

#ifndef SE_api_H
#define SE_api_H

#include <sys/types.h>
#include "se_basicblock.h"
#include "se_fun.h"
#include "se_got.h"
#include "se_incode.h"
#include "se_isa.h"
#include "se_utils.h"

/***********************************************************************
 * tool entry point, all the tools should be implemented in the
 * functions. 
 * ********************************************************************/
void api_tool(void);

/***********************************************************************
 * record context on stack, and handle it, then restore context.
 * ********************************************************************/
extern ADDRESS entre_make_context_switch_code(ADDRESS target_addr);

extern void entre_make_new_functions();

/***********************************************************************
 * copy code from *code to codecache, the length of code is len. 
 * codecache_n is the point to the top of codecache.
 * ********************************************************************/
extern ADDRESS entre_cc_add_code(unsigned* code, unsigned len);

#endif
