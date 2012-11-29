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

void
mutex_notify_released_lock(mutex_t *lock)
{
    /* nothing to do here */
}

void
mutex_wait_contended_lock(mutex_t *lock)
{
    /* FIXME: we don't actually use system calls to synchronize on Linux,
     * one day we would use futex(2) on this path (PR 295561). 
     * For now we use a busy-wait lock.
     * If we do use a true wait need to set client_thread_safe_for_synch around it */

    /* we now have to undo our earlier request */
    atomic_dec_and_test(&lock->lock_requests);

    while (!mutex_trylock(lock)) {
        thread_yield();
    }

#ifdef DEADLOCK_AVOIDANCE
    /* HACK: trylock's success causes it to do DEADLOCK_AVOIDANCE_LOCK, so to
     * avoid two in a row (causes assertion on owner) we unlock here
     * In the future we will remove the trylock here and this will go away.
     */
    deadlock_avoidance_unlock(lock, true);
#endif

    return;
}
