/**
 * Copyright (C) 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU gengetopt
 *
 * GNU gengetopt is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
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

#ifndef _STRING_BUILDER_H_
#define _STRING_BUILDER_H_

#include <vector>
#include <ostream>


class string_builder
{
public:

    enum LocalisationType {
	NONE = 0,
	LOCALISE,
	GENGETOPT,
    };

    enum EscapeSetting {
	RAW = 0,
	ESCAPE,
    };

    string_builder();

    /**
     * Constructor that adds a part.
     */
    /*
    string_builder(
	const std::string &str, LocalisationType l10n );
    */

    /**
     * Add a string part to the string builder.  You can specify whether the
     * string should undergo no localisation, localisation by the end-program,
     * or localisation by gengetopt.  You can specify whether the string should
     * be escaped or inserted exactly as provided.
     *
     * @param str the string
     * @param l10n the localisation type
     * @param escape the escape settings
     */
    void add_part(
	const std::string &str, LocalisationType l10n = NONE,
	EscapeSetting escape = RAW );

    /**
     * Retrieve the number of parts in this string builder.
     *
     * @return the number of parts
     */
    unsigned int get_num_parts();

    /**
     * Generate the string builder declaration.  This declares an array of
     * pointers to chars that the string builder uses and should be done once
     * per scope block.  You are required to specify the maximum number of
     * string parts that you will require.
     *
     * @param max_num_parts maximum required numbee of string parts
     */
    static void generate_string_builder_declaration(
	std::ostream &stream, unsigned int indent, unsigned int max_num_parts );

    /**
     * Generate the string builder
     *
     * @param target the name of the target variable
     */
    void generate_string_builder(
	std::ostream &stream, unsigned int indent, const std::string &target );

    /**
     * Generate the string builder
     *
     * @param target the name of the target array variable
     * @param index the index into the target array variable
     */
    void generate_string_builder(
	std::ostream &stream, unsigned int indent,
	const std::string &target, unsigned int index );

    bool operator ==( const string_builder &that ) const;

    /**
     * Stream operator.  Use to append a string to the string builder with the
     * current localisation type (which defaults to NONE) and escape setting
     * (which defaults to RAW).
     *
     * @param str the string to append to the string builder
     * @return a reference to this object
     */
    string_builder &operator <<(
	const std::string &str );

    /**
     * Stream operator.  Use to change the current localisation type.
     *
     * @param l10n the localisation type
     * @return a reference to this object
     */
    string_builder &operator <<(
	LocalisationType l10n );

    /**
     * Stream operator.  Use to change the current escape setting.
     *
     * @param escape the escape setting
     * @return a reference to this object
     */
    string_builder &operator <<(
	EscapeSetting escape );

protected:

    /**
     * Return a string in which newlines are prefixed by a backslash.
     *
     * @param str the string on which to work
     * @return the same string, with newlines escaped
     */
    std::string escape_newlines( const std::string &str ) const;

    /**
     * Generate the string builder
     *
     * @param target the name of the target array variable
     * @param index the index into the target array variable
     */
    void generate_string_builder(
	std::ostream &stream, unsigned int indent,
	const std::string &target, const std::string &index );

    /** part strings */
    std::vector< std::string > _parts;

    /** should strings be localised? */
    std::vector< LocalisationType > _l10n_types;

    /** current localisation type (for stream operator) */
    LocalisationType _current_l10n;

    /** current escape setting (for stream operator) */
    EscapeSetting _current_escape;
};

#endif /* _STRING_BUILDER_H_ */
