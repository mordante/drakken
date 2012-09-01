/*
 * Copyright (C) 2012 by Mark de Wever <koraq@xs4all.nl>
 * Part of the Drakken project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY.
 *
 * See the COPYING file for more details.
 */

#include "modules/compiler/detail/node/argument_list.hpp"

#include "lib/utility/foreach.tpp"

namespace compiler {
namespace detail {
namespace node {

targument_list::targument_list()
	: arguments_()
{
}

std::string
targument_list::get_signature() const
{
	/*
	 * The extra trailing underscore is not a problem, so keep it.
	 */
	std::string result;
	FOREACH(const argument, arguments_) {
		/*
		 * The type is not parsed yet so hard-coded as int.
		 */
		result += "int_";
		if(argument) {} // silence the compiler.
//		result += *argument->value;
//		result += '_';
	}
	return result;
}

void
targument_list::generate_code(std::ostream& /*output*/)
{
	/* DO NOTHING */
}

void
targument_list::add(tidentifier* argument)
{
	arguments_.push_back(argument);
}

} // namespace node
} // namespace detail
} // namespace compiler
