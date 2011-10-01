/*
This file is licensed to you under the license specified in the included file
`LICENSE'. Look there for further details.
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/*
  This function is called when found EOF.
 */
#include <stdio.h>

int
yywrap ()
{
  /* fprintf (stderr, "yywrap() called.\n"); */
  return 1;
}

