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
#include <errno.h>

#include "global.h"
#include "binary.h"
#include "share_app.h"

struct struct_executable Executable;

void entre_dump_function()
{
	Elf32_Sym * pSymTab;
	UINT32      nSymTab; 
	char *      pStrTab;
	UINT32      nStrTab;

	char * funName;
	ADDRESS addr;
	int size;

	Elf32_Sym * fun;

	pSymTab = Executable.pSymTab;
	nSymTab = Executable.nSymTab; 
	pStrTab = Executable.pStrTab;
	nStrTab = Executable.nStrTab;

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
 * bubble sort
 * after sorting:
 * rank[0] point to the min number
 * rank[n] point to the max number 
 * the order is according the st_value value
 * *****************************************************************/
#if 0
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
#endif

/*******************************************************************
 * quick sort
 * after sorting:
 * rank[0] point to the min number
 * rank[n] point to the max number 
 * the order is according the st_value value
 * *****************************************************************/
#if 1
int entre_partition(Elf32_Sym ** rank, int low, int high)
{
	Elf32_Sym * tmp=rank[low];
	ADDRESS pivotkey=rank[low]->st_value;
	while(low<high)
	{
		while(low<high && rank[high]->st_value>=pivotkey) 
			--high;
		rank[low] = rank[high];
		while(low<high && rank[low]->st_value<=pivotkey)
			++low;
		rank[high] = rank[low];
	}
	rank[low] = tmp;
	return low;
}

void entre_qSort(Elf32_Sym ** rank, int low, int high)
{
	int pivotloc;

    if(low<high)
    {
        pivotloc = entre_partition(rank, low, high);
		entre_qSort(rank, low, pivotloc-1);   
		entre_qSort(rank, pivotloc+1, high);         
	}
}

static void entre_function_sort(Elf32_Sym * sym, Elf32_Sym ** rank, int n)
{
    int i,j,k;
    ADDRESS min = 0, tmp;
    Elf32_Sym * sym_p;
				    
    for(i = 0; i< n; i++)
        rank[i] = sym + i;
	
	entre_qSort(rank, 0, n-1);
}
#endif

/**********************************************************************
 * scan Symbol Table, extract STT_ST_FUNC type symbol and reorder them.
 * record them in the Executalbe.pSymTab and Executable.nSymTab. copy 
 * accoding String Table to Executable.pStrTab and Executable.nStrTab.
 * *******************************************************************/
Status entre_IRMarkFunctions(void)
{
	char exe_name_full[256];
#ifdef DEBUG_REACH
    printf("reach begin of function entre_IRMarkFunctions.\n");
#endif

    INDEX i,j;

    Elf32_Sym *pSymTab = Executable.pSymTab;
    UINT32     nSymTab = Executable.nSymTab;
    char      *pStrTab = Executable.pStrTab;
    UINT32     nStrTab = Executable.nStrTab;

	get_application_full_name(exe_name_full);

    if (nSymTab == 0)
//    {
//        printf("\n");
//        printf("             *************************************************************\n");
//        printf("             **        %s\n", exe_name_full);
//        printf("             **        STRIP: The symtab information is stripped!         \n");
//        printf("             **                     Can't Instrument!                     \n");
//        printf("             *************************************************************\n\n");
        return STRIP;
//    }
//	else
//	{/* spec-cpu2000 178.galgel will crash when print this message on srreen */
//        printf("\n");
//        printf("             *************************************************************\n");
//        printf("             **        %s\n", exe_name_full);
//        printf("             **        This Application is Running under SEntre!          \n");
//        printf("             *************************************************************\n\n");
//	}

    Executable.pSymTab = NULL;
    Executable.nSymTab = 0;
    Executable.pStrTab = (char *)malloc(nStrTab);
    Executable.nStrTab = 0;
    Executable.rel_offset = 0;

    /* temporary Symbol array used for function name sort. */
    Elf32_Sym *aSymTemp = (Elf32_Sym *) calloc(sizeof(Elf32_Sym), nSymTab);
    Elf32_Sym **SymRank = (Elf32_Sym **) calloc(sizeof(Elf32_Sym *), nSymTab);

	ENTRE_REACH_HERE();

 	/* for app with -shared -fPIC */
    for(i=1; i<nSymTab; i++)
	{
        Elf32_Sym *pSymTabItem = pSymTab + i;
        unsigned char SymType = ELF32_ST_TYPE(pSymTabItem->st_info);

        if( SymType==STT_FUNC && pSymTabItem->st_value >= Executable.pCodeStart 
                              && pSymTabItem->st_value < Executable.pCodeEnd )
        {
            char *pSymTabItemName = pStrTab + pSymTabItem->st_name;
            if(strncmp(pSymTabItemName, "main", 5) == 0)
    		{
//    			printf("main address: %x\n", pSymTabItem->st_value);
    			entre_init_rel_offset(pSymTabItem->st_value);
    			break;
    		}
		}
	} /* end of for */

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

#if 0		
			/* the function Symbol has been recorded before. */
			/* this condition will not happen & the code ruduce the performace */
            int flag = 0;
            for(j=0; j<Executable.nSymTab; j++)
            {
                if(pSymTabItem->st_value == aSymTemp[j].st_value)
				{
                    flag = 1;
					break;
				}
            }
            if(flag == 1) continue;
#endif
            /* need? */
            ADDRESS addr;
            if(strcmp(pSymTabItemName, "_flush_cache") == 0)
            {
                addr = pSymTabItem->st_value;
                continue;
            }
            if(addr == pSymTabItem->st_value)
                continue;

			/* +Executable.rel_offset is for app with -shared -fPIC */
            aSymTemp[Executable.nSymTab].st_value = pSymTabItem->st_value + Executable.rel_offset;
            aSymTemp[Executable.nSymTab].st_size = pSymTabItem->st_size;
            aSymTemp[Executable.nSymTab].st_name = Executable.nStrTab;
			strcpy(Executable.pStrTab + Executable.nStrTab, pSymTabItemName);
            Executable.nStrTab += strlen(pSymTabItemName) + 1;

			Executable.nSymTab++;
        }
    }/* end of for */

