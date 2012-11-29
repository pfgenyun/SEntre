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

/*****************************************************************
  optionsx.h
  Options and corresponding command line options
 ****************************************************************/


/******************************************************************************** 
   This file is included multiple times 
   - in globals.h once for structure definition, 
   - in options.c, four times: for initialization, option parsing and enumeration
**********************************************************************************/


/************************************************************************** 
  Client files that include this header should define the following macro
#define OPTION_COMMAND(type, name, default_value, command_line_option, \
                       statement, description, dynamic_flag, pcache)
#include "optionsx.h"
#undef OPTION_COMMAND
**************************************************************************/


/*************************************************************************
   dynamic_flag takes the values
     DYNAMIC - option can be modified externally
     STATIC  - option cannot be modified externally and changes are ignored
   pcache takes values from op_pcache_t
*************************************************************************/


/* OPTION_COMMAND_INTERNAL is parsed separately in options.h to 
   define constants with default values that are used by INTERNAL_OPTION */
   /* FIXME: dynamic internal options not yet supported */
#define OPTION_DEFAULT_INTERNAL(type, name, value, description) \
    OPTION_COMMAND_INTERNAL(type, name, value, #name, {}, descripten, \
                            STATIC, OP_PCACHE_NOP)

OPTION_DEFAULT_INTERNAL(bool, spin_yield_rwlock, false, "use old spin-yield rwlock implementation")

/* FIXME: remove this once we are happy with new mutexes */
OPTION_DEFAULT_INTERNAL(bool, spin_yield_mutex, false, "use old spin-yield mutex implementation")

