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

/*************************************************************************
  options.c
  Options definition and handling of corresponding command line options
 *************************************************************************/

#include "options.h"


/**************************************************************************************/
/**************************************************************************************/

#ifndef EXPOSE_INTERNAL_OPTIONS
/* default values for internal options are kept in a separate struct */
#  define OPTION_COMMAND_INTERNAL(type, name, default_value, command_line_option, statement, description, flag, pcache) default_value, 
#  define OPTION_COMMAND(type, name, default_value, command_line_option, \
                         statement, description, flag, pcache) /* nothing */
/* read only source for default internal option values and names
 * no lock needed since never written
 */
const internal_options_t default_internal_options = {
#  include "optionsx.h"
};
#undef OPTION_COMMAND_INTERNAL
#undef OPTION_COMMAND
#endif

/**************************************************************************************/
/**************************************************************************************/

#ifdef EXPOSE_INTERNAL_OPTIONS
#  define OPTION_COMMAND_INTERNAL OPTION_COMMAND
#else 
/* DON'T FIXME: In order to support easy switching of an internal
   option into user accessible one we could waste some memory by
   allocating fields in options_t even for INTERNAL options.  That would
   let us have INTERNAL_OPTION be a more flexible macro that can use
   either the constant value, or the dynamically set variable
   depending on the option declaration in optionsx.h.  However, 
   it increases the code size of this file (there is also a minor increase
   in other object files since more option fields need longer than 8-bit offsets)
   For now we can live without this.
*/
#  define OPTION_COMMAND_INTERNAL(type, name, default_value, command_line_option, statement, description, flag, pcache) /* nothing, */
#endif

/* all to default values */
#define OPTION_COMMAND(type, name, default_value, command_line_option, \
                       statement, description, flag, pcache) default_value,
/* read only source for default option values and names
 * no lock needed since never written
 */
const options_t default_options = {
#  include "optionsx.h"
};

/**************************************************************************************/
/**************************************************************************************/
