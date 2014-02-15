# ************************************************************
# * Copyright (c) 2010-present Peng Fei.  All rights reserved.
# ************************************************************/

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistribution and use in source and binary forms must authorized by
# Peng Fei.
#
# Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.

SHELL := /bin/bash

OBJ = entre.o top_level.o global.o binary.o basicblock.o \
	  codecache.o function.o stack.o got.o context_switch.o \
	  isa.o in_code.o make_new_function.o control_trans.o redirect.o \
	  trace.o OOprofile.o bb_freq.o utils.o options.o os.o share_app.o \
	  bb_num.o
SOURCE = entre.c top_level.c global.c binary.c basicblock.c \
	 codecache.c function.c stack.c got.c context_switch.c \
	 isa.c in_code.c make_new_function.c control_trans.c redirect.c \
	 trace.c OOprofile.c bb_freq.c utils.c options.c os.c share_app.c \
	 bb_num.c

MABI = 32
CC = gcc
C_FLAG = -g -O0 -fPIC -shared -mabi=$(MABI)
LINK_FLAG = -ldl 

##### Debug Flags
#D_FLAG = -DDEBUG -DDUMP_FUNC -DDUMP_BB -DDUMP_CONTEXT -DDUMP_DIRTY_CALL -DDEBUG_REACH
#D_FLAG = -DDEBUG -DDUMP_FUNC -DDUMP_BB
#D_FLAG = -DDUMP_BB
D_FLAG =

##### Function Flags 
##### for chrome don't define -DMAP
##### -DINSN_IN_DATE used for gdb, for large app, eg. GCC, don't define -DINSN_IN_DATE
#F_FLAG = -DMAP -DINSN_IN_DATE
FFLAG = -DMAP -DAPI_MODE
#FFLAG = -DMAP -DAPI_MODE -DOUT_SVG
#FFLAG = -DMAP -DAPI_MODE -DOUT_SVG -DOUT_TRACE_STACK
#FFLAG = -DMAP -DAPI_MODE -DOUT_SVG -DOUT_TRACE_HEAP
ifeq ($(MABI),64)
    F_FLAG = ${FFLAG} -DN64
endif
ifeq ($(MABI),n32)
    F_FLAG = ${FFLAG} -DN32
endif
ifeq ($(MABI),32)
    F_FLAG = ${FFLAG} -DO32
endif
#F_FLAG = 

#####Tool Flags
#TOOL_FLAG = -DTRACE
#TOOL_FLAG = -DOOprofile
#TOOL_FLAG = -DBB_FREQ -DDEBUG
#TOOL_FLAG = -DBB_FREQ
#TOOL_FLAG =
 
BUILD_HOME = ~/.SEntre/
INSTALL_HOME = ~/.SEntre/
SRCDIR = ${BUILD_HOME}src/
OBJDIR = ${BUILD_HOME}obj/
LIBDIR = ${INSTALL_HOME}lib/


#$(OBJ) : $(SOURCE)
#	$(CC) ${C_FLAG}  $(SOURCE) -c

ALL:
	rm -f ${SRCDIR}*
	if test -d $(BUILD_HOME); then			\
		echo "BUILD HOME:$(BUILD_HOME) exits!";		\
	else						\
		mkdir $(BUILD_HOME);			\
	fi;							
							\
	if test -d $(INSTALL_HOME); then		\
		echo "INSTALL HOME:$(INSTALL_HOME) exits!";	\
	else						\
		mkdir $(INSTALL_HOME);			\
	fi;							
							\
	if test -d $(SRCDIR); then			\
		echo "BUILD SRC:$(SRCDIR) exits!";		\
	else						\
		mkdir $(SRCDIR);			\
	fi;							
							\
	if test -d $(OBJDIR); then			\
		echo "BUILD OBJ:$(OBJDIR) exits!";		\
	else						\
		mkdir $(OBJDIR);			\
	fi;							
							\
	if test -d $(LIBDIR); then			\
		echo "INSTALL LIB:$(LIBDIR) exits!";		\
	else						\
		mkdir $(LIBDIR);			\
	fi;							
							\
	cp	../../core/*.h	${SRCDIR};			\
	cp	../include/*.h	${SRCDIR};			\
	cp	*.c	${SRCDIR};			\
	cp	../../core/*.c	${SRCDIR};			\
	cp	../../core/lib/*	${SRCDIR};			\
	cp	../../core/linux/*	${SRCDIR};			\
	cp	../../core/mips/*	${SRCDIR};			\
							\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}utils.c                -c -o  ${OBJDIR}utils.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}options.c              -c -o  ${OBJDIR}options.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}os.c                   -c -o  ${OBJDIR}os.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}share_app.c            -c -o  ${OBJDIR}share_app.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE ${SRCDIR}bb_num.c               -c -o  ${OBJDIR}bb_num.o;			\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o ${INSTALL_HOME}sentre_trace.so $(OBJ);		\
	cd -;													

	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}utils.c                -c -o  ${OBJDIR}utils.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}options.c              -c -o  ${OBJDIR}options.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}os.c                   -c -o  ${OBJDIR}os.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}share_app.c            -c -o  ${OBJDIR}share_app.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG ${SRCDIR}bb_num.c               -c -o  ${OBJDIR}bb_num.o;			\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o ${INSTALL_HOME}sentre_trace_out.so $(OBJ);		\
	cd -;													

	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}utils.c                -c -o  ${OBJDIR}utils.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}options.c              -c -o  ${OBJDIR}options.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}os.c                   -c -o  ${OBJDIR}os.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}share_app.c            -c -o  ${OBJDIR}share_app.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_STACK ${SRCDIR}bb_num.c               -c -o  ${OBJDIR}bb_num.o;			\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o ${INSTALL_HOME}sentre_trace_out_stack.so $(OBJ);		\
	cd -;													

	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}utils.c                -c -o  ${OBJDIR}utils.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}options.c              -c -o  ${OBJDIR}options.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}os.c                   -c -o  ${OBJDIR}os.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}share_app.c            -c -o  ${OBJDIR}share_app.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DTRACE -DOUT_SVG -DOUT_TRACE_HEAP ${SRCDIR}bb_num.c               -c -o  ${OBJDIR}bb_num.o;			\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o ${INSTALL_HOME}sentre_trace_out_heap.so $(OBJ);		\
	cd -;													

	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}utils.c                -c -o  ${OBJDIR}utils.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}options.c              -c -o  ${OBJDIR}options.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}os.c                   -c -o  ${OBJDIR}os.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}share_app.c            -c -o  ${OBJDIR}share_app.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ ${SRCDIR}bb_num.c               -c -o  ${OBJDIR}bb_num.o;			\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o ${INSTALL_HOME}sentre_bb.so $(OBJ);		\
	cd -;													
	
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}utils.c                -c -o  ${OBJDIR}utils.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}options.c              -c -o  ${OBJDIR}options.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}os.c                   -c -o  ${OBJDIR}os.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}share_app.c            -c -o  ${OBJDIR}share_app.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} -DBB_FREQ -DOUT_SVG ${SRCDIR}bb_num.c               -c -o  ${OBJDIR}bb_num.o;			\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o ${INSTALL_HOME}sentre_bb_out.so $(OBJ);		\
	cd -;													

clean :
	-rm -f ${OBJDIR}*.o

distclean:
	-rm -f ${LIBDIR}*.so ${OBJDIR}*.o

check:
	
