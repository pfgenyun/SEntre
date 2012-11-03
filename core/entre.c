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


/********************************************************************
 the entrypoint of entre                                            
 *******************************************************************/

#ifndef __cplusplus
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>   /* dlsym  */
#include <fcntl.h>   /* open   */
#include <unistd.h>  /* close  */
#include <string.h>  /* strcmp */
#include <errno.h>

#include "global.h"
#include "entre.h"
#include "top_level.h"

void (*real_fini) (void);

void entre_fini()
{
	entre_collection();
	real_fini();
}

/*******************************************************************
 intercept the function  _libc_start_main                          
 *****************************************************************/
void __libc_start_main(PARAMS_START_MAIN)
{
    char exe_name[256];
    char exe_name_full[256];
    Status status;

	/* locale original _libc_start_main */
    void (*real_libc_start_main) (PARAMS_START_MAIN);
    real_libc_start_main = (void(*)(PARAMS_START_MAIN)) dlsym
                            (RTLD_NEXT, "__libc_start_main");
    real_fini = fini;

	/* do with profile or optimization or just running */
    sprintf(exe_name, "%s", ubp_av[0]);
	
    get_application_full_name(exe_name_full);
    INT32 fp = open(exe_name_full, O_RDONLY);
//#ifdef DEBUG
    printf("the value of exe_name: %s\n", exe_name);
    printf("the value of exe_name_full: %s\n", exe_name_full);
    printf("the value of fp: %d\n", fp);
//#endif	
    if (fp<0)
    {
        printf("open error. errno: %d\n", errno);
        exit(0);
    }

    if(strcmp(exe_name, "/bin/bash")!=0 && strcmp(exe_name, "/bin/sh")!=0 
       && strcmp(exe_name, "bash")!=0 && strcmp(exe_name, "sh")!=0 
       && strcmp(exe_name, "/usr/bin/perl") !=0 && strcmp(exe_name, "bin/perl")!=0 && strcmp(exe_name, "perl")!=0
       && strcmp(exe_name, "/usr/bin/python")!=0 && strcmp(exe_name, "/bin/python")!=0 && strcmp(exe_name, "python")!=0)
    {
        printf("Yes, work begins!\n");
        status = entre_optimize(fp); /* the main framework of entre */
        switch (status)
        {
           case NORMAL:
                printf("Yes, work finished!\n\n");
                break;
           case STRIP:
                printf("Cancel instrument. Original app runs!\n\n");
                break;
            default : 
                break;
        }
    }
    else
    {
        printf("Script file, NOT instrument!\n\n");
    }
    close(fp);

//    real_libc_start_main(main, argc, ubp_av, auxvec, init, fini, rtld_fini, stack_end);
    real_libc_start_main(main, argc, ubp_av, auxvec, init, entre_fini, rtld_fini, stack_end);
}
