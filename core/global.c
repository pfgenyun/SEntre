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
#ifdef OUT_SVG
    fprintf(stdtrace, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
    fprintf(stdtrace, "<svg width=\"1000000\" height=\"1000000\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");
#endif
#endif
}

void entre_global_file_close()
{
#ifdef TRACE
#ifdef OUT_SVG
	struct trace *trace_t;
    int x=20, y=20, i;
    for(trace_t=all_trace+0, i=0; i<trace_n; ++i, trace_t=all_trace+i)
    {   
        fprintf(stdtrace, "<text style=\"font-size:30;stroke:none;fill:rgb(0,0,0);\" x=\"%d\" y=\"%d\">\n", x, y); 
        fprintf(stdtrace, "Fun:%s, insn addr:0x%x, access addr:0x%x, mem_access_insn:%x, counter:%d\n", trace_t->fun_name, trace_t->insn_addr, trace_t->access_addr, trace_t->mem_access_insn, trace_t->counter);
        fprintf(stdtrace, "</text>\n");
       	fprintf(stdtrace, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"10\" style=\"file:blue;stroke:pink;stroke-width:5;fill-opacity:0.1;stroke-opacity:0.9\"/>\n", x + 800, y - 10, trace_t->counter);
        y += 20; 
    }   
    fprintf(stdtrace, "</svg>");
#endif
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
