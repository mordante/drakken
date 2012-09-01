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
 * Contains the nop node class.
 *
 * This node is used when a node doesn't need to generate code.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_NOP_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_NOP_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

namespace compiler {
namespace detail {
namespace node {

class tnop
	: public tnode_
{
public:

	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
