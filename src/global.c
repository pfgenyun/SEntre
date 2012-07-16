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
