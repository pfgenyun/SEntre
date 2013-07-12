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

#include "se_api.h"

#if 0
DECLARE_CXTSWPROT_VAR(mutex_t thread_initexit_lock,
                      INIT_LOCK_FREE(thread_initexit_lock));
#endif

void SEntre_analysis(struct context * context)
{
    ADDRESS old_addr, new_addr, counter_addr;
    
    new_addr = context->ra + IN_CODE_LW_NUM;
    old_addr = entre_map_newAddr_2_oldInsnAddr(new_addr);
    counter_addr = entre_get_bb_counter_addr(old_addr);
#if 1
    ATOMIC_INC(int, *(ADDRESS *)counter_addr);
#endif
#if 0
//	mutex_lock(&thread_initexit_lock);
//	*(ADDRESS *)counter_addr += 1;
//	mutex_unlock(&thread_initexit_lock);
#endif
} 
