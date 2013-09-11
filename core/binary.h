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


#ifndef BINARY_H
#define BINARY_H

#include <elf.h>
#include "global.h"
#include "binary.h"

struct struct_executable
{
	/* rel_offset = (rel)main - (ori)main */
    UINT32 rel_offset;		/* for PIC app */
    
    ADDRESS PltStart;  /* plt segment start address */
    ADDRESS PltEnd;    /* plt segment end address */
    UINT32 PltSize;        /* size of plt section */

    ADDRESS pCodeStart;  /* code segment start address */
    ADDRESS pCodeEnd;    /* code segment end address */
    UINT32 pSize;        /* size of code section */

    char* pSectionNameStrTab;   /* point to section name string table */
    UINT32 nSectionNameStrTab;   /* size of section name string table */

    ADDRESS* pGot;  /* point to GOT entries */
    UINT32 nGot;    /* number of GOT entries */

    Elf32_Sym* pSymTab;   /* point to Symbol Table entries */
    UINT32 nSymTab;       /* number of Symbol Table entries */
    char* pStrTab;        /* point to String Table */
    UINT32 nStrTab;       /* size of String Table */

    Elf32_Sym* pDynamicSymTab;  /* point to Dynamic Symbol Table entries */
    UINT32 nDynamicSymTab;      /* number of Dynamic Symbol Table entries*/
    char* pDynamicStrTab;       /* point to Dynamic String Table */
    UINT32 nDynamicStrTab;      /* size of Dynamic String Table */
};

extern struct struct_executable Executable;

#define FOR_EACH_FUNCTION(fun) \
    for( fun = Executable.pSymTab; fun < Executable.pSymTab + Executable.nSymTab; fun++)
#define FOR_EACH_INSN_IN_FUN(fun, addr) \
    for(addr = fun->st_value; addr < fun->st_value + fun->st_size; addr += 4)

Status  entre_initExecutable(int);
void entre_executable_flush(void);

void entre_dump_function();

#endif
