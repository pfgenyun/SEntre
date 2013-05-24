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


OBJ = entre.o top_level.o global.o binary.o basicblock.o \
	  codecache.o function.o stack.o got.o context_switch.o \
	  isa.o in_code.o make_new_function.o control_trans.o redirect.o \
	  trace.o OOprofile.o bb_freq.o share_app.o
SOURCE = entre.c top_level.c global.c binary.c basicblock.c \
	 codecache.c function.c stack.c got.c context_switch.c \
	 isa.c in_code.c make_new_function.c control_trans.c redirect.c \
	 trace.c OOprofile.c bb_freq.c share_app.c

CC = gcc
C_FLAG = -g -O0 -fPIC -shared 
LINK_FLAG = -ldl 

#D_FLAG = -DDEBUG -DDUMP_FUNC -DDUMP_BB -DDUMP_CONTEXT -DDUMP_DIRTY_CALL -DDEBUG_REACH -DMAP
#D_FLAG = -DDEBUG -DDUMP_FUNC -DDUMP_BB -DDEBUG_REACH
#D_FLAG = -DDEBUG -DDUMP_BB -DDEBUG_REACH
#D_FLAG = -DDUMP_BB
#D_FLAG = -DDUMP_DIRTY_CALL
#D_FLAG = -DDEBUG_REACH -DDEBUG 
D_FLAG = -DDEBUG -DMAP -DDUMP_DIRTY_CALL
#D_FLAG = -DDEBUG_REACH
#D_FLAG = 


#TOOL_FLAG = -DTRACE
#TOOL_FLAG = -DOOprofile
#TOOL_FLAG = -DBB_FREQ -DDEBUG
#TOOL_FLAG = -DBB_FREQ
TOOL_FLAG = 

OBJDIR = ../.lib/
LIBDIR = ../.lib/

#$(OBJ) : $(SOURCE)
#	$(CC) ${C_FLAG}  $(SOURCE) -c

ALL:
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} entre.c                -c -o  ${OBJDIR}entre.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} top_level.c            -c -o  ${OBJDIR}top_level.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} global.c               -c -o  ${OBJDIR}global.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} binary.c               -c -o  ${OBJDIR}binary.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} basicblock.c           -c -o  ${OBJDIR}basicblock.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} codecache.c            -c -o  ${OBJDIR}codecache.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} function.c             -c -o  ${OBJDIR}function.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} stack.c                -c -o  ${OBJDIR}stack.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} got.c                  -c -o  ${OBJDIR}got.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} isa.c                  -c -o  ${OBJDIR}isa.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} in_code.c              -c -o  ${OBJDIR}in_code.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} make_new_function.c    -c -o  ${OBJDIR}make_new_function.o;		\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} control_trans.c        -c -o  ${OBJDIR}control_trans.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} context_switch.c       -c -o  ${OBJDIR}context_switch.o;			\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} redirect.c             -c -o  ${OBJDIR}redirect.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} trace.c                -c -o  ${OBJDIR}trace.o;					\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} OOprofile.c            -c -o  ${OBJDIR}OOprofile.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} bb_freq.c              -c -o  ${OBJDIR}bb_freq.o;				\
	$(CC) ${C_FLAG} ${D_FLAG} ${TOOL_FLAG} share_app.c            -c -o  ${OBJDIR}share_app.o;				\
															\
	cd ${OBJDIR};											\
	${CC} ${C_FLAG} ${LINK_FLAG}  -o sentre.so $(OBJ);		\
	cd -;													

	
clean :
	-rm -f ${OBJDIR}*.o

distclean:
	-rm -f ${LIBDIR}*.so ${OBJDIR}*.o

