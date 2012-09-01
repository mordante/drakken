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
 * Contains the value node.
 *
 * A value node is an abstract class mainly concerned with loading and
 * storing of values. The value can be an expression, a variable, a
 * immediate.
 *
 * @note The class might get renamed to rvalue_ and a lvalue_ class will be
 * added to represent nodes that can be written.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_VALUE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_VALUE_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

#include <string>

namespace compiler {
namespace detail {
namespace node {

class tvalue_
	: public tnode_
{
public:

	/***** ***** Virtual operations. ***** *****/

	/**
	 * Loads the value in a register.
	 *
	 * @param output              The output stream to write to.
	 * @param reg                 The string representation of the register.
	 */
	virtual void
	load(std::ostream& output, const std::string& reg) = 0;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
