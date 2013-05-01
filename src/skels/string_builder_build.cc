/*
 * File automatically generated by
 * gengen 1.4.3rc by Lorenzo Bettini 
 * http://www.gnu.org/software/gengen
 */

#include "string_builder_build.h"

void
string_builder_build_gen_class::generate_string_builder_build(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  if (( part_index == 0 ))
    {
      stream << "strcpy( ";
      generate_string (target, stream, indent + indent_str.length ());
      if (is_target_array)
        {
          stream << "[";
          generate_string (target_index, stream, indent + indent_str.length ());
          stream << "]";
        }
      stream << ", string_builder_parts[0] );";
      stream << "\n";
      stream << indent_str;
    }
  else
    {
      stream << "strcat( ";
      generate_string (target, stream, indent + indent_str.length ());
      if (is_target_array)
        {
          stream << "[";
          generate_string (target_index, stream, indent + indent_str.length ());
          stream << "]";
        }
      stream << ", string_builder_parts[";
      stream << part_index;
      stream << "] );";
      stream << "\n";
      stream << indent_str;
    }
}
