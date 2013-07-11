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

#ifndef SE_FUN_H
#define SE_FUN_H

#include "globals_shared.h"

extern struct function
{
    char *f_name;          /* function name */
    ADDRESS f_address;     /* function start address */
    unsigned f_codesize;   /* function's instuction size or code size*/
    unsigned f_firstBB;    /* first basic block id in the basic block array */
    unsigned f_numBB;      /* basic block number of this function */
}function_t;

/* record the instrument point information in a function */
extern struct instrumentRecordTable
{
    ADDRESS oldInstrumentP; //address of instrument point in origin address space
    ADDRESS newInstrumentP; //addresss of instrument point in codecache 
}instrumentRecordTable_t;

#define ALL_FUNCTION_SIZE (1024*24*10)
extern struct function all_function[ALL_FUNCTION_SIZE];
extern int all_function_size;
extern int all_function_n;

#define FUNCTION_NUMS entre_function_num()
#define FUNCTION_START_ADDRESS(fun) entre_function_start_address(fun)
#define FUNCTION_SIZE entre_function_size(fun);

/********************************************************************
 * return the start address according to the function.
 * *****************************************************************/
extern ADDRESS entre_function_start_address(struct function * fun);

/********************************************************************
 * return the next address according to the function.
 * *****************************************************************/
extern ADDRESS entre_function_next_address(struct function * fun);

/********************************************************************
 * return the function according to the name.
 * *****************************************************************/
extern struct function * entre_find_function(char * name);

extern void entre_for_all_function(void (*my_fun)(struct function *));

/********************************************************************
 * return the name of the function according to the old address.
 * *****************************************************************/
extern char * entre_find_funName_from_funOldAddr(ADDRESS oldAddr);

/********************************************************************
 * map instruction address in codecache to the function name. 
 * *****************************************************************/
extern char *entre_map_newAddr_2_oldFunName(ADDRESS newAddr);

/********************************************************************
 * map instruction address in codecache to the function name.
 * *****************************************************************/
extern ADDRESS entre_map_newAddr_2_oldInsnAddr(ADDRESS newAddr);

/********************************************************************
 * map instruction address in codecache to the orignal address of 
 * function beginning.
 * *****************************************************************/
extern ADDRESS entre_map_newAddr_2_oldFunAddr(ADDRESS newAddr);

#endif
