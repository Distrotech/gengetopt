# Copyright (C) 1999-2007  Free Software Foundation, Inc.
#  
# This file is part of GNU gengetopt 
#
# GNU gengetopt is free software; you can redistribute it and/or modify 
# it under the terms of the GNU General Public License as published by 
# the Free Software Foundation; either version 3, or (at your option) 
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


if NO_CROSSCOMPILING

# .ggonu is used in this test suite for command line parsers that have
# to be created without --unamed-opt

SUFFIXES = .ggo .ggonu .ggoconf .ggostr .err

# we do not generate the gengetopt version number in the output
# file so that the number does not disturb in diffing when changing
# gengetopt version
PROGNAME = $(top_builddir)/src/gengetopt$(EXEEXT) --gen-version

PROGNAMESHOWHELP = $(PROGNAME) --show-help --long-help
PROGNAMESHOWFULLHELP = $(PROGNAME) --show-full-help --long-help

PROGNAMESHOWHELPREQUIRED = $(PROGNAME) --show-help --long-help --show-required

GGO_COMPILE = $(PROGNAME) --input=$< --func-name=$*_parser --file-name=$*

.ggo.c:
	$(GGO_COMPILE) --unamed-opt --show-required

.ggonu.c:
	$(PROGNAME) --input $< --func-name $*_parser --file-name $*

.ggoconf.c:
	$(GGO_COMPILE) --unamed-opt="OTHER NAMES" --conf-parser --arg-struct-name="my_args_info" --no-handle-error

.ggostr.c:
	$(GGO_COMPILE) --unamed-opt="OTHER NAMES" --string-parser --arg-struct-name=$*_struct --include-getopt

.ggo.err:
	$(PROGNAME) --unamed-opt -i $< --file-name null 2> $@ || true

# INCLUDES is added to LDFLAGS because .ggo file are sources, and thus
# the .c files are passed to the linker, which also compiles, thus
# the include options should be passed to it as well
AM_LDFLAGS = $(DEFS) $(INCLUDES)

#LDADD = $(GETOPTLONG_O) $(STRDUP_O) -lefence

# these are for gnulib
AM_CPPFLAGS = -I$(top_srcdir)/gl -I$(top_builddir)/gl

LDADD = $(top_builddir)/gl/libgnu.la

EXPECT = 1

VALGRINDTESTS = no_strings no_multi_strings no_unamed no_optgiven.sh \
more_than_once.sh canonize-names \
no_prog_name \
default_values default_cmdline test_all_opts.sh \
test_all_opts_file_save.sh \
test_groups.sh \
test_conf_parser.sh test_conf_parser_ov.sh test_conf_parser_ov2.sh \
test_conf_parser_ov3.sh \
test_conf_parser_ov4.sh \
test_conf_parser_err.sh test_conf_parser_err_string.sh \
test_conf_parser_grp.sh \
test_conf_parser_save.sh \
test_multiple.sh \
test_multiple_err.sh \
test_sections.sh \
test_default_values.sh \
test_values.sh test_values_err.sh \
test_dep.sh \
test_multiple_parsers.sh \
test_sections_option_help \
test_all_opts_option_help \
test_groups_option_help

TESTS = $(VALGRINDTESTS) \
test_show_help.sh \
test_err.sh

check_PROGRAMS = no_strings no_multi_strings no_unamed no_optgiven \
no_optgiven2 more_than_once no_prog_name \
canonize-names default_values default_cmdline test_all_opts \
test_groups test_conf_parser test_conf_parser_ov \
test_conf_parser_ov2 \
test_conf_parser_ov3 \
test_conf_parser_ov4 \
test_conf_parser_file_save \
test_multiple test_sections test_values test_redef_help \
test_multiple_parsers \
test_sections_option_help \
test_all_opts_option_help \
test_groups_option_help

hidden_options_programs = test_all_opts

# in order to make it work with parallel make we need to make
# these deps explicit
# NOTE: this problem shows only on distribution tarballs
# since files in .deps are empty
no_strings_cmd.h: no_strings_cmd.c
no_multi_strings_cmd.h: no_multi_strings_cmd.c
no_unamed_cmd.h: no_unamed_cmd.c
no_optgiven_cmd.h: no_optgiven_cmd.c
more_than_once_cmd.h: more_than_once_cmd.c
canonize-names-cmd.h: canonize-names-cmd.c
default_values_cmd.h: default_values_cmd.c
cmdline.h: cmdline.c
test_all_opts_cmd.h: test_all_opts_cmd.c
test_groups_cmd.h: test_groups_cmd.c
test_conf_parser_cmd.h: test_conf_parser_cmd.c
test_multiple_cmd.h: test_multiple_cmd.c
test_sections_cmd.h: test_sections_cmd.c
test_values_cmd.h: test_values_cmd.c
test_redef_help_cmd.h: test_redef_help_cmd.c
test_main_cmdline_cmd.h: test_main_cmdline_cmd.c
test_first_cmdline_cmd.h: test_first_cmdline_cmd.c
test_second_cmdline_cmd.h: test_second_cmdline_cmd.c

