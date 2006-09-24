/**
 * Copyright (C) 1999-2005  Free Software Foundation, Inc.
 *
 * This file is part of GNU gengetopt
 *
 * GNU gengetopt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * GNU gengetopt is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with gengetopt; see the file COPYING. If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


%{
#include <string.h>

#ifndef HAVE_STRDUP
extern "C" char *strdup (const char *s) ;
#endif

#include "argsdef.h"
#include "parser.h"
extern int gengetopt_count_line;

static void update_count_line (char *str);
static void updateTokenInfo (int pos);

#define LINEBUF_LEN 1024

#define PUSH(s) yy_push_state(s);
#define POP() yy_pop_state();

int tokenpos = 0;
char linebuf[LINEBUF_LEN] ; /* current line */

%}

%option stack nomain yylineno noyywrap nounput

ws [ ]+
tabs [\t]+

%s SIZE_STATE

%%


string		updateTokenInfo (-1); yylval.argtype = ARG_STRING; return TOK_ARGTYPE;
int		updateTokenInfo (-1); yylval.argtype = ARG_INT; return TOK_ARGTYPE;
short		updateTokenInfo (-1); yylval.argtype = ARG_SHORT; return TOK_ARGTYPE;
long		updateTokenInfo (-1); yylval.argtype = ARG_LONG; return TOK_ARGTYPE;
float		updateTokenInfo (-1); yylval.argtype = ARG_FLOAT; return TOK_ARGTYPE;
double		updateTokenInfo (-1); yylval.argtype = ARG_DOUBLE; return TOK_ARGTYPE;
longdouble	updateTokenInfo (-1); yylval.argtype = ARG_LONGDOUBLE; return TOK_ARGTYPE;
longlong	updateTokenInfo (-1); yylval.argtype = ARG_LONGLONG; return TOK_ARGTYPE;

package        	updateTokenInfo (-1); return TOK_PACKAGE;
version        	updateTokenInfo (-1); return TOK_VERSION;
groupoption     updateTokenInfo (-1); yylloc.first_line = gengetopt_count_line; return TOK_GROUPOPTION;
yes|required    updateTokenInfo (-1); return TOK_YES;
no|optional	updateTokenInfo (-1); return TOK_NO;
option		updateTokenInfo (-1); yylloc.first_line = gengetopt_count_line; return TOK_OPTION;
flag		updateTokenInfo (-1); return TOK_FLAG;
on	        updateTokenInfo (-1); return TOK_ON;
off	        updateTokenInfo (-1); return TOK_OFF;
purpose		updateTokenInfo (-1); return TOK_PURPOSE;
default		updateTokenInfo (-1); return TOK_DEFAULT;
typestr		updateTokenInfo (-1); return TOK_TYPESTR;
group		updateTokenInfo (-1); return TOK_GROUP;
groupdesc	updateTokenInfo (-1); return TOK_GROUPDESC;
defgroup	updateTokenInfo (-1); return TOK_DEFGROUP;
multiple	updateTokenInfo (-1); return TOK_MULTIPLE;
argoptional	updateTokenInfo (-1); return TOK_ARGOPTIONAL;
sectiondesc     updateTokenInfo (-1); return TOK_SECTIONDESC;
section         updateTokenInfo (-1); return TOK_SECTION;
values          updateTokenInfo (-1); return TOK_VALUES;
hidden		updateTokenInfo (-1); return TOK_HIDDEN;
dependon	updateTokenInfo (-1); return TOK_DEPENDON;
text    	updateTokenInfo (-1); return TOK_TEXT;
args    	updateTokenInfo (-1); return TOK_ARGS;

"=" { updateTokenInfo (-1); return '='; }
"," { updateTokenInfo (-1); return ','; }

"(" { PUSH(SIZE_STATE); updateTokenInfo (-1); return '('; }
<SIZE_STATE>"-" { updateTokenInfo (-1); return '-'; }
<SIZE_STATE>[[:digit:]]+ { updateTokenInfo (-1); yylval.str = strdup(yytext); return TOK_SIZE; }
")" { POP(); updateTokenInfo (-1); return ')'; }

[[:alnum:]-]	 updateTokenInfo (-1); yylval.chr = yytext[0]; return TOK_CHAR;
\"[^\"\n]*\"	{
  /* if you add or remove symbols, change canonize_vars
     function */
  updateTokenInfo (-1);
  yytext [strlen(yytext) - 1] = 0;
  yylval.str = yytext + 1;
  return TOK_STRING;
}

\"[^\"]*\"	{
  /* if you add or remove symbols, change canonize_vars
     function */
  updateTokenInfo (-1);
  yytext [strlen(yytext) - 1] = 0;
  yylval.str = yytext + 1;
  update_count_line (yylval.str);
  return TOK_MLSTRING;
}

{ws}           updateTokenInfo (-1);
{tabs}         updateTokenInfo (8*yyleng);

#[^\n]*		/* comments begin with # in any place */
\n.*		update_count_line (0); yyless(1) ; /* give back all but the \n to rescan */

\r              {}

.		{
  return 1000; /* little hack to produce a parse error too. */
}

%%

/*
  Otherwise '\n' within a TOK_MLSTRING would not be counted
*/
void
update_count_line (char *str)
{
  if (str)
    {
      char *p;
      for (p = str; *p; ++p)
        if (*p == '\n')
          ++gengetopt_count_line;
    }
  else
    {
      ++gengetopt_count_line;
      tokenpos = 0 ; /* reset token position */
      strncpy (linebuf, yytext+1, LINEBUF_LEN - 1); /* save the next line */
    }
}

void
updateTokenInfo( int pos )
{
  if ( pos >= 0 )
    tokenpos += pos ;
  else
    tokenpos += yyleng ;
}
