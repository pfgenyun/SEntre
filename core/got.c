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

int entre_got_find_instrument_num_from_newAddr(ADDRESS newAddr)
{
    int i, j;
	for(i=0; GOT_NEW_ADDR(i)<=newAddr; i++)
	    ;
	for(j=0; j<got[i-1].instrumentPointNum; j++)
	{
		if(newAddr<got[i-1].funInstrumentP[j].newInstrumentP)
		{
			break;
		}
	}
	return j;
}

int entre_got_find_j_num_from_newAddr(ADDRESS newAddr)
{
    int i, j;
    for(i=0; GOT_NEW_ADDR(i)<=newAddr; i++)
        ;
    for(j=0; j<got[i-1].jPointNum; j++)
    {
        if(newAddr<got[i-1].fun_jP[j].new_jP)
        {
            break;
        }
    }
    return j;
}

int entre_got_find_bal_num_from_newAddr(ADDRESS newAddr)
{
    int i, j;
    for(i=0; GOT_NEW_ADDR(i)<=newAddr; i++)
        ;
    for(j=0; j<got[i-1].bPointNum; j++)
    {
        if(newAddr<got[i-1].fun_bP[j].new_bP)
        {
            break;
        }
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
	int i, j;

	for(i=0; i<got_size; i++)
	{
		got[i].instrumentPointNum = 0;
		got[i].jPointNum = 0;
		got[i].bPointNum = 0;
		got[i].funInstrumentP = (struct instrumentRecordTable *)malloc(INSTRUMENT_SIZE*sizeof(struct instrumentRecordTable));
		if(got[i].funInstrumentP == NULL)
		{
		    printf("EE: MALLOC ERROR in GOT INIT!\n");
			exit(0);
		}
		got[i].fun_jP = (struct jump_RecordTable *)malloc(INSTRUMENT_SIZE*sizeof(struct jump_RecordTable));
		if(got[i].fun_jP == NULL)
		{
			printf("EE: MALLOC fun_jP ERROR in GOT INIT!\n");
			exit(0);
		}
		got[i].fun_bP = (struct bal_RecordTable *)malloc(INSTRUMENT_SIZE*sizeof(struct bal_RecordTable));
		if(got[i].fun_bP == NULL)
		{
			printf("EE: MALLOC fun_bP ERROR in GOT INIT!\n");
			exit(0);
		}
	    for(j=0; j<INSTRUMENT_SIZE; j++)
		{
			got[i].funInstrumentP[j].oldInstrumentP = 0;
			got[i].funInstrumentP[j].newInstrumentP = 0;
			got[i].fun_jP[j].old_jP = 0;
			got[i].fun_jP[j].new_jP = 0;
		}
	}
}

void entre_got_add_bal_point(ADDRESS oldAddr, ADDRESS newAddr)
{
    /* -1 is for got_n++ in the entre_got_add_entry() */
    int numP = got[got_n-1].bPointNum;
    got[got_n-1].fun_bP[numP].old_bP = oldAddr;
    got[got_n-1].fun_bP[numP].new_bP = newAddr;
    got[got_n-1].bPointNum++;
}

void entre_got_add_jump_point(ADDRESS oldAddr, ADDRESS newAddr)
{
    /* -1 is for got_n++ in the entre_got_add_entry() */
    int numP = got[got_n-1].jPointNum;
    got[got_n-1].fun_jP[numP].old_jP = oldAddr;
    got[got_n-1].fun_jP[numP].new_jP = newAddr;
    got[got_n-1].jPointNum++;
}  

void entre_got_add_instrument_point(ADDRESS oldAddr, ADDRESS newAddr)
{
    /* -1 is for got_n++ in the entre_got_add_entry() */
	int numP = got[got_n-1].instrumentPointNum;
    got[got_n-1].funInstrumentP[numP].oldInstrumentP = oldAddr;
    got[got_n-1].funInstrumentP[numP].newInstrumentP = newAddr;

	got[got_n-1].instrumentPointNum++;

//    printf("old instrumentP:%x new instrumentP %x instrument num:%d in got\n", 
//			got[got_n-1].funInstrumentP[numP].oldInstrumentP, 
//			got[got_n-1].funInstrumentP[numP].newInstrumentP, 
//			got[got_n-1].instrumentPointNum);
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
