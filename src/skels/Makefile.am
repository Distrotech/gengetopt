# Copyright (C) 2002 Lorenzo Bettini <http://www.lorenzobettini.it>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# if gengen is not installed we simply ignore the changes
# FIXME: maybe we have to notify the developer about it

if NO_GENGEN
%.h %.cc: %.h_skel
	touch $@
else
GENERATE = $(GENGEN)

&.h: %.cc
%.cc: %.h_skel
	$(GENERATE) -i $< --file-name $*.h --gen-name $* --separate-files --expand-tabs
	touch $@
endif

INCLUDES = -I@top_srcdir@/src

noinst_LTLIBRARIES = libgen.la

libgen_la_SOURCES = header.cc c_source.cc handle_help.cc handle_version.cc \
generic_option.cc required_option.cc dependant_option.cc \
generic_option_group.cc group_counter.cc group_option.cc \
print_help_string.cc \
multiple_opt_list.cc multiple_opt_list.h \
multiple_opt_struct.cc multiple_opt_struct.h \
multiple_option.cc multiple_option.h \
multiple_fill_array.cc multiple_fill_array.h \
multiple_fill_array_default.cc multiple_fill_array_default.h \
copyright.cc \
free_string.cc free_string.h \
free_multiple.cc free_multiple.h \
free_inputs_string.cc free_inputs_string.h \
reset_group.cc reset_group.h \
exit_failure.cc exit_failure.h \
update_given.cc update_given.h \
update_arg.cc update_arg.h \
option_arg.cc option_arg.h \
given_field.cc given_field.h \
clear_given.cc clear_given.h \
clear_arg.cc clear_arg.h \
free_list.cc free_list.h \
file_save.cc file_save.h \
file_save_multiple.cc file_save_multiple.h \
init_args_info.cc init_args_info.h \
custom_getopt_gen.cc custom_getopt_gen.h

BUILT_SOURCES = header.h c_source.h header.cc c_source.cc \
handle_help.h handle_version.h handle_help.cc handle_version.cc \
generic_option.h required_option.h dependant_option.h \
generic_option.cc required_option.cc dependant_option.cc \
generic_option_group.h group_counter.h group_option.h \
generic_option_group.cc group_counter.cc group_option.cc \
print_help_string.h print_help_string.cc \
multiple_opt_list.cc multiple_opt_list.h \
multiple_opt_struct.cc multiple_opt_struct.h \
multiple_option.cc multiple_option.h \
multiple_fill_array.cc multiple_fill_array.h \
multiple_fill_array_default.cc multiple_fill_array_default.h \
copyright.cc copyright.h \
free_string.cc free_string.h \
free_multiple.cc free_multiple.h \
free_inputs_string.cc free_inputs_string.h \
reset_group.cc reset_group.h \
exit_failure.cc exit_failure.h \
update_given.cc update_given.h \
update_arg.cc update_arg.h \
option_arg.cc option_arg.h \
given_field.cc given_field.h \
clear_given.cc clear_given.h \
clear_arg.cc clear_arg.h \
free_list.cc free_list.h \
file_save.cc file_save.h \
file_save_multiple.cc file_save_multiple.h \
init_args_info.cc init_args_info.h \
custom_getopt_gen.cc custom_getopt_gen.h

EXTRA_DIST = header.h_skel c_source.h_skel handle_help.h_skel \
handle_version.h_skel generic_option.h_skel \
required_option.h_skel dependant_option.h_skel \
generic_option_group.h_skel group_counter.h_skel group_option.h_skel \
print_help_string.h_skel \
multiple_opt_list.h_skel multiple_opt_struct.h_skel multiple_option.h_skel \
multiple_fill_array.h_skel multiple_fill_array_default.h_skel \
copyright.h_skel free_string.h_skel \
free_multiple.h_skel free_inputs_string.h_skel \
reset_group.h_skel \
exit_failure.h_skel \
update_given.h_skel \
update_arg.h_skel \
option_arg.h_skel \
given_field.h_skel \
clear_given.h_skel \
clear_arg.h_skel \
free_list.h_skel \
file_save.h_skel \
file_save_multiple.h_skel \
init_args_info.h_skel \
custom_getopt_gen.h_skel \
$(BUILT_SOURCES)

built-clean:
	rm -f $(BUILT_SOURCES)