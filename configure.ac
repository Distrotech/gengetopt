# Copyright (C) 1999-2007  Free Software Foundation, Inc.
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

dnl Process this file with autoconf to produce a configure script.
AC_INIT(reconf)

AM_CONFIG_HEADER(config.h)

AM_INIT_AUTOMAKE(gengetopt,2.19.1)

dnl directory for docs (html)
AC_SUBST(gengetoptdocdir)
gengetoptdocdir=$datadir/doc/gengetopt

dnl directory for examples
AC_SUBST(gengetoptexamplesdir)
gengetoptexamplesdir=$gengetoptdocdir/examples

dnl Checks for C compiler.
AC_PROG_CC

dnl Use of GnuLib
gl_EARLY

dnl add options for non GNU compilers
AC_NONGNU_FLAGS

dnl Checks for typedefs, structures, and compiler characteristics.
dnl AC_C_CONST obsolescent
AC_TYPE_SIZE_T
AC_C_LONG_LONG

dnl Checks for C++ compiler.
AC_PROG_CXX

AC_CANONICAL_HOST

dnl under IRIX64, the non GNU compiler seems to require this flag
dnl in order to use standard namespace std
if test "$GCC" != "yes"; then \
case "$host_os" in
  irix6*) CXXFLAGS="-LANG:std $CXXFLAGS";; \
esac;
fi

AC_PROG_INSTALL

dnl check for ranlib, for building common code
AC_PROG_RANLIB

dnl test for --enable-warnings command line option
AC_ARG_ENABLE( warnings, [  --enable-warnings       enable compiler warnings], AC_COMPILE_WARNINGS )

dnl check for STL
AC_CXX_HAVE_STL

dnl check for sstream.h
AC_CXX_HAVE_SSTREAM

dnl for executable extensions
AC_EXEEXT

dnl for yacc or bison
AC_PROG_YACC

dnl set some flags for yacc to generate header file
AC_SUBST(YFLAGS)dnl
YFLAGS="$YFLAGS -d -v"

dnl for lex or flex
AM_PROG_LEX

dnl Checks for libraries.
dnl Replace `main' with a function in -lfl:
AC_CHECK_LIB(fl, main)

dnl check for Electric Fence library, but do not link it automatically
dnl don't use it anymore: use valgrind
dnl AC_HAVE_LIBRARY(libefence.a, [LIBS="$LIBS"])

dnl if (f)lex library is not present (yywrap won't be found) we provide
dnl a simple implementation (see yywrap.cc) which will be included in
dnl libobjs and linked against the program (see src/Makefile.am)
dnl this works with flex generated files (I don't know about others)
AC_REPLACE_FUNCS(yywrap)

dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(malloc.h strings.h unistd.h libintl.h stddef.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_HEADER_STDBOOL
#AC_FUNC_MALLOC
#AC_FUNC_REALLOC
#AC_FUNC_STRTOD

# For gnulib.
gl_INIT

dnl Checks for library functions.
dnl AC_REPLACE_FUNCS(strdup)

dnl check for getopt in standard library
dnl adl_FUNC_GETOPT_LONG
dnl AC_CHECK_FUNCS(getopt_long)

AC_PATH_PROGS(TAR, tar gtar)

dnl this is only for highlighting source for documentation
dnl GNU source-highlight can be found at
dnl http://www.gnu.org/software/src-highlite
AC_PATH_PROGS(SOURCEHIGHLIGHT, source-highlight)

dnl the following is a program for generating a program that
dnl generates a source and substitutes some values
AC_PATH_PROGS(GENGEN, gengen)

dnl this is for testing purpose and development
AC_PATH_PROGS(VALGRIND, valgrind)

dnl this is only for developers who use change command line options
AC_PATH_PROGS(HELP2MAN, help2man)
AM_CONDITIONAL(NO_HELP2MAN, test -z "$ac_cv_path_HELP2MAN" )

dnl AM_CONDITIONAL(NO_GETOPTLONG, test "$ac_cv_func_getopt_long" = no  )
AM_CONDITIONAL(NO_STRDUP, test "$ac_cv_func_strdup" = no )
AM_CONDITIONAL(NO_SOURCEHIGHLIGHT, test -z "$ac_cv_path_SOURCEHIGHLIGHT" )
AM_CONDITIONAL(NO_GENGEN, test -z "$ac_cv_path_GENGEN" )
dnl AM_CONDITIONAL(NO_SSTREAM, test -z "$ac_cv_cxx_have_sstream" )

AH_TEMPLATE(HAVE_LONG_LONG)

AC_OUTPUT([Makefile
           src/Makefile src/includes/Makefile src/skels/Makefile
           doc/Makefile gl/Makefile
           tests/Makefile tests/no_optgiven.sh
           tests/valgrind_tests.sh
           tests/valgrind_suppressions.sh
           tests/more_than_once.sh
           tests/test_all_opts.sh
           tests/test_all_opts_file_save.sh
           tests/test_groups.sh
           tests/test_conf.conf
           tests/test_conf_inc.conf
           tests/test_conf_parser.sh
           tests/test_conf_parser_save.sh
           tests/test_conf_parser_grp.sh
           tests/test_conf_parser_ov.sh
           tests/test_conf_parser_ov2.sh
           tests/test_conf_parser_ov3.sh
           tests/test_conf_parser_ov2.c
           tests/test_conf_parser_ov3.c
           tests/test_conf_parser_err.sh
           tests/test_conf_parser_err_string.sh
           tests/test_multiple.sh
           tests/test_multiple_err.sh
           tests/test_sections.sh tests/test_default_values.sh
           tests/test_values.sh tests/test_values_err.sh
           tests/test_show_help.sh tests/test_err.sh tests/test_dep.sh
           tests/test_multiple_parsers.sh],
          [chmod +x tests/valgrind_tests.sh
           chmod +x tests/valgrind_suppressions.sh
           chmod +x tests/no_optgiven.sh
           chmod +x tests/more_than_once.sh
           chmod +x tests/test_all_opts.sh
           chmod +x tests/test_all_opts_file_save.sh
           chmod +x tests/test_groups.sh
           chmod +x tests/test_conf_parser.sh
           chmod +x tests/test_conf_parser_save.sh
           chmod +x tests/test_conf_parser_grp.sh
           chmod +x tests/test_conf_parser_ov.sh
           chmod +x tests/test_conf_parser_ov2.sh
           chmod +x tests/test_conf_parser_ov3.sh
           chmod +x tests/test_conf_parser_err.sh
           chmod +x tests/test_conf_parser_err_string.sh
           chmod +x tests/test_multiple.sh
           chmod +x tests/test_multiple_err.sh
           chmod +x tests/test_sections.sh
           chmod +x tests/test_default_values.sh
           chmod +x tests/test_values.sh
           chmod +x tests/test_values_err.sh
           chmod +x tests/test_err.sh
           chmod +x tests/test_dep.sh
           chmod +x tests/test_show_help.sh
           chmod +x tests/test_multiple_parsers.sh])
