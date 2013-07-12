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

#ifndef SE_BASICBLOCK_H
#define SE_BASICBLOCK_H

#include <sys/types.h>
#include "globals_shared.h"

typedef enum
{
    BB_SINGLE,
    BB_NORMAL,          /* normal instruction */
    BB_JR_LINK,         /* jump and link, jalr */
    BB_JR_NO_LINK,      /* jump, jar */
    BB_B_LINK,          /* branch and link, bal */
    BB_B_NO_LINK,       /* branch, bne */
    BB_J_LINK,          /* jump and link, jal */
    BB_J_NO_LINK,       /* jump, j */
}BB_CLASS;

extern struct bb
{
    UINT32 counter;        /* executable times */
    ADDRESS start;         /* BB begin virtual address */
    int insn_num;          /* instructions in BB */
    INSN_T i1;
    INSN_T i2;
    ADDRESS in_point;
    BB_CLASS type;
    char * fun_name;       /* function name */
}bb_t;

extern struct bb all_bb[];
extern unsigned all_bb_size;
extern unsigned all_bb_n;

/********************************************************************
 * return the address of demain counter of basic block according to
 * the text address addr.
 * *****************************************************************/
extern ADDRESS entre_get_bb_counter_addr(ADDRESS addr);

/********************************************************************
 * return the basic block index according to the text address addr.
 * *****************************************************************/
extern int entre_get_bb_index(ADDRESS );

/* binary search in all_bb */
extern int entre_is_bb_begin(ADDRESS);

#endif
