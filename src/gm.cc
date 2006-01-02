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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include <fstream>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C"
{
#include "argsdef.h"
#include "global_opts.h"
};

#include "ggo_options.h"

#include "gm.h"
#include "my_sstream.h"

#include "groups.h"
#include "skels/update_arg.h"
#include "skels/option_arg.h"
#include "skels/required_option.h"
#include "skels/dependant_option.h"
#include "skels/generic_option.h"
#include "skels/group_option.h"
#include "skels/group_counter.h"
#include "skels/generic_option_group.h"
#include "skels/handle_help.h"
#include "skels/handle_version.h"
#include "skels/print_help_string.h"
#include "skels/multiple_opt_list.h"
#include "skels/multiple_opt_struct.h"
#include "skels/multiple_option.h"
#include "skels/multiple_fill_array.h"
#include "skels/multiple_fill_array_default.h"
#include "skels/free_string.h"
#include "skels/free_multiple.h"
#include "skels/free_inputs_string.h"
#include "skels/reset_group.h"
#include "skels/exit_failure.h"
#include "skels/update_given.h"
#include "skels/given_field.h"
#include "skels/clear_given.h"
#include "skels/clear_arg.h"
#include "skels/free_list.h"
#include "skels/file_save.h"
#include "skels/file_save_multiple.h"
#include "gm_utils.h"
#include "fileutils.h"

#ifndef HAVE_STRDUP
extern "C" char *strdup (const char *s) ;
#endif

#define MAX_STARTING_COLUMN 32

#define EXE_NAME "argv[0]"

#define PARSER_NAME_PREFIX (c_source_gen_class::parser_name + "_")
#define OPTION_VALUES_NAME(n) (PARSER_NAME_PREFIX + n + "_values")

using std::endl;

extern char * gengetopt_package;
extern char * gengetopt_version;
extern char * gengetopt_purpose;
extern char * gengetopt_input_filename;

extern groups_collection_t gengetopt_groups;

static void _generate_option_arg(ostream &stream,
                                 unsigned int indent,
                                 struct gengetopt_option * opt);

static void
generate_help_desc_print(ostream &stream,
                         unsigned int desc_column,
                         const char *descript, const char *defval,
                         const string &values);

CmdlineParserCreator::CmdlineParserCreator (char *function_name,
                                            char *struct_name,
                                            char *unamed_options_,
                                            char *filename_,
                                            char *header_ext, char *c_ext,
                                            bool long_help_,
                                            bool no_handle_help_,
                                            bool no_handle_version_,
                                            bool no_handle_error_,
                                            bool conf_parser_,
                                            bool gen_version,
                                            const string &comment_) :
  filename (filename_),
  args_info_name (struct_name),
  comment (comment_),
  unamed_options (unamed_options_),
  long_help (long_help_), no_handle_help (no_handle_help_),
  no_handle_version (no_handle_version_), no_handle_error (no_handle_error_),
  conf_parser (conf_parser_), gen_gengetopt_version (gen_version),
  tab_indentation (0)
{
  parser_function_name = canonize_names (function_name);
  c_filename = create_filename (filename, c_ext);
  header_filename = create_filename (filename, header_ext);

  // header_gen_class
  const string stripped_header_file_name = strip_path (filename);
  set_header_file_name (stripped_header_file_name);
  if (gen_gengetopt_version)
    header_gen_class::set_generator_version
      ("version " VERSION);
  const string my_ifndefname =
    to_upper (strip_path (stripped_header_file_name));
  set_ifndefname (canonize_names (my_ifndefname.c_str ()));
  header_gen_class::set_parser_name (parser_function_name);
  const string my_package_var_name =
    to_upper (parser_function_name) + "_PACKAGE";
  const string my_version_var_name =
    to_upper (parser_function_name) + "_VERSION";
  header_gen_class::set_package_var_name (my_package_var_name);
  c_source_gen_class::set_package_var_name (my_package_var_name);
  header_gen_class::set_version_var_name (my_version_var_name);
  c_source_gen_class::set_version_var_name (my_version_var_name);
  header_gen_class::set_args_info (args_info_name);
  c_source_gen_class::set_args_info (args_info_name);
  const string uppersand = "\"";

  if (gengetopt_package)
    set_package_var_val
      (uppersand + gengetopt_package + uppersand);
  else
    set_package_var_val ("PACKAGE");

  if (gengetopt_version)
    set_version_var_val
      (uppersand + gengetopt_version + uppersand);
  else
    set_version_var_val ("VERSION");

  header_gen_class::set_generate_config_parser (conf_parser);

  // c_source_gen_class
  set_command_line (comment);
  if (gen_gengetopt_version)
    c_source_gen_class::set_generator_version
      ("version " VERSION);
  c_source_gen_class::set_parser_name (parser_function_name);
  set_source_name (filename);

  ostringstream exit_failure_str;
  exit_failure_gen_class exit_gen;
  exit_gen.set_parser_name (c_source_gen_class::parser_name);
  exit_gen.set_handle_error (! no_handle_error);
  exit_gen.generate_exit_failure (exit_failure_str);
  set_final_exit (exit_failure_str.str ());

  set_conf_parser (conf_parser);

  struct gengetopt_option * opt;
  gen_strdup = (unamed_options != 0 || conf_parser);

  if (! gen_strdup)
    {
      foropt
        if (opt->type != ARG_FLAG || opt->type != ARG_NO) {
          gen_strdup = true;
          break;
        }
    }

  set_do_generate_strdup(gen_strdup);
  set_check_possible_values(has_values());
  set_multiple_token_functions(has_multiple_options_with_type());
  set_multiple_token_vars(has_multiple_options_with_type());
  set_handle_unamed(unamed_options);
  set_check_required_options(has_required() || has_dependencies());
  set_has_purpose((gengetopt_purpose != 0));
  set_purpose(generate_purpose());
  set_no_package((gengetopt_package == 0));
}

