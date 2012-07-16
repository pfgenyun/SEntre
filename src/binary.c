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
#include <string.h>
#include <sys/stat.h>  /* fstat */
#include <unistd.h>
#include <sys/mman.h>  /* mmap */
#include <elf.h>
#include <asm/cachectl.h>

#include "global.h"
#include "binary.h"

struct struct_executable Executable;

void entre_dump_function()
{
	Elf32_Sym * pSymTab = Executable.pSymTab;
	UINT32      nSymTab = Executable.nSymTab; 
	char *      pStrTab = Executable.pStrTab;
	UINT32      nStrTab = Executable.nStrTab;

	char * funName;
	ADDRESS addr;
	int size;

	Elf32_Sym * fun;

	FOR_EACH_FUNCTION(fun)
	{
		funName = pStrTab + fun->st_name;
		addr = fun->st_value;
		size = fun->st_size;
		printf("%25s\tSTART= 0x%x END= 0x%x start = %d end = %d size = %d \n",
				funName, addr, addr+size, addr, addr+size, size);
	}
}

void entre_executable_flush(void)
{
	cacheflush(Executable.pCodeStart, Executable.pCodeEnd-Executable.pCodeStart, ICACHE);
}

/*******************************************************************
 * after sorting:
 * rank[0] point to the min number
 * rank[n] point to the max number 
 * the order is according the st_value value
 * *****************************************************************/
static void entre_function_sort(Elf32_Sym * sym, Elf32_Sym ** rank, int n)
{
    int i,j,k;
    ADDRESS min = 0, tmp;
    Elf32_Sym * sym_p;
				    
    for(i = 0; i< n; i++)
        rank[i] = sym + i;
					    
    for(i = 0; i< n - 1; i++)
    {   
        k = i;
        min = rank[k]->st_value;    
            for(j = i + 1; j < n; j++)
            {   
                tmp = rank[j]->st_value;
                if(tmp < min)
                {   
                    min = tmp;
                    k = j;
                }   
            }   
					    
            if(k != i)
            {   
                sym_p = rank[k];
                rank[k] = rank[i];
                rank[i] = sym_p;
            }   
    }   
}

/**********************************************************************
 * scan Symbol Table, extract STT_ST_FUNC type symbol and reorder them.
 * record them in the Executalbe.pSymTab and Executable.nSymTab. copy 
 * accoding String Table to Executable.pStrTab and Executable.nStrTab.
 * *******************************************************************/
void entre_IRMarkFunctions(void)
{
    INDEX i,j;

    Elf32_Sym *pSymTab = Executable.pSymTab;
    UINT32     nSymTab = Executable.nSymTab;
    char      *pStrTab = Executable.pStrTab;
    UINT32     nStrTab = Executable.nStrTab;

    Executable.pSymTab = NULL;
    Executable.nSymTab = 0;
    Executable.pStrTab = (char *)malloc(nStrTab);
    Executable.nStrTab = 0;

    /* temporary Symbol array used for function name sort. */
    Elf32_Sym *aSymTemp = (Elf32_Sym *) calloc(sizeof(Elf32_Sym), nSymTab);
    Elf32_Sym **SymRank = (Elf32_Sym **) calloc(sizeof(Elf32_Sym *), nSymTab);

    for(i=1; i<nSymTab; i++)
    {
        Elf32_Sym *pSymTabItem = pSymTab + i;
        unsigned char SymType = ELF32_ST_TYPE(pSymTabItem->st_info);

        if( SymType==STT_FUNC && pSymTabItem->st_value >= Executable.pCodeStart 
                              && pSymTabItem->st_value < Executable.pCodeEnd )
        {
            char *pSymTabItemName = pStrTab + pSymTabItem->st_name;

            /* the following with "continue" condition are neglect, which 
			   dose not record in the Executable structure. */
            if(strncmp(pSymTabItemName, "__libc_start_main", 17) == 0)
                continue;
            if(strncmp(pSymTabItemName, "__libc_csu", 10) == 0)
                continue;
            if(strncmp(pSymTabItemName, "entre_", 6) == 0)
                continue;
            
			/* the function Symbol has been recorded before. */
            int flag = 0;
            for(j=0; j<Executable.nSymTab; j++)
            {
                if(pSymTabItem->st_value == aSymTemp[j].st_value)
                    flag = 1;
            }
            if(flag == 1) continue;

            /* need? */
            ADDRESS addr;
            if(strcmp(pSymTabItemName, "_flush_cache") == 0)
            {
                addr = pSymTabItem->st_value;
                continue;
            }
            if(addr == pSymTabItem->st_value)
                continue;

            aSymTemp[Executable.nSymTab].st_value = pSymTabItem->st_value;
            aSymTemp[Executable.nSymTab].st_size = pSymTabItem->st_size;
            aSymTemp[Executable.nSymTab].st_name = Executable.nStrTab;
			strcpy(Executable.pStrTab + Executable.nStrTab, pSymTabItemName);
            Executable.nStrTab += strlen(pSymTabItemName) + 1;

			Executable.nSymTab++;
        }
    }/* end of for */

    /* sort the function Symbols */
    entre_function_sort(aSymTemp, SymRank, Executable.nSymTab);
    
	/* copy recoreded Function Symbol from aSymTemp to Executable.pSymTab orderly.*/
    Executable.pSymTab = (Elf32_Sym *) malloc(sizeof(Elf32_Sym)*Executable.nSymTab);
    for(i=0; i<Executable.nSymTab; i++)
    {
        Executable.pSymTab[i] = *(SymRank[i]);
    }

    /* the following change st_size if its value is 0. why? */
    for(i=0; i<Executable.nSymTab-1; i++)
    {
        if(Executable.pSymTab[i].st_size == 0)
        {
            Executable.pSymTab[i].st_size = Executable.pSymTab[i+1].st_value - 
				                            Executable.pSymTab[i].st_value;
        }
    }
    if(Executable.pSymTab[Executable.nSymTab-1].st_size == 0)
        Executable.pSymTab[Executable.nSymTab-1].st_size = Executable.pCodeEnd -
                        Executable.pSymTab[Executable.nSymTab-1].st_value;

    free(aSymTemp);
    free(SymRank);

    /* the remaining symbol name string table must be smaller than original one, 
	   so the pointer will not change. */
    Executable.pStrTab = realloc(Executable.pStrTab, Executable.nStrTab);
}


