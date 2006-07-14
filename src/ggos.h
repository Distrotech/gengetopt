/*
This file is licensed to you under the license specified in the included file
`LICENSE'. Look there for further details.
*/


#ifndef _GENGETOPT_GGOS_H
#define _GENGETOPT_GGOS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <list>
#include <iostream>

#include "acceptedvalues.h"
#include "argsdef.h"

struct gengetopt_option
{
  char short_opt;
  char * long_opt;
  char * desc;
  int type; /* values in `argsdef.h' */
  int flagstat ;
  int required;
  char * var_arg; /* canonized long_opt + "_arg" = argument var */
  int default_given ; /* if a default is given */
  char * default_string ; /* default value for this option, if string */
  char * group_value; /* group name, if it's part of an option group */
  char * group_desc; /* group description, if it's part of an option group */
  bool multiple; /* whether this option can be given more than once */
  char * multiple_min; /* minimum occurrences of a multiple option (-1: not specified) */
  char * multiple_max; /* maximum occurrences of a multiple option (-1: not specified) */
  bool arg_is_optional; /* whether the argument is optional */
  bool hidden; /* whether this option will be hidden from the help output */
  char *type_str; /* Alternative name for type,
                     e.g. "URL" or "SECONDS" */
  const AcceptedValues *acceptedvalues; /* values that can be passed to this option */
  char *section; /* the section of this option */
  char *section_desc; /* the description associated with the possible section */
  char *dependon; /* the name of the option this one depends on */
  
  /* parser information */
  char *filename; /* source file */
  int linenum; /* line number */
  
  gengetopt_option() :
    short_opt(0), long_opt(0), desc(0), type(ARG_NO),
    flagstat(-1),
    required(1), var_arg(0), default_string(0),
    group_value(0), group_desc(0),
    multiple(false), arg_is_optional(false), hidden(false),
    type_str(0), acceptedvalues(0),
    section(0), section_desc(0), dependon(0),
    filename(0), linenum(0)
    {
    }
};

typedef std::list<gengetopt_option *> gengetopt_option_list;

std::ostream & operator <<(std::ostream &s, gengetopt_option &opt);

#endif /* _GENGETOPT_GGOS_H */
