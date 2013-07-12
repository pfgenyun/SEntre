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

#ifndef SE_GOT_H
#define SE_GOT_H

#include "globals_shared.h"

/* copy code from original palce to codecache, got is used to record 
   the old address and the new address of functions */
extern struct got
{
    ADDRESS old_addr;
    ADDRESS new_addr_orig;  //function start addr without new instruction
    ADDRESS new_addr_t9;    //function start addr with t9 dealing code
    ADDRESS new_addr_func;  //function start addr with function begin and end instrument code
    ADDRESS new_addr_final; //function start addr finally
    struct instrumentRecordTable *funInstrumentP;
    int instrumentPointNum;
}got_t;

/***********************************************************************
 * add entry address to the got table.
 * ********************************************************************/
extern void entre_got_add_entry(ADDRESS old_addr, ADDRESS new_addr);

/***********************************************************************
 * get the top address of codecache.
 * ********************************************************************/
extern ADDRESS entre_cc_get_top_address();

/***********************************************************************
 * return the new_addr_orig according to the old address.
 * ********************************************************************/
extern ADDRESS entre_got_find_orig(ADDRESS old_address);

/***********************************************************************
 * return the new_addr_t9 according to the old address.
 * ********************************************************************/
extern ADDRESS entre_got_find_t9(ADDRESS old_address);

/***********************************************************************
 * return the start address according to the old address.
 * ********************************************************************/
extern ADDRESS entre_got_find_func(ADDRESS old_address);

/***********************************************************************
 * return the start address finally according to the old address.
 * ********************************************************************/
extern ADDRESS entre_got_find_final(ADDRESS old_address);

/***********************************************************************
 * return the old address according to the new address.
 * ********************************************************************/
extern ADDRESS entre_got_map_newAddr_2_oldFunAddr(ADDRESS newAddr);

/***********************************************************************
 * return the new address according to the old address.
 * ********************************************************************/
extern ADDRESS entre_got_map_oldAddr_2_newFunAddr(ADDRESS oldAddr);

/***********************************************************************
 * add the instrument point to got table.
 * ********************************************************************/
extern void entre_got_add_instrument_point(ADDRESS oldAddr, ADDRESS newAddr);

/***********************************************************************
 * return the instrument number according to the new address.
 * ********************************************************************/
extern int entre_got_find_instrument_num_from_newAddr(ADDRESS newAddr);

#define GOT_OLD_ADDR(i) (got[i].old_addr)
#define GOT_NEW_ADDR_ORIG(i)  (got[i].new_addr_orig)
#define GOT_NEW_ADDR_T9(i)    (got[i].new_addr_t9)
#define GOT_NEW_ADDR_FUNC(i)  (got[i].new_addr_func)
#define GOT_NEW_ADDR_FINAL(i) (got[i].new_addr_final)
#define GOT_NEW_ADDR(i) GOT_NEW_ADDR_FINAL(i)

#endif