no_strings_SOURCES = no_strings_cmd.ggo no_strings.c
no_multi_strings_SOURCES = no_multi_strings_cmd.ggo no_multi_strings.c
no_unamed_SOURCES = no_unamed_cmd.ggonu no_unamed.c
no_optgiven_SOURCES = no_optgiven_cmd.ggo no_optgiven.c
no_optgiven2_SOURCES = no_optgiven_cmd.ggo no_optgiven2.c
more_than_once_SOURCES = more_than_once_cmd.ggo more_than_once.c
canonize_names_SOURCES = canonize-names-cmd.ggo canonize-names.c
default_values_SOURCES = default_values_cmd.ggo default_values.c
default_cmdline_SOURCES = cmdline.ggo default_cmdline.c
test_all_opts_SOURCES = test_all_opts_cmd.ggo test_all_opts.c
no_prog_name_SOURCES = test_all_opts_cmd.ggo no_prog_name.c 
# force using our version of getopt
test_groups_SOURCES = test_groups_cmd.ggo test_groups.c
test_conf_parser_SOURCES = test_conf_parser_cmd.ggoconf test_conf_parser.c
test_conf_parser_ov_SOURCES = test_conf_parser_cmd.ggoconf test_conf_parser_ov.c
test_conf_parser_ov2_SOURCES = test_conf_parser_cmd.ggoconf test_conf_parser_ov2.c
test_conf_parser_ov3_SOURCES = test_conf_parser_cmd.ggoconf test_conf_parser_ov3.c
test_conf_parser_ov4_SOURCES = test_conf_parser_cmd.ggoconf test_conf_parser_ov4.c
test_conf_parser_file_save_SOURCES = test_conf_parser_cmd.ggoconf test_conf_parser_file_save.c
test_multiple_SOURCES = test_multiple_cmd.ggo test_multiple.c
test_sections_SOURCES = test_sections_cmd.ggo test_sections.c
test_values_SOURCES = test_values_cmd.ggo test_values.c
test_redef_help_SOURCES = test_redef_help_cmd.ggo test_redef_help.c
test_multiple_parsers_SOURCES = test_main_cmdline_cmd.ggo test_first_cmdline_cmd.ggostr test_second_cmdline_cmd.ggostr test_multiple_parsers.c
test_sections_option_help_SOURCES = test_sections_cmd.ggo test_sections_option_help.c
test_all_opts_option_help_SOURCES = test_all_opts_cmd.ggo test_all_opts_option_help.c
test_groups_option_help_SOURCES = test_groups_cmd.ggo test_groups_option_help.c

CHECKDIFFFILES = no_strings_cmd.c no_strings_cmd.h \
no_multi_strings_cmd.c no_multi_strings_cmd.h \
no_unamed_cmd.c no_unamed_cmd.h \
no_optgiven_cmd.c no_optgiven_cmd.h \
more_than_once_cmd.c more_than_once_cmd.h \
canonize-names-cmd.c canonize-names-cmd.h \
default_values_cmd.c default_values_cmd.h \
cmdline.c cmdline.h \
test_all_opts_cmd.c test_all_opts_cmd.h \
test_groups_cmd.c test_groups_cmd.h \
test_conf_parser_cmd.c test_conf_parser_cmd.h \
test_multiple_cmd.c test_multiple_cmd.h \
test_sections_cmd.c \
test_values_cmd.c test_values_cmd.h \
test_redef_help_cmd.c test_redef_help_cmd.h \
test_main_cmdline_cmd.c test_main_cmdline_cmd.h \
test_first_cmdline_cmd.c test_first_cmdline_cmd.h \
test_second_cmdline_cmd.c test_second_cmdline_cmd.h  

BUILT_SOURCES = $(CHECKDIFFFILES) $(ERRFILES)

