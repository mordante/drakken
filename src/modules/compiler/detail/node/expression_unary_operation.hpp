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

/**
 * @file
 * Contains the unary operation expression nodes.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_EXPRESSION_UNARY_OPERATION_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_EXPRESSION_UNARY_OPERATION_HPP_INCLUDED

#include "modules/compiler/detail/node/value.hpp"

namespace compiler {
namespace detail {
namespace node {
namespace unary_operation_type {

enum ttype
{
	  load
};

} // namespace unary_operation_type

template<unary_operation_type::ttype T>
class texpression_unary_operation
	: public tvalue_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @pre                       @p lhs != @c NULL
	 *
	 * @param lhs                 Initialises @ref lhs_.
	 */
	explicit texpression_unary_operation(tvalue_* lhs);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);

	/** Overridden from @ref tvalue_. */
	virtual void
	load(std::ostream& output, const std::string& reg);


	/***** ***** Members. ***** *****/

private:

	/** The left hand side of the operator, a rvalue. */
	tvalue_* lhs_;
};

/**
 * The load expression loads the value of an expression in the proper register.
 */
typedef
		texpression_unary_operation<unary_operation_type::load>
		texpression_load;

} // namespace node
} // namespace detail
} // namespace compiler

#endif
