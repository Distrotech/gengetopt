/* default_cmdline.c test */

/* the cmdline parser is generated with default names */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>

#include "cmdline.h"

static struct gengetopt_args_info args_info;

int
main (int argc, char **argv)
{  
  if (cmdline_parser (argc, argv, &args_info) != 0)
    exit(1) ;

  printf ("Value of foo: %d\n", args_info.foo_arg);
  printf ("Value of bar: %s\n", args_info.bar_arg);

  cmdline_parser_free (&args_info);

  return 0;
}
