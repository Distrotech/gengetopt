# Copyright (C) 1999, 2000, 2001  Free Software Foundation, Inc.
#  
# This file is part of GNU gengetopt 
#
# GNU gengetopt is free software; you can redistribute it and/or modify 
# it under the terms of the GNU General Public License as published by 
# the Free Software Foundation; either version 2, or (at your option) 
# any later version. 
#
# GNU gengetopt is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
# Public License for more details. 
#
# You should have received a copy of the GNU General Public License along 
# with gengetopt; see the file COPYING. If not, write to the Free Software 
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. 

PROGNAME = $(top_builddir)/src/gengetopt$(EXEEXT)
MAKE_SAMPLES = $(MAKE) $(AM_MAKEFLAGS) $(EXTRA_PROGRAMS)
SAMPLES_STAMP = samples.stamp
GGO_FILES = $(srcdir)/sample1.ggo $(srcdir)/sample2.ggo 

# we don't have to link to anything
LIBS =

# check if we need to link with getopt.o and strdup.o
if NO_GETOPTLONG
GETOPTLONG_O = $(top_builddir)/src/getopt.o $(top_builddir)/src/getopt1.o
else
GETOPTLONG_O =
endif

if NO_STRDUP
STRDUP_O = $(top_builddir)/src/strdup.o
else
STRDUP_O =
endif

# man page
man_MANS = gengetopt.1

if NO_HELP2MAN
gengetopt.1: $(top_srcdir)/src/cmdline.ggo
	touch $@
else
gengetopt.1: $(top_srcdir)/src/cmdline.ggo
	$(HELP2MAN) $(PROGNAME) > $@
endif


EXTRA_PROGRAMS = sample1 sample2
sample1_SOURCES = cmdline1.c main1.cc
sample2_SOURCES = cmdline2.c main2.c

LDADD = $(GETOPTLONG_O) $(STRDUP_O)

INCLUDES = -I@top_srcdir@/src/

gengetoptdoc_DATA = gengetopt.html index.html 

gengetoptexamples_DATA = sample1.ggo sample2.ggo main1.cc main2.c \
                         cmdline1.c cmdline1.h cmdline2.c cmdline2.h

AM_MAKEINFOHTMLFLAGS=--no-split

info_TEXINFOS = gengetopt.texinfo

GENERATEDINFOS = cmdline1.h.texinfo main1.cc.texinfo test_conf_parser.c.texinfo \
test_conf_parser_ov2.c.texinfo help_output.texinfo \
multiple_example.c.texinfo \
test_multiple_parsers.c.texinfo

BUILT_SOURCES = $(GENERATEDINFOS)

RUNSOURCEHIGHLIGHT=$(SOURCEHIGHLIGHT) -f texinfo --style-file=texinfo.style --output-dir=$(top_builddir)/doc/

gengetopt.texinfo: $(GENERATEDINFOS)

if NO_SOURCEHIGHLIGHT
%.h.texinfo: %.h
	touch $@

%.cc.texinfo: %.cc
	touch $@

test_conf_parser.c.texinfo: $(top_srcdir)/tests/test_conf_parser.c
	cat $(top_srcdir)/tests/test_conf_parser.c | sed -f $(srcdir)/input.sed > $@

test_conf_parser_ov2.c.texinfo: $(top_srcdir)/tests/test_conf_parser_ov2.c
	cat $(top_srcdir)/tests/test_conf_parser_ov2.c | sed -f $(srcdir)/input.sed > $@

test_multiple_parsers.c.texinfo: $(top_srcdir)/tests/test_multiple_parsers.c
	cat $(top_srcdir)/tests/test_multiple_parsers.c | sed -f $(srcdir)/input.sed > $@

%.c.texinfo: %.c
	touch $@
else
%.h.texinfo: %.h
	$(RUNSOURCEHIGHLIGHT) $< 

%.cc.texinfo: %.cc
	$(RUNSOURCEHIGHLIGHT) $< 

test_conf_parser.c.texinfo: $(top_srcdir)/tests/test_conf_parser.c
	$(RUNSOURCEHIGHLIGHT) $(top_srcdir)/tests/test_conf_parser.c 

test_conf_parser_ov2.c.texinfo: $(top_srcdir)/tests/test_conf_parser_ov2.c
	$(RUNSOURCEHIGHLIGHT) $(top_srcdir)/tests/test_conf_parser_ov2.c

