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

#include "modules/compiler/detail/node/expression_binary_operation.hpp"

#include "lib/utility/validate.tpp"

#include <ostream>

namespace compiler {
namespace detail {
namespace node {
namespace binary_operation_type {

static std::ostream&
operator<<(std::ostream& lhs, const ttype rhs)
{
	switch(rhs) {
		case add:
			lhs << "add";
			return lhs;

		case subtract:
			lhs << "sub";
			return lhs;

		case multiply:
			lhs << "mul";
			return lhs;

	}

	return lhs;
}

} // namespace binary_operation_type

template<binary_operation_type::ttype T>
texpression_binary_operation<T>::texpression_binary_operation(
		  tvalue_* lhs
		, tvalue_* rhs)
	: lhs_(lhs)
	, rhs_(rhs)
{
	PRE_CONDITION(lhs);
	PRE_CONDITION(rhs);
}

template<binary_operation_type::ttype T>
void
texpression_binary_operation<T>::load(
		  std::ostream& output
		, const std::string& reg)
{
#if 0
	output << "//LOAD BINARY " << T << " ->>\n";
#endif

	generate_code(output);
	output << "\tpop\t\t" << reg << "\n";

#if 0
	output << "//LOAD BINARY " << T << " <<-\n";
#endif
}

template<binary_operation_type::ttype T>
void
texpression_binary_operation<T>::generate_code(std::ostream& output)
{
output << "//GENERATE BINARY " << T << " ->>\n";
	// Save registers
	output
			<< "\tpush\t\tr0\n"
			<< "\tpush\t\tr1\n"
			;

	// Load lhs in r0
	lhs_->load(output, "r0");

	// Load rhs in r1
	rhs_->load(output, "r1");

	// Operation
	output << "\t" << T << ".32\t\tr0, r0, r1\n";

	// Store result in temp
	output << "\tmov.32\t\tr3, r0\n";

	// Restore registers
	output
			<< "\tpop\t\tr1\n"
			<< "\tpop\t\tr0\n"
			;

	// Store result
	output << "\tpush\t\tr3\n";

#if 0
	output << "//GENERATE BINARY " << T << " <<-\n";
#endif
}

template class texpression_binary_operation<binary_operation_type::add>;
template class texpression_binary_operation<binary_operation_type::subtract>;
template class texpression_binary_operation<binary_operation_type::multiply>;

} // namespace node
} // namespace detail
} // namespace compiler