/* *******************************************************************
 * record the executable sections info, incluing symtab strtab dynsym 
 * strsym got and text.
 * ******************************************************************/
void entre_BinaryLoad(void* start_fp)
{
    INDEX i,j;
    
    Elf32_Ehdr *pElfHeader = (Elf32_Ehdr *) start_fp;    /* ELF Header address */
    UINT32      nSection = pElfHeader->e_shnum;    /* number of sections */
    Elf32_Shdr *pSectionHeaderStart =(Elf32_Shdr *)((char*)pElfHeader + pElfHeader->e_shoff);  /* Section Header Table address */

    /* Section Name String Table info */
    Elf32_Shdr *pSectionHeaderItem = pSectionHeaderStart + pElfHeader->e_shstrndx;
    char *pSectionNameStrTab = (char *)((char*)pElfHeader + pSectionHeaderItem->sh_offset); /* ? */
    Executable.pSectionNameStrTab = (char *)malloc(sizeof(pSectionHeaderItem->sh_size));
    Executable.nSectionNameStrTab = pSectionHeaderItem->sh_size;  /* ? */
    
    /* symtab, strtab, and got is unquie, assum text is also unquie (?)*/
    for(i=1; i<nSection; i++)
    {
        pSectionHeaderItem = pSectionHeaderStart + i;
        char *pSectionName = pSectionNameStrTab + pSectionHeaderItem->sh_name; /* type convect? */
        
        if(strcmp(pSectionName,".got")==0)
        { /* .got exists when executing, get its virtual address */
            Executable.pGot = (ADDRESS *)pSectionHeaderItem->sh_addr;         /* virtual address */
            Executable.nGot = pSectionHeaderItem->sh_size / sizeof(ADDRESS);
        }
        else if(strcmp(pSectionName,".symtab")==0)
        { /* .symtab does not exists after loading , need copy */
            Executable.pSymTab = (Elf32_Sym *)((char *)pElfHeader + pSectionHeaderItem->sh_offset);  /* mmap address */
            Executable.nSymTab = pSectionHeaderItem->sh_size / sizeof(Elf32_Sym);
        }
        else if(strcmp(pSectionName,".strtab")==0)
        { /* .strtab does not exists after loading , need copy */
            Executable.pStrTab = (char *)((char *)pElfHeader + pSectionHeaderItem->sh_offset); /* mmap address */
            Executable.nStrTab = pSectionHeaderItem->sh_size / sizeof(char);
        }
		else if(strcmp(pSectionName,".dynsym")==0)
        { /* .dynsym exists when executing, get its virtual address */
            Executable.pDynamicSymTab = (Elf32_Sym *)pSectionHeaderItem->sh_addr;         /* virtual address */
            Executable.nDynamicSymTab = pSectionHeaderItem->sh_size / sizeof(Elf32_Sym);
        }
		else if(strcmp(pSectionName,".dynstr")==0)
        { /* .dynstr exists when executing, get its virtual address */
            Executable.pDynamicStrTab = (char *)pSectionHeaderItem->sh_addr;         /* virtual address */
            Executable.nDynamicStrTab = pSectionHeaderItem->sh_size / sizeof(char);
        }
		else if(strcmp(pSectionName,".text")==0)
        { /* .text exists when executing, get its virtual address. assum .text is unquie */
            Executable.pCodeStart = pSectionHeaderItem->sh_addr;
            Executable.pCodeEnd   =  pSectionHeaderItem->sh_addr + pSectionHeaderItem->sh_size ;
        }   

        ADDRESS pPageStart = Executable.pCodeStart & (~(pagesize - 1));
        mprotect((void*)pPageStart, Executable.pCodeEnd - pPageStart, PROT_READ | PROT_WRITE | PROT_EXEC);
    }
}



void entre_initExecutable(int fp)
{
    struct stat stat_date;

    int fs = fstat(fp, &stat_date);
    void *start_fp = mmap(NULL, stat_date.st_size, PROT_READ, MAP_SHARED, fp, 0);
	entre_BinaryLoad(start_fp);
	entre_IRMarkFunctions();
	munmap(start_fp, stat_date.st_size);
}
