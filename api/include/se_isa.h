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

#ifndef SE_ISA_H
#define SE_ISA_H

#include "globals_shared.h"

extern struct context
{
    UINT64  stack;
    UINT64  zero;
    UINT64  at;
    UINT64  v0;
    UINT64  v1;
    UINT64  a0;
    UINT64  a1;
    UINT64  a2;
    UINT64  a3;
    UINT64  t0;
    UINT64  t1;
    UINT64  t2;
    UINT64  t3;
    UINT64  t4;
    UINT64  t5;
    UINT64  t6;
    UINT64  t7;
    UINT64  s0;
    UINT64  s1;
    UINT64  s2;
    UINT64  s3;
    UINT64  s4;
    UINT64  s5;
    UINT64  s6;
    UINT64  s7;
    UINT64  t8;
    UINT64  t9;
    UINT64  k0;
    UINT64  k1;
    UINT64  gp;
    UINT64  sp;
    UINT64  fp;
    UINT64  ra;
    UINT64  old_t9;
    UINT64  old_sp;
    UINT64  old_ra;
}context_t;

#define INSN_BYTES 4        /* bytes of instruction */
#define IN_CODE_LW_NUM  3*INSN_BYTES

/****************************************************
 * part of the instruction identification.
 ***************************************************/
extern inline int entre_is_lui(INSN_T insn);
extern inline int entre_is_sdc1(INSN_T insn);
extern inline int entre_is_ldc1(INSN_T insn);
extern inline int entre_is_swc1(INSN_T insn);
extern inline int entre_is_lwc1(INSN_T insn);
extern inline int entre_is_sh(INSN_T insn);
extern inline int entre_is_lh(INSN_T insn);
extern inline int entre_is_sb(INSN_T insn);
extern inline int entre_is_lb(INSN_T insn);
extern inline int entre_is_sw(INSN_T insn);
extern inline int entre_is_lw(INSN_T insn);
extern inline int entre_is_b(INSN_T insn);
extern inline int entre_is_j(INSN_T insn);
extern inline int entre_is_jal(INSN_T insn);
extern inline int entre_is_jalr(INSN_T insn);
extern inline int entre_is_jr(INSN_T insn);
extern inline int entre_is_jr_ra(INSN_T insn);
extern inline int entre_is_jr_call(INSN_T insn);

#endif
