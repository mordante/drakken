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

#include "modules/compiler/detail/node/definition_method.hpp"

#include "lib/utility/validate.tpp"
#include "modules/compiler/detail/symbol/named_scope.hpp"

#include <iostream>

namespace compiler {
namespace detail {
namespace node {

tdefinition_method::tdefinition_method(
		  const symbol::tnamed_scope& scope
		, tidentifier* name
		, targument_list* argument_list
		, tnode_* statement_list)
	: scope_(scope)
	, name_(name)
	, argument_list_(argument_list)
	, statement_list_(statement_list)
{
	PRE_CONDITION(name);
	PRE_CONDITION(argument_list);
	PRE_CONDITION(statement_list);
}

std::string
tdefinition_method::get_signature() const
{
	return
			  std::string()
			+ "method"
			+ '|'
			/** @todo Add the relevant method attributes. */
			+ '|'
			+ scope_.signature() + name_->name()
			+ '|'
			+ argument_list_->get_signature()
			+ '|'
			/**
			 * @todo Evaluate whether we want to add an empty return element.
			 */
			;
}

void
tdefinition_method::generate_code(std::ostream& output)
{
	output
			<< get_signature() << ":\n"
			<< "\tpush\t\tr14\n"
			<< "\tmov.32\t\tr14, r15\n";

	statement_list_->generate_code(output);

	output
			<< "\tpop\t\tr14\n"
			<< "\tret\n";
}

} // namespace node
} // namespace detail
} // namespace compiler
