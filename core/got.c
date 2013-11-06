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
#include <string.h>
#include "make_new_function.h"
#include "global.h"
#include "got.h"
#include "in_code.h"

struct got * got;
int got_size;
int got_n;

int entre_got_find_instrument_num_from_newAddr(ADDRESS newAddr)
{
    int i, j = 0;
	struct instrumentRecordTable *cur = NULL;

	for(i=0; GOT_NEW_ADDR(i) <= newAddr; i++)
	    ;

	if(got[i-1].instrumentPointNum == 0)
		return 0;

	cur = got[i-1].funInstrumentP;
	while(cur != NULL)
	{
		if(newAddr < cur->newInstrumentP)
			break;
		cur = cur->next;
		j++;
	}
	return j;
}

int entre_got_find_j_num_from_newAddr(ADDRESS newAddr)
{
    int i, j = 0;
	struct jump_RecordTable *cur = NULL;

    for(i=0; GOT_NEW_ADDR(i)<=newAddr; i++)
        ;

	if(got[i-1].jPointNum == 0)
		return 0;

	cur = got[i-1].fun_jP;
	while(cur != NULL)
	{
		if(newAddr < cur->new_jP)
			break;
		cur = cur->next;
		j++;
	}
	return j;
}

int entre_got_find_bal_num_from_newAddr(ADDRESS newAddr)
{
    int i, j;
	struct bal_RecordTable *cur = NULL;

    for(i=0; GOT_NEW_ADDR(i)<=newAddr; i++)
        ;

	if(got[i-1].bPointNum == 0)
		return 0;

	cur = got[i-1].fun_bP;
	while(cur != NULL)
	{
		if(newAddr < cur->new_bP)
			break;
		cur = cur->next;
		j++;
	}
	return j;
}

ADDRESS entre_got_map_oldAddr_2_newFunAddr(ADDRESS oldAddr)
{
    int i, j;
	for(i=0; i<got_n-1; i++)
	{
//		printf("new addr in got: %x %x\n", GOT_OLD_ADDR(i), oldAddr);
		if(oldAddr>=GOT_OLD_ADDR(i) && oldAddr<GOT_OLD_ADDR(i+1))
		    return GOT_NEW_ADDR(i);
	}
	return 0;
}

ADDRESS entre_got_map_newAddr_2_oldFunAddr(ADDRESS newAddr)
{
    int i, j;
	for(i=0; i<got_n-1; i++)
	{
//		printf("new addr in got: %x %x\n", GOT_NEW_ADDR(i), newAddr);
		if(newAddr>=GOT_NEW_ADDR(i) && newAddr<GOT_NEW_ADDR(i+1))
		    return GOT_OLD_ADDR(i);
	}
	return 0;
}

ADDRESS entre_got_map_oldAddr_2_oldFunAddr(ADDRESS oldAddr)
{
    int i, j;
   for(i=0; i<got_n-1; i++)
   {
       if(oldAddr>=GOT_OLD_ADDR(i) && oldAddr<GOT_OLD_ADDR(i+1))
           return GOT_OLD_ADDR(i);
   }
   return 0;
}

#if 1
/* binary search in got table */
int entre_binary_search(ADDRESS old_address)
{
	int low, high, mid;

    low = 0;
	high = got_n - 1;
	mid = 0;

	if(old_address == GOT_OLD_ADDR(low))
        return low;
	if(old_address == GOT_OLD_ADDR(high))
        return high;
	
	while(low <= high)
	{
		mid = low + (high - low)/2;
//		mid = (high + low)/2;
		if(old_address == GOT_OLD_ADDR(mid))
		    return mid;
		
		if(GOT_OLD_ADDR(mid) > old_address)
		    high = mid - 1;
		else
		    low = mid + 1;
	}

	if(low > high)
	    return -1;
}

ADDRESS entre_got_find_final(ADDRESS old_address)
{
	int index;
	
	index = entre_binary_search(old_address);
	if(index != -1)
		return GOT_NEW_ADDR_FINAL(index);

	return 0;
}
#endif

#if 0
/* sequential search in got table */
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
#endif

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

void entre_got_init_instrument_point()
{
	int i;

	for(i=0; i<got_size; i++)
	{
		got[i].instrumentPointNum = 0;
		got[i].jPointNum = 0;
		got[i].bPointNum = 0;
	}
}

