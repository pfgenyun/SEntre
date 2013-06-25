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

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "basicblock.h"
#include "binary.h"
#include "function.h"
#include "isa.h"


Elf32_Sym *current_fun;

struct bb all_bb[BB_SIZE];  /* contain all basic block */
unsigned all_bb_size;       /* the basic block array size */
unsigned all_bb_n;          /* the real basic block num */

struct address_list addr_list[ADDR_LIST_SIZE]; /* contain all BB addr */
//struct address_list * addr_list; /* contain all BB addr */
unsigned addr_list_n;      /* the real address  number */

/******************************************************************
 * ***************************************************************/
#if 0
/* sequential search in all_bb */
int entre_is_bb_begin(ADDRESS addr)
{
	int i;
	for(i=0; i<all_bb_n; i++)
	{
		if(all_bb[i].start == addr)
			return 1;
	}
	return 0;
}
#endif

/* binary search in all_bb */
#if 1
int entre_is_bb_begin(ADDRESS addr)
{
	int low, high, mid;

    low = 0;
	high = all_bb_n - 1;
	mid = 0;

	if(addr == all_bb[low].start)
        return 1;
	if(addr == all_bb[high].start)
        return 1;
	
	while(low <= high)
	{
		mid = low + (high - low)/2;
//		mid = (high + low)/2;
		if(addr == all_bb[mid].start)
		    return 1;
		
		if(all_bb[mid].start > addr)
		    high = mid - 1;
		else
		    low = mid + 1;
	}

	if(low > high)
	    return 0;
}
#endif

/********************************************************************
 * return the basic block index according to the text address addr.
 * *****************************************************************/
#if 0
int entre_get_bb_index(ADDRESS addr)
{
	int i=0;
	for(i=0; i<all_bb_n; i++)
	{
		if(all_bb[i].start == addr)
			return i;
	}
	return -1;
}
#endif

/* binary search in all_bb */
#if 1
int entre_get_bb_index(ADDRESS addr)
{
	int low, high, mid;

    low = 0;
	high = all_bb_n - 1;
	mid = 0;

	if(addr == all_bb[low].start)
        return low;
	if(addr == all_bb[high].start)
        return high;
	
	while(low <= high)
	{
		mid = low + (high - low)/2;
//		mid = (high + low)/2;
		if(addr == all_bb[mid].start)
		    return mid;
		
		if(all_bb[mid].start > addr)
		    high = mid - 1;
		else
		    low = mid + 1;
	}

	if(low > high)
	    return -1;
}
#endif

/********************************************************************
 * return the address of demain counter of basic block according to
 * the text address addr.
 * *****************************************************************/
ADDRESS entre_get_bb_counter_addr(ADDRESS addr)
{
	int bb_index;
	ADDRESS bb_counter_addr;
	
	bb_index = entre_get_bb_index(addr);
	if(bb_index < 0)
	{
		printf("basic block begin addr: 0x%x\n", addr);
		entre_my_error("basic block begin addr error");
	}
	bb_counter_addr =(ADDRESS)&(all_bb[bb_index].counter);

	return bb_counter_addr;
}

/********************************************************************
 * after mark one function, call this function to output mark data.*
 * all BB info are recoreded in the all_BB struct 
 * original is wrong: tmp_bb_n = all_bb_n. right 
 * *****************************************************************/
void entre_fini_addr_list(void)
{
    INDEX i, index;
    int tmp_bb_n;
    ADDRESS addr;
    unsigned size_byte;

    tmp_bb_n = all_bb_n;

    if(all_bb_n + addr_list_n > all_bb_size) 
	{
		printf("all_bb_n: %d, addr_list_n:%d, all_bb_size: %d\n", all_bb_n, addr_list_n, all_bb_size);
        entre_my_error("all_basic_block size insufficient!\n");
	}
    /* copy entry address from addr_list to all_bb */
    for(index=addr_list[0].next; index!=NULL_INDEX; index=addr_list[index].next)
    {
        addr = addr_list[index].addr;
        all_bb[tmp_bb_n].start = addr;
		all_bb[tmp_bb_n].fun_name = (char *) &(Executable.pStrTab[(int)current_fun->st_name]);
        tmp_bb_n ++;
//#ifdef DEBUG
		if(all_bb[tmp_bb_n-1].start == all_bb[tmp_bb_n-2].start)
			entre_my_error("basic block divided error, redundant basic block.\n\n");
//#endif
    }

    /* calculate basic block size, bb sequence is order between function
	   in addr_list, but disorder in function */
    for(i=all_bb_n; i<tmp_bb_n-1; i++)
    {
        size_byte = all_bb[i+1].start - all_bb[i].start;
        all_bb[i].insn_num = size_byte >> 2;
	}
	/* the last basic block size */
    if((tmp_bb_n - all_bb_n) == 1)
        all_bb[i].insn_num = current_fun->st_size >> 2;
    else
        all_bb[i].insn_num = (current_fun->st_size - (all_bb[i].start - current_fun->st_value)) >> 2;

    all_bb_n = tmp_bb_n;
}

