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

#include "se_api.h"
#include <string.h>

struct bb_counter{
        ADDRESS addr;
        unsigned num_before;
        unsigned num_after;
};

struct bb_counter bb_num[1024];
unsigned bb_nn = 0;

#ifdef API_MODE
void entre_dump_api()
{
	int i, length;
	FILE * fp; 

	char * short_name;
	char full_name[256]={0} ; 
	char output_file[256]={0} ; 

	short_name = get_application_short_name(full_name);

	length = strlen(short_name);
	for(i=0; i<length; i++)
	output_file[i] = short_name[i];
	strcpy(&output_file[i], "_bb_num.sentre");

	fp = fopen(output_file, "w");
	for(i = 0; i < bb_nn; i++)
	{   
		fprintf(fp, "addr: %x\tnum_before: %d \tnum_after: %d \n",
				bb_num[i].addr, bb_num[i].num_before, bb_num[i].num_after);
	}   
	fclose(fp);
}
#endif

int entre_get_bb_num_index(ADDRESS addr)
{
//        int low, high, mid;
//
//    	low = 0;
//        high = bb_nn - 1;
//        mid = 0;
//
//        if(addr == bb_num[low].addr)
//        return low;
//        if(addr == bb_num[high].addr)
//        return high;
//
//        while(low <= high)
//        {
//                mid = low + (high - low)/2;
////              mid = (high + low)/2;
//                if(addr == bb_num[mid].addr)
//                    return mid;
//
//                if(bb_num[mid].addr > addr)
//                    high = mid - 1;
//                else
//                    low = mid + 1;
//        }
//
//        if(low > high)
//            return -1;
	int i;
	
	for(i = 0; i < bb_nn; i++)
	{
		if(bb_num[i].addr == addr)
			return i;
	}

	return -1;
}

ADDRESS entre_get_bb_num_addr_before(ADDRESS addr)
{
	int bb_index, temp;
	ADDRESS bb_counter_addr;

	bb_index = entre_get_bb_num_index(addr);
	if(bb_index < 0)
	{
		temp = bb_nn;
		bb_num[bb_nn].addr = addr;
		bb_nn++;	
		bb_counter_addr =(ADDRESS)(&(bb_num[temp].num_before));
	}
	else
		bb_counter_addr =(ADDRESS)(&(bb_num[bb_index].num_before));

	return bb_counter_addr;
}

ADDRESS entre_get_bb_num_addr_after(ADDRESS addr)
{
	int bb_index, temp;
	ADDRESS bb_counter_addr;

	bb_index = entre_get_bb_num_index(addr);
	if(bb_index < 0)
	{
		temp = bb_nn;
		bb_num[bb_nn].addr = addr;
		bb_nn++;	
		bb_counter_addr =(ADDRESS)(&(bb_num[temp].num_after));
	}
	else
		bb_counter_addr =(ADDRESS)&((bb_num[bb_index].num_after));

	return bb_counter_addr;
}

void entre_bb_freq_num(struct context * context)
{
	ADDRESS old_addr, new_addr, counter_addr, target_addr;
	INSN_T insn;

	new_addr = context->ra + IN_CODE_LW_NUM;
	old_addr = entre_map_newAddr_2_oldInsnAddr(new_addr);
	insn = INSN_AT(old_addr);
	target_addr = entre_branch_target(old_addr, insn);
	if(target_addr > old_addr)
	{
		counter_addr = entre_get_bb_num_addr_after(old_addr);
		ATOMIC_INC(int, *(unsigned *)counter_addr);
	}
	else
	{
		counter_addr = entre_get_bb_num_addr_before(old_addr);
		ATOMIC_INC(int, *(unsigned *)counter_addr);
	}
	return ;
}
