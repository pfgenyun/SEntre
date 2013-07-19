/* SEntre_api_begin */
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


#ifndef UTILS_H
#define UTILS_H

#ifdef API_MODE
#include "utils.h"
#endif

/* SEntre_api_end */
//#include "global.h"

/**************************************************************************************/
/**************************************************************************************/

#ifdef assert
# undef assert
#endif
/* avoid mistake of lower-case assert */
#define assert assert_no_good_use_ASSERT_instead


/**************************************************************************************/
/**************************************************************************************/

#ifdef DEBUG
# ifdef INTERNAL
/* cast to void to avoid gcc warning "statement with no effect" when used as
 * a statement and x is a compile-time false
 * FIXME: cl debug build allocates a local for each ?:, so if this gets
 * unrolled in some optionsx or other expansion we could have stack problems!
 */
#   define ASSERT(x) \
        ((void)((!(x)) ? (internal_error(__FILE__, __LINE__, #x), 0) : 0))
/* make type void to avoid gcc 4.1 warnings about "value computed is not used"
 * (case 7851).  can also use statement expr ({;}) but only w/ gcc, not w/ cl.
 */
#   define ASSERT_MESSAGE(msg, x) ((!(x)) ? \
        (internal_error(msg " @" __FILE__, __LINE__, #x), (void)0) : (void)0)
# else 
/* cast to void to avoid gcc warning "statement with no effect" */
#   define ASSERT(x) \
        ((void)((!(x)) ? (internal_error(__FILE__, __LINE__, ""), 0) : 0))
#   define ASSERT_MESSAGE(msg, x) ((void)((!(x)) ? (internal_error(__FILE__, __LINE__, ""), 0) : 0))
# endif /* INTERNAL */
#else
# define ASSERT(x)         ((void) 0)
# define ASSERT_MESSAGE(msg, x) ASSERT(x)
#endif /* DEBUG */

/**************************************************************************************/

#if defined(INTERNAL) || defined(DEBUG)
void internal_error(char *file, int line, char *expr);
bool ignore_assert(const char *assert_file_line, const char *expr);
#endif

/**************************************************************************************/
/**************************************************************************************/

/* thread synchronization */
#define LOCK_FREE_STATE -1     /* allows a quick >=0 test for contention */
#define LOCK_SET_STATE (LOCK_FREE_STATE + 1)  /* set when requested by a single thread */
/* any value greater than LOCK_SET_STATE means multiple threads requested the lock */

typedef void * contention_event_t;
#define CONTENTION_EVENT_NOT_CREATED ((contention_event_t)0)

typedef struct _mutex_t {
    volatile int lock_requests; /* number of threads requesting this lock minus 1 */
    /* a value greater than LOCK_FREE_STATE means the lock has been requested */
    contention_event_t contended_event; /* handle to event object to wait on when contended */
#ifdef DEADLOCK_AVOIDANCE
    /* These fields are initialized with the INIT_LOCK_NO_TYPE macro */
    char *    name;             /* set to variable lock name and location */
    /* We flag as a violation if a lock with rank numerically smaller
     * or equal to the rank of a lock already held by the owning thread is acquired
     */
    uint      rank;             /* sets rank order in which this lock can be set */
    thread_id_t owner;            /* TID of owner (reusable, not available before initialization) */
    struct _mutex_t *prev_owned_lock; /* linked list of thread owned locks */
    uint count_times_acquired;  /* count total times this lock was acquired */
    uint count_times_contended; /* count total times this lock was contended upon */
    uint count_times_spin_pause; /* count total times this lock was contended in a spin pause loop */
    uint max_contended_requests;/* maximum number of simultaneous requests when contended */
    uint count_times_spin_only; /* count times contended but grabbed after spinning without yielding */
    /* we need to register all locks in the process to be able to dump regular statistics */
    /* linked list of all live locks (for all threads), another ad hoc double linked circular list */
    struct _mutex_t *prev_process_lock;
    struct _mutex_t *next_process_lock;
    /* TODO: we should also add cycles spent while holding the lock, KSTATS-like */
#endif /* DEADLOCK_AVOIDANCE */
    /* Any new field needs to be initialized with INIT_LOCK_NO_TYPE */
} mutex_t;

/* A spin_mutex_t is the same thing as a mutex_t (and all utils.c users use it as
 * such).  It exists only to enforce type separation outside of utils.c which
 * is why we can't simply do a typedef mutex_t spin_mutex_t. */
typedef struct _spin_mutex_t {
    mutex_t lock;
} spin_mutex_t;

/* perhaps for DEBUG all locks should record owner? */
typedef struct _recursive_lock_t {
    mutex_t lock;
    /* ASSUMPTION: reading owner field is atomic!
     * Thus must allocate this statically (compiler should 4-byte-align
     * this field, which is good enough) or align it manually!
     * FIXME: provide creation routine that does that for non-static locks
     */
    thread_id_t owner;
    uint count;
} recursive_lock_t;

typedef struct _read_write_lock_t {
    mutex_t lock;
    /* FIXME: could be merged w/ lock->state if want to get more sophisticated...
     * we could use the lock->state as a 32-bit counter, incremented 
     * by readers, and with the MSB bit (sign) set by writers 
     */
    volatile int num_readers;
    /* we store the writer so that writers can be readers */
    thread_id_t writer;
    volatile int num_pending_readers;       /* readers that have contended with a writer */
    contention_event_t writer_waiting_readers; /* event object for writer to wait on */
    contention_event_t readers_waiting_writer; /* event object for readers to wait on */
    /* make sure to update the two INIT_READWRITE_LOCK cases if you add new fields  */
} read_write_lock_t;

/* Ignore the arguments */
#  define INIT_LOCK_NO_TYPE(name, rank) {LOCK_FREE_STATE, CONTENTION_EVENT_NOT_CREATED}

/* FIXME: gcc 4.1.1 complains "initializer element is not constant"
 * if we have our old (x) here; presumably some older gcc needed it;
 * once sure nobody does let's remove this define altogether.
 */
#  define STRUCTURE_TYPE(x)

#define EXPANDSTR(x) #x
#define STRINGIFY(x) EXPANDSTR(x)

#define INIT_LOCK_FREE(lock) STRUCTURE_TYPE(mutex_t) INIT_LOCK_NO_TYPE( \
       #lock "(mutex)" "@" __FILE__ ":" STRINGIFY(__LINE__),          \
       LOCK_RANK(lock))

#define ASSIGN_INIT_LOCK_FREE(var, lock) do {                           \
     mutex_t initializer_##lock = STRUCTURE_TYPE(mutex_t) INIT_LOCK_NO_TYPE(\
            #lock "(mutex)" "@" __FILE__ ":" STRINGIFY(__LINE__),       \
                                                 LOCK_RANK(lock));      \
     var = initializer_##lock;                                          \
   } while (0)

#define ASSIGN_INIT_SPINMUTEX_FREE(var, spinmutex) \
    ASSIGN_INIT_LOCK_FREE((var).lock, spinmutex)

#define INIT_RECURSIVE_LOCK(lock) STRUCTURE_TYPE(recursive_lock_t) {       \
     INIT_LOCK_NO_TYPE(                                                 \
       #lock "(recursive)" "@" __FILE__ ":" STRINGIFY(__LINE__) ,       \
       LOCK_RANK(lock)),                                                \
     INVALID_THREAD_ID, 0                                               \
   }

#define INIT_READWRITE_LOCK(lock) STRUCTURE_TYPE(read_write_lock_t) {       \
     INIT_LOCK_NO_TYPE(                                                 \
       #lock "(readwrite)" "@" __FILE__ ":" STRINGIFY(__LINE__) ,       \
       LOCK_RANK(lock)),                                                \
       0, INVALID_THREAD_ID,                                            \
       0,                                                               \
       CONTENTION_EVENT_NOT_CREATED, CONTENTION_EVENT_NOT_CREATED       \
   }
#define INIT_READWRITE_LOCK(lock) STRUCTURE_TYPE(read_write_lock_t) {       \
     INIT_LOCK_NO_TYPE(                                                 \
       #lock "(readwrite)" "@" __FILE__ ":" STRINGIFY(__LINE__) ,       \
       LOCK_RANK(lock)),                                                \
       0, INVALID_THREAD_ID,                                            \
       0,                                                               \
       CONTENTION_EVENT_NOT_CREATED, CONTENTION_EVENT_NOT_CREATED       \
   }

