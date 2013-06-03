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

/**************************************************************************** 
  file "arch_exports.h" -- mips-specific exported declarations
  References: 
    <<see mips run>> second version
 ***************************************************************************/

#ifndef ARCH_EXPORTS_H
#define ARCH_EXPORTS_H 

#define atomic_swap(v, new)    xchg(v, new)

#define xchg(ptr,x)                         \
  ({                                    \
     __typeof__(*(ptr)) _x_ = (x);                  \
     (__typeof__(*(ptr))) __xchg((ptr), (unsigned long)_x_,     \
                 sizeof(*(ptr)));           \
  })

static inline unsigned long __xchg_u32(volatile int * m, unsigned int val)
{
   unsigned int retval;    
   unsigned long dummy;

   __asm__ __volatile__(
        "   .set    mips3                   \n"
        "1: ll  %0, %3          # xchg_u32  \n"
        "   .set    mips0                   \n"
        "   move    %2, %z4                 \n"
        "   .set    mips3                   \n"
        "   sc  %2, %1                  \n"
        "   beqzl   %2, 1b                  \n"
        "   .set    mips0                   \n"
        : "=&r" (retval), "=m" (*m), "=&r" (dummy)
        : "R" (*m), "Jr" (val)
        : "memory");

   return retval;
}

static inline unsigned long __xchg_u64(volatile unsigned long * m, unsigned long val)
{
   unsigned long retval;
    unsigned long dummy;

   __asm__ __volatile__(
        "   .set    mips3                   \n"
        "1: lld %0, %3          # xchg_u64  \n"
        "   move    %2, %z4                 \n"
        "   scd %2, %1                  \n"
        "   beqzl   %2, 1b                  \n"
        "   .set    mips0                   \n"
        : "=&r" (retval), "=m" (*m), "=&r" (dummy)
        : "R" (*m), "Jr" (val)
        : "memory");

   return retval;
}

static inline unsigned long __xchg(volatile void * ptr, unsigned long x, int size)
{
    switch (size) {
    case 4:
        return __xchg_u32(ptr, x);
    case 8:
        return __xchg_u64(ptr, x);
    }

    return x;
}

#define smp_llsc_mb()   __asm__ __volatile__("": : :"memory")
#define cmpxchg(ptr, old, new)  __cmpxchg(ptr, old, new, smp_llsc_mb(), smp_llsc_mb())
#define atomic_compare_exchange_int(ptr, old, new) cmpxchg(ptr, old, new)

#define __cmpxchg_asm(ld, st, m, old, new)              \
({                                  \
    __typeof(*(m)) __ret;                       \
    __asm__ __volatile__(                   \
        "   .set    push                \n" \
        "   .set    noat                \n" \
        "   .set    mips3               \n" \
        "1: " ld "  %0, %2      # __cmpxchg_asm \n" \
        "   bne %0, %z3, 2f         \n" \
        "   .set    mips0               \n" \
        "   move    $1, %z4             \n" \
        "   .set    mips3               \n" \
        "   " st "  $1, %1              \n" \
        "   beqzl   $1, 1b              \n" \
        "2:                     \n" \
        "   .set    pop             \n" \
        : "=&r" (__ret), "=R" (*m)              \
        : "R" (*m), "Jr" (old), "Jr" (new)          \
        : "memory");                        \
    __ret;                              \
})

#define __cmpxchg(ptr, old, new, pre_barrier, post_barrier)     \
({                                  \
    __typeof__(ptr) __ptr = (ptr);                  \
    __typeof__(*(ptr)) __old = (old);               \
    __typeof__(*(ptr)) __new = (new);               \
    __typeof__(*(ptr)) __res = 0;                   \
                                    \
    pre_barrier;                            \
    switch (sizeof(*(__ptr))) {                 \
    case 4:                             \
        __res = __cmpxchg_asm("ll", "sc", __ptr, __old, __new); \
        break;                          \
    case 8:                             \
        if (sizeof(long) == 8) {                \
            __res = __cmpxchg_asm("lld", "scd", __ptr,  \
                       __old, __new);       \
            break;                      \
        }                           \
    default:                            \
        break;                          \
    }                               \
    post_barrier;                           \
    __res;                              \
})

