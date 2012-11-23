
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


/*
 * utils.c - miscellaneous utilities
 */

#include "global.h"
#include "utils.h"

/**************************************************************************************/
/**************************************************************************************/
#if defined(INTERNAL) || defined(DEBUG)
/* checks whether an assert statement should be ignored, 
 * produces a warning if so and returns true,
 * otherwise returns false
 */

void internal_error(char *file, int line, char *expr)
{
    /* need to be fix */
}

#endif


/**************************************************************************************/
/**************************************************************************************/

#ifdef DEADLOCK_AVOIDANCE

enum {LOCK_NOT_OWNABLE, LOCK_OWNABLE};

void
deadlock_avoidance_unlock(mutex_t *lock, bool ownable)
{
    /* need to be fix */ 
}
#define DEADLOCK_AVOIDANCE_LOCK(lock, acquired, ownable) deadlock_avoidance_lock(lock, acquired, ownable) 
#define DEADLOCK_AVOIDANCE_UNLOCK(lock, ownable) deadlock_avoidance_unlock(lock, ownable)
#else
#  define DEADLOCK_AVOIDANCE_LOCK(lock, acquired, ownable) /* do nothing */
#  define DEADLOCK_AVOIDANCE_UNLOCK(lock, ownable) /* do nothing */
#endif /* DEADLOCK_AVOIDANCE */


/**************************************************************************************/
/**************************************************************************************/

/* Read write locks */
/* A read write lock allows multiple readers or alternatively a single writer */

/* We're keeping here an older implementation under
   INTERNAL_OPTION(spin_yield_rwlock) that spins on the contention
   path.  In the Attic we also have the initial naive implementation
   wrapping mutex_t'es !INTERNAL_OPTION(fast_rwlock).
*/

/* 
   FIXME: Since we are using multiple words to contain the state,
   we still have to keep looping on contention events.

   We need to switch to using a single variable for this but for now
   let's first put all pieces of the kernel objects support together.

   PLAN:  All state should be in one 32bit word.
   Then we need one atomic operation that decrements readers and tells us:
   1) whether there was a writer (e.g. MSB set)
   2) whether this was the last reader (e.g. 0 in all other bits)
   Only when 1) & 2) are true (e.g. 0x80000000) we need to notify the writer.
   Think about using XADD: atomic_add_exchange(state, -1)
*/
/* FIXME: See /usr/src/linux-2.4/include/asm-mips/rwlock.h,
   spinlock.h and /usr/src/linux-2.4/arch/mips/kernel/semaphore.c
   for the Linux kernel implementation on MIPS.
 */

/* Currently we are using kernel objects to block on contention paths.
   Writers are blocked from each other at the mutex_t, and are notified
   by previous readers by an auto event.  Readers, of course, can have
   the lock simultaneously, but block on a previous writer - note also
   on an auto event.  Broadcasting to all readers is done by
   explicitly waking up each by the previous one, while the writer
   continues execution.  There is no fairness to the readers that are
   blocked vs any new readers that will grab the lock immediately, and
   for that matter vs any new writers.
    
   FIXME: Keep in mind that a successful wait on the kernel events in read
   locks should not be used as a guarantee that the current thread can
   proceed with a granted request.  We should rather keep looping to
   verify that we are back on the fast path.

   Due to the two reasons above we still have unbound loops in the
   rwlock primitives. It also lets the Linux implementation just yield.  
*/

void read_lock(read_write_lock_t *rw)
{

    /* wait for writer here if lock is held 
     * FIXME: generalize DEADLOCK_AVOIDANCE to both detect
     * order violations and gather contention stats for
     * this mutex-less synch
     */
    if (INTERNAL_OPTION(spin_yield_rwlock))
    {
        do 
        {
            while(mutex_testlock(&rw->lock))
            {
                /* contended read */
                /* am I the writer?
                 * ASSUMPTION: reading field is atomic 
                 * For linux get_thread_id() is expensive -- we
                 * should either address that through special handling
                 * of native and new thread cases, or switch this
                 * routine to pass in dcontext and use that.
                 * Update: linux get_thread_id() now calls get_tls_thread_id()
                 * and avoids the syscall (xref PR 473640).
                 * FIXME: we could also reorganize this check so that it is done only once
                 * instead of in the loop body but it doesn't seem wortwhile
                 */
                if (rw->writer == get_thread_id())
                {
                    
                    /* we would share the code below but we do not want
                     * the deadlock avoidance to consider this an acquire
                     */
                    ATOMIC_INC(int, rw->num_readers);
                    return;
                }
                DEADLOCK_AVOIDANCE_LOCK(&rw->lock, false, LOCK_NOT_OWNABLE);
                /* FIXME: last places where we yield instead of wait */
                thread_yield();
            }
            ATOMIC_INC(int, rw->num_readers);
            if (!imutex_testlock(&rw->lock))
                break;	/* do-while*/
            /* else race with write, must try again */
            ATOMIC_DEC(int, rw->num_readers);
        }while(true);
        DEADLOCK_AVOIDANCE_LOCK(&rw->lock, true, LOCK_NOT_OWNABLE);
        return;
    }


    /* event based notification, yet still need to loop */
    do 
    {
        while (mutex_testlock(&rw->lock)) 
        {
            /* contended read */
            /* am I the writer?
             * ASSUMPTION: reading field is atomic 
             * For linux get_thread_id() is expensive -- we
             * should either address that through special handling
             * of native and new thread cases, or switch this
             * routine to pass in dcontext and use that.
             * Update: linux get_thread_id() now calls get_tls_thread_id()
             * and avoids the syscall (xref PR 473640).
             */
            if (rw->writer == get_thread_id()) 
            {
                /* we would share the code below but we do not want
                 * the deadlock avoidance to consider this an acquire
                 */
                /* we also have to do this check on the read_unlock path  */
                ATOMIC_INC(int, rw->num_readers);
                return;
            }
            DEADLOCK_AVOIDANCE_LOCK(&rw->lock, false, LOCK_NOT_OWNABLE);

            ATOMIC_INC(int, rw->num_pending_readers);
            /* if we get interrupted before we have incremented this counter? 
               Then no signal will be send our way, so we shouldn't be waiting then
            */
            if (mutex_testlock(&rw->lock)) 
            {
                /* still holding up */
                rwlock_wait_contended_reader(rw);
            } 
            else 
            {
                /* otherwise race with writer */
                /* after the write lock is released pending readers
                   should no longer wait since no one will wake them up */
                /* no need to pause */
            }
            /* Even if we didn't wait another reader may be waiting for notification */
            if (!atomic_dec_becomes_zero(&rw->num_pending_readers)) 
            {
                /* If we were not the last pending reader,
                   we need to notify another waiting one so that 
                   it can get out of the contention path.
                */
                rwlock_notify_readers(rw);
                /* Keep in mind that here we don't guarantee that after blocking
                   we have an automatic right to claim the lock.
                */ 
            }
        }
        /* fast path */
        ATOMIC_INC(int, rw->num_readers);
        if (!mutex_testlock(&rw->lock))
            break;
        /* else, race with writer, must try again */
        /* FIXME: need to get num_readers and the mutex in one place,
           or otherwise add a mutex grabbed by readers for the above
           test.
        */
        ATOMIC_DEC(int, rw->num_readers);
        /* What if a writer thought that this reader has
         already taken turn - and will then wait thinking this guy has
         grabbed the read lock first?  For now we'll have to wake up
         the writer to retry even if it spuriously wakes up the next writer.
        */
        // FIXME: we need to do only when num_readers has become zero,
        // but it is OK for now as this won't usually happen
        rwlock_notify_writer(rw); /* --ok since writers still have to loop */
        /* hint we are spinning */
        SPINLOCK_PAUSE();
    } while (true);

    DEADLOCK_AVOIDANCE_LOCK(&rw->lock, true, LOCK_NOT_OWNABLE);
}

