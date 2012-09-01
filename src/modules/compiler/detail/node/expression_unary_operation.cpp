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

#include "modules/compiler/detail/node/expression_unary_operation.hpp"

#include <ostream>

namespace compiler {
namespace detail {
namespace node {

namespace unary_operation_type {

static std::ostream&
operator<<(std::ostream& lhs, const ttype rhs)
{
	switch(rhs) {
		case load:
			/* DO NOTHING */
			return lhs;

	}

	return lhs;
}

} // namespace unary_operation_type

template<unary_operation_type::ttype T>
texpression_unary_operation<T>::texpression_unary_operation(tvalue_* lhs)
	: lhs_(lhs)
{
}

template<unary_operation_type::ttype T>
void
texpression_unary_operation<T>::load(
		  std::ostream& output
		, const std::string& reg)
{
#if 0
	output << "//LOAD UNNARY " << T << " ->>\n";
#endif

	lhs_->load(output, reg);

#if 0
	output << "//LOAD UNNARY " << T << " <<-\n";
#endif
}

template<unary_operation_type::ttype T>
void
texpression_unary_operation<T>::generate_code(std::ostream& output)
{
#if 0
	output << "//GENERATE UNNARY " << T << " ->>\n";
#endif

	// Load lhs in r0
	lhs_->load(output, "r0");

	// Operation
	output << T;

	// Store result
	output << "\tpush\t\tr0\n";

	output << "//XXX <<-\n";

#if 0
	output << "//GENERATE UNNARY " << T << " <<-\n";
#endif
}

template class texpression_unary_operation<unary_operation_type::load>;

} // namespace node
} // namespace detail
} // namespace compiler
