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

#endif
