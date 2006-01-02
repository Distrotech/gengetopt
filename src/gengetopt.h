/**
 * Copyright (C) 1999, 2000, 2001  Free Software Foundation, Inc.
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

#ifndef _GENGETOPT_H
#define _GENGETOPT_H

#include "acceptedvalues.h"
#include "ggos.h"

int gengetopt_define_package (char * s) ;
int gengetopt_define_version (char * s) ;
int gengetopt_define_purpose (char * s) ;
void gengetopt_set_section (const char * s, const char *sd) ;
int gengetopt_add_group (const char * s, const char *desc, int required) ;
int gengetopt_has_option (const char * long_opt, char short_opt);
int gengetopt_add_option (const char * long_opt, char short_opt,
                          const char * desc,
                          int type, int flagstat, int required,
                          const char *default_value,
                          const char * group_value,
                          const char * type_str,
                          const AcceptedValues *acceptedvalues,
                          int multiple = 0,
                          int argoptional = 0);
int gengetopt_create_option (gengetopt_option *&opt, const char * long_opt, char short_opt,
                          const char * desc,
                          int type, int flagstat, int required,
                          const char *default_value,
                          const char * group_value,
                          const char * type_str,
                          const AcceptedValues *acceptedvalues,
                          int multiple = 0,
                          int argoptional = 0);

int gengetopt_has_option (gengetopt_option *opt);
int gengetopt_check_option (gengetopt_option *opt,
    bool groupoption);
int gengetopt_add_option (gengetopt_option *opt);

#endif /* _GENGETOPT_H */
