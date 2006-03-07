/* uses more than one gengetopt generated parsers */

#include <stdlib.h>
#include <stdio.h>

#include "test_all_opts_cmd.h"
#include "test_conf_parser_cmd.h"

static struct gengetopt_args_info args_info;
static struct my_args_info my_args_info;

int
main(int argc, char **argv)
{
  char *argv_for_args_info[] = {"more_cmdparsers", "-r10", 0};
  if (test_all_opts_cmd_parser (2, argv_for_args_info, &args_info) != 0)
    exit(1) ;

  printf("arg for -r: %s\n", args_info.required_arg);

  test_all_opts_cmd_parser_free(&args_info);

  char *argv_for_my_args_info[] = {"more_cmdparsers", "-r20", "-ahello", 0};
  if (test_conf_parser_cmd_parser 
      (3, argv_for_my_args_info, &my_args_info) != 0)
    exit(1) ;

  printf("arg for -r: %s\n", my_args_info.required_arg);
  printf("arg for -a: %s\n", my_args_info.opta_arg);

  test_conf_parser_cmd_parser_free (&my_args_info);

  return 0;
}
