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

#include <sstream>
#include <cassert>
#include "string_builder.h"
#include "skels/string_builder_declare.h"
#include "skels/string_builder_allocate.h"
#include "skels/string_builder_build.h"
#include "skels/string_builder_prepare.h"


string_builder::string_builder()
    :
    _current_l10n( NONE ),
    _num_allocable_parts( 0 )
{
}

/*
string_builder::string_builder(
    const std::string &str, LocalisationType l10n )
    :
    _current_l10n( NONE )
{
    add_part( str, l10n );
}
*/

void string_builder::add_part(
    const std::string &str, LocalisationType l10n /*= NONE*/ )
{
    // ignore empty strings
    if( str.size() )
    {
	// can we append this to the end of the previous string?
	std::vector< std::string >::size_type num_parts = _parts.size();
	if( num_parts && _l10n_types[ num_parts - 1 ] == l10n &&
	    ( l10n == NONE || l10n == TRANSLATOR_NOTES ) )
	{
	    // append to end of previous string
	    _parts[ num_parts - 1 ] += str;
	}
	else
	{
	    // no, add new part
	    _parts.push_back( str );
	    _l10n_types.push_back( l10n );

	    // unless this part is translator notes, it is an allocable
	    // component of the string
	    if( l10n != TRANSLATOR_NOTES )
		_num_allocable_parts++;
	}
    }
}


void string_builder::generate_string_builder_declaration(
    ostream &stream, unsigned int indent, unsigned int num_allocable_parts )
{
    string_builder_declare_gen_class declarer;
    declarer.set_num_allocable_parts( num_allocable_parts );
    declarer.generate_string_builder_declare( stream, indent );
}


void string_builder::generate_string_builder(
    ostream &stream, unsigned int indent, const std::string &target )
{
    generate_string_builder( stream, indent, target, "" );
}


void string_builder::generate_string_builder(
    ostream &stream, unsigned int indent,
    const std::string &target, unsigned int index )
{
    std::ostringstream oss;
    oss << index;
    generate_string_builder( stream, indent, target, oss.str() );
}


bool string_builder::operator ==( const string_builder &that ) const
{
    return _parts == that._parts && _l10n_types == that._l10n_types;
}


std::string string_builder::escape_newlines( const std::string &str ) const
{
    std::ostringstream ss;
    std::size_t pos = 0, next;
    while( ( next = str.find_first_of( '\n', pos ) ) != std::string::npos ) {
	ss << str.substr( pos, next - pos ) << "\\n";
	pos = next + 1;
    }
    ss << str.substr( pos );
    return ss.str();
}


void string_builder::generate_string_builder(
    ostream &stream, unsigned int indent,
    const std::string &target, const std::string &index )
{
    // preparation of strings
    string_builder_prepare_gen_class preparer;
    for( unsigned int a = 0, idx = 0; a < _parts.size(); a++ )
    {
	preparer.set_first_part( a == 0 );
	preparer.set_gengetopt_localised( false );
	preparer.set_localised( false );
	preparer.set_raw_c( false );
	preparer.set_translator_notes( false );
	switch( _l10n_types[ a ] ) {
	case GENGETOPT:
	    preparer.set_gengetopt_localised( true );
	    preparer.set_allocable_part_index( idx++ );
	    break;
	case LOCALISE:
	    preparer.set_localised( true );	
	    preparer.set_allocable_part_index( idx++ );
	    break;
	case RAW_C:
	    preparer.set_raw_c( true );
	    preparer.set_allocable_part_index( idx++ );
	    break;
	case TRANSLATOR_NOTES:
	    preparer.set_translator_notes( true );
	    break;
	default:
	    preparer.set_allocable_part_index( idx++ );
	    break;
	}
	preparer.set_value( escape_newlines( _parts[ a ] ) );
	preparer.generate_string_builder_prepare( stream, indent );
    }

    // allocation of target string
    string_builder_allocate_gen_class allocator;
    allocator.set_num_allocable_parts( _num_allocable_parts );
    allocator.set_target( target );
    allocator.set_is_target_array( !index.empty() );
    allocator.set_target_index( index );
    allocator.generate_string_builder_allocate( stream, indent );

    // build target string
    string_builder_build_gen_class builder;
    builder.set_target( target );
    builder.set_is_target_array( !index.empty() );
    builder.set_target_index( index );
    if( _num_allocable_parts > 0 ) {
	builder.set_first( true );
	builder.generate_string_builder_build( stream, indent );
	if( _num_allocable_parts > 1 ) {
	    builder.set_first( false );
	    builder.set_num_allocable_parts( _num_allocable_parts );
	    builder.generate_string_builder_build( stream, indent );
	}
    }
}


string_builder &string_builder::operator <<(
    const std::string &str )
{
    add_part( str, _current_l10n );
    return *this;
}


string_builder &string_builder::operator <<(
    LocalisationType l10n )
{
    _current_l10n = l10n;
    return *this;
}


std::string string_builder::generate_unlocalised_string() const
{
    std::ostringstream oss;
    for( unsigned int i = 0; i < _parts.size(); i++ )
	if( _l10n_types[ i ] != TRANSLATOR_NOTES )
	    oss << _parts[ i ];
    return oss.str();
}