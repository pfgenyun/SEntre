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


#ifndef GOT_H
#define GOT_H

#include "global.h"

#define INSTRUMENT_SIZE	1204

/* record the instrument point information in a function */
struct instrumentRecordTable
{
    ADDRESS oldInstrumentP;	//address of instrument point in origin address space
	ADDRESS newInstrumentP;	//addresss of instrument point in codecache 
};

/* copy code from original palce to codecache, got is used to record 
   the old address and the new address of functions */
struct got
{
    ADDRESS old_addr;
    ADDRESS new_addr_orig;	//function start addr without new instruction
    ADDRESS new_addr_t9;	//function start addr with t9 dealing code
    ADDRESS new_addr_func;	//function start addr with function begine and end instrument code
	ADDRESS new_addr_final;	//function start addr finally
	struct instrumentRecordTable *funInstrumentP;
	int instrumentPointNum;
};

void entre_got_init(int);
//ADDRESS entre_got_find(ADDRESS old_address);
ADDRESS entre_got_find_orig(ADDRESS old_address);
ADDRESS entre_got_find_t9(ADDRESS old_address);
ADDRESS entre_got_find_func(ADDRESS old_address);
ADDRESS entre_got_find_final(ADDRESS old_address);
ADDRESS entre_got_map_newAddr_2_oldFunAddr(ADDRESS newAddr);
ADDRESS entre_got_map_oldAddr_2_newFunAddr(ADDRESS oldAddr);
void entre_init_instrument_point(void);
void entre_got_add_instrument_point(ADDRESS oldAddr, ADDRESS newAddr);
int entre_got_find_instrument_num_from_newAddr(ADDRESS newAddr);

#define GOT_OLD_ADDR(i) (got[i].old_addr)
//#define GOT_NEW_ADDR(i) (got[i].new_addr)
#define GOT_NEW_ADDR_ORIG(i)  (got[i].new_addr_orig)
#define GOT_NEW_ADDR_T9(i)    (got[i].new_addr_t9)
#define GOT_NEW_ADDR_FUNC(i)  (got[i].new_addr_func)
#define GOT_NEW_ADDR_FINAL(i) (got[i].new_addr_final)
#define GOT_NEW_ADDR(i) GOT_NEW_ADDR_FINAL(i)

#endif
