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


#ifndef OOPROFILE_H
#define OOPROFILE_H

void entre_OOprofile_init();
void entre_OOprofile_fini();
void entre_OOprofile_record(struct context * context);
void entre_func_begin_OOprofile(struct context * context);
void entre_func_end_OOprofile(struct context * context);

#define OPCONTROL_INIT		\
	"opcontrol  --init;opcontrol --no-vmlinux;opcontrol --event=MEM_READ:200;opcontrol --reset"

#define OPCONTROL_SETUP		\
	"opcontrol --start"

//#define OPCONTROL_REPORT	\
	"opcontrol --stop; opreport -l ./test6"

#define OPCONTROL_REPORT	\
	"opcontrol  --dump;opreport -l ./test"

#define OPCONTROL_FINI	\
	"opcontrol -h"

#endif

