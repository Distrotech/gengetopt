/*
 * File automatically generated by
 * gengen 0.6 by Lorenzo Bettini 
 * http://www.lorenzobettini.it/software/gengen
 */

#include "copyright.h"

void
copyright_gen_class::generate_copyright(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  stream << "Copyright (C) ";
  generate_string (year, stream, indent + indent_str.length ());
  stream << "  Free Software Foundation Inc.";
  stream << "\n";
  stream << indent_str;
  stream << "This program comes with ABSOLUTELY NO WARRANTY; for details";
  stream << "\n";
  stream << indent_str;
  stream << "please see the file 'COPYING' supplied with the source code.";
  stream << "\n";
  stream << indent_str;
  stream << "This is free software, and you are welcome to redistribute it";
  stream << "\n";
  stream << indent_str;
  stream << "under certain conditions; again, see 'COPYING' for details.";
  stream << "\n";
  stream << indent_str;
  stream << "This program is released under the GNU General Public License.";
  stream << "\n";
  stream << indent_str;
}