void
CmdlineParserCreator::generateBreak(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');

  stream << endl;
  stream << indent_str;
  stream << "break;";
}

void
CmdlineParserCreator::do_update_arg (struct gengetopt_option *opt,
                                     ostream &stream,
                                     unsigned int indent,
                                     const string argstr = "optarg",
                                     const string orig_argstr = "optarg")
{
  if (opt->type == ARG_NO)
    {
      stream << "break;";
      return;
    }

  string indent_str (indent, ' ');
  const int offset = 4;

  update_arg_gen_class update_arg_gen;
  update_arg_gen.set_optarg(argstr);
  update_arg_gen.set_orig_optarg(orig_argstr);
  update_arg_gen.set_opt_var (opt->var_arg);

  if (opt->multiple)
    {
      update_arg_gen.set_structure (string (opt->var_arg) + "_new");
    }
  else
    {
      update_arg_gen.set_structure (ARGS_STRUCT);
    }

  if (opt->arg_is_optional)
    {
      if (opt->multiple)
        {
          update_arg_gen_class str_gen_null;

          str_gen_null.set_string_arg(opt->type == ARG_STRING);
          str_gen_null.set_no_free(true);
          str_gen_null.set_has_arg(true);
          str_gen_null.set_optarg ("NULL");
          str_gen_null.set_orig_optarg ("NULL");
          str_gen_null.set_structure (string (opt->var_arg) + "_new");
          str_gen_null.set_opt_var (opt->var_arg);
          str_gen_null.generate_update_arg (stream, indent);
          stream << endl;
        }

      stream << "if (" << argstr << ")" << endl;
      stream << indent_str << "  {" << endl;
      stream << indent_str << "    ";
      indent += offset;
    }

    update_arg_gen.set_has_arg(true);

    if (opt->multiple)
    {
      update_arg_gen.set_no_free(true);
    }
    else
    {
      update_arg_gen.set_no_free(false);
    }

  switch (opt->type)
    {
    case ARG_FLAG:
      update_arg_gen.set_flag_arg(true);
      update_arg_gen.set_has_arg(false);
      break;
    case ARG_STRING:
      update_arg_gen.set_string_arg(true);
      break;
    case ARG_INT:
      update_arg_gen.set_int_arg(true);
      break;
    case ARG_SHORT:
      update_arg_gen.set_int_arg(true);
      update_arg_gen.set_cast ("(short)");
      break;
    case ARG_LONG:
      update_arg_gen.set_long_arg(true);
      break;
    case ARG_FLOAT:
      update_arg_gen.set_float_arg(true);
      update_arg_gen.set_cast ("(float)");
      break;
    case ARG_DOUBLE:
      update_arg_gen.set_float_arg(true);
      break;
    case ARG_LONGDOUBLE:
      update_arg_gen.set_float_arg(true);
      update_arg_gen.set_cast ("(long double)");
      break;
    case ARG_LONGLONG:
      update_arg_gen.set_longlong_arg(true);
      break;
    default:
      fprintf (stderr, "gengetopt: bug found in %s:%d\n", __FILE__,
               __LINE__);
      abort ();
    }

    update_arg_gen.set_package_var_name (EXE_NAME);
    update_arg_gen.set_numeric(is_numeric(opt));
    
  update_arg_gen.generate_update_arg (stream, indent);

  if (opt->arg_is_optional)
    {
      stream << endl;
      stream << indent_str << "  }";
      indent -= offset;
    }
}

int
CmdlineParserCreator::generate ()
{
  int head_result;

  head_result = generate_header_file ();
  if (head_result)
    return head_result;

  return generate_source ();
}

int
CmdlineParserCreator::generate_header_file ()
{
  if (! gengetopt_options.size())
    {
      fprintf (stderr, "gengetopt: none option given\n");
      return 1;
    }

  /* ****************************************************** */
  /* HEADER FILE******************************************* */
  /* ****************************************************** */

  ofstream *output_file = open_fstream (header_filename);
  generate_header (*output_file);
  output_file->close ();
  delete output_file;

  return 0;
}

void
CmdlineParserCreator::generate_option_arg(ostream &stream,
                                          unsigned int indent)
{
  struct gengetopt_option * opt;

  foropt
    if (opt->type != ARG_NO) {
      switch (opt->type) {
      case ARG_FLAG:
      case ARG_STRING:
      case ARG_INT:
      case ARG_SHORT:
      case ARG_LONG:
      case ARG_FLOAT:
      case ARG_DOUBLE:
      case ARG_LONGDOUBLE:
      case ARG_LONGLONG:
        _generate_option_arg (stream, indent, opt);

        break;
      default:
        fprintf (stderr, "gengetopt: bug found in %s:%d!!\n",
                 __FILE__, __LINE__);
        abort ();
      }
    }
}

void
_generate_option_arg(ostream &stream,
                     unsigned int indent,
                     struct gengetopt_option *opt)
{
  option_arg_gen_class option_arg_gen;

  string type = arg_types[opt->type];
  string origtype = "char *";

  if (opt->multiple) {
    type += "*";
    origtype += "*";
  }

  option_arg_gen.set_type(type);
  option_arg_gen.set_origtype(origtype);
  option_arg_gen.set_flag_arg((opt->type == ARG_FLAG));
  option_arg_gen.set_desc(opt->desc);
  option_arg_gen.set_name(opt->var_arg);

