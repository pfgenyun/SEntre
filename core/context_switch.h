/* SEntre_api_begin */
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

/* SEntre_api_end */
//#define SCODE_SIZE (73+8)
//#define CONTEXT_STACK_NUM	(32+3+1+2)

#define SCODE_SIZE (73+64+8)
#define CONTEXT_STACK_NUM	(32+3+1+32+2)
#define CONTEXT_STACK_LO	(32+1+32)
#define CONTEXT_STACK_HI	(32+1+32+1)
#define CONTEXT_STACK_SIZE	(CONTEXT_STACK_NUM*8)

/* SEntre_api_begin */
/***********************************************************************
 * context defined.
 * ********************************************************************/
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
    UINT64  f0;   
    UINT64  f1;    
    UINT64  f2;     
    UINT64  f3;    
    UINT64  f4;    
    UINT64  f5;    
    UINT64  f6;     
    UINT64  f7;    
    UINT64  f8;    
    UINT64  f9;    
    UINT64  f10;    
    UINT64  f11;    
    UINT64  f12;    
    UINT64  f13;    
    UINT64  f14;     
    UINT64  f15;    
    UINT64  f16;    
    UINT64  f17;    
    UINT64  f18;    
    UINT64  f19;    
    UINT64  f20;    
    UINT64  f21;    
    UINT64  f22;     
    UINT64  f23;    
    UINT64  f24;     
    UINT64  f25;    
    UINT64  f26;     
    UINT64  f27;     
    UINT64  f28;     
    UINT64  f29;     
    UINT64  f30;
    UINT64  f31;    
    UINT64  lo;    
    UINT64  hi;    
    UINT64  old_t9;
	UINT64  old_sp;
    UINT64  old_ra;    
};

/* SEntre_api_end */
ADDRESS entre_make_context_switch_code(ADDRESS target_addr);
void entre_dump_context(struct context * context);

#define GET_CONTEXT(reg,context)       (((UINT64*)(context))[reg])
#define PUT_CONTEXT(reg,context,val)   ( (((UINT64*)(context))[reg])= (val))

/* SEntre_api_begin */
#endif
/* SEntre_api_end */
