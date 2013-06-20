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
	  trace.o OOprofile.o bb_freq.o utils.o options.o os.o share_app.o
SOURCE = entre.c top_level.c global.c binary.c basicblock.c \
	 codecache.c function.c stack.c got.c context_switch.c \
	 isa.c in_code.c make_new_function.c control_trans.c redirect.c \
	 trace.c OOprofile.c bb_freq.c utils.c options.c os.c share_app.c

CC = gcc
C_FLAG = -g -O0 -fPIC -shared 
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
#F_FLAG = -DMAP 
F_FLAG = 

#####Tool Flags
#TOOL_FLAG = -DTRACE
#TOOL_FLAG = -DOOprofile
#TOOL_FLAG = -DBB_FREQ -DDEBUG
TOOL_FLAG = -DBB_FREQ
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
	cp	*.h	${SRCDIR};			\
	cp	*.c	${SRCDIR};			\
	cp	lib/*	${SRCDIR};			\
	cp	linux/*	${SRCDIR};			\
	cp	mips/*	${SRCDIR};			\
							\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}utils.c                -c -o  ${OBJDIR}utils.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}options.c              -c -o  ${OBJDIR}options.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}os.c                   -c -o  ${OBJDIR}os.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${F_FLAG} ${TOOL_FLAG} ${SRCDIR}share_app.c            -c -o  ${OBJDIR}share_app.o;			\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o ${INSTALL_HOME}sentre.so $(OBJ);		\
	cd -;													

	
clean :
	-rm -f ${OBJDIR}*.o

distclean:
	-rm -f ${LIBDIR}*.so ${OBJDIR}*.o

check:
	