  if (opt->default_given)
    {
      option_arg_gen.set_has_default(true);
      option_arg_gen.set_default_value(opt->default_string);
    }

  if (opt->type == ARG_FLAG)
    {
      option_arg_gen.set_default_on(opt->flagstat);
    }

  if (opt->type == ARG_LONGLONG)
    {
      option_arg_gen.set_long_long_arg(true);
      option_arg_gen.set_longlongtype(arg_types[opt->type]);
      option_arg_gen.set_longtype(arg_types[ARG_LONG]);
    }

  option_arg_gen.generate_option_arg(stream, indent);
}

void
CmdlineParserCreator::generate_option_given(ostream &stream,
                                            unsigned int indent)
{
  struct gengetopt_option * opt;
  string indent_str (indent, ' ');
  bool first = true;
  given_field_gen_class given_gen;

  foropt
    {
      switch (opt->type) {
      case ARG_NO:
      case ARG_FLAG:
      case ARG_STRING:
      case ARG_INT:
      case ARG_SHORT:
      case ARG_LONG:
      case ARG_FLOAT:
      case ARG_DOUBLE:
      case ARG_LONGDOUBLE:
      case ARG_LONGLONG: break;
      default:
        fprintf (stderr, "gengetopt: bug found in %s:%d!!\n",
                 __FILE__, __LINE__);
        abort ();
      }
      if (! first)
        stream << indent_str;
      else
        first = false;

      given_gen.set_multiple (opt->multiple);
      given_gen.set_arg_name (opt->var_arg);
      given_gen.set_long_opt (opt->long_opt);
      given_gen.set_group (opt->multiple && opt->group_value);
      given_gen.generate_given_field (stream);
    }

  if (unamed_options)
    {
      stream << endl;
      stream << indent_str;
      stream << "char **inputs ; /* unamed options */\n" ;
      stream << indent_str;
      stream << "unsigned inputs_num ; /* unamed options number */" ;
    }
}

void
CmdlineParserCreator::generate_option_values_decl(ostream &stream,
                                                  unsigned int indent)
{
  struct gengetopt_option * opt;
  bool first = true;

  foropt
    {
      if (opt->acceptedvalues) {
        if (first) {
          first = false;
        }

        stream << "extern char *" << OPTION_VALUES_NAME(opt->var_arg) <<
          "[] ;\t/* Possible values for " << opt->long_opt << ".  */\n";
      }
    }

  if (! first)
    stream << "\n";
}

void
CmdlineParserCreator::generate_option_values(ostream &stream,
                                             unsigned int indent)
{
  struct gengetopt_option * opt;
  bool first = true;

  foropt
    {
      if (opt->acceptedvalues) {
        if (first) {
          first = false;
        }

        stream << "char *" << OPTION_VALUES_NAME(opt->var_arg) <<
          "[] = {" << opt->acceptedvalues->toString(false) <<
          ", 0} ;\t/* Possible values for " << opt->long_opt << ".  */\n";
      }
    }

  if (! first)
    stream << "\n";
}

const string
CmdlineParserCreator::generate_usage_string(bool use_config_package)
{
  struct gengetopt_option * opt;
  ostringstream usage;
  const char   *type_str;

  usage << "Usage: ";
  if (gengetopt_package)
    usage << gengetopt_package;
  else if (use_config_package)
    usage << "%s";

  usage << " ";

  if ( long_help )
    {
      foropt
        if (opt->required && !opt->hidden) /* required options */
          switch (opt->type) {
          case ARG_INT:
          case ARG_SHORT:
          case ARG_LONG:
          case ARG_FLOAT:
          case ARG_DOUBLE:
          case ARG_LONGDOUBLE:
          case ARG_LONGLONG:
          case ARG_STRING:
            if (opt->type_str)
              type_str = opt->type_str;
            else
              type_str = arg_names[opt->type];

            if (opt->short_opt)
              {
                usage << "-" << opt->short_opt
                      << type_str << "|";
              }
            usage << "--" << opt->long_opt << "=" <<
              type_str << " ";
            break;
          default:
            fprintf (stderr, "gengetopt: bug found in %s:%d!!\n",
                     __FILE__, __LINE__);
            abort ();
          }
      foropt
        if (!opt->required && !opt->hidden)
          switch (opt->type) {
          case ARG_NO:
          case ARG_FLAG:
            usage << "[";
            if (opt->short_opt)
              {
                usage << "-" << opt->short_opt << "|";
              }
            usage << "--" << opt->long_opt << "] ";
            break;
          case ARG_INT:
          case ARG_SHORT:
          case ARG_LONG:
          case ARG_FLOAT:
          case ARG_DOUBLE:
          case ARG_LONGDOUBLE:
          case ARG_LONGLONG:
          case ARG_STRING:
            if (opt->type_str)
              type_str = opt->type_str;
            else
              type_str = arg_names[opt->type];

            if (opt->short_opt)
              {
                usage << "-" << opt->short_opt
                      << type_str << "|";
              }
            usage << "--" << opt->long_opt << "=" <<
              type_str << " ";
            break;
          default: fprintf (stderr, "gengetopt: bug found in %s:%d!!\n",
                            __FILE__, __LINE__);
            abort ();
          }
    }
  else
    { /* if not long help we generate it as GNU standards */
      usage << "[OPTIONS]...";
    }

  if ( unamed_options )
    usage << " [" << unamed_options << "]...";

  usage << "\\n";

  return usage.str ();
}