/*********************************************************************
 * add entry_addr to the addr_list and *
 * filt repeated entry address  *
 * ******************************************************************/
int entre_add_bb_entry_to_addr_list(ADDRESS entry_addr)
{
    int index_p = 0;
    int index_pre = 0;

    if(entry_addr < current_fun->st_value || 
       entry_addr >= current_fun->st_value + current_fun->st_size)
	{
		printf("entry_addr: %x fun_start: %x fun_end: %x\n", 
				entry_addr, current_fun->st_value, current_fun->st_value + current_fun->st_size);
        entre_my_error("entry_error!");
	}

    /* find the right place to insert entry_addr in addr_list */
    while(index_p != NULL_INDEX)
    {
        if(entry_addr > addr_list[index_p].addr)
        {
            index_pre = index_p;
            index_p = addr_list[index_p].next;
        }
		else
            break;
    }

    /* filt repreated entry address */
    if(entry_addr == addr_list[index_p].addr)
        return 1;

	if(addr_list_n >= ADDR_LIST_SIZE )
		entre_my_error("address list size insufficient!\n");
    
    /* insert the new entry_addr in addr_list */
    addr_list[addr_list_n].addr = entry_addr;
    addr_list[addr_list_n].next = index_p;
    addr_list[index_pre].next = addr_list_n;

    addr_list_n ++;

    return 1;
}


void entre_add_jr_no_link_insn(ADDRESS addr, INSN_T insn)
{
    ADDRESS entry;
    entry = addr + 8;

    if(entry < current_fun->st_value || 
       entry >= current_fun->st_value + current_fun->st_size);
//        entre_my_error("jr_no_link addr error");
    else 
        entre_add_bb_entry_to_addr_list(entry);
}


void entre_add_jump_no_link_insn(ADDRESS addr, INSN_T insn)
{
    entre_add_jr_no_link_insn(addr, insn);
}


void entre_add_branch_insn(ADDRESS addr, INSN_T insn)
{
    ADDRESS target1, target2;
    target1 = entre_branch_target(addr, insn);
    target2 = addr + 8;
    
    if(target1 < current_fun->st_value ||
       target1 >= current_fun->st_value + current_fun->st_size);
//        entre_my_error("branch addr error");
    else
        entre_add_bb_entry_to_addr_list(target1);

    if(target2 < current_fun->st_value ||
	   target2 >= current_fun->st_value + current_fun->st_size);
//		entre_my_error("branch addr error");
    else
	    entre_add_bb_entry_to_addr_list(target2);
}


/*********************************************************************
 * get instruction type *
 * *******************************************************************/
INSN_CLASS entre_insn_type(INSN_T insn)
{
    int main_op;
    int sub_op;
    int s_reg;
    int t_reg;

    main_op = MAIN_OP(insn);
    sub_op = SUB_OP(insn);
	s_reg = S_REG(insn);
	t_reg = T_REG(insn);

	if(main_op == 0)  
	{   
	    if(sub_op == 8) return JR_NO_LINK;  //jr 
		else if(sub_op == 9) return JR_LINK;    //jalr 
	    else return GENERAL;
	}   
	else if( main_op == 1 ) 
    {   
        if( t_reg <= 3) return B_NO_LINK;  //bltz bgez bltzl bgezl 
        else if ( (t_reg >= 16) && (t_reg <= 19) ) return B_LINK; // bltzal bgezal bltzall bgezall
        else return GENERAL;
    }   
    else if(main_op == 2) return J_NO_LINK;     //j 
    else if(main_op == 3) return J_LINK;        //jal
    else if(main_op <= 7 && main_op >= 4) return B_NO_LINK; // beq bne blez bgtz 
    else if(main_op <= 15) return GENERAL;   
    else if(main_op == 16) 
    {   
        if(s_reg == 8 && t_reg <= 3 ) return B_NO_LINK; //bc0f bc0t bc0f1 bc0t1
        else return GENERAL;
    }   
    else if(main_op == 17) 
    {   
        if(s_reg >=8 && s_reg <= 10) return B_NO_LINK; // bc1f bc1t bc1f1 bc1t1 bc1any2f ...
        else return GENERAL;
    }   
    else if(main_op == 18 )
    {   
        if(s_reg == 8 && t_reg <= 3) return B_NO_LINK; //bc2f bc2t bc2f1 bc2t1
        else return GENERAL;
    }   
    else if(main_op == 19) return GENERAL;
    else if(main_op <= 23) return B_NO_LINK; //beql bnel blezl bgtzl
    else return GENERAL;
}


