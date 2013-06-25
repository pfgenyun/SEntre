/************************************************************
 * Copyright (c) 2010-present Peng Fei.  All rights reserved.
 *************************************************************/

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


#ifndef BASICBLOCK_H
#define BASICBLOCK_H
#include "global.h"


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

struct bb
{
    UINT32 counter;        /* executable times */
    ADDRESS start;         /* BB begin virtual address */
    int insn_num;          /* instructions in BB */
    INSN_T i1;
    INSN_T i2;
    ADDRESS in_point;
    BB_CLASS type;
    char * fun_name;       /* function name */
};

#define BB_SIZE (1*MEGA_1) * 5

struct address_list
{
    ADDRESS addr;
    int next;
};

#define ADDR_LIST_SIZE	10240 
//#define ADDR_LIST_SIZE	1024 * 1024
#define NULL_INDEX		-1
#define MIN_ADDR		0

void entre_init_mark_bb();
void entre_mark_bb();

void entre_dump_bb();
void entre_dump_one_bb(struct bb * bb_p);

ADDRESS entre_get_bb_counter_addr(ADDRESS );
int entre_get_bb_index(ADDRESS );
int entre_is_bb_begin(ADDRESS);

#define FOR_EACH_BB(bb, i) for(bb=all_bb+0, i=0; i<all_bb_n; ++i, bb=all_bb+i)
#define BASIC_BLOCK(index) (&all_bb[index])

extern struct bb all_bb[];
extern unsigned all_bb_size;
extern unsigned all_bb_n;

#endif
