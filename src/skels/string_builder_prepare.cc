/*
 * File automatically generated by
 * gengen 1.4.3rc by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#include "string_builder_prepare.h"

void
string_builder_prepare_gen_class::generate_string_builder_prepare(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  if (( part_index == 0 ))
    {
      stream << "\n";
      stream << indent_str;
    }
  if (gengetopt_localised)
    {
      stream << "string_builder_parts[";
      stream << part_index;
      stream << "] = _G( \"";
      generate_string (value, stream, indent + indent_str.length ());
      stream << "\" );";
      stream << "\n";
      stream << indent_str;
    }
  else
    {
      if (localised)
        {
          stream << "string_builder_parts[";
          stream << part_index;
          stream << "] = _( \"";
          generate_string (value, stream, indent + indent_str.length ());
          stream << "\" );";
          stream << "\n";
          stream << indent_str;
        }
      else
        {
          stream << "string_builder_parts[";
          stream << part_index;
          stream << "] = \"";
          generate_string (value, stream, indent + indent_str.length ());
          stream << "\";";
          stream << "\n";
          stream << indent_str;
        }
    }
}