/**********************************************************************
 * init the struct addr_list *
 * *******************************************************************/
void entre_init_addr_list(void)
{
//	ENTRE_REACH_HERE();
//    addr_list =  malloc(ADDR_LIST_SIZE * sizeof(struct address_list));
//	if(addr_list == NULL)
//	{
//        printf("malloc of addr_list failed!\n");
//		exit(0);
//	}
    addr_list[0].addr = MIN_ADDR;
    addr_list[0].next = NULL_INDEX;

    addr_list_n = 1;

//	ENTRE_REACH_HERE();
}


/*********************************************************************
 * mark basic block in current_fun function *
 * *******************************************************************/
void entre_mark_bb_in_function(void)
{
    INSN_T insn;
    ADDRESS addr;
    INSN_CLASS class;

    entre_init_addr_list();
    entre_add_bb_entry_to_addr_list(current_fun->st_value);

    FOR_EACH_INSN_IN_FUN(current_fun, addr)
    {
//        printf("ADDR_AT: %x", addr);
//		ENTRE_REACH_HERE();
        insn = INSN_AT(addr);
//		ENTRE_REACH_HERE();
        class = entre_insn_type(insn);
        
        switch(class)
        {
            case GENERAL:             /* normal instruction */     
                break;
            case JR_LINK:            /* jump and link, jalr */
                break;
            case JR_NO_LINK:         /* jump, jr */
                entre_add_jr_no_link_insn(addr, insn);
                break;
            case B_LINK:             /* branch and link, bal */
                entre_add_branch_insn(addr, insn);
                break;
            case B_NO_LINK:          /* branch, bne */
                entre_add_branch_insn(addr, insn);
            case J_LINK:             /* jump and link, jal */
                break;
            case J_NO_LINK:          /* jump, j */
                entre_add_jump_no_link_insn(addr, insn);
                break;
            default:
                entre_my_error("INSN CLASS ERROR!\n");
        }
    }

    entre_fini_addr_list();
}


/*********************************************************************
  mark all basic block, store in array all_bb and 
  record function infomation in all_function .
 * ******************************************************************/
void entre_mark_bb(void)
{
    int start_bb;
    int end_bb;
    Elf32_Sym *fun;

//    entre_init_addr_list();

    FOR_EACH_FUNCTION(fun)
    {
//        entre_init_one_function_for_share_pic(fun);
        start_bb = all_bb_n;
        current_fun = fun;
        entre_mark_bb_in_function();
        end_bb = all_bb_n;

        entre_init_one_function(fun, start_bb, end_bb-start_bb);
    }
}

/*********************************************************************
 * init BB array *
 * ******************************************************************/
void entre_init_mark_bb(void)
{
    INDEX i;
    all_bb_n = 0;
    all_bb_size = BB_SIZE;

    for(i=0; i<all_bb_size; i++)
    {
        all_bb[i].counter  = 0;
        all_bb[i].start    = 0;
        all_bb[i].insn_num = 0;
        all_bb[i].i1       = 0;
        all_bb[i].i2       = 0;
        all_bb[i].in_point = 0;
        all_bb[i].type     = 0;
        all_bb[i].fun_name = '\0';
    }
}


/**********************************************************************
********************************debug**********************************
***********************************************************************/
void entre_dump_bb()
{
	struct bb * bb_p;
	int i, length;
	FILE * fp;

	char * short_name;
	char full_name[256]={0} ; 
	char output_file[256]={0} ; 
	
	short_name = get_application_short_name(full_name);

	length = strlen(short_name);
	for(i=0; i<length; i++)
	    output_file[i] = short_name[i];
	strcpy(&output_file[i], "_bb.sentre");

	fp = fopen(output_file, "w");
	FOR_EACH_BB(bb_p, i)
	{
//		printf("start: %x\tinsn_num: %d\tin_point: %x\ti1: %x\ti2: %x\tcounter: %ld\n",
//	bb_p->start, bb_p->insn_num, bb_p->in_point, bb_p->i1, bb_p->i2, bb_p->counter);
		fprintf(fp, "start: %x\tend: %x \tinsn_num: %d \tcounter: %-14d\tfun_name: %s\n",
	bb_p->start, bb_p->start + bb_p->insn_num * 4, bb_p->insn_num, bb_p->counter, bb_p->fun_name);
	}
	fclose(fp);
}

void entre_dump_one_bb(struct bb * bb_p)
{
    printf("start %x\tinsn_num %d\tin_point %x\ti1 %x\ti2 %x\tcounter %ld\n",
	bb_p->start,bb_p -> insn_num,bb_p->in_point, bb_p->i1,bb_p->i2,bb_p -> counter);
}

