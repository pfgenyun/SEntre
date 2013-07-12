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

#ifndef SE_UTILS_H
#define SE_UTILS_H

#include "utils.h"
#include "os_shared.h"
#include "os_exports.h"
#include "arch_exports.h"

/**************************************************************************
 * Atomic operation.
 *************************************************************************/
#define ATOMIC_INC(type, var) ATOMIC_INC_##type(var)
#define ATOMIC_DEC(type, var) ATOMIC_DEC_##type(var)

/**************************************************************************
 * The decaration of lock.
 *************************************************************************/
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

/**************************************************************************
 * basic synchronization functions.
 *************************************************************************/
extern void mutex_lock(mutex_t *mutex);
extern bool mutex_trylock(mutex_t *mutex);
extern void mutex_unlock(mutex_t *mutex);

/**************************************************************************
 * A read write lock allows multiple readers or alternatively a single 
 * writer.
 *************************************************************************/
extern void read_lock(read_write_lock_t *rw);
extern void write_lock(read_write_lock_t *rw);
extern bool write_trylock(read_write_lock_t *rw);
extern void read_unlock(read_write_lock_t *rw);
extern void write_unlock(read_write_lock_t *rw);

/**************************************************************************
 * A recursive lock can be taken more than once by the owning thread.
 *************************************************************************/
extern void acquire_recursive_lock(recursive_lock_t *lock);
extern bool try_recursive_lock(recursive_lock_t *lock);
extern void release_recursive_lock(recursive_lock_t *lock);

#endif
