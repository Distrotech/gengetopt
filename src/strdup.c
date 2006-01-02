/* strdup.c replacement of strdup, which is not standard */

#include <stdlib.h>
#include <string.h>

char *
strdup (const char *s)
{
  char *result = (char*)malloc(strlen(s) + 1);

  if (result == (char*)0)
    return (char*)0;

  strcpy(result, s);

  return result;
}
