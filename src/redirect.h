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


#ifndef MAIN_ENTRY_H
#define MAIN_ENTRY_H

#include "function.h"

void entre_call_redirect(struct context * context);
void entre_redict_jalr(struct context * context);
void entre_transfer_redirect(void);
void entre_jal_b_redirect(struct function * fun);
int entre_get_b_new_target(ADDRESS old_target_addr, ADDRESS b_addr, int fun_call_num);
int entre_out_of_j_range(ADDRESS new_replace_addr, ADDRESS new_target_addr); 

#endif
