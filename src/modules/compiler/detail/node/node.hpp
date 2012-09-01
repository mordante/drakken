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
 * Contains the basic node class.
 *
 * This is the base for the AST, all other nodes used in the AST should derive
 * from this class.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_NODE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_NODE_HPP_INCLUDED

#include <iosfwd>

namespace compiler {
namespace detail {
namespace node {

class tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	tnode_();

	virtual ~tnode_();

private:

	tnode_&
	operator=(const tnode_&); /* = delete */

	tnode_(const tnode_&); /* = delete */

public:


	/***** ***** Virtual operations. ***** *****/

	/**
	 * Generates the assembly output.
	 *
	 * In a later stage it first should produce intermediate code, which then
	 * in turn is converted to assembly. For now it just generates the wanted
	 * code.
	 */
	virtual void
	generate_code(std::ostream& output) = 0;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
