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

#ifndef SE_INCODE_H
#define SE_INCODE_H

#include "globals_shared.h"

#define IN_CODE_SIZE    10
#define IN_CODE_BYTES   IN_CODE_SIZE*INSN_BYTES
#define IN_CODE_LW_NUM  3*INSN_BYTES

/***********************************************************************
 * this code is implanted into the function, placed before jalr and jr 
 * instruction. the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
extern void entre_make_in_code_call(ADDRESS context_switch_addr);

/***********************************************************************
 * this code is implanted into the function, placed before st and ld 
 * instruction. the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
extern void entre_make_in_code_mem(ADDRESS context_switch_addr);

/***********************************************************************
 * this code is implanted into the function, placed at function begin
 * and end, or placed at basic block begin and basic block end.
 * the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
extern void entre_make_in_code_OOprofile(ADDRESS context_switch_addr);

/***********************************************************************
 * this code is implanted into the function, placed at basic block begin.
 * the stack which overflow this function does not use in
 * the following functon context_switch .
 * *********************************************************************/
extern void entre_make_in_code_bb_freq(ADDRESS bb_counter_addr);

/***********************************************************************
 * return the size of code according to the call redirect.
 * ********************************************************************/
extern int entre_in_code_call_get(INSN_T ** code_array);

/***********************************************************************
 * return the size of code according to the trace redirect.
 * ********************************************************************/
extern int entre_in_code_mem_get(INSN_T ** code_array);

/***********************************************************************
 * return the size of code according to the OOprofile redirect.
 * ********************************************************************/
extern int entre_in_code_OOprofile_get(INSN_T ** code_array);

/***********************************************************************
 * return the size of code according to the basicblock redirect.
 * ********************************************************************/
extern int entre_in_code_bb_freq_get(INSN_T ** code_array);

#endif