#ifdef DEBUG
	printf("Executable.ref_offset = %x\n", Executable.rel_offset);
	ENTRE_REACH_HERE();
#endif

    /* sort the function Symbols */
    entre_function_sort(aSymTemp, SymRank, Executable.nSymTab);
	/* copy recoreded Function Symbol from aSymTemp to Executable.pSymTab orderly.*/
    Executable.pSymTab = (Elf32_Sym *) malloc(sizeof(Elf32_Sym)*Executable.nSymTab);
    for(i=0; i<Executable.nSymTab; i++)
    {
        Executable.pSymTab[i] = *(SymRank[i]);
    }

#ifdef DEBUG
    for(i=0; i<10; i++)
    {
		printf("the %d symble address: %x\n", i, Executable.pSymTab[i].st_value);
    }
#endif

	ENTRE_REACH_HERE();

    Executable.pCodeStart = Executable.pCodeStart + Executable.rel_offset;
    Executable.pCodeEnd = Executable.pCodeEnd + Executable.rel_offset;

	ADDRESS pPageStart = Executable.pCodeStart & (~(pagesize - 1));
    mprotect((void*)pPageStart, Executable.pCodeEnd - pPageStart, PROT_READ | PROT_WRITE | PROT_EXEC);

    /* the following change st_size if its value is 0. why? */
    for(i=0; i<Executable.nSymTab-1; i++)
    {
        if(Executable.pSymTab[i].st_size <= 0)
        {
//			printf("i: %d current st_value: %x, next st_value: %x \n",
//					i, Executable.pSymTab[i].st_value, Executable.pSymTab[i+1].st_value);
            Executable.pSymTab[i].st_size = Executable.pSymTab[i+1].st_value - 
				                            Executable.pSymTab[i].st_value;
        }
    }
    if(Executable.pSymTab[Executable.nSymTab-1].st_size <= 0)
	{
//			printf("i: %d pcodeEnd: %x, current st_value: %x \n",
//					nSymTab-1, Executable.pCodeEnd, Executable.pSymTab[Executable.nSymTab-1].st_value);

        Executable.pSymTab[Executable.nSymTab-1].st_size = Executable.pCodeEnd -
                        Executable.pSymTab[Executable.nSymTab-1].st_value;
	}
    free(aSymTemp);
    free(SymRank);

    /* the remaining symbol name string table must be smaller than original one, 
	   so the pointer will not change. */
    Executable.pStrTab = realloc(Executable.pStrTab, Executable.nStrTab);

#ifdef DEBUG_REACH
    printf("reach end of function entre_IRMarkFunctions.\n");
#endif

    return 0;
}


/* *******************************************************************
 * record the executable sections info, incluing symtab strtab dynsym 
 * strsym got and text.
 * ******************************************************************/
void entre_BinaryLoad(void* start_fp)
{
#ifdef DEBUG_REACH
    printf("reach begin of function entre_BinaryLoad.\n");
#endif

    INDEX i,j;
 
    Elf32_Ehdr *pElfHeader = (Elf32_Ehdr *) start_fp;    /* ELF Header address */
    UINT32      nSection = pElfHeader->e_shnum;    /* number of sections */
    Elf32_Shdr *pSectionHeaderStart =(Elf32_Shdr *)((char*)pElfHeader + pElfHeader->e_shoff);  /* Section Header Table address */

    /* Section Name String Table info */
    Elf32_Shdr *pSectionHeaderItem = pSectionHeaderStart + pElfHeader->e_shstrndx;

    char *pSectionNameStrTab = (char *)((char*)pElfHeader + pSectionHeaderItem->sh_offset);
//    Executable.pSectionNameStrTab = (char *)malloc(sizeof(pSectionHeaderItem->sh_size));
    Executable.nSectionNameStrTab = pSectionHeaderItem->sh_size;

    /* symtab, strtab, and got is unquie, assum text is also unquie */
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
            Executable.pCodeEnd   = pSectionHeaderItem->sh_addr + pSectionHeaderItem->sh_size ;
            Executable.pSize      = pSectionHeaderItem->sh_size;
        }   
    }

    ADDRESS pPageStart = Executable.pCodeStart & (~(pagesize - 1));
    mprotect((void*)pPageStart, Executable.pCodeEnd - pPageStart, PROT_READ | PROT_WRITE | PROT_EXEC);

#ifdef DEBUG_REACH
    printf("reach end of function entre_BinaryLoad.\n");
#endif
}

Status entre_initExecutable(int fp)
{
    Status status;
    struct stat stat_date;
    int fs;
    void *start_fp;

#ifdef DEBUG_REACH
    printf("reach begin of function entre_initExecutable.\n");
#endif
    fs = fstat(fp, &stat_date);
    start_fp = mmap(NULL, stat_date.st_size, PROT_READ, MAP_SHARED, fp, 0);
    if (start_fp == (void *)-1)
    {
    	printf("mmap error!  errno: %d\n\n", errno);
    	exit(0);
    }
    entre_BinaryLoad(start_fp);
    status = entre_IRMarkFunctions();
    if(status) return status;
    munmap(start_fp, stat_date.st_size);

#ifdef DEBUG_REACH
    printf("reach end of function entre_initExecutable.\n");
#endif
    return 0;
}
