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
	/* For multithead and multiprocess,the output file
	 * shoud not open here. because every thread and 
	 * process should hava its own output file. */
#ifdef TRACE
	int i, length;
	char * short_name;
	char full_name[256]={0} ; 
	char output_file[256]={0} ; 
	
	short_name = get_application_short_name(full_name);
	length = strlen(short_name);
	for(i=0; i<length; i++)
	    output_file[i] = short_name[i];
	strcpy(&output_file[i], "_trace.sentre");

	if(NULL == (stdtrace = fopen(output_file, "w")))
	{
		printf("EE: Can not open file stdtrace\n");
	}
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
#ifndef INSN_IN_DATE
    free(codecache);
#endif
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

char * get_application_short_name(char * exe_name_full)
{
	char * ptr;

	get_application_full_name(exe_name_full);
	ptr = strrchr(exe_name_full, '/');
	return ptr+1;
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