static void
generate_help_desc_print(ostream &stream,
                         unsigned int desc_column,
                         const char *descript, const char *defval,
                         const string &values)
{
  string desc;
  string desc_with_default = descript;

  if (defval || values.size())
    {
      desc_with_default += "  (";

      if (values.size()) {
        desc_with_default += "possible values=";
        desc_with_default += values;
        if (defval)
          desc_with_default += " ";
      }

      if (defval) {
        desc_with_default += "default=";
        desc_with_default += defval;
      }

      desc_with_default += ")";
    }

  wrap_cstr ( desc, desc_column, 2, desc_with_default );

  stream << desc;
}


void
CmdlineParserCreator::generate_help_option_print(ostream &stream,
                                                 unsigned int indent)
{
  OptionHelpList *option_list = generate_help_option_list();

  print_help_string_gen_class print_gen;

  for (OptionHelpList::const_iterator it = option_list->begin();
       it != option_list->end(); ++it)
    {
      print_gen.set_helpstring(*it);
      print_gen.generate_print_help_string(stream, indent);
    }

  delete option_list;
}

const string
CmdlineParserCreator::generate_purpose()
{
  string wrapped_purpose;

  if (gengetopt_purpose != NULL)
    {
      wrap_cstr(wrapped_purpose, 0, 0, gengetopt_purpose);
    }

  return wrapped_purpose;
}

OptionHelpList *
CmdlineParserCreator::generate_help_option_list()
{
  OptionHelpList *option_list = new OptionHelpList;

  long desc_col;
  struct gengetopt_option * opt;

  int           type_len;
  const char   *type_str;
  ostringstream stream;

  /* calculate columns */
  desc_col = 0;
  foropt {
    if (opt->hidden)
        continue;
    
    int width = 2 + 4 + 2;  // ws + "-a, " + ws

    width += strlen (opt->long_opt) + 2;  // "--"

    if ((opt->type != ARG_FLAG) &&
        (opt->type != ARG_NO))
      {
        if (opt->type_str)
          type_str = opt->type_str;
        else
          type_str = arg_names[opt->type];
        type_len = strlen(type_str);

        width += type_len + 1;        // "="

        if (opt->arg_is_optional)
          width += 2; // "[" and "]"
      }

    if (width > desc_col)
      desc_col = width;
  }

  if (desc_col > MAX_STARTING_COLUMN)
    desc_col = MAX_STARTING_COLUMN;

  /* print justified options */
  char *prev_group = 0;
  char *curr_section = 0;
  bool first_option = true;

  foropt
    {
      if (opt->hidden)
        continue;  
      
      if (opt->group_value &&
          (! prev_group || strcmp (opt->group_value, prev_group) != 0))
        {
          string group_string = "\\n Group: ";
          string wrapped_desc;

          if (opt->group_desc && strlen (opt->group_desc))
            {
              wrapped_desc = "\\n  ";
              wrap_cstr (wrapped_desc, 2, 0, opt->group_desc);
            }

          group_string += opt->group_value + wrapped_desc;

          option_list->push_back (group_string);

          prev_group = opt->group_value;
        }

      if (opt->section &&
          (!curr_section || strcmp (curr_section, opt->section)))
        {
          curr_section = opt->section;

          ostringstream sec_string;

          if (! first_option)
            sec_string << "\\n";

          sec_string << opt->section << ":" ;

          string wrapped_def;
          wrap_cstr(wrapped_def, 0, 0, sec_string.str());
          option_list->push_back(wrapped_def);

          if (opt->section_desc)
            {
              string wrapped_desc ( 2, ' ');
              wrap_cstr ( wrapped_desc, 2, 0, opt->section_desc );

              option_list->push_back(wrapped_desc);
            }
        }

      first_option = false;
      const char * def_val = NULL;
      string def_str = "`";

      ostringstream option_stream;

      if (opt->type == ARG_FLAG || opt->type == ARG_NO)
        {
          def_val = NULL;

          if (opt->short_opt)
            option_stream << "  -" << opt->short_opt << ", ";
          else
            option_stream << "      ";

          option_stream << "--" << opt->long_opt;

          if (opt->type == ARG_FLAG)
            def_val = opt->flagstat ? "on" : "off";
        }
      else
        {
          def_val = NULL;

          if (opt->type_str)
            type_str = opt->type_str;
          else
            type_str = arg_names[opt->type];

          type_len = strlen(type_str);

          if (opt->short_opt)
            {
              option_stream << "  -" << opt->short_opt << ", ";
            }
          else
            {
              option_stream << "      ";
            }

          bool arg_optional = opt->arg_is_optional;
          option_stream << "--" << opt->long_opt
                 << (arg_optional ? "[" : "")
                 << "=" << type_str
                 << (arg_optional ? "]" : "");

          if (opt->default_string)
            {
              def_str += opt->default_string;
              def_str += "'";
              def_val = def_str.c_str();
            }
        }

      const string &option_string = option_stream.str();
      stream << option_string;
      const char *opt_desc = opt->desc;

      if (option_string.size() >= MAX_STARTING_COLUMN)
        {
          string indent (MAX_STARTING_COLUMN, ' ');
          stream << "\\n" << indent;
        }
      else
        {
          string indent (desc_col - option_string.size(), ' ');
          stream << indent;
        }

      generate_help_desc_print(stream, desc_col, opt_desc, def_val,
        (opt->acceptedvalues ? opt->acceptedvalues->toString() : ""));

      option_list->push_back(stream.str());
      stream.str("");
    }

  return option_list;
}