#define ASSIGN_INIT_READWRITE_LOCK_FREE(var, lock) do {                 \
     read_write_lock_t initializer_##lock = STRUCTURE_TYPE(read_write_lock_t)   \
      {INIT_LOCK_NO_TYPE(                                               \
            #lock "(readwrite)" "@" __FILE__ ":" STRINGIFY(__LINE__),   \
                                                 LOCK_RANK(lock)),      \
       0, INVALID_THREAD_ID,                                            \
       0,                                                               \
       CONTENTION_EVENT_NOT_CREATED, CONTENTION_EVENT_NOT_CREATED       \
      };                                                                \
     var = initializer_##lock;                                          \
   } while (0)

#define ASSIGN_INIT_RECURSIVE_LOCK_FREE(var, lock) do {                 \
     recursive_lock_t initializer_##lock = STRUCTURE_TYPE(recursive_lock_t)   \
      {INIT_LOCK_NO_TYPE(                                               \
            #lock "(recursive)" "@" __FILE__ ":" STRINGIFY(__LINE__),   \
                                                 LOCK_RANK(lock)),      \
       INVALID_THREAD_ID, 0};                                           \
     var = initializer_##lock;                                          \
   } while (0)

#define INIT_SPINLOCK_FREE(lock) STRUCTURE_TYPE(mutex_t) {SPINLOCK_FREE_STATE, }

