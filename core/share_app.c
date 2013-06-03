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
 This file is for the application compiled with -fPIC -share option
 (dynamic shared). For example : chrome.
 When running, the address of the symbols is different of the .symtab
 section in ELF file of the application.
 *******************************************************************/

#include "global.h"
#include "share_app.h"
#include "function.h"
#include "binary.h"

extern void (*rel_main)();

void entre_init_rel_offset(ADDRESS orig_main)
{
//	printf("the address of orignal main: %x\n", orig_main);
//	printf("the address of main after relocaton: %x\n", *rel_main);
	Executable.rel_offset = (ADDRESS)*rel_main - orig_main;

//	printf("orig_main: %x rel_address: %x rel_offset: %x\n", orig_main, *rel_main, Executable.rel_offset);
}


