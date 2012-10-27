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
#include <sys/mman.h>
#include <asm/cachectl.h>
#include "global.h"
#include "codecache.h"
#include "isa.h"
#include "binary.h"

/* Each mips instruction 32 bits*/
unsigned *codecache;
unsigned codecache_size; 
unsigned codecache_n;

void entre_init_cc(void)
{
    codecache_size = Executable.pSize;
    codecache = malloc(codecache_size * sizeof(unsigned));
    codecache_n = 0;

    ADDRESS pPageStart = (unsigned)codecache & (~(pagesize - 1));
    mprotect((void*)pPageStart, codecache_size*sizeof(unsigned), PROT_READ | PROT_WRITE | PROT_EXEC);
}

ADDRESS entre_cc_get_top_address()
{
	return (ADDRESS) (&codecache[codecache_n]);
}

/***********************************************************************
 * copy code from *code to codecache, the length of code is len. 
 * codecache_n is the point to the top of codecache.
 * ********************************************************************/
void entre_cc_add_code(unsigned* code, unsigned len)
{
	int i;
	if( codecache_n + len > codecache_size )
	{
		printf(" ADD CODE ERROR, codecache overflow!\n");
		exit(1);
	}
	for(i=0; i<len; i++)
		codecache[codecache_n+i] = code[i];
	codecache_n += len;
}

/*******************************************************************
 replace instruction at address addr with insn in codecache
********************************************************************/
void entre_cc_replace(ADDRESS addr, INSN_T insn)
{
	INSN_AT(addr) = insn;
}

void entre_cc_flush()
{
	ADDRESS pPageStart = (unsigned)codecache&(~(pagesize-1));
	mprotect((void*)pPageStart, codecache_size*sizeof(unsigned), PROT_READ|PROT_WRITE|PROT_EXEC);
	cacheflush(codecache, codecache_size*sizeof(unsigned), BCACHE);
}
