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


#ifndef CONTEXT_SWITCH_H
#define CONTEXT_SWITCH_H

#include "global.h"

#define SCODE_SIZE 73

struct context
{
	UINT64  stack;
    UINT64  zero;   
    UINT64  at;    
    UINT64  v0;     
    UINT64  v1;    
    UINT64  a0;    
    UINT64  a1;    
    UINT64  a2;     
    UINT64  a3;    
    UINT64  t0;    
    UINT64  t1;    
    UINT64  t2;    
    UINT64  t3;    
    UINT64  t4;    
    UINT64  t5;    
    UINT64  t6;     
    UINT64  t7;    
    UINT64  s0;    
    UINT64  s1;    
    UINT64  s2;    
    UINT64  s3;    
    UINT64  s4;    
    UINT64  s5;    
    UINT64  s6;     
    UINT64  s7;    
    UINT64  t8;     
    UINT64  t9;    
    UINT64  k0;     
    UINT64  k1;     
    UINT64  gp;     
    UINT64  sp;     
    UINT64  fp;
    UINT64  ra;    
    UINT64  old_t9;
	UINT64  old_sp;
    UINT64  old_ra;    
};

ADDRESS entre_make_context_switch_code(ADDRESS target_addr);
void entre_dump_context(struct context * context);

#define GET_CONTEXT(reg,context)       (((UINT64*)(context))[reg])
#define PUT_CONTEXT(reg,context,val)   ( (((UINT64*)(context))[reg])= (val))

#endif
