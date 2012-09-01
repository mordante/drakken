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

#include "modules/compiler/detail/node/rvalue_variable.hpp"

#include "modules/compiler/detail/symbol/named_scope.hpp"

#include <iostream>

namespace compiler {
namespace detail {
namespace node {

trvalue_variable::trvalue_variable(const symbol::tvariable& symbol)
	: scope_(symbol.parent)
	, name_(symbol.signature)
{
	name_.resize(name_.size() - 1);
}

std::string
trvalue_variable::get_signature() const
{
#if 0
	return
			  std::string()
			+ "variable"
			+ '|'
			/** @todo Add the relevant method attributes. */
			+ '|'
			+ ns_.signature() + *name_->value
			+ '|'
			+ "int"
			+ '|'
			/**
			 * @todo Evaluate whether we want to add an empty return element.
			 */
			;
#else
	return name_;
#endif
}

void
trvalue_variable::generate_code(std::ostream& /*output*/)
{
	/* Do NOTHING */
}

void
trvalue_variable::load(std::ostream& output, const std::string& reg)
{
	output
			<< "\tpush\t\t" << get_signature() << "|\n"
			<< "\tpop\t\t" << reg << "\n"
			<< "\tmov.32\t\t" << reg << ", [" << reg << "]\n"
#if 0
			<< "\tregisters\n"
#endif
			;
}

} // namespace node
} // namespace detail
} // namespace compiler
