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


#ifndef FUNCTION_H
#define FUNCTION_H

#include <elf.h>
#include "global.h"

/* SEntre_api_end */
#define ALL_FUNCTION_SIZE (1024*24*10)

struct function
{
    char *f_name;          /* function name */
    ADDRESS f_address;     /* function start address */
    unsigned f_codesize;   /* function's instuction size or code size*/
    unsigned f_firstBB;    /* first basic block id in the basic block array */
    unsigned f_numBB;      /* basic block number of this function */
};

void entre_init_function();
#ifdef N64
void entre_init_one_function(Elf64_Sym *, unsigned, unsigned);
#else
void entre_init_one_function(Elf32_Sym *, unsigned, unsigned);
#endif
inline int entre_function_num();
ADDRESS entre_function_start_address(struct function * fun);
ADDRESS entre_function_next_address(struct function * fun);
int entre_function_size(struct function * fun);
struct function * entre_find_function(char * name);
void entre_for_all_function(void (*my_fun)(struct function *));
int entre_is_before_main(struct function * fun);
/* SEntre_api_begin */
/********************************************************************
 * return the name of the function according to the old address.
 * *****************************************************************/
char * entre_find_funName_from_funOldAddr(ADDRESS oldAddr);
/* SEntre_api_end */

#define FUNCTION_NUMS entre_function_num()
#define FUNCTION_START_ADDRESS(fun) entre_function_start_address(fun)
#define FUNCTION_SIZE entre_function_size(fun);

/* SEntre_api_begin */

#endif
/* SEntre_api_end */
