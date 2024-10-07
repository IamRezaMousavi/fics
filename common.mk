# vars.mk  --  common vars

ROOT := ./
INCLUDE_DIR := $(ROOT)include/
TARGETS_DIR := $(ROOT)maketargets/
TGTS = fics fics_addplayer makerank


# options.mk

# Locations of the data, players and games directories.
FICS_HOME ?= .

PREFIX ?= .

CC ?= cc
CFLAGS = -O2 -Wall -g -pipe -std=c11 \
	-Wsign-compare \
	-Wstrict-prototypes

CXX ?= c++
CXXFLAGS = -O2 -Wall -g -pipe -std=c++17

# C preprocessor flags
CPPFLAGS = -D_DEFAULT_SOURCE=1

LDFLAGS =
LDLIBS = -lbsd -lcrypt
RM ?= @rm -f

E = @echo
Q = @

# addplayer
AP_LDFLAGS =
AP_LDLIBS = -lbsd -lcrypt

# makerank
MR_LDFLAGS =
MR_LDLIBS = -lbsd


# common.mk  --  common rules

.c.o:
	$(E) "  CC      " $@
	$(Q) $(CC) $(CFLAGS) -I $(INCLUDE_DIR) $(CPPFLAGS) -c -o $@ $<
.cpp.o:
	$(E) "  CXX     " $@
	$(Q) $(CXX) $(CXXFLAGS) -I $(INCLUDE_DIR) $(CPPFLAGS) -c -o $@ $<