void read_unlock(read_write_lock_t *rw)
{
    if (INTERNAL_OPTION(spin_yield_rwlock))
    {
        ATOMIC_DEC(int, rw->num_readers);
        DEADLOCK_AVOIDANCE_UNLOCK(&rw->lock, LOCK_NOT_OWNABLE);
        return;
    }

    /* if we were the last reader to hold the lock, (i.e. final value is 0) 
       we may need to notify a waiting writer */

    /* unfortunately even on the hot path (of a single reader) we have
       to check if the writer is in fact waiting.  Even though this is
       not atomic we don't need to loop here - write_lock() will loop.
    */
    if (atomic_dec_becomes_zero(&rw->num_readers)) 
    {
        /* if the writer is waiting it definitely needs to hold the mutex */
        if (mutex_testlock(&rw->lock)) 
        {
            /* test that it was not this thread owning both write and read lock */
            if (rw->writer != get_thread_id()) 
            {
                /* we're assuming the writer has been forced to wait,
                   but since we can't tell whether it did indeed wait this 
                   notify may leave signaled the event for the next turn

                   If the writer has grabbed the mutex and checked
                   when num_readers==0 and has gone assuming to be the
                   rwlock owner.  In that case the above
                   rwlock_notify_writer will give the wrong signal to
                   the next writer.  
                   --ok since writers still have to loop 
                */
                rwlock_notify_writer(rw);
            }
        }
    }

    DEADLOCK_AVOIDANCE_UNLOCK(&rw->lock, LOCK_NOT_OWNABLE);
}


void write_lock(read_write_lock_t *rw)
{
    /* we do not follow the pattern of having lock call trylock in
     * a loop because that would be unfair to writers -- first guy
     * in this implementation gets to write
     */
    if (INTERNAL_OPTION(spin_yield_rwlock)) 
    {
        mutex_lock(&rw->lock);
        while (rw->num_readers > 0) 
        {
            /* contended write */
            DEADLOCK_AVOIDANCE_LOCK(&rw->lock, false, LOCK_NOT_OWNABLE);
            /* FIXME: last places where we yield instead of wait */
            thread_yield();
        }
        rw->writer = get_thread_id();
        return;
    }

    /* the same as spin_yield_rwlock pengfei */
    mutex_lock(&rw->lock);
    /* We still do this in a loop, since the event signal doesn't guarantee 
       that num_readers is 0 when unblocked. 
     */
    while (rw->num_readers > 0) 
    {
        /* contended write */
        DEADLOCK_AVOIDANCE_LOCK(&rw->lock, false, LOCK_NOT_OWNABLE);
        rwlock_wait_contended_writer(rw);
    }
    rw->writer = get_thread_id();
}

void write_unlock(read_write_lock_t *rw)
{
#ifdef DEADLOCK_AVOIDANCE
    ASSERT(rw->writer == rw->lock.owner);
#endif
    rw->writer = INVALID_THREAD_ID;
    if (INTERNAL_OPTION(spin_yield_rwlock)) 
    {
        mutex_unlock(&rw->lock);
        return;
    }
    /* we need to signal all waiting readers (if any) that they can now go
       ahead.  No writer should be allowed to lock until all currently
       waiting readers are unblocked.
     */
    /* We first unlock so that any blocked readers can start making
       progress as soon as they are notified.  Further field
       accesses however have to be assumed unprotected.
    */
    mutex_unlock(&rw->lock);
    /* check whether any reader is currently waiting */
    if (rw->num_pending_readers > 0) 
    {
        /* after we've released the write lock, pending readers will no longer wait */
        rwlock_notify_readers(rw);
    }
}
