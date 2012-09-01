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

#include "modules/compiler/detail/node/statement_list.hpp"

#include "lib/utility/foreach.tpp"
#include "lib/utility/validate.tpp"

namespace compiler {
namespace detail {
namespace node {

tstatement_list::tstatement_list()
	: statements_()
{
}

void
tstatement_list::generate_code(std::ostream& output)
{
	FOREACH(node, statements_) {
		node->generate_code(output);
	}
}

void
tstatement_list::add(tnode_* statement)
{
	PRE_CONDITION(statement);

	statements_.push_back(statement);
}

} // namespace node
} // namespace detail
} // namespace compiler
