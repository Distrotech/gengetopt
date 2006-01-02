/*
 * File automatically generated by
 * gengen 0.6 by Lorenzo Bettini 
 * http://www.lorenzobettini.it/software/gengen
 */

#include "update_arg.h"

void
update_arg_gen_class::generate_update_arg(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  if (int_arg)
    {
      generate_string (structure, stream, indent + indent_str.length ());
      stream << "->";
      generate_string (opt_var, stream, indent + indent_str.length ());
      stream << "_arg = ";
      generate_string (cast, stream, indent + indent_str.length ());
      stream << "strtol (";
      generate_string (optarg, stream, indent + indent_str.length ());
      stream << ", &stop_char, 0);";
    }
  else
    {
      if (flag_arg)
        {
          stream << "args_info->";
          generate_string (opt_var, stream, indent + indent_str.length ());
          stream << "_flag = !(args_info->";
          generate_string (opt_var, stream, indent + indent_str.length ());
          stream << "_flag);";
        }
      else
        {
          if (long_arg)
            {
              generate_string (structure, stream, indent + indent_str.length ());
              stream << "->";
              generate_string (opt_var, stream, indent + indent_str.length ());
              stream << "_arg = ";
              generate_string (cast, stream, indent + indent_str.length ());
              stream << "strtol (";
              generate_string (optarg, stream, indent + indent_str.length ());
              stream << ", &stop_char, 0);";
            }
          else
            {
              if (float_arg)
                {
                  generate_string (structure, stream, indent + indent_str.length ());
                  stream << "->";
                  generate_string (opt_var, stream, indent + indent_str.length ());
                  stream << "_arg = ";
                  generate_string (cast, stream, indent + indent_str.length ());
                  stream << "strtod (";
                  generate_string (optarg, stream, indent + indent_str.length ());
                  stream << ", &stop_char);";
                }
              else
                {
                  if (longlong_arg)
                    {
                      stream << "#ifdef HAVE_LONG_LONG";
                      stream << "\n";
                      stream << indent_str;
                      generate_string (structure, stream, indent + indent_str.length ());
                      stream << "->";
                      generate_string (opt_var, stream, indent + indent_str.length ());
                      stream << "_arg = (long long int) strtol (";
                      generate_string (optarg, stream, indent + indent_str.length ());
                      stream << ", &stop_char, 0);";
                      stream << "\n";
                      stream << indent_str;
                      stream << "#else";
                      stream << "\n";
                      stream << indent_str;
                      generate_string (structure, stream, indent + indent_str.length ());
                      stream << "->";
                      generate_string (opt_var, stream, indent + indent_str.length ());
                      stream << "_arg = (long) strtol (";
                      generate_string (optarg, stream, indent + indent_str.length ());
                      stream << ", &stop_char, 0);";
                      stream << "\n";
                      stream << indent_str;
                      stream << "#endif";
                    }
                  else
                    {
                      if (string_arg)
                        {
                          if (no_free)
                            {
                              generate_string (structure, stream, indent + indent_str.length ());
                              stream << "->";
                              generate_string (opt_var, stream, indent + indent_str.length ());
                              stream << "_arg = gengetopt_strdup (";
                              generate_string (optarg, stream, indent + indent_str.length ());
                              stream << ");";
                            }
                          else
                            {
                              stream << "if (";
                              generate_string (structure, stream, indent + indent_str.length ());
                              stream << "->";
                              generate_string (opt_var, stream, indent + indent_str.length ());
                              stream << "_arg)";
                              stream << "\n";
                              stream << indent_str;
                              stream << "  free (";
                              generate_string (structure, stream, indent + indent_str.length ());
                              stream << "->";
                              generate_string (opt_var, stream, indent + indent_str.length ());
                              stream << "_arg); /* free previous string */";
                              stream << "\n";
                              stream << indent_str;
                              generate_string (structure, stream, indent + indent_str.length ());
                              stream << "->";
                              generate_string (opt_var, stream, indent + indent_str.length ());
                              stream << "_arg = gengetopt_strdup (";
                              generate_string (optarg, stream, indent + indent_str.length ());
                              stream << ");";
                            }
                        }
                    }
                }
            }
        }
    }
  if (numeric)
    {
      stream << "\n";
      stream << indent_str;
      stream << "if (!(stop_char && *stop_char == '\\0')) {";
      stream << "\n";
      stream << indent_str;
      stream << "  fprintf(stderr, \"%s: invalid numeric value: %s\\n\", ";
      generate_string (package_var_name, stream, indent + indent_str.length ());
      stream << ", ";
      generate_string (optarg, stream, indent + indent_str.length ());
      stream << ");";
      stream << "\n";
      stream << indent_str;
      stream << "  goto failure;";
      stream << "\n";
      stream << indent_str;
      stream << "}";
    }
  if (has_arg)
    {
      stream << "\n";
      stream << indent_str;
      if (no_free)
        {
          generate_string (structure, stream, indent + indent_str.length ());
          stream << "->";
          generate_string (opt_var, stream, indent + indent_str.length ());
          stream << "_orig = ";
          generate_string (orig_optarg, stream, indent + indent_str.length ());
          stream << ";";
        }
      else
        {
          stream << "if (";
          generate_string (structure, stream, indent + indent_str.length ());
          stream << "->";
          generate_string (opt_var, stream, indent + indent_str.length ());
          stream << "_orig)";
          stream << "\n";
          stream << indent_str;
          stream << "  free (";
          generate_string (structure, stream, indent + indent_str.length ());
          stream << "->";
          generate_string (opt_var, stream, indent + indent_str.length ());
          stream << "_orig); /* free previous string */";
          stream << "\n";
          stream << indent_str;
          generate_string (structure, stream, indent + indent_str.length ());
          stream << "->";
          generate_string (opt_var, stream, indent + indent_str.length ());
          stream << "_orig = gengetopt_strdup (";
          generate_string (orig_optarg, stream, indent + indent_str.length ());
          stream << ");";
        }
    }
}
