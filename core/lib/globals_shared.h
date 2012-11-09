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

/***************************************************************************
  globals_shared.h
  definitions to be shared with core-external modules
 **************************************************************************/

#ifndef GLOBALS_SHARED_H
#define GLOBALS_SHARED_H

/*************************************************************************************/
/*************************************************************************************/

#define SEntre_OPTION(opt) (ASSERT_OWN_READWRITE_LOCK(IS_OPTION_STRING(opt), \
                            &options_lock), sentre_options.opt)
/* For use where we don't want ASSERT defines. Currently only used in FATAL_USAGE_ERROR
 * so it can be used in files that require all asserts to be client asserts. */
#define DYNAMO_OPTION_NOT_STRING(opt) (sentre_options.opt)

#if defined(INTERNAL) || defined(CLIENT_INTERFACE)
#define EXPOSE_INTERNAL_OPTIONS
#endif

#ifdef EXPOSE_INTERNAL_OPTIONS
  /* Use only for experimental non-release options */
  /* Internal option value can be set on the command line only in INTERNAL builds */
  /* We should remove the ASSERT if we convert an internal option into non-internal */
# define INTERNAL_OPTION(opt) ((IS_OPTION_INTERNAL(opt)) ? (SEntre_OPTION(opt)) : \
                               (ASSERT_MESSAGE("non-internal option argument "#opt, false), \
                                SEntre_OPTION(opt)))
#else
  /* Use only for experimental non-release options, 
     default value is assumed and command line options are ignored */
  /* We could use IS_OPTION_INTERNAL(opt) ? to determine whether an option is defined as INTERNAL in
     optionsx.h and have that be the only place to modify to transition between internal and external options.
     The compiler should be able to eliminate the inappropriate part of the constant expression,
     if the specific option is no longer defined as internal so we don't have to modify the code.
     Still I'd rather have explicit uses of DYNAMO_OPTION or INTERNAL_OPTION for now.
  */
# define INTERNAL_OPTION(opt) DEFAULT_INTERNAL_OPTION_VALUE(opt)
#endif /* EXPOSE_INTERNAL_OPTIONS */


/*************************************************************************************/
/*************************************************************************************/

#endif

