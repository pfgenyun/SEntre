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


#ifndef REG_H
#define REG_H

typedef enum
{
    REG_ZERO,	//0
    REG_AT,		//1
    REG_V0,		//2,3
    REG_V1,
    REG_A0,		//4-7
    REG_A1,
	REG_A2,
	REG_A3,
	REG_T0,		//8-15
	REG_T1,		
	REG_T2,		
	REG_T3,		
	REG_T4,		
	REG_T5,		
	REG_T6,		
	REG_T7,	
	REG_S0,		//16-23
	REG_S1,
	REG_S2,
	REG_S3,
	REG_S4,
	REG_S5,
	REG_S6,
	REG_S7,
    REG_T8,		//24,25
	REG_T9,	
	REG_K0,		//26,27
	REG_K1,
	REG_GP,		//28
	REG_SP,		//29
	REG_FP,		//30
	REG_RA		//31
}MIPS_REG;

#endif
