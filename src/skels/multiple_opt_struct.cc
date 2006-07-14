/*
 * File automatically generated by
 * gengen 0.6 by Lorenzo Bettini 
 * http://www.lorenzobettini.it/software/gengen
 */

#include "multiple_opt_struct.h"

void
multiple_opt_struct_gen_class::generate_multiple_opt_struct(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  stream << "struct ";
  generate_string (list_name, stream, indent + indent_str.length ());
  stream << "_list";
  stream << "\n";
  stream << indent_str;
  stream << "{";
  stream << "\n";
  stream << indent_str;
  indent = 2;
  stream << "  ";
  generate_string (type, stream, indent + indent_str.length ());
  stream << " arg;";
  indent = 0;
  stream << "\n";
  stream << indent_str;
  stream << "  char *orig;";
  stream << "\n";
  stream << indent_str;
  stream << "  struct ";
  generate_string (list_name, stream, indent + indent_str.length ());
  stream << "_list * next;";
  stream << "\n";
  stream << indent_str;
  stream << "};";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
}
