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
 * Contains the assign statement node.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_STATEMENT_ASSIGN_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_STATEMENT_ASSIGN_HPP_INCLUDED

#include "modules/compiler/detail/node/identifier.hpp"

namespace compiler {
namespace detail {
namespace node {

class tstatement_assign
	: public tnode_
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
	tstatement_assign(tidentifier* lhs, tnode_* rhs);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);


	/***** ***** Members. ***** *****/

private:

	/** The left hand side of the assign statement, a lvalue. */
	tidentifier* lhs_;

	/** The right hand side of the assign statement, a rvalue. */
	tnode_* rhs_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
