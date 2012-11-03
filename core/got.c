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


#include <stdlib.h>
#include "make_new_function.h"
#include "global.h"
#include "got.h"
#include "in_code.h"

struct got * got;
int got_size;
int got_n;

ADDRESS entre_got_find_final(ADDRESS old_address)
{
	int i;
	for(i=0; i<got_n; i++)
	{
		if(old_address == GOT_OLD_ADDR(i))
			return GOT_NEW_ADDR_FINAL(i);
	}
	return 0;
}

ADDRESS entre_got_find_func(ADDRESS old_address)
{
	int i;
	for(i=0; i<got_n; i++)
	{
		if(old_address == GOT_OLD_ADDR(i))
			return GOT_NEW_ADDR_FUNC(i);
	}
	return 0;
}

ADDRESS entre_got_find_t9(ADDRESS old_address)
{
	int i;
	for(i=0; i<got_n; i++)
	{
		if(old_address == GOT_OLD_ADDR(i))
			return GOT_NEW_ADDR_T9(i);
	}
	return 0;
}

ADDRESS entre_got_find_orig(ADDRESS old_address)
{
	int i;
	for(i=0; i<got_n; i++)
	{
		if(old_address == GOT_OLD_ADDR(i))
			return GOT_NEW_ADDR_ORIG(i);
	}
	return 0;
}

void entre_got_add_entry(ADDRESS old_addr, ADDRESS new_addr)
{
	GOT_OLD_ADDR(got_n) = old_addr;
	
	GOT_NEW_ADDR_ORIG(got_n) = new_addr + LOAD_T9_BYTES;
	GOT_NEW_ADDR_T9(got_n) = new_addr;
	GOT_NEW_ADDR_FUNC(got_n) = new_addr;
	GOT_NEW_ADDR_FINAL(got_n) = new_addr;

#ifdef OOprofile
	GOT_NEW_ADDR_ORIG(got_n) = new_addr + LOAD_T9_BYTES + IN_CODE_BYTES;
	GOT_NEW_ADDR_T9(got_n) = new_addr + IN_CODE_BYTES;
	GOT_NEW_ADDR_FUNC(got_n) = new_addr;
	GOT_NEW_ADDR_FINAL(got_n) = new_addr + IN_CODE_BYTES;
#endif

#ifdef BB_FREQ
	GOT_NEW_ADDR_ORIG(got_n) = new_addr + LOAD_T9_BYTES;
	GOT_NEW_ADDR_T9(got_n) = new_addr + IN_CODE_BYTES;
	GOT_NEW_ADDR_FUNC(got_n) = new_addr;
	GOT_NEW_ADDR_FINAL(got_n) = new_addr;
#endif

	got_n ++;
}

void entre_got_init(int size)
{
    got_size = size;
    got = (struct got *)malloc(sizeof(struct got)*got_size);
    got_n = 0;
}
