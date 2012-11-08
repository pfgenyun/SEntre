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

#ifndef OPTIONS_H
#define OPTIONS_H


/* for all option uses */
/* N.B.: for 64-bit should we make the uint_size options be size_t?
 * For now we're ok with all such options maxing out at 4GB, and in fact
 * some like the fcache options are assumed to not be larger.
 */
#define uint_size uint
#define uint_time uint
/* So far all addr_t are external so we don't have a 64-bit problem */
#define uint_addr ptr_uint_t

/* Does this option affect persistent cache formation? */
typedef enum 
{
    OP_PCACHE_NOP    = 0, /* No effect on pcaches */
    OP_PCACHE_LOCAL  = 1, /* Can only relax (not tighten), and when it relaxes any
                           * module that module is marked via
                           * os_module_set_flag(MODULE_WAS_EXEMPTED). */
    OP_PCACHE_GLOBAL = 2, /* Affects pcaches but not called out as local. */
} op_pcache_t;


/* We use an enum for default values of non-string options so that the compiler
 * will fold them away (cl, at least, won't do it even for struct fields
 * declared const), and also to determine whether options are internal or take
 * string values or affect peristent caches.
 * In order for this to work optionsx.h strings must either be EMPTY_STRING or
 * a string in the OPTION_STRING() macro.
 * N.B.: for 64-bit presumably every enum value is 64-bit-wide b/c some
 * of them are.  FIXME: could split up the enums to save space: or are we
 * never actually storing these values?
 */
#define OPTION_STRING(x) 0 /* no string in enum */
#define EMPTY_STRING     0 /* no string in enum */
#define OPTION_COMMAND(type, name, default_value, command_line_option, statement, \
                       description, flag, pcache)                                 \
    OPTION_DEFAULT_VALUE_##name = (ptr_uint_t) default_value, \
    OPTION_IS_INTERNAL_##name = false, \
    OPTION_IS_STRING_##name = ISSTRING_##type, \
    OPTION_AFFECTS_PCACHE_##name = pcache,
#define OPTION_COMMAND_INTERNAL(type, name, default_value, command_line_option, \
                                statement, description, flag, pcache)           \
    OPTION_DEFAULT_VALUE_##name = (ptr_uint_t) default_value, \
    OPTION_IS_INTERNAL_##name = true, \
    OPTION_IS_STRING_##name = ISSTRING_##type, \
    OPTION_AFFECTS_PCACHE_##name = pcache,
enum option_is_internal 
{
#   include "optionsx.h"
};
#undef OPTION_COMMAND
#undef OPTION_COMMAND_INTERNAL
#undef OPTION_STRING
#undef EMPTY_STRING

/***************************************************************************************/
/***************************************************************************************/

/* for all other option uses */
#define OPTION_STRING(x) x
#define EMPTY_STRING {0}        /* fills the constant char structure with zeroes */

/* the Option struct typedef */
#define OPTION_COMMAND(type, name, default_value, command_line_option, statement, \
                       description, flag, pcache)                                 \
    type name;
#ifdef EXPOSE_INTERNAL_OPTIONS
#  define OPTION_COMMAND_INTERNAL(type, name, default_value, command_line_option, \
                                  statement, description, flag, pcache)           \
    type name;
#else 
#  define OPTION_COMMAND_INTERNAL(type, name, default_value, command_line_option, \
                                  statement, description, flag, pcache) /* nothing */
#endif
typedef struct _option_t
{
#    include "optionsx.h"
} option_t;
#undef OPTION_COMMAND
#undef OPTION_COMMAND_INTERNAL

/***************************************************************************************/
/***************************************************************************************/

#ifndef EXPOSE_INTERNAL_OPTIONS
/* special struct for internal option default values */
#  define OPTION_COMMAND(type, name, default_value, command_line_option, statement, \
                         description, flag, pcache) /* nothing */
#  define OPTION_COMMAND_INTERNAL(type, name, default_value, command_line_option, \
                                  statement, description, flag, pcache)           \
    const type name;
typedef struct _internal_options_t 
{
#   include "optionsx.h"
} internal_options_t;
#  undef OPTION_COMMAND
#  undef OPTION_COMMAND_INTERNAL
#endif

/***************************************************************************************/
/***************************************************************************************/

#undef uint_size
#undef uint_time
#undef uint_addr

/***************************************************************************************/
/***************************************************************************************/

#endif