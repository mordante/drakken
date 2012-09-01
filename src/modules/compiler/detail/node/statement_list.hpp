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
 * Contains the statement list node.
 *
 * A statement list is a block of code, containing zero or more statements.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_STATEMENT_LIST_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_STATEMENT_LIST_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

#include <vector>

namespace compiler {
namespace detail {
namespace node {

class tstatement_list
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	tstatement_list();


	/***** ***** Operations. ***** *****/

	/**
	 * Adds a statement to the list.
	 *
	 * @pre                      @p statement != @c NULL
	 *
	 * @param statement          The statement to add.
	 */
	void
	add(tnode_* statement);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);


	/***** ***** Members. ***** *****/

private:

	/** The statements in the list. */
	std::vector<tnode_*> statements_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
