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


#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <sys/types.h>

#include "globals_shared.h"

#include "utils.h"
#include "options.h"

#include "os_exports.h"
#include "arch_exports.h"

/* SEntre_api_end */
#define MEGA_1 (1024*1024)  /* 1M */
/* SEntre_api_begin */
/***********************************************************************
 * bytes of instruction.
 * ********************************************************************/
#define INSN_BYTES 4

/* SEntre_api_end */
#ifdef DEBUG_REACH
    #define ENTRE_REACH_HERE()    printf("reach file %s at line %d here.\n", __FILE__, __LINE__);
#else
    #define ENTRE_REACH_HERE() 
#endif

enum STATUS
{
    NORMAL  =	0x00,
    STRIP   =	0x01,
};

/* FIXME: what is range of thread_id_t on linux?
 * linux routines use -1 as sentinel, right?
 * if so, change thread_id_t to be a signed int and use -1?
 * For now, based on observation, no process on linux has id 0.
 */
#define INVALID_THREAD_ID  0

typedef enum STATUS Status;

extern int pagesize;
#ifdef TRACE
extern FILE * stdtrace;
#endif

#ifdef INSN_IN_DATE
extern unsigned codecache[];
#else
extern unsigned * codecache;
#endif

void entre_global_env_init(void);
void entre_my_error(char *);
void entre_global_file_open();
void entre_global_file_close();
void entre_memory_free();

void get_application_full_name(char *);
char * get_application_short_name(char *);

/* SEntre_api_begin */
#endif
/* SEntre_api_end */