void
CmdlineParserCreator::generate_given_init(ostream &stream,
                                          unsigned int indent)
{
  struct gengetopt_option * opt;
  string indent_str (indent, ' ');
  clear_given_gen_class clear_given;
  clear_given.set_arg_struct(ARGS_STRUCT);

  /* now we initialize "given" fields */
  foropt
    {
      stream << indent_str;
      clear_given.set_var_arg(opt->var_arg);
      clear_given.set_group(opt->multiple && opt->group_value);
      clear_given.generate_clear_given(stream);
    }

  groups_collection_t::const_iterator end = gengetopt_groups.end();
  for ( groups_collection_t::const_iterator idx = gengetopt_groups.begin();
        idx != end; ++idx)
    {
      stream << indent_str;
      stream << ARGS_STRUCT << "->" << canonize_name (idx->first) << "_group_counter = 0 ;";
      stream << endl;
    }
}

void
CmdlineParserCreator::generate_reset_groups(ostream &stream, unsigned int indent)
{
  struct gengetopt_option * opt;
  string indent_str (indent, ' ');
  ostringstream body;
  reset_group_gen_class reset_group;
  clear_given_gen_class clear_given;
  clear_given.set_arg_struct(ARGS_STRUCT);

  reset_group.set_args_info (c_source_gen_class::args_info);

  groups_collection_t::const_iterator end = gengetopt_groups.end();
  for ( groups_collection_t::const_iterator idx = gengetopt_groups.begin();
        idx != end; ++idx)
    {
      body.str ("");
      bool found_option = false;
      bool multiple_arg = false;

      foropt
      {
        if (opt->group_value && strcmp(opt->group_value, idx->first.c_str()) == 0)
          {
            /* now we reset "given" fields */
            stream << indent_str;
            clear_given.set_var_arg(opt->var_arg);
            if (opt->multiple && opt->group_value)
              multiple_arg = true;
            clear_given.set_group(opt->multiple && opt->group_value);
            clear_given.generate_clear_given(body);

            free_option (opt, body, indent);
            found_option = true;
          }
      }

      if (found_option)
        {
          reset_group.set_multiple_arg(multiple_arg);
          reset_group.set_name (canonize_name (idx->first));
          reset_group.set_body (body.str ());
          reset_group.generate_reset_group (stream);
        }
    }
}

void
CmdlineParserCreator::free_option(struct gengetopt_option *opt,
                                  ostream &stream, unsigned int indent)
{
  if (! opt->type)
    return;

  if (opt->type != ARG_NO && opt->type != ARG_FLAG)
    {
      if (opt->multiple)
        {
          free_multiple_gen_class free_multiple;
          free_multiple.set_comment ("previous argument");
          free_multiple.set_has_string_type(opt->type == ARG_STRING);
          free_multiple.set_structure (ARGS_STRUCT);

          free_multiple.set_opt_var (opt->var_arg);
          free_multiple.generate_free_multiple
            (stream, indent);
        }
      else
        {
          free_string_gen_class free_string;
          free_string.set_comment ("previous argument");
          free_string.set_has_string_type(opt->type == ARG_STRING);
          free_string.set_structure (ARGS_STRUCT);

          free_string.set_opt_var (opt->var_arg);
          free_string.generate_free_string (stream, indent);
        }
    }
  else if (opt->multiple)
    {
      free_string_gen_class free_string;
      free_string.set_comment ("previous argument");
      free_string.set_structure (ARGS_STRUCT);

      // it's not really a string, but an array anyway
      free_string.set_opt_var (opt->var_arg);
      free_string.generate_free_string (stream, indent);
    }
}


void
CmdlineParserCreator::generate_struct_def(ostream &stream, unsigned int indent)
{
  struct gengetopt_option * opt;
  multiple_opt_struct_gen_class multiple_opt_struct;

  /* define structs for multiple options */
  foropt
    {
      if (opt->multiple && opt->type)
        {
          multiple_opt_struct.set_type (arg_types[opt->type]);
          multiple_opt_struct.set_arg_name (opt->var_arg);
          multiple_opt_struct.generate_multiple_opt_struct (stream, 0);
        }
    }
}

void
CmdlineParserCreator::generate_list_def(ostream &stream, unsigned int indent)
{
  struct gengetopt_option * opt;
  string indent_str (indent, ' ');
  multiple_opt_list_gen_class multiple_opt_list;
  bool generated_counter = false;

  /* define linked-list structs for multiple options */
  foropt
    {
      if (opt->multiple)
        {
          if (opt->type)
            {
              if (! generated_counter)
              {
                stream << indent_str;
                stream << "int i;        /* Counter */" << endl;
                generated_counter = true;
                stream << endl;
              }

              stream << indent_str;
              multiple_opt_list.set_arg_name (opt->var_arg);
              multiple_opt_list.generate_multiple_opt_list (stream, indent);
              stream << endl;
            }
        }
    }
}

void
CmdlineParserCreator::generate_multiple_fill_array(ostream &stream, unsigned int indent)
{
  struct gengetopt_option * opt;
  string indent_str (indent, ' ');
  multiple_fill_array_gen_class filler;

  /* copy linked list into the array */
  foropt
    {
      if (opt->multiple && opt->type)
        {
          stream << indent_str;
          filler.set_type (arg_types[opt->type]);
          filler.set_option_var_name (opt->var_arg);
          filler.generate_multiple_fill_array (stream, indent);

          if (opt->default_given)
            {
              multiple_fill_array_default_gen_class def_filler;
              string def_value = opt->default_string;

              def_filler.set_type (arg_types[opt->type]);
              def_filler.set_option_var_name (opt->var_arg);
              if (opt->type == ARG_STRING)
                def_value = "gengetopt_strdup(\"" +
                  def_value + "\")";
              def_filler.set_default_value (def_value);
              def_filler.generate_multiple_fill_array_default (stream, indent);
            }

          stream << endl;
        }
    }
}

