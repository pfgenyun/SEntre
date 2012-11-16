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
  os_shared.h - shared declarations for os facilities from linux 
  Future: Linux and Win share the same API in this file
          the different APIs are defined in linux/os_exports.h
 *******************************************************************/


#ifndef OS_SHARED_H
#define OS_SHARED_H


thread_id_t get_thread_id(void);
process_id_t get_process_id(void);
void thread_yield(void);

/* these must be plain literals since we need these in pragmas/attributes */
#define NEVER_PROTECTED_SECTION  ".nspdata"
#define RARELY_PROTECTED_SECTION ".data"
#define FREQ_PROTECTED_SECTION   ".fspdata"
#define CXTSW_PROTECTED_SECTION  ".cspdata"

/* User MUST supply an init value, or else cl will leave in .bss (will show up
 * at end of .data), which is why we hardcode the = here!
 * We use varargs to allow commas in the init if a struct.
 */
#define DECLARE_FREQPROT_VAR(var, ...)                        \
    START_DATA_SECTION(FREQ_PROTECTED_SECTION, "w")           \
    var VAR_IN_SECTION(FREQ_PROTECTED_SECTION) = __VA_ARGS__; \
    END_DATA_SECTION() 

#define DECLARE_CXTSWPROT_VAR(var, ...)                        \
    START_DATA_SECTION(CXTSW_PROTECTED_SECTION, "w")           \
    var VAR_IN_SECTION(CXTSW_PROTECTED_SECTION) = __VA_ARGS__; \
    END_DATA_SECTION() 

#define DECLARE_NEVERPROT_VAR(var, ...)                        \
    START_DATA_SECTION(NEVER_PROTECTED_SECTION, "w")           \
    var VAR_IN_SECTION(NEVER_PROTECTED_SECTION) = __VA_ARGS__; \
    END_DATA_SECTION() 


#endif
