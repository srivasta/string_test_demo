############################ -*- Mode: Makefile -*- ###########################
## Makefile<string_test> --- 
## Author           : Manoj Srivastava ( srivasta@glaurung.green-gryphon.com ) 
## Created On       : Thu Feb 20 12:46:26 2003
## Created On Node  : glaurung.green-gryphon.com
## Last Modified By : Manoj Srivastava
## Last Modified On : Thu Feb 27 17:49:38 2003
## Last Machine Used: ember.green-gryphon.com
## Update Count     : 26
## Status           : Unknown, Use with caution!
## HISTORY          : 
## Description      : $Id: Makefile,v 1.2 2003/02/21 12:05:34 srivasta Exp $
## 
## Copyright (C) 2003 Manoj Srivastava
## 
## This sample implementation of string functions is free software;
## you can redistribute it and/or modify it under the terms of the GNU
## General Public License as published by the Free Software
## Foundation; either version 2, or (at your option) any later
## version.
##
## This sample implementation of string functions is distributed in
## the hope that it will be useful, but WITHOUT ANY WARRANTY; without
## even the implied warranty of MERCHANTABILITY or FITNESS FOR A
## PARTICULAR PURPOSE.  See the GNU General Public License for more
## details.
##
## You should have received a copy of the GNU General Public License
## along with This sample implementation of string functions; see the
## file COPYING.  If not, write to the Free Software Foundation, Inc.,
## 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
##
###############################################################################

## The sources present in this directory
SRC=string_test.c Makefile Doxyfile COPYING

## Automatically extract the C files from the sources
CFILES+=$(patsubst %.l,%.yy.c,$(LEXFILES)) \
                 $(patsubst %.y,%.tab.c,$(YACCFILES)) \
                 $(filter %.c,$(SRC))

## If the C files are present, generate a list of OBJECTS automatically
ifneq ($(strip $(CFILES)),)
OBJECTS+=$(patsubst %.c,%.o,$(CFILES)) 
endif

## Debugging option for the compiler
CDEBUG+=-g

## @brief Optimizing options
COPTS=-pipe -O3 -g

## Warnings. You can never have too many warnings
CWARNS=-ansi -pedantic -Wall -W -Wtraditional -Wconversion -Wshadow \
       -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align \
       -Wwrite-strings -Waggregate-return -Wstrict-prototypes \
       -Wmissing-prototypes -Wmissing-declarations \
       -fshort-enums -fno-common -Dgets=DONT_USE_GETS -Dlint \
       -Wnested-externs -Winline

## Additional files we remove when cleaning
FILES_TO_CLEAN=stringtest stringtest.tag
DIRS_TO_CLEAN=html latex man

ifdef DO_DEBUG
CFLAGS+= $(CDEBUG) -DDEBUG
endif
ifneq ($(strip $(NO_OPTIMIZE)),)
CFLAGS+= $(COPTS)
endif
ifneq ($(strip $(DEBUG)),)
CFLAGS+= -DDEBUG=$(DEBUG)
endif
ifeq ($(strip $(NO_WARNS)),)
CFLAGS+= $(CWARNS)
endif


## Default target
all: stringtest

## The regression test suite for the library functions
stringtest: $(OBJECTS)
	$(REASON)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)


## Clean the files created during build
clean:
	rm -f  $(FILES_TO_CLEAN) 
	rm -fr  $(DIRS_TO_CLEAN) 
	rm -f core `find . \( -name '*.orig' -o -name '*.rej' -o \
          -name '*~' -o -name '*.bak' -o -name '#*#' -o \
          -name '.*.orig' -o -name '.*.rej' -o -name '.SUMS' -o \
          -size 0  -o -name '*.o' \) -print` TAGS


## Why some action is being taken
REASON= @if [ -f $@ ]; then \
 echo "====== making $(notdir $@) because of $(notdir $?) ======";\
 else \
   echo "====== making (creating) $(notdir $@) from $(notdir $?) ======"; \
 fi
