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
  os.c - Linux specific routines
 ***************************************************************************/

#include "global.h"
#include "os_private.h"
#include "syscall.h"

thread_id_t
get_sys_thread_id()
{
    thread_id_t id;
    id = sentre_syscall(SYS_gettid, 0);
    return id;
}

thread_id_t
get_thread_id(void)
{
    thread_id_t id;
    id = get_sys_thread_id();
    return id;
}

void
thread_yield()
{
    sentre_syscall(SYS_sched_yield);
}

/*************************************************************************/
/*************************************************************************/

void
rwlock_wait_contended_reader(read_write_lock_t *rwlock)
{
    thread_yield();
}

void
rwlock_notify_readers(read_write_lock_t *rwlock)
{
    /* nothing to do here */
}

