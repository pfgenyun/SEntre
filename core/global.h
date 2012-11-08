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

#define MEGA_1 (1024*1024)  /* 1M */
#define INSN_BYTES 4        /* bytes of instruction */

typedef unsigned ADDRESS;
typedef unsigned UINT32;
typedef int INT32;
typedef int INDEX;
typedef unsigned INSN_T;
typedef int REG_T;
typedef long long UINT64;

typedef pid_t thread_id_t;
typedef pid_t process_id_t;

enum STATUS
{
    NORMAL  =	0x00,
    STRIP   =	0x01,
};

typedef enum STATUS Status;

extern int pagesize;
#ifdef TRACE
extern FILE * stdtrace;
#endif
extern unsigned * codecache;

void entre_global_env_init(void);
void entre_my_error(char *);
void entre_global_file_open();
void entre_global_file_close();
void entre_memory_free();

void get_application_full_name(char *);

#endif