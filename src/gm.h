/**
 * Copyright (C) 1999, 2000, 2001, 2002  Free Software Foundation, Inc.
 *
 * This file is part of GNU gengetopt
 *
 * GNU gengetopt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * GNU gengetopt is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with gengetopt; see the file COPYING. If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _GM_H
#define _GM_H

#include "skels/header.h"
#include "skels/c_source.h"

#include <list>
#include <string>

#define TAB_LEN 2

struct gengetopt_option;

typedef std::list<std::string> OptionHelpList;

class CmdlineParserCreator : public header_gen_class, public c_source_gen_class
{
 protected:
  char *parser_function_name;
  char *filename;
  char *args_info_name;
  char *header_filename;
  char *c_filename;
  string output_dir;
  string comment;
  char *unamed_options;
  string show_required_string;

  bool long_help;
  bool no_handle_help;
  bool no_handle_version;
  bool no_handle_error;
  bool conf_parser;
  bool string_parser;
  bool gen_gengetopt_version;
  bool gen_strdup;

  unsigned int tab_indentation ; /* tab indentation level */

  void inc_indent()
    {
      tab_indentation += TAB_LEN ;
    }

  void dec_indent()
    {
      tab_indentation -= TAB_LEN ;
    }

  void indent()
    {
      unsigned int i ;

      for ( i = 1 ; i <= tab_indentation ; ++i )
        printf (" ");
    }

  void do_update_arg (struct gengetopt_option *opt,
                      ostream &stream, unsigned int indent, const string argstr,
                      const string orig_argstr);
  void free_option(struct gengetopt_option *opt,
                   ostream &stream, unsigned int indent);

  int generate_header_file();
  int generate_source();

  string generate_getopt_string();

  // to be implemented in header_gen_class
  virtual void generate_option_arg(ostream &stream, unsigned int indent);
  virtual void generate_option_given(ostream &stream, unsigned int indent);
  virtual void generate_option_values_decl(ostream &stream, unsigned int indent);

  // to be implemented in c_source_gen_class
  virtual void generate_clear_arg(ostream &stream, unsigned int indent);
  virtual void generate_given_init(ostream &stream, unsigned int indent);
  virtual void generate_struct_def(ostream &stream, unsigned int indent);
  virtual void generate_option_values(ostream &stream, unsigned int indent);

  virtual void generate_handle_help(ostream &stream, unsigned int indent,
                                    bool full_help = false);
  virtual void generate_handle_no_short_option(ostream &stream,
                                               unsigned int indent);
  virtual void generate_handle_option(ostream &stream, unsigned int indent);
  virtual void generate_handle_required(ostream &stream, unsigned int indent);
  virtual void generate_handle_dependencies(ostream &stream, unsigned int indent);
  virtual void generate_handle_group(ostream &stream, unsigned int indent);
  virtual void generate_group_counters(ostream &stream, unsigned int indent);
  virtual void generate_handle_version(ostream &stream, unsigned int indent);
  virtual void generate_help_option_print(ostream &stream,
                                          unsigned int indent);
  virtual void generate_full_help_option_print(ostream &stream,
                                          unsigned int indent);
  virtual void generate_long_option_struct(ostream &stream,
                                           unsigned int indent);
  virtual void generate_reset_groups(ostream &stream, unsigned int indent);

  virtual void generate_free(ostream &stream, unsigned int indent);
  virtual void generate_list_free(ostream &stream, unsigned int indent);

  virtual void generate_file_save_loop(ostream &stream, unsigned int indent);
  virtual void generate_init_args_info(ostream &stream, unsigned int indent);

  virtual void generate_custom_getopt(ostream &stream, unsigned int indent);

  void generateBreak(ostream &stream, unsigned int indent = 0);

  void handle_options(ostream &, unsigned int, bool has_short);

 public:

  CmdlineParserCreator (char *function_name, char *struct_name,
                        char *unamed_options,
                        char *filename, char *header_ext, char *c_ext,
                        bool long_help, bool no_handle_help,
                        bool no_handle_version,
                        bool no_handle_error, bool conf_parser, bool string_parser,
                        bool gen_version, bool gen_getopt,
                        const string &comment,
                        const string &outdir,
                        const string &show_required);

  int generate();

  virtual void generate_list_def(ostream &stream, unsigned int indent);
  virtual void generate_multiple_fill_array(ostream &stream, unsigned int indent);
  virtual void generate_update_multiple_given(ostream &stream, unsigned int indent);
  const string generate_purpose();
  const string generate_description();
  const string generate_usage_string(bool use_config_package = true);

  /**
   * generate a list of option descriptions that will be printed in the
   * help output
   * 
   * @param generate_hidden if true, include also the hidden options
   */
  OptionHelpList *generate_help_option_list(bool generate_hidden = false);
};

#endif /* _GM_H */
