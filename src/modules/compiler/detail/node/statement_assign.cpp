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

#include "modules/compiler/detail/node/statement_assign.hpp"

#include "lib/utility/validate.tpp"

#include <ostream>

namespace compiler {
namespace detail {
namespace node {

tstatement_assign::tstatement_assign(tidentifier* lhs, tnode_* rhs)
	: lhs_(lhs)
	, rhs_(rhs)
{
	PRE_CONDITION(lhs);
	PRE_CONDITION(rhs);
}

void
tstatement_assign::generate_code(std::ostream& output)
{
	// Execute the expression
	rhs_->generate_code(output);

	// Load the result in r1
	output << "\tpop\t\tr1\n";

	// Store result in destination
	output
			<< "\tpush\t\tvariable|int|" << lhs_->name() << "|\n"

			<< "\tpop\t\tr0\n"
			<< "\tmov.32\t\t[r0], r1\n"
#if 0
			<< "\tregisters\n"
			<< "\tmemory\t\tvariable|int|answer|\n"
#endif
			;
}

} // namespace node
} // namespace detail
} // namespace compiler
