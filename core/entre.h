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


#ifndef ENTRE_H
#define EHTRE_H

/* parameters of function _libc_start_main */
#define PARAMS_START_MAIN                             \
        int (*main) (int, char**, char**),            \
        int argc,                                     \
        char *__unbounded *__unbounded ubp_av,        \
        void (*auxvec) (void),                        \
        void (*init) (void),                          \
        void (*fini) (void),                          \
        void (*rtld_fini) (void),                     \
        void *__unbounded stack_end

#endif
