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


#ifndef IN_CODE_H
#define IN_CODE_H

#include "global.h"

#define IN_CODE_SIZE	10
#define IN_CODE_BYTES	IN_CODE_SIZE*INSN_BYTES
#define IN_CODE_LW_NUM	3*INSN_BYTES

void entre_make_in_code_call(ADDRESS);
void entre_make_in_code_mem(ADDRESS);
void entre_make_in_code_OOprofile(ADDRESS);
void entre_make_in_code_bb_freq(ADDRESS);
int entre_in_code_call_get(INSN_T ** code_array);
int entre_in_code_mem_get(INSN_T ** code_array);
int entre_in_code_OOprofile_get(INSN_T ** code_array);
int entre_in_code_bb_freq_get(INSN_T ** code_array);

#endif
