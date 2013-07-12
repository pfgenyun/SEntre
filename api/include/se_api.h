/************************************************************
 * Copyright (c) 2013-present MeiWenBin.  All rights reserved.
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

#ifndef SE_api_H
#define SE_api_H

#include <sys/types.h>

/***********************************************************************
 * contains the basicblock table definition and some related functions.
 * ********************************************************************/
#include "se_basicblock.h"

/***********************************************************************
 * contains the fun table definition and some related functions.
 * ********************************************************************/
#include "se_fun.h"

/***********************************************************************
 * contains the got table definition and some related functions.
 * ********************************************************************/
#include "se_got.h"

/***********************************************************************
 * contains the context definition and identification of some
 * instructions.
 * ********************************************************************/
#include "se_isa.h"

/***********************************************************************
 * contains some lock manipulation functions, such an atomic manipulation
 * functions, mutex lock, read-write lock, recursive lock.
 * ********************************************************************/
#include "se_utils.h"

#endif
