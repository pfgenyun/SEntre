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
#include "binary.h"
#include "stack.h"
#include "codecache.h"
#include "function.h"
#include "basicblock.h"
#include "got.h"
#include "context_switch.h"
#include "in_code.h"
#include "make_new_function.h"
#include "control_trans.h"
#include "redirect.h"

#ifdef API_MODE
#ifdef TRACE
#include "trace.h"
#endif

#ifdef OOprofile
#include "OOprofile.h"
#endif

#ifdef BB_FREQ
#include "bb_freq.h"
#endif

#include "se_mode.h"
#endif

#ifdef API_MODE
#endif

Status entre_optimize(int fp)
{
    Status status;
    entre_global_env_init();
    status = entre_initExecutable(fp);
    if(status) return status;

#ifdef DUMP_FUNC
    entre_dump_function();
#endif

    entre_init_stack();
    entre_init_cc();                 /* init codecache */
    entre_init_function();
    entre_init_mark_bb();
    entre_mark_bb();

#ifdef DUMP_BB
    entre_dump_bb();
#endif

#ifdef DEBUG
	printf("\n**********step one.**********\n\n");
#endif
    entre_got_init(FUNCTION_NUMS);
    ADDRESS context_switch_addr_call = 
	entre_make_context_switch_code((ADDRESS)entre_call_redirect);
    entre_make_in_code_call(context_switch_addr_call);

#ifdef API_MODE
	ADDRESS context_switch_addr_analysis =
	entre_make_context_switch_code((ADDRESS)SEntre_analysis);
	entre_make_in_code_mode(context_switch_addr_analysis);
#endif

    entre_instrument_omit_init();
    entre_make_new_functions();
    entre_transfer_redirect();

    entre_control_transfer();
#ifdef OOprofile
    entre_OOprofile_init();
#endif
    entre_executable_flush();
    entre_cc_flush();

#ifdef DEBUG
	printf("\n**********step two.**********\n\n");
#endif

}

void entre_collection()
{
    entre_global_file_close();
    entre_memory_free();
#ifdef OOprofile
    entre_OOprofile_fini();
#endif

#ifdef BB_FREQ
	entre_dump_bb();
#endif
}

