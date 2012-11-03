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


#ifndef CODECACHE_H
#define CODECACHE_H

#include "global.h"

#define CODECACHE_SIZE (1*MEGA_1)


void entre_init_cc();
void entre_cc_flush();

ADDRESS entre_cc_get_top_address();
void entre_cc_add_code(unsigned* code, unsigned len);  /* add code to cc*/
void entre_cc_replace(ADDRESS, INSN_T);

#endif