void
CmdlineParserCreator::generate_update_multiple_given(ostream &stream, unsigned int indent)
{
  if (! has_multiple_options())
    return;

  string indent_str (indent, ' ');

  stream << endl;
  stream << indent_str;

  update_given_gen_class update_given_gen;
  struct gengetopt_option * opt;

  foropt
    {
      if (opt->multiple)
        {
          update_given_gen.set_option_var_name (opt->var_arg);
          update_given_gen.generate_update_given (stream, indent);
        }
    }
}

void
CmdlineParserCreator::generate_clear_arg(ostream &stream, unsigned int indent)
{
  struct gengetopt_option * opt;
  clear_arg_gen_class clear_arg;

  /* now we initialize value fields */
  foropt
    {
      if (opt->type == ARG_NO)
        continue;

      clear_arg.set_name(opt->var_arg);
      clear_arg.set_suffix("arg");
      clear_arg.set_value("NULL");
      clear_arg.set_has_orig(opt->type != ARG_FLAG);
      clear_arg.set_has_arg(false);

      if (opt->multiple && opt->type)
        {
          clear_arg.set_has_arg(true);
        }
      else if (opt->type == ARG_STRING)
        {
          clear_arg.set_has_arg(true);
          if (opt->default_given)
            clear_arg.set_value
                ("gengetopt_strdup (\"" + string(opt->default_string) +
                "\")");
        }
      else if (opt->type == ARG_FLAG)
        {
          clear_arg.set_has_arg(true);
          clear_arg.set_suffix("flag");
          clear_arg.set_value(opt->flagstat ? "1" : "0");
        }
      else if (opt->default_given)
        {
          clear_arg.set_has_arg(true);
          clear_arg.set_value(opt->default_string);
        }

      clear_arg.generate_clear_arg(stream, indent);
    }
}

void
CmdlineParserCreator::generate_long_option_struct(ostream &stream,
                                                  unsigned int indent)
{
  string indent_str (indent, ' ');
  struct gengetopt_option * opt;

  foropt
    {
      stream << indent_str;

      stream << "{ \"" << opt->long_opt << "\",\t"
             << (opt->type == ARG_NO || opt->type == ARG_FLAG ? 0 :
                 (opt->arg_is_optional ? 2 : 1))
             << ", NULL, ";

      if (opt->short_opt)
        stream << "\'" << opt->short_opt << "\'";
      else
        stream << "0";

      stream << " }," << endl;
    }
}

string
CmdlineParserCreator::generate_getopt_string()
{
  struct gengetopt_option * opt;
  ostringstream built_getopt_string;

  foropt
    if (opt->short_opt)
      {
        built_getopt_string << opt->short_opt <<
          (opt->type == ARG_NO || opt->type == ARG_FLAG ? "" : ":");
        built_getopt_string <<
          (opt->arg_is_optional ? ":" : "");
      }

  return built_getopt_string.str ();
}

void
CmdlineParserCreator::generate_handle_help(ostream &stream,
                                           unsigned int indent)
{
 if (no_handle_help)
   {
     generic_option_gen_class help_gen;
     help_gen.set_long_option (HELP_LONG_OPT);
     help_gen.set_short_option (HELP_SHORT_OPT_STR);
     help_gen.set_option_comment (HELP_OPT_DESCR);
     help_gen.set_option_var_name (HELP_LONG_OPT);
     help_gen.set_package_var_name (EXE_NAME);
     help_gen.set_has_short_option (true);

     help_gen.generate_generic_option (stream, indent);

     string indent_str (indent + 2, ' ');
     stream << parser_function_name << "_free (&local_args_info);\n";
     stream << indent_str;
     stream << "return 0;";
   }
 else
   {
     handle_help_gen_class help_gen;
     help_gen.set_parser_name (parser_function_name);
     help_gen.generate_handle_help (stream, indent);
   }
}

void
CmdlineParserCreator::generate_handle_version(ostream &stream,
                                              unsigned int indent)
{
 if (no_handle_version)
   {
     generic_option_gen_class version_gen;
     version_gen.set_long_option (VERSION_LONG_OPT);
     version_gen.set_short_option (VERSION_SHORT_OPT_STR);
     version_gen.set_option_comment (VERSION_OPT_DESCR);
     version_gen.set_option_var_name (VERSION_LONG_OPT);
     version_gen.set_package_var_name (EXE_NAME);
     version_gen.set_has_short_option (true);

     version_gen.generate_generic_option (stream, indent);

     string indent_str (indent + 2, ' ');
     stream << parser_function_name << "_free (&local_args_info);\n";
     stream << indent_str;
     stream << "return 0;";
   }
 else
   {
     handle_version_gen_class version_gen;
     version_gen.set_parser_name (parser_function_name);
     version_gen.generate_handle_version (stream, indent);
   }
}

void
CmdlineParserCreator::generate_handle_no_short_option(ostream &stream,
                                                      unsigned int indent)
{
  handle_options(stream, indent, false);
}

void
CmdlineParserCreator::generate_handle_option(ostream &stream,
                                             unsigned int indent)
{
  handle_options(stream, indent, true);
}