/* in order to use parallel names to the above INIT_*LOCK routines */
#define DELETE_LOCK(lock) mutex_delete(&lock)
#define DELETE_SPINMUTEX(spinmutex) spinmutex_delete(&spinmutex)
#define DELETE_RECURSIVE_LOCK(rec_lock) mutex_delete(&(rec_lock).lock)
#define DELETE_READWRITE_LOCK(rwlock) mutex_delete(&(rwlock).lock)

/* mutexes need to release any kernel objects that were created */
void mutex_delete(mutex_t *lock);

/* SEntre_api_begin */

/**************************************************************************
 * basic synchronization functions.
 *************************************************************************/
void mutex_lock(mutex_t *mutex);
bool mutex_trylock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);
/* SEntre_api_end */
void mutex_fork_reset(mutex_t *mutex);

/* spinmutex synchronization */
bool spinmutex_trylock(spin_mutex_t *spin_lock);
void spinmutex_lock(spin_mutex_t *spin_lock);
void spinmutex_lock_no_yield(spin_mutex_t *spin_lock);
void spinmutex_unlock(spin_mutex_t *spin_lock);
void spinmutex_delete(spin_mutex_t *spin_lock);

/* tests if a lock is held, but doesn't grab it */
/* note that this is not a synchronizing function, its intended uses are :
 * 1. for synch code to guarantee that a thread it has suspened isn't holding
 * a lock (note that a return of true doesn't mean that the suspended thread 
 * is holding the lock, could be some other thread)
 * 2. for when you want to assert that you hold a lock, while you can't 
 * actually do that, you can assert with this function that the lock is held
 * by someone
 * 3. read_{un,}lock use this function to check the state of write lock mutex
 */
static inline bool
mutex_testlock(mutex_t *lock)
{
    return lock->lock_requests > LOCK_FREE_STATE;
}

/* SEntre_api_begin */

/**************************************************************************
 * A recursive lock can be taken more than once by the owning thread.
 *************************************************************************/
void acquire_recursive_lock(recursive_lock_t *lock);
bool try_recursive_lock(recursive_lock_t *lock);
void release_recursive_lock(recursive_lock_t *lock);
/* SEntre_api_end */
bool self_owns_recursive_lock(recursive_lock_t *lock);

/* SEntre_api_begin */

/**************************************************************************
 * A read write lock allows multiple readers or alternatively a single 
 * writer.
 *************************************************************************/
void read_lock(read_write_lock_t *rw);
void write_lock(read_write_lock_t *rw);
bool write_trylock(read_write_lock_t *rw);
void read_unlock(read_write_lock_t *rw);
void write_unlock(read_write_lock_t *rw);
/* SEntre_api_end */
bool self_owns_write_lock(read_write_lock_t *rw);

/* test whether locks are held at all */
#define WRITE_LOCK_HELD(rw) (mutex_testlock(&(rw)->lock) && ((rw)->num_readers == 0))
#define READ_LOCK_HELD(rw) ((rw)->num_readers > 0)

/**************************************************************************************/
/**************************************************************************************/
/* FIXME: no way to tell if current thread is one of the readers */
#define ASSERT_OWN_READ_LOCK(pred, rw) \
    ASSERT(!(pred) || READ_LOCK_HELD(rw))
#define READWRITE_LOCK_HELD(rw) (READ_LOCK_HELD(rw) || self_owns_write_lock(rw))
#define ASSERT_OWN_READWRITE_LOCK(pred, rw) \
    ASSERT(!(pred) || READWRITE_LOCK_HELD(rw))
#define ASSERT_OWN_RECURSIVE_LOCK(pred, l) \
    ASSERT(!(pred) || self_owns_recursive_lock(l))



/* SEntre_api_begin */

#endif
/* SEntre_api_end */