void entre_got_add_bal_point(ADDRESS oldAddr, ADDRESS newAddr)
{
    /* -1 is for got_n++ in the entre_got_add_entry() */
    if(got[got_n-1].bPointNum == 0)
    {   
        got[got_n-1].fun_bP = (struct bal_RecordTable *)malloc(sizeof(struct bal_RecordTable));
		if(got[got_n-1].fun_bP == NULL)
		{
			printf("EE: MALLOC fun_bP ERROR!\n");
			exit(0);
		}
		memset(got[got_n-1].fun_bP, 0, sizeof(struct bal_RecordTable));
        got[got_n-1].fun_bP->old_bP = oldAddr;
        got[got_n-1].fun_bP->new_bP = newAddr;
        got[got_n-1].fun_bP->next = NULL;
    }   
    else
    {   
        struct bal_RecordTable *cur = NULL;
        for(cur = got[got_n-1].fun_bP; cur->next != NULL; cur = cur->next)
            ;   
        struct bal_RecordTable *temp = (struct bal_RecordTable *)malloc(sizeof(struct bal_RecordTable));
		if(temp == NULL)
		{
			printf("EE: MALLOC temp ERROR!\n");
			exit(0);
		}
		memset(temp, 0, sizeof(struct bal_RecordTable));
        temp->old_bP = oldAddr;
        temp->new_bP = newAddr;
		temp->next = cur->next;
		cur->next = temp;
	}
    got[got_n-1].bPointNum++;
}

void entre_got_add_jump_point(ADDRESS oldAddr, ADDRESS newAddr)
{
    /* -1 is for got_n++ in the entre_got_add_entry() */
    if(got[got_n-1].jPointNum == 0)
    {   
        got[got_n-1].fun_jP = (struct jump_RecordTable *)malloc(sizeof(struct jump_RecordTable));
		if(got[got_n-1].fun_jP == NULL)
		{
			printf("EE: MALLOC fun_jP ERROR!\n");
			exit(0);
		}
		memset(got[got_n-1].fun_jP, 0, sizeof(struct jump_RecordTable));
        got[got_n-1].fun_jP->old_jP = oldAddr;
        got[got_n-1].fun_jP->new_jP = newAddr;
        got[got_n-1].fun_jP->next = NULL;
    }   
    else
    {   
        struct jump_RecordTable *cur = NULL;
        for(cur = got[got_n-1].fun_jP; cur->next != NULL; cur = cur->next)
            ;   
        struct jump_RecordTable *temp = (struct jump_RecordTable *)malloc(sizeof(struct jump_RecordTable));
		if(temp == NULL)
		{
			printf("EE: MALLOC temp ERROR!\n");
			exit(0);
		}
		memset(temp, 0, sizeof(struct jump_RecordTable));
        temp->old_jP = oldAddr;
        temp->new_jP = newAddr;
		temp->next = cur->next;
		cur->next = temp;
	}
    got[got_n-1].jPointNum++;
}  

void entre_got_add_instrument_point(ADDRESS oldAddr, ADDRESS newAddr)
{
	int i;

    /* -1 is for got_n++ in the entre_got_add_entry() */
	struct instrumentRecordTable *cur = NULL;

	if(got[got_n-1].instrumentPointNum == 0)
	{
		got[got_n-1].funInstrumentP = (struct instrumentRecordTable *)malloc(sizeof(struct instrumentRecordTable));
		if(got[got_n-1].funInstrumentP == NULL)
		{
			printf("EE: MALLOC funInstrumentP ERROR!\n");
			exit(0);
		}
		memset(got[got_n-1].funInstrumentP, 0, sizeof(struct instrumentRecordTable));
		got[got_n-1].funInstrumentP->oldInstrumentP = oldAddr;
		got[got_n-1].funInstrumentP->newInstrumentP = newAddr;
		got[got_n-1].funInstrumentP->next = NULL;
	}
	else
	{
		for(cur = got[got_n-1].funInstrumentP, i = 0; cur->next != NULL; cur = cur->next, i++)
			;
		struct instrumentRecordTable *temp = (struct instrumentRecordTable *)malloc(sizeof(struct instrumentRecordTable));
		if(temp == NULL)
		{
			printf("EE: MALLOC temp ERROR!\n");
			exit(0);
		}
		memset(temp, 0, sizeof(struct instrumentRecordTable));
		temp->oldInstrumentP = oldAddr;
		temp->newInstrumentP = newAddr;
		temp->next = cur->next;
		cur->next = temp;
	}
	got[got_n-1].instrumentPointNum++;
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

	if(got_n > got_size)
	{
	    printf("EE: GOT OVERFLOW!\n");
	    exit(0);
	}
}

void entre_got_init(int size)
{
    got_size = size;
    got = (struct got *)malloc(sizeof(struct got)*got_size);
    got_n = 0;
	if(got == NULL)
	{
	    printf("EE: MALLOC ERROR in GOT INIT!\n");
		exit(0);
	}

#ifdef MAP
    entre_got_init_instrument_point();
#endif
}
