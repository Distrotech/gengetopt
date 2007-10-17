/*
 * File automatically generated by
 * gengen 1.1 by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#include "handle_version.h"

void
handle_version_gen_class::generate_handle_version(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  if (short_opt)
    {
      stream << "case 'V':	/* Print version and exit.  */";
      stream << "\n";
      stream << indent_str;
    }
  else
    {
      stream << "if (strcmp (long_options[option_index].name, \"version\") == 0) {";
      stream << "\n";
      stream << indent_str;
    }
  stream << "  ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_print_version ();";
  stream << "\n";
  stream << indent_str;
  indent = 2;
  stream << "  ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_free (&local_args_info);";
  indent = 0;
  stream << "\n";
  stream << indent_str;
  stream << "  exit (EXIT_SUCCESS);";
  if (( ! short_opt ))
    {
      stream << "\n";
      stream << indent_str;
      stream << "}";
    }
}
