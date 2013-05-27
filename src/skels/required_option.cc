/*
 * File automatically generated by
 * gengen 1.4.3rc by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#include "required_option.h"

void
required_option_gen_class::generate_required_option(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  if (checkrange)
    {
      stream << "if (";
      generate_string (mode_condition, stream, indent + indent_str.length ());
      stream << "check_multiple_option_occurrences(";
      generate_string (package_var_name, stream, indent + indent_str.length ());
      stream << ", args_info->";
      generate_string (option_var_name, stream, indent + indent_str.length ());
      stream << "_given, args_info->";
      generate_string (option_var_name, stream, indent + indent_str.length ());
      stream << "_min, args_info->";
      generate_string (option_var_name, stream, indent + indent_str.length ());
      stream << "_max, \"";
      generate_string (option_descr, stream, indent + indent_str.length ());
      stream << "\"))";
      stream << "\n";
      stream << indent_str;
      stream << "   error = 1;";
      stream << "\n";
      stream << indent_str;
      stream << "\n";
      stream << indent_str;
    }
  else
    {
      stream << "if (";
      generate_string (mode_condition, stream, indent + indent_str.length ());
      stream << "! args_info->";
      generate_string (option_var_name, stream, indent + indent_str.length ());
      stream << "_given)";
      stream << "\n";
      stream << indent_str;
      stream << "  {";
      stream << "\n";
      stream << indent_str;
      stream << "    fprintf (stderr, GENGETOPT_(\"%s%s: %s option required\\n\"),";
      stream << "\n";
      stream << indent_str;
      stream << "	     ";
      generate_string (package_var_name, stream, indent + indent_str.length ());
      stream << ", error_location,";
      stream << "\n";
      stream << indent_str;
      stream << "	     \"";
      generate_string (option_descr, stream, indent + indent_str.length ());
      stream << "\");";
      stream << "\n";
      stream << indent_str;
      stream << "    error = 1;";
      stream << "\n";
      stream << indent_str;
      stream << "  }";
      stream << "\n";
      stream << indent_str;
      stream << "\n";
      stream << indent_str;
    }
}