void
CmdlineParserCreator::handle_options(ostream &stream, unsigned int indent, bool has_short)
{
  const string tmpvar("multi_token"); // reuse the `c' variable (returning getopt_long value)
  const string optarg("optarg");

  struct gengetopt_option * opt;
  generic_option_gen_class option_gen;
  multiple_option_gen_class multip_opt_gen;
  string indent_str (indent, ' ');
  bool first = true;

  option_gen.set_package_var_name (EXE_NAME);
  option_gen.set_has_short_option (has_short);
  multip_opt_gen.set_package_var_name (EXE_NAME);
  multip_opt_gen.set_has_short_option (has_short);

  foropt
    {
      if ((has_short && opt->short_opt) || (!has_short && !opt->short_opt))
        {
          if (has_short || first)
            stream << indent_str;

          if (opt->short_opt == HELP_SHORT_OPT && strcmp(opt->long_opt, HELP_LONG_OPT) == 0) {
            generate_handle_help(stream, indent);
            stream << endl;
            stream << endl;
            continue;
          }

          if (opt->short_opt == VERSION_SHORT_OPT && strcmp(opt->long_opt, VERSION_LONG_OPT) == 0) {
            generate_handle_version(stream, indent);
            stream << endl;
            stream << endl;
            continue;
          }

          string short_opt (1, opt->short_opt);
          if (opt->multiple)
            {
              ostringstream list_stream;
              ostringstream str_stream;

              multip_opt_gen.set_short_option (short_opt);
              multip_opt_gen.set_option_comment (opt->desc);
              multip_opt_gen.set_long_option (opt->long_opt);
              multip_opt_gen.set_option_var_name (opt->var_arg);
              multip_opt_gen.set_option_has_values (opt->acceptedvalues != 0);
              multip_opt_gen.set_option_values (OPTION_VALUES_NAME(opt->var_arg));

              if (opt->type)
                { // arguments possibly exists
                    if (opt->acceptedvalues != 0) {
                        // we take the argument from the vector of values
                        string optarg_ = OPTION_VALUES_NAME(opt->var_arg) + "[found]";
                        do_update_arg (opt, str_stream, 0, optarg_, tmpvar);
                    } else {
                        do_update_arg (opt, str_stream, 0, tmpvar, tmpvar);
                    }
                  multip_opt_gen.set_option_has_type(true);

                  multip_opt_gen.set_update_arg(str_stream.str());
                }
              else
                multip_opt_gen.set_option_has_type(false);

              generic_option_group_gen_class group_gen;
              if (opt->group_value)
                {
                  multip_opt_gen.set_group_var_name (canonize_name (opt->group_value));
                  multip_opt_gen.set_option_has_group(true);
                }
              else
                multip_opt_gen.set_option_has_group(false);

              multip_opt_gen.generate_multiple_option (stream, indent);
            }
          else
            {
              option_gen.set_short_option (short_opt);
              option_gen.set_option_comment (opt->desc);
              option_gen.set_long_option (opt->long_opt);
              option_gen.set_option_var_name (opt->var_arg);
              option_gen.set_option_has_values (opt->acceptedvalues != 0);
              option_gen.set_option_values (OPTION_VALUES_NAME(opt->var_arg));

              ostringstream update_stream;

              generic_option_group_gen_class group_gen;
              if (opt->group_value)
                {
                  ostringstream group_stream;

                  group_stream << endl;
                  group_stream << "  ";
                  group_gen.set_group_var_name
                    (canonize_name (opt->group_value));
                  group_gen.generate_generic_option_group (group_stream, 2);
                  option_gen.set_update_group_count (group_stream.str ());
                }
              else
                option_gen.set_update_group_count ("");

              if (opt->acceptedvalues != 0) {
                  // we take the argument from the vector of values
                  string optarg_ = OPTION_VALUES_NAME(opt->var_arg) + "[found]";
                  do_update_arg (opt, update_stream, 0, optarg_, optarg);
              } else {
                  do_update_arg (opt, update_stream, 0);
              }

              option_gen.set_update_arg(update_stream.str());

              option_gen.generate_generic_option (stream, indent);

              if (opt->type != ARG_NO && has_short)
                generateBreak(stream, indent + 2);
            }

          if (has_short)
            {
              stream << endl;
              stream << endl;
            }

          if (first && !has_short)
            {
              first = false;
              option_gen.set_gen_else ("else ");
              multip_opt_gen.set_gen_else ("else ");
            }
        }
    }

  if (! first && !has_short) // something has been generated
    {
      generateBreak(stream, indent);
      stream << endl;
    }
}

#define GROUP_REQUIRED_COMPARISON "!="
#define GROUP_NOT_REQUIRED_COMPARISON ">"
#define GROUP_REQUIRED_MESSAGE "One"
#define GROUP_NOT_REQUIRED_MESSAGE "At most one"

void
CmdlineParserCreator::generate_handle_group(ostream &stream,
                                            unsigned int indent)
{
  group_option_gen_class opt_gen;
  string indent_str (indent, ' ');
  opt_gen.set_package_var_name (EXE_NAME);

  opt_gen.set_Comparison_rule(GROUP_NOT_REQUIRED_COMPARISON " 1");

  groups_collection_t::const_iterator end = gengetopt_groups.end();
  for ( groups_collection_t::const_iterator idx = gengetopt_groups.begin();
        idx != end; ++idx)
    {
      stream << indent_str;
      opt_gen.set_group_name (idx->first);
      opt_gen.set_group_var_name (canonize_name (idx->first));
      if (idx->second.required)
        {
          opt_gen.set_number_required(GROUP_REQUIRED_MESSAGE);
        }
      else
        {
          opt_gen.set_number_required(GROUP_NOT_REQUIRED_MESSAGE);
        }

      opt_gen.generate_group_option (stream, indent);
      stream << endl;
    }
}

