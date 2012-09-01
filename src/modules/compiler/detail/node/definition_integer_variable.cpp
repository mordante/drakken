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

#include "modules/compiler/detail/node/definition_integer_variable.hpp"

#include "lib/utility/validate.tpp"
#include "modules/compiler/detail/node/identifier.hpp"
#include "modules/compiler/detail/node/rvalue_integer.hpp"

#include <ostream>

namespace compiler {
namespace detail {
namespace node {

tdefinition_integer_variable::tdefinition_integer_variable(
		  tidentifier* name
		, trvalue_integer* value)
	: name_(name)
	, value_(value)
{
	PRE_CONDITION(name);
	PRE_CONDITION(value);
}

std::string
tdefinition_integer_variable::get_signature() const
{
	return
			std::string()
		  + "variable"
		  + '|'
		  +	"int"
		  + '|'
		  + name_->name()
		  + '|'
		  ;
}

void
tdefinition_integer_variable::generate_code(std::ostream& output)
{
	output << get_signature() << ":\n";

	output << "\traw\t\t";
	value_->generate_code(output);
	output << '\n';
}

} // namespace node
} // namespace detail
} // namespace compiler
