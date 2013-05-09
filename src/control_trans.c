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

#include "global.h"
#include "isa.h"
#include "got.h"
#include "function.h"
#include "reg.h"
#include "in_code.h"

void entre_control_transfer()
{
	int i;
	INSN_T trans[4];
	struct function * fun_main;
	ADDRESS main_old_addr;
	ADDRESS main_new_addr;
	
	fun_main = entre_find_function("main");
	main_old_addr = fun_main->f_address;
	main_new_addr = entre_got_find_final(main_old_addr);

#ifdef DDEBUG
	printf("control_tran, old_address %x\t new_address %x\n", main_old_addr, main_new_addr);
#endif

	if(main_new_addr == 0)
		entre_my_error("can not find main.\n");
//	main_new_addr -= 8;		/* gcc4.3 use t9 when entry main */
#ifdef OOprofile
	main_new_addr -= IN_CODE_BYTES;		/* OOpfofile function begine INCODE not exec except main */
#endif

	trans[0] = entre_make_lui(REG_T9, main_new_addr>>16);
	trans[1] = entre_make_inc_x(REG_T9, main_new_addr&0xffff);
	trans[2] = entre_make_jr(REG_T9);
	trans[3] = entre_make_nop();
	for(i=0; i<4; i++)
		INSN_AT(main_old_addr + i*4) = trans[i];

}
