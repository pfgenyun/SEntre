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


/* to dispatch on string default values, kept in struct not enum */
#define ISSTRING_bool 0
#define ISSTRING_uint 0
#define ISSTRING_uint_size 0
#define ISSTRING_uint_time 0
#define ISSTRING_ptr_uint_t 0
#define ISSTRING_pathstring_t 1
#define ISSTRING_liststring_t 1

/* Does this option affect persistent cache formation? */
typedef enum 
{
    OP_PCACHE_NOP    = 0, /* No effect on pcaches */
    OP_PCACHE_LOCAL  = 1, /* Can only relax (not tighten), and when it relaxes any
                           * module that module is marked via
                           * os_module_set_flag(MODULE_WAS_EXEMPTED). */
    OP_PCACHE_GLOBAL = 2, /* Affects pcaches but not called out as local. */
} op_pcache_t;

/***************************************************************************************/
/***************************************************************************************/

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
} options_t;
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

/* For default integer values we use an enum, while for default string values we
 * use the default_options struct instance that is already being used
 * for option parsing, and a second one for internal options when !INTERNAL
 */
extern const options_t default_options;

#ifndef EXPOSE_INTERNAL_OPTIONS
/* only needs to contain string options, but no compile-time way to
 * do that without having OPTION_COMMAND_INTERNAL_STRING()!
 */
extern const internal_options_t default_internal_options;
#endif

#define IS_OPTION_INTERNAL(name) (OPTION_IS_INTERNAL_##name)
#define IS_OPTION_STRING(name) (OPTION_IS_STRING_##name)
/* FIXME : figure out a way to handle types here so that we don't have to cast
 * strings to ints to avoid compiler warnings */
#define DEFAULT_OPTION_VALUE(name) (IS_OPTION_STRING(name) ? (int)default_options.name : \
                                    OPTION_DEFAULT_VALUE_##name)
#ifdef EXPOSE_INTERNAL_OPTIONS
#  define DEFAULT_INTERNAL_OPTION_VALUE DEFAULT_OPTION_VALUE
#else
#  define DEFAULT_INTERNAL_OPTION_VALUE(name) (IS_OPTION_STRING(name) ? \
                                               default_internal_options.name : \
                                               OPTION_DEFAULT_VALUE_##name)
#endif

/***************************************************************************************/
/***************************************************************************************/

#endif
