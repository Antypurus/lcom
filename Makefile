# Makefile for lab5
COMPILER_TYPE= gnu
CC=gcc
PROG= proj
SRCS= proj.c vbe.c video_gr.c test5.c lmlib.h VideoCard.h vbe.h test5.h video_gr.h timer.c timer.h mouse.c mouse.h MS.h keyboard.h sprite.h sprite.c Projectile.h Projectile.c
CCFLAGS= -Wall
DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys
LDFLAGS+= -L .
MAN=
BINDIR?= /usr/sbin
.include <bsd.prog.mk>
.include <bsd.gcc.mk>