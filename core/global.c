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


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   /* open   */
#include <unistd.h>  /* close  */
#include <string.h>

#include "global.h"


int pagesize;
#ifdef TRACE
FILE * stdtrace;
#endif

void entre_global_file_open()
{
#ifdef TRACE
    stdtrace = fopen("entre_trace.txt", "w");
#endif
}

void entre_global_file_close()
{
#ifdef TRACE
    fclose(stdtrace);
#endif
}

void entre_memory_free()
{
    free(codecache);
}

void entre_global_env_init(void)
{
    pagesize = getpagesize();
    entre_global_file_open();
}

void entre_my_error(char *msg)
{
    printf("%s%c", msg, '\n');
    exit(1);
    printf("Can't reach here!\n");
}

void get_application_full_name(char * exe_name_full)
{
    int pid;
    char proc[250];
    int length;

    /*this is a shitty way of getting the process name,
      but i can't think of anything better... */

    pid = getpid();
    sprintf(proc, "/proc/%d/exe", pid);
    length = readlink(proc, exe_name_full, 250);
    if(length > 0)
    {
#ifdef DEBUG
        printf("the length of the path: %d \n", length);
#endif
        exe_name_full[length] = '\0';
    }
    else
    {
        printf("readlink error!\n");
        exit(0);
    }
}
