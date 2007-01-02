//
// C++ Interface: gm_utils
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifndef GM_UTILS_H
#define GM_UTILS_H

#include <string>

#include "ggos.h"

using std::string;

char *canonize_names(const char * name);
const string canonize_name(const string &name);
const string strip_path(const string &);
const string to_upper(const string &);

bool has_multiple_options_string();
bool has_multiple_options();
bool has_multiple_options_with_type();
bool has_required();
bool has_dependencies();
bool has_options();
bool has_hidden_options();
bool has_values();

/**
 * Whether the specified option deals with number
 *
 * @param opt
 * @return
 */
bool is_numeric(const gengetopt_option *opt);

/**
 * Performs word wrapping on the passed string (and return the result in the first
 * parameter).
 *
 * @param wrapped the output parameter
 * @param from_column the string start from this column
 * @param second_indent an additional indentation for lines after the
 * first one
 * @param orig the original string that must be wrapped
 */
void wrap_cstr (string &wrapped, unsigned int from_column, unsigned int second_indent, const string &orig);

#endif
