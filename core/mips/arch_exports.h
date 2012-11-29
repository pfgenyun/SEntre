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

/* need to fix up */
#define ATOMIC_INC_suffix(suffix, var) 		\
   __asm__ __volatile__(" " 			\
                        : "=m" (var) 		\
                        : 			\
                        : "memory")		
#define ATOMIC_INC_int(var) ATOMIC_INC_suffix("l", var)
#define ATOMIC_INC_int64(var) ATOMIC_INC_suffix("q", var)
#define ATOMIC_INC(type, var) ATOMIC_INC_##type(var)

/* need to fix up */
#define ATOMIC_DEC_suffix(suffix, var) 		\
   __asm__ __volatile__(" "			\
                        : "=m" (var) 		\
                        : 			\
                        : "memory")		
#define ATOMIC_DEC_int(var) ATOMIC_DEC_suffix("l", var)
#define ATOMIC_DEC_int64(var) ATOMIC_DEC_suffix("q", var)
#define ATOMIC_DEC(type, var) ATOMIC_DEC_##type(var)

/* need to fix up */
#define SPINLOCK_PAUSE() 

/* need to fix up */
# define SET_FLAG(cc, flag) __asm__ __volatile__("")
# define SET_IF_NOT_ZERO(flag) SET_FLAG(nz, flag)
# define SET_IF_NOT_LESS(flag) SET_FLAG(nl, flag)


/* Atomically increments *var by 1
 * Returns true if the resulting value is zero, otherwise returns false
 */ 
static inline bool atomic_inc_and_test(volatile int *var)
{
    unsigned char c;

    ATOMIC_INC(int, *var);
    /* flags should be set according to resulting value, now we convert that back to C */
    SET_IF_NOT_ZERO(c);
    /* FIXME: we add an extra memory reference to a local, 
       although we could put the return value in EAX ourselves */
    return c == 0;
}

/* Atomically decrements *var by 1
 * Returns true if the initial value was zero, otherwise returns false
 */ 
static inline bool atomic_dec_and_test(volatile int *var)
{
    unsigned char c;

    ATOMIC_DEC(int, *var);
    /* result should be set according to value before change, now we convert that back to C */
    SET_IF_NOT_LESS(c);
    /* FIXME: we add an extra memory reference to a local, 
       although we could put the return value in EAX ourselves */
    return c == 0;
}

/* Atomically decrements *var by 1
 * Returns true if the resulting value is zero, otherwise returns false
 */ 
static inline bool atomic_dec_becomes_zero(volatile int *var)
{
    unsigned char c;

    ATOMIC_DEC(int, *var);
    /* result should be set according to value after change, now we convert that back to C */
    SET_IF_NOT_ZERO(c);
    /* FIXME: we add an extra memory reference to a local, 
       although we could put the return value in EAX ourselves */
    return c == 0;
}

#endif