GENERATED_TESTS	= no_strings_cmd.c.test no_strings_cmd.h.test \
no_multi_strings_cmd.c.test no_multi_strings_cmd.h.test \
no_unamed_cmd.c.test no_unamed_cmd.h.test \
no_optgiven_cmd.c.test no_optgiven_cmd.h.test \
more_than_once_cmd.c.test more_than_once_cmd.h.test \
canonize-names-cmd.c.test canonize-names-cmd.h.test \
default_values_cmd.c.test default_values_cmd.h.test \
cmdline.c.test cmdline.h.test \
test_all_opts_cmd.c.test test_all_opts_cmd.h.test \
test_groups_cmd.c.test test_groups_cmd.h.test \
test_conf_parser_cmd.c.test test_conf_parser_cmd.h.test \
test_multiple_cmd.c.test test_multiple_cmd.h.test \
test_sections_cmd.c.test \
test_values_cmd.c.test test_values_cmd.h.test \
test_all_opts.save.test test_multiple.save.test test_conf_parser.save.test \
test_redef_help_cmd.c.test test_redef_help_cmd.h.test \
test_main_cmdline_cmd.c.test test_main_cmdline_cmd.h.test \
test_first_cmdline_cmd.c.test test_first_cmdline_cmd.h.test \
test_second_cmdline_cmd.c.test test_second_cmdline_cmd.h.test

# the original command line used to be:
# $(GGO_COMPILE) --no-handle-error -u
# but now are in the input .ggo file
no_optgiven_cmd.c: no_optgiven_cmd.ggo
	$(GGO_COMPILE)

# using $(top_builddir) should test also the removal of leading path
# for the generation of the #ifndef in the generated header file
canonize-names-cmd.c: canonize-names-cmd.ggo
	$(PROGNAME) --input $(srcdir)/canonize-names-cmd.ggo --func-name $*-parser --file-name $(top_builddir)/tests/$*

cmdline.c: cmdline.ggo
	$(PROGNAME) --input $(srcdir)/cmdline.ggo

TESTSOUT = test.out
TESTSOUTPUT = test.output

ERRFILES = wrong_flag.err wrong_flag2.err wrong_group.err wrong_group2.err \
wrong_dep.err wrong_default.err wrong_numeric_value.err wrong_enum_use.err
ERRGGOFILES = wrong_flag.ggo wrong_flag2.ggo wrong_group.ggo wrong_group2.ggo \
wrong_dep.ggo wrong_default.ggo wrong_numeric_value.ggo wrong_enum_use.ggo

EXTRA_DIST = no_optgiven.sh.in more_than_once.sh.in \
test_all_opts.sh.in test_all_opts_file_save.sh.in \
test_groups.sh.in test_conf_parser.sh.in test_conf_parser_save.sh.in \
test_conf_parser_grp.sh.in \
test_conf_parser_ov.sh.in test_conf_parser_ov2.sh.in \
test_conf_parser_ov3.sh.in \
test_conf_parser_ov4.sh.in \
test_conf_parser_err.sh.in test_conf_parser_err_string.sh.in \
test_multiple.sh.in test_multiple_err.sh.in test_sections.sh.in test_default_values.sh.in \
test_conf_parser_ov2.c.in test_conf_parser_ov3.c.in \
test_conf_parser_ov4.c.in \
test_values.sh.in test_values_err.sh.in test_show_help.sh.in \
valgrind_tests.sh.in valgrind_suppressions.sh.in test_err.sh.in \
test_dep.sh.in test_multiple_parsers.sh.in \
$(GENERATED_TESTS) \
$(TESTSOUTPUT) \
suppressions.supp \
test_conf.conf.in \
test_conf_inc.conf.in test_conf_inc_inc.conf test_conf_inc2.conf \
test_conf2.conf test_conf3.conf test_conf_err.conf \
test_conf_err_string.conf test_conf_err_string2.conf \
test_section_with_all_hidden.ggo \
test_required_optional_cmd.ggo \
$(ERRFILES) $(ERRGGOFILES) 

check-err: $(ERRFILES)
	for source in $(ERRFILES); do \
	  test_input="`echo $$source|sed s/err/ggo/`"; \
	  $(PROGNAME) --unamed-opt -i $(srcdir)/$$test_input --file-name null 2> $$source.out || true ; \
	  sed -i -e "s/.*\///" $$source.out ; \
	  echo "diff $$source.out $$source"; \
	  if ! diff $$source.out $(srcdir)/$$source; \
	  then errors=1; fi; \
	done ; \
	test -z $$errors

