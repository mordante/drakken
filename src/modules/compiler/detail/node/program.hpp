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
 * Contains the program node.
 *
 * This node is the root of the AST.
 *
 * At the moment is only contains a list of defintions, but it should also
 * contain declarations of types and functions.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_PROGRAM_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_PROGRAM_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

#include <string>

namespace compiler {
namespace detail {
namespace node {

class tprogram
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor
	 *
	 * @pre                       @p interface != @c NULL
	 * @pre                       @p implementation != @c NULL
	 *
	 * @param interface           Initialises @ref interface_.
	 * @param implementation      Initialises @ref implementation_.
	 * @param main_signature      Initialises @ref main_signature_.
	 */
	tprogram(
			  tnode_* interface
			, tnode_* implementation
			, const std::string& main_signature);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);


	/***** ***** Members. ***** *****/

private:

	/** Link to the interface section of the program. */
	tnode_* interface_;

	/** Link to the implementation section of the program. */
	tnode_* implementation_;

	/**
	 * The signature of the main procedure.
	 *
	 * There are several signatures allowed, depending on the one selected the
	 * code generations differs. E.g. the method versions need to force a
	 * return value for the execution, the function versions will return the
	 * value.
	 */
	std::string main_signature_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
