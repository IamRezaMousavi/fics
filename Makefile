# Makefile for use with BSD make
# SPDX-FileCopyrightText: 2023 Markus Uhlin <maxxe@rpblc.net>
# SPDX-License-Identifier: ISC

# common rules
include common.mk

LDLIBS =
AP_LDLIBS =
MR_LDLIBS =

all: $(TGTS)

include FICS/build.mk


.PHONY: clean $(TGTS)

clean:
	$(E) "  CLEAN"
	$(RM) $(INCLUDE_DIR)ficspaths.h
	$(RM) $(OBJS)
	$(RM) $(AP_OBJS)
	$(RM) $(MR_OBJS)
	$(RM) $(TGTS)

