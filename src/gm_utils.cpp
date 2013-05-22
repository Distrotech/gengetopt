//
// C++ Implementation: gm_utils
//
// Description:
//
//
// Author: Lorenzo Bettini <http://www.lorenzobettini.it>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>
#include <sstream>

#include "gm_utils.h"
#include "ggo_options.h"
#include "argsdef.h"
#include "groups.h"

using namespace std;

extern groups_collection_t gengetopt_groups;

char *
canonize_names(const char *name) {
    char *pvar;
    char *p;

    pvar = strdup(name);

    for (p = pvar; *p; ++p)
        if (*p == '.' || *p == '-')
            *p = '_';

    return pvar;
}

// remove the path from the file name
const string strip_path(const string &s) {
    string::size_type pos_of_sep;

    pos_of_sep = s.rfind("/");
    if (pos_of_sep == string::npos)
        pos_of_sep = s.rfind("\\"); // try also with DOS path sep

    if (pos_of_sep == string::npos)
        return s; // no path

    return s.substr(pos_of_sep + 1);
}

const string to_upper(const string &old) {
    string upper = old;

    for (string::iterator s = upper.begin(); s != upper.end(); ++s)
        *s = toupper(*s);

    return upper;
}

const string canonize_name(const string &old) {
    string canonized = old;

    for (string::iterator s = canonized.begin(); s != canonized.end(); ++s)
        if (*s == '.' || *s == '-' || *s == ' ')
            *s = '_';

    return canonized;
}

const string canonize_enum(const string &old) {
    string canonized;

    for (string::const_iterator s = old.begin(); s != old.end(); ++s)
        if (*s == '-')
            canonized += "MINUS_";
        else if (*s == '+')
            canonized += "PLUS_";
        else
            canonized += *s;

    return canonized;
}

bool has_multiple_options_all_string() {
    if (!has_multiple_options())
        return false;

    struct gengetopt_option * opt = 0;

    foropt {
        if (opt->multiple && (opt->type && opt->type != ARG_STRING))
            return false;
    }

    return true;
}

bool has_multiple_options_string() {
    if (!has_multiple_options())
        return false;

    struct gengetopt_option * opt = 0;

    foropt {
        if (opt->multiple && opt->type == ARG_STRING)
            return true;
    }

    return false;
}

bool has_multiple_options() {
    struct gengetopt_option * opt = 0;

    foropt {
        if (opt->multiple)
            return true;
    }

    return false;
}

bool has_multiple_options_with_type() {
    gengetopt_option * opt = 0;

    for (gengetopt_option_list::iterator it = gengetopt_options.begin(); it
            != gengetopt_options.end() && (opt = *it); ++it)
        if (opt->multiple && opt->type)
            return true;

    return false;
}

bool has_multiple_options_with_default() {
    gengetopt_option * opt = 0;

    for (gengetopt_option_list::iterator it = gengetopt_options.begin(); it
            != gengetopt_options.end() && (opt = *it); ++it)
        if (opt->multiple && opt->default_given)
            return true;

    return false;
}

bool has_options_with_details(bool strict_hidden) {
    gengetopt_option * opt = 0;

    for (gengetopt_option_list::iterator it = gengetopt_options.begin(); it
            != gengetopt_options.end() && (opt = *it); ++it)
        if (opt->details && (!strict_hidden || !opt->hidden))
            return true;

    return false;
}

bool has_options_with_type() {
    gengetopt_option * opt = 0;

    for (gengetopt_option_list::iterator it = gengetopt_options.begin(); it
            != gengetopt_options.end() && (opt = *it); ++it)
        if (opt->type && opt->type != ARG_FLAG)
            return true;

    return false;
}

bool has_options_with_mode() {
    gengetopt_option * opt = 0;

    for (gengetopt_option_list::iterator it = gengetopt_options.begin(); it
            != gengetopt_options.end() && (opt = *it); ++it)
        if (opt->mode_value)
            return true;

    return false;
}

bool has_required() {
    struct gengetopt_option * opt = 0;

    foropt {
        if (opt->required)
            return true;
    }

    groups_collection_t::const_iterator end = gengetopt_groups.end();
    for (groups_collection_t::const_iterator idx = gengetopt_groups.begin(); idx
            != end; ++idx) {
        if (idx->second.required) {
            return true;
        }
    }

    return false;
}

bool has_dependencies() {
    struct gengetopt_option * opt = 0;

    foropt {
        if (opt->dependon)
            return true;
    }

    return false;
}

bool has_options() {
    struct gengetopt_option * opt = 0;

    foropt {
        if (opt->short_opt) {
            if (opt->short_opt != 'h' && opt->short_opt != 'V')
                return true;
        }
    }

    return false;
}

bool has_hidden_options() {
    struct gengetopt_option * opt = 0;

    foropt {
        if (opt->hidden) {
            return true;
        }
    }

    return false;
}

bool has_values() {
    struct gengetopt_option * opt = 0;

    for (gengetopt_option_list::iterator it = gengetopt_options.begin(); it
            != gengetopt_options.end(); ++it) {
        opt = *it;
        if (opt->acceptedvalues) {
            return true;
        }
    }

    return false;
}

bool is_numeric(const gengetopt_option *opt) {
    switch (opt->type) {
    case ARG_INT:
    case ARG_SHORT:
    case ARG_LONG:
    case ARG_FLOAT:
    case ARG_DOUBLE:
    case ARG_LONGDOUBLE:
    case ARG_LONGLONG:
        return true;
    default:
        return false;
    }
}