test_multiple_parsers.c.texinfo: $(top_srcdir)/tests/test_multiple_parsers.c
	$(RUNSOURCEHIGHLIGHT) $(top_srcdir)/tests/test_multiple_parsers.c

%.c.texinfo: %.c
	$(RUNSOURCEHIGHLIGHT) $< 
endif

help_output.texinfo: $(top_srcdir)/src/cmdline.ggo
	$(PROGNAME) --show-help -i $(top_srcdir)/src/cmdline.ggo --set-package="gengetopt" --set-version="" > $@

EXTRA_DIST = sample1.ggo sample2.ggo samples.stamp \
             cmdline1.c cmdline1.h cmdline2.c cmdline2.h \
             $(man_MANS) $(gengetoptdoc_DATA) cxxconfig.h \
             testdata \
             $(GENERATEDINFOS) \
             input.sed \
             multiple_example.c

cmdline1.h: cmdline1.c
cmdline1.c: sample1.ggo
	$(PROGNAME) -i $(srcdir)/sample1.ggo -Fcmdline1 --long-help -u

cmdline2.c: sample2.ggo
	$(PROGNAME) --input=$(srcdir)/sample2.ggo --func-name=my_cmdline_parser --file-name=cmdline2 --unamed-opts --no-handle-help --no-handle-version

cmdline1.o: cmdline1.c
	$(CC) $(DEFS) $(CFLAGS) $(DEFAULT_INCLUDES) $(INCLUDES) -c cmdline1.c

cmdline2.o: cmdline2.c
	$(CC) $(DEFS) $(CFLAGS) $(DEFAULT_INCLUDES) $(INCLUDES) -DMY_CMDLINE_PARSER_PACKAGE=\"sample2\" -DMY_CMDLINE_PARSER_VERSION=\"2.0\" -c cmdline2.c

# session for tests
RUN_SAMPLE1 = ./sample1$(EXEEXT) -i 10 --flag-opt cmdline?.c
RUN_SAMPLE1_1 = ./sample1$(EXEEXT) --help --int-opt -34
# the next one generates an error 'cause -i option is not given
RUN_SAMPLE1_2 = ./sample1$(EXEEXT) -F
RUN_SAMPLE2 = ./sample2$(EXEEXT) -i 10 -l 20
RUN_SAMPLE2_1 = ./sample2$(EXEEXT) --version
RUN_SAMPLE2_2 = ./sample2$(EXEEXT) --help

check-am: testdata
	rm -f test.out
	touch $(GGO_FILES)
	$(MAKE) $(AM_MAKEFLAGS) sample1$(EXEEXT) sample2$(EXEEXT)
	$(RUN_SAMPLE1) >> test.out && \
	$(RUN_SAMPLE1_1) >> test.out && \
	$(RUN_SAMPLE2) >> test.out || \
	$(RUN_SAMPLE1_2) 2>> test.out
	$(RUN_SAMPLE2_1) >> test.out 
	$(RUN_SAMPLE2_2) >> test.out 
	@echo expect no output from diff
	diff $(srcdir)/testdata test.out

testdata:
	rm -f testdata
	$(RUN_SAMPLE1) >> testdata
	$(RUN_SAMPLE1_1) >> testdata
	$(RUN_SAMPLE2) >> testdata || \
	$(RUN_SAMPLE1_2) 2>> testdata
	$(RUN_SAMPLE2_1) >> testdata
	$(RUN_SAMPLE2_2) >> testdata

# this is to build samples once gengetopt has changed
# this is for development only.
samples: $(SAMPLES_STAMP)
	$(MAKE) $(AM_MAKEFLAGS) $(EXTRA_PROGRAMS)
#	echo timestamp > $(SAMPLES_STAMP)

$(SAMPLES_STAMP): $(PROGNAME)
	touch $(GGO_FILES)
	echo timestamp > $(SAMPLES_STAMP)

clean_gen:
	rm -f $(GENERATEDINFOS)

CLEANFILES = $(EXTRA_PROGRAMS)

DISTCLEANFILES = cmdline1.h cmdline1.c cmdline2.h \
cmdline2.c test.out samples.stamp $(BUILT_SOURCES)

MAINTAINERCLEANFILES = cmdline1.c cmdline2.c cmdline1.h cmdline2.h \
                       $(SAMPLES_STAMP)