void
CmdlineParserCreator::generate_handle_required(ostream &stream,
                                               unsigned int indent)
{
  struct gengetopt_option * opt;
  required_option_gen_class opt_gen;
  opt_gen.set_package_var_name ("prog_name");
  string indent_str (indent, ' ');

  /* write test for required options */
  foropt
    if ( opt->required )
      {
        stream << indent_str;

        ostringstream req_opt;
        req_opt << "'--" << opt->long_opt << "'";
        if (opt->short_opt)
          req_opt << " ('-" << opt->short_opt << "')";

        opt_gen.set_option_var_name (opt->var_arg);
        opt_gen.set_option_descr (req_opt.str ());

        opt_gen.generate_required_option (stream, indent);

        stream << endl;
      }

  // now generate the checks for required group options
  group_option_gen_class group_opt_gen;
  group_opt_gen.set_package_var_name ("prog_name");

  group_opt_gen.set_Comparison_rule("== 0");
  group_opt_gen.set_number_required(GROUP_REQUIRED_MESSAGE);

  groups_collection_t::const_iterator end = gengetopt_groups.end();
  for ( groups_collection_t::const_iterator idx = gengetopt_groups.begin();
        idx != end; ++idx)
  {
    if (idx->second.required)
    {
      stream << indent_str;
      group_opt_gen.set_group_name (idx->first);
      group_opt_gen.set_group_var_name (canonize_name (idx->first));

      group_opt_gen.generate_group_option (stream, indent);
      stream << endl;
    }
  }
}

void
CmdlineParserCreator::generate_handle_dependencies(ostream &stream,
                                               unsigned int indent)
{
  struct gengetopt_option * opt;
  dependant_option_gen_class opt_gen;
  opt_gen.set_package_var_name ("prog_name");
  string indent_str (indent, ' ');

  /* write test for required options */
  foropt
    if ( opt->dependon )
      {
        stream << indent_str;

        ostringstream req_opt;
        req_opt << "'--" << opt->long_opt << "'";
        if (opt->short_opt)
          req_opt << " ('-" << opt->short_opt << "')";

        opt_gen.set_option_var_name (opt->var_arg);
        opt_gen.set_dep_option (canonize_name(opt->dependon));
        opt_gen.set_option_descr (req_opt.str ());
        opt_gen.set_dep_option_descr (opt->dependon);

        opt_gen.generate_dependant_option (stream, indent);

        stream << endl;
      }
}

void
CmdlineParserCreator::generate_group_counters(ostream &stream,
                                              unsigned int indent)
{
  group_counter_gen_class counter_gen;
  string indent_str (indent, ' ');

  groups_collection_t::const_iterator end = gengetopt_groups.end();
  for ( groups_collection_t::const_iterator idx = gengetopt_groups.begin();
        idx != end; ++idx)
    {
      stream << indent_str;
      counter_gen.set_group_name (canonize_name (idx->first));
      counter_gen.generate_group_counter (stream, indent);
      stream << endl;
    }
}

int
CmdlineParserCreator::generate_source ()
{
  /* ****************************************************** */
  /* ********************************************** C FILE  */
  /* ****************************************************** */

  set_usage_string (generate_usage_string ());
  set_getopt_string (generate_getopt_string ());

  ofstream *output_file = open_fstream (c_filename);
  generate_c_source (*output_file);
  output_file->close ();
  delete output_file;

  return 0;
}

void
CmdlineParserCreator::generate_free(ostream &stream,
                                    unsigned int indent)
{
  string indent_str (indent, ' ');
  struct gengetopt_option * opt;

  stream << endl;
  stream << indent_str;

  if (unamed_options || has_multiple_options_string ())
    {
      stream << "unsigned int i;";
      stream << endl;
      stream << indent_str;
    }

  foropt
    {
      free_option (opt, stream, indent);
    }

  if (unamed_options)
    {
      stream << endl;
      stream << indent_str;

      free_inputs_string_gen_class free_inputs_string;
      free_inputs_string.set_structure (ARGS_STRUCT);
      free_inputs_string.generate_free_inputs_string (stream, indent);
    }
}

void
CmdlineParserCreator::generate_list_free(ostream &stream,
                                         unsigned int indent)
{
  struct gengetopt_option * opt;

  if (! has_multiple_options())
    return;

  free_list_gen_class free_list;

  foropt
    {
      if (opt->multiple && opt->type) {
        free_list.set_list_name(opt->var_arg);
        free_list.set_string_list(opt->type == ARG_STRING);
        free_list.generate_free_list(stream, indent);
      }
    }
}

void
CmdlineParserCreator::generate_file_save_loop(ostream &stream, unsigned int indent)
{
  struct gengetopt_option * opt;

  file_save_multiple_gen_class file_save_multiple;
  const string suffix = "_orig";
  const string suffix_given = "_given";

  foropt {
    file_save_gen_class file_save;
    file_save.set_opt_name(opt->long_opt);

    if (opt->multiple) {
      file_save.set_check_given(false);
    } else {
      file_save.set_check_given(true);
      file_save.set_given(opt->var_arg + suffix_given);
    }

    if (opt->type != ARG_NO && opt->type != ARG_FLAG) {
      file_save.set_arg(opt->var_arg + suffix + (opt->multiple ? " [i]" : ""));
      file_save.set_has_arg(true);
    } else {
      file_save.set_has_arg(false);
    }

    if (opt->multiple) {
      ostringstream buffer;

      file_save.generate_file_save(buffer, indent);

      file_save_multiple.set_has_arg(opt->type != ARG_NO);
      file_save_multiple.set_opt_var(opt->var_arg);
      file_save_multiple.set_opt_name(opt->long_opt);
      file_save_multiple.set_write_cmd(buffer.str());

      file_save_multiple.generate_file_save_multiple(stream, indent);
    } else {
      file_save.generate_file_save(stream, indent);
    }
  }
}


