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
 * Contains the binary operation expression nodes.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_EXPRESSION_BINARY_OPERATION_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_EXPRESSION_BINARY_OPERATION_HPP_INCLUDED

#include "modules/compiler/detail/node/value.hpp"

namespace compiler {
namespace detail {
namespace node {
namespace binary_operation_type {

enum ttype
{
	  add
	, subtract
	, multiply
};

} // namespace binary_operation_type

template<binary_operation_type::ttype T>
class texpression_binary_operation
	: public tvalue_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @pre                       @p lhs != @c NULL
	 * @pre                       @p rhs != @c NULL
	 *
	 * @param lhs                 Initialises @ref lhs_.
	 * @param rhs                 Initialises @ref rhs_.
	 */
	texpression_binary_operation(tvalue_* lhs, tvalue_* rhs);


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

	/** The right hand side of the operator, a rvalue. */
	tvalue_* rhs_;
};

/** Defines an add expression node. */
typedef
		texpression_binary_operation<binary_operation_type::add>
		texpression_add;

/** Defines a subtract expression node. */
typedef
		texpression_binary_operation<binary_operation_type::subtract>
		texpression_subtract;

/** Defines a multiply expression node. */
typedef
		texpression_binary_operation<binary_operation_type::multiply>
		texpression_multiply;

} // namespace node
} // namespace detail
} // namespace compiler

#endif