$(TESTSOUTPUT):
	rm -f $(TESTSOUTPUT); \
        for source in $(TESTS); do \
	  echo "*** $$source" >> $@; \
	  $(top_builddir)/tests/$$source >> $@ 2>&1; \
	done && \
	for source in $(check_PROGRAMS); do \
	  echo "*** $$source -h" >> $@; \
	  $(top_builddir)/tests/$$source -h >> $@ 2>&1; \
	done && \
	for source in $(hidden_options_programs); do \
	  echo "*** $$source --full-help" >> $@; \
	  $(top_builddir)/tests/$$source --full-help >> $@ 2>&1; \
	done && \
	$(PROGNAMESHOWHELP) < $(srcdir)/test_all_opts_cmd.ggo >> $@ 2>&1;
	$(PROGNAMESHOWHELP) < $(srcdir)/test_section_with_all_hidden.ggo >> $@ 2>&1;
	$(PROGNAMESHOWFULLHELP) < $(srcdir)/test_section_with_all_hidden.ggo >> $@ 2>&1;
	$(PROGNAMESHOWHELPREQUIRED) < $(srcdir)/test_required_optional_cmd.ggo >> $@ 2>&1;
	$(PROGNAMESHOWHELPREQUIRED) --default-optional < $(srcdir)/test_required_optional_cmd.ggo >> $@ 2>&1;

store-backup: $(BUILT_SOURCES) $(TESTSOUTPUT)
	rm -f *.test; \
	for source in $(BUILT_SOURCES); do \
	  back_output="`echo $$source.test`"; \
	  echo "saving $$back_output"; \
	  cp $$source $(srcdir)/$$back_output; \
	done; \
	for source in `ls $(srcdir)/*.save`; do \
	  test_output="`echo $$source|sed s/save/save\.test/`"; \
	  cp $$source $(srcdir)/$$test_output; \
        done; \
	cp $(TESTSOUT) $(srcdir)/$(TESTSOUTPUT); \
	rm -f *.err.test

check-diff:
	for source in $(CHECKDIFFFILES); do \
	  back_output="`echo $$source.test`"; \
	  echo "diff $$source $$back_output"; \
	  if ! diff $$source $(srcdir)/$$back_output; \
	  then errors=1; fi; \
	done && \
	echo "creating output of tests..."; \
	rm -f $(TESTSOUT); \
        for tests in $(TESTS); do \
	  echo "*** $$tests" >> $(srcdir)/$(TESTSOUT); \
	  $(top_builddir)/tests/$$tests >> $(srcdir)/$(TESTSOUT) 2>&1 ; \
	done && \
	for tests in $(check_PROGRAMS); do \
	  echo "*** $$tests -h" >> $(srcdir)/$(TESTSOUT); \
	  $(top_builddir)/tests/$$tests -h >> $(srcdir)/$(TESTSOUT) 2>&1; \
	done && \
	for tests in $(hidden_options_programs); do \
	  echo "*** $$tests --full-help" >> $(srcdir)/$(TESTSOUT); \
	  $(top_builddir)/tests/$$tests --full-help >> $(srcdir)/$(TESTSOUT) 2>&1; \
	done && \
	$(PROGNAMESHOWHELP) < $(srcdir)/test_all_opts_cmd.ggo >> $(srcdir)/$(TESTSOUT) 2>&1; \
	$(PROGNAMESHOWHELP) < $(srcdir)/test_section_with_all_hidden.ggo >> $(srcdir)/$(TESTSOUT) 2>&1; \
	$(PROGNAMESHOWFULLHELP) < $(srcdir)/test_section_with_all_hidden.ggo >> $(srcdir)/$(TESTSOUT) 2>&1; \
	$(PROGNAMESHOWHELPREQUIRED) < $(srcdir)/test_required_optional_cmd.ggo >> $(srcdir)/$(TESTSOUT) 2>&1; \
	$(PROGNAMESHOWHELPREQUIRED) --default-optional < $(srcdir)/test_required_optional_cmd.ggo >> $(srcdir)/$(TESTSOUT) 2>&1; \
        echo "diff $(TESTSOUTPUT) $(TESTSOUT)"; \
        if ! diff $(TESTSOUTPUT) $(srcdir)/$(TESTSOUT); \
        then errors=1; fi; \
	for source in `ls $(srcdir)/*.save`; do \
	  test_output="`echo $$source|sed s/save/save\.test/`"; \
	  echo "diff $(srcdir)/$$source $$test_output"; \
	  if ! diff $(srcdir)/$$source $$test_output; \
	  then errors=1; fi; \
        done; \
        test -z $$errors

my-check: clean check check-diff

check-valgrind:
	$(top_builddir)/tests/valgrind_tests.sh $(VALGRINDTESTS)
	$(top_builddir)/tests/valgrind_tests.sh $(top_builddir)/tests/default_values$(EXEEXT) --help
	$(top_builddir)/tests/valgrind_tests.sh $(top_builddir)/tests/default_values$(EXEEXT) --version
	$(top_builddir)/tests/valgrind_tests.sh $(top_builddir)/tests/test_all_opts$(EXEEXT) --help

clean-err:
	rm -f *.err

CLEANFILES = *_cmd.c *_cmd.h *-cmd.h *-cmd.c cmdline.c cmdline.h *.save *.err.out

endif