#define ATOMIC_INC_int(var) atomic_add_return(1, (volatile int *)&(var))
#define ATOMIC_INC_int64(var) atomic64_add_return(1, (volatile long *)&(var))
#define ATOMIC_INC(type, var) ATOMIC_INC_##type(var)

static inline int atomic_add_return(int i, volatile int *v)
{
    int result, temp;

    __asm__ __volatile__(
    "   .set    mips3                   \n"
    "1: ll  %1, %2      # atomic_add_return \n"
    "   addu    %0, %1, %3              \n"
    "   sc  %0, %2                  \n"
    "   beqzl   %0, 1b                  \n"
    "   addu    %0, %1, %3              \n"
    "   .set    mips0                   \n"
    : "=&r" (result), "=&r" (temp), "=m" (*v)
    : "Ir" (i), "m" (*v)
    : "memory");

    return result;
}

static inline long atomic64_add_return(long i, volatile long *v)
{
    long result, temp;

    __asm__ __volatile__(
    "   .set    mips3                   \n"
    "1: lld %1, %2      # atomic64_add_return   \n"
    "   daddu   %0, %1, %3              \n"
    "   scd %0, %2                  \n"
    "   beqzl   %0, 1b                  \n"
    "   daddu   %0, %1, %3              \n"
    "   .set    mips0                   \n"
    : "=&r" (result), "=&r" (temp), "=m" (*v)
    : "Ir" (i), "m" (*v)
    : "memory");

    return result;
}

#define ATOMIC_DEC_int(var) atomic_sub_return(1, (volatile int *)&(var))
#define ATOMIC_DEC_int64(var) atomic64_sub_return(1, (volatile long *)&(var))
#define ATOMIC_DEC(type, var) ATOMIC_DEC_##type(var)

static inline int atomic_sub_return(int i, volatile int *v)
{
    int result, temp;

    __asm__ __volatile__(
    "   .set    mips3                   \n"
    "1: ll  %1, %2      # atomic_sub_return \n"
    "   subu    %0, %1, %3              \n"
    "   sc  %0, %2                  \n"
    "   beqzl   %0, 1b                  \n"
    "   subu    %0, %1, %3              \n"
    "   .set    mips0                   \n"
    : "=&r" (result), "=&r" (temp), "=m" (*v)
    : "Ir" (i), "m" (*v)
    : "memory");

    return result;
}

static inline long atomic64_sub_return(long i, volatile long *v)
{
    long result, temp;

    __asm__ __volatile__(
    "   .set    mips3                   \n"
    "1: lld %1, %2      # atomic64_sub_return   \n"
    "   dsubu   %0, %1, %3              \n"
    "   scd %0, %2                  \n"
    "   beqzl   %0, 1b                  \n"
    "   dsubu   %0, %1, %3              \n"
    "   .set    mips0                   \n"
    : "=&r" (result), "=&r" (temp), "=m" (*v)
    : "Ir" (i), "m" (*v)
    : "memory");
    return result;
}

#define SPINLOCK_PAUSE()	__asm__ __volatile__("": : :"memory")

/* Atomically increments *var by 1
 * Returns true if the resulting value is zero, otherwise returns false
 */ 
static inline bool atomic_inc_and_test(volatile int *var)
{
	return (ATOMIC_INC(int, *(var)) == 0);
}

/* Atomically decrements *var by 1
 * Returns true if the initial value was zero, otherwise returns false
 */ 
static inline bool atomic_dec_and_test(volatile int *var)
{
	return (ATOMIC_DEC(int, *(var)) == -1);
}

/* Atomically decrements *var by 1
 * Returns true if the resulting value is zero, otherwise returns false
 */ 
static inline bool atomic_dec_becomes_zero(volatile int *var)
{
	return (ATOMIC_DEC(int, *(var)) == 0);
}

#endif
