//
// C++ Implementation: fileutils
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdio.h>
#include <stdlib.h>

#include "fileutils.h"

char *
create_filename (char *name, char *ext)
{
  char *filename ;

  filename = (char *) malloc (strlen (name) + strlen (ext) + 2);
  /* 2 = 1 for the . and one for the '\0' */
  if (! filename)
    {
      fprintf (stderr, "Error in memory allocation! %s %d\n",
               __FILE__, __LINE__);
      abort ();
    }

  sprintf (filename, "%s.%s", name, ext);

  return filename ;
}

ofstream *
open_fstream (char *filename)
{
  ofstream *fstream = new ofstream (filename);

  if ( ! (*fstream) )
    {
      fprintf( stderr, "Error creating %s\n", filename ) ;
      abort() ;
    }

  return fstream;
}
