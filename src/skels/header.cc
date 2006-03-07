/*
 * File automatically generated by
 * gengen 0.6 by Lorenzo Bettini 
 * http://www.lorenzobettini.it/software/gengen
 */

#include "header.h"

void
header_gen_class::generate_header(ostream &stream, unsigned int indent)
{
  string indent_str (indent, ' ');
  indent = 0;

  stream << "/* ";
  generate_string (header_file_name, stream, indent + indent_str.length ());
  stream << ".h */";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "/* File autogenerated by gengetopt ";
  generate_string (generator_version, stream, indent + indent_str.length ());
  stream << "  */";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "#ifndef ";
  generate_string (ifndefname, stream, indent + indent_str.length ());
  stream << "_H";
  stream << "\n";
  stream << indent_str;
  stream << "#define ";
  generate_string (ifndefname, stream, indent + indent_str.length ());
  stream << "_H";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "/* If we use autoconf.  */";
  stream << "\n";
  stream << indent_str;
  stream << "#ifdef HAVE_CONFIG_H";
  stream << "\n";
  stream << indent_str;
  stream << "#include \"config.h\"";
  stream << "\n";
  stream << indent_str;
  stream << "#endif";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "#ifdef __cplusplus";
  stream << "\n";
  stream << indent_str;
  stream << "extern \"C\" {";
  stream << "\n";
  stream << indent_str;
  stream << "#endif /* __cplusplus */";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "#ifndef ";
  generate_string (package_var_name, stream, indent + indent_str.length ());
  stream << "\n";
  stream << indent_str;
  stream << "#define ";
  generate_string (package_var_name, stream, indent + indent_str.length ());
  stream << " ";
  generate_string (package_var_val, stream, indent + indent_str.length ());
  stream << "\n";
  stream << indent_str;
  stream << "#endif";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "#ifndef ";
  generate_string (version_var_name, stream, indent + indent_str.length ());
  stream << "\n";
  stream << indent_str;
  stream << "#define ";
  generate_string (version_var_name, stream, indent + indent_str.length ());
  stream << " ";
  generate_string (version_var_val, stream, indent + indent_str.length ());
  stream << "\n";
  stream << indent_str;
  stream << "#endif";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "struct ";
  generate_string (args_info, stream, indent + indent_str.length ());
  stream << "\n";
  stream << indent_str;
  stream << "{";
  stream << "\n";
  stream << indent_str;
  indent = 2;
  stream << "  ";
  if (option_arg.size () > 0)
    generate_string (option_arg, stream, indent + indent_str.length ());
  else
    generate_option_arg (stream, indent + indent_str.length ());
  indent = 0;
  stream << "\n";
  stream << indent_str;
  indent = 2;
  stream << "  ";
  if (option_given.size () > 0)
    generate_string (option_given, stream, indent + indent_str.length ());
  else
    generate_option_given (stream, indent + indent_str.length ());
  indent = 0;
  stream << "\n";
  stream << indent_str;
  indent = 2;
  if (group_counters.size () > 0)
    generate_string (group_counters, stream, indent + indent_str.length ());
  else
    generate_group_counters (stream, indent + indent_str.length ());
  indent = 0;
  stream << indent_str;
  stream << "} ;";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "int ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << " (int argc, char * const *argv, struct ";
  generate_string (args_info, stream, indent + indent_str.length ());
  stream << " *args_info);";
  stream << "\n";
  stream << indent_str;
  stream << "int ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "2 (int argc, char * const *argv, struct ";
  generate_string (args_info, stream, indent + indent_str.length ());
  stream << " *args_info, int override, int initialize, int check_required);";
  stream << "\n";
  stream << indent_str;
  stream << "int ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_file_save(const char *filename, struct ";
  generate_string (args_info, stream, indent + indent_str.length ());
  stream << " *args_info);";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "void ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_print_help(void);";
  stream << "\n";
  stream << indent_str;
  if (has_hidden)
    {
      stream << "void ";
      generate_string (parser_name, stream, indent + indent_str.length ());
      stream << "_print_full_help(void);";
      stream << "\n";
      stream << indent_str;
    }
  stream << "void ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_print_version(void);";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "void ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_init (struct ";
  generate_string (args_info, stream, indent + indent_str.length ());
  stream << " *args_info);";
  stream << "\n";
  stream << indent_str;
  stream << "void ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_free (struct ";
  generate_string (args_info, stream, indent + indent_str.length ());
  stream << " *args_info);";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  if (generate_config_parser)
    {
      stream << "int ";
      generate_string (parser_name, stream, indent + indent_str.length ());
      stream << "_configfile (char * const filename, struct ";
      generate_string (args_info, stream, indent + indent_str.length ());
      stream << " *args_info, int override, int initialize, int check_required);";
      stream << "\n";
      stream << indent_str;
      stream << "\n";
      stream << indent_str;
    }
  stream << "int ";
  generate_string (parser_name, stream, indent + indent_str.length ());
  stream << "_required (struct ";
  generate_string (args_info, stream, indent + indent_str.length ());
  stream << " *args_info, const char *prog_name);";
  stream << "\n";
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  if (option_values_decl.size () > 0)
    generate_string (option_values_decl, stream, indent + indent_str.length ());
  else
    generate_option_values_decl (stream, indent + indent_str.length ());
  stream << indent_str;
  stream << "\n";
  stream << indent_str;
  stream << "#ifdef __cplusplus";
  stream << "\n";
  stream << indent_str;
  stream << "}";
  stream << "\n";
  stream << indent_str;
  stream << "#endif /* __cplusplus */";
  stream << "\n";
  stream << indent_str;
  stream << "#endif /* ";
  generate_string (ifndefname, stream, indent + indent_str.length ());
  stream << "_H */";
  stream << "\n";
  stream << indent_str;
}
