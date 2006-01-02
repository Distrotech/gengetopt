/* test_values.c test */

/* test values options */

#include <stdlib.h>
#include <stdio.h>

#include "test_values_cmd.h"

static struct gengetopt_args_info args_info;

int
main (int argc, char **argv)
{
  unsigned int i;
  int result = 0;

  if (test_values_cmd_parser (argc, argv, &args_info) != 0) {
    result = 1;
    goto end;
  }

  if (args_info.string_values_given)
    {
      printf ("specified --string-values with argument %s\n", args_info.string_values_arg);
      printf ("specified --string-values with (original) argument %s\n", args_info.string_values_orig);
    }

  printf ("specified --string-values-def with argument %s\n", args_info.string_values_def_arg);

  if (args_info.string_values_no_short_given)
    {
      printf ("specified --string-values-no-short with argument %s\n", args_info.string_values_no_short_arg);
    }

  for (i = 0; i < args_info.multistring_values_given; ++i) 
    {
      printf ("specified --multistring-values with argument %s\n", args_info.multistring_values_arg[i]);
      printf ("specified --multistring-values with (original) argument %s\n", args_info.multistring_values_orig[i]);
    }

  for (i = 0; i < args_info.multistring_values_no_short_given; ++i)
    printf ("specified --multistring-values-no-short with argument %s\n", args_info.multistring_values_no_short_arg[i]);

 end:
  test_values_cmd_parser_free (&args_info);

  return result;
}
