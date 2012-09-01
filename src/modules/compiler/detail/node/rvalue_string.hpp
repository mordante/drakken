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
 * Contains the string rvalue node.
 *
 * @todo This class is not really finished yet, copied from older code.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_RVALUE_STRING_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_RVALUE_STRING_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

namespace compiler {
namespace detail {
namespace node {

template<class T>
struct trvalue
	: public tnode_
{
	/***** ***** Constructor, destructor, assignment. ***** *****/

	explicit trvalue(const T value__)
		: value(value__)
	{
	}


	/***** ***** Operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream&) {}


	/***** ***** Members. ***** *****/

	const T value;
};

typedef trvalue<const std::string*> trvalue_string;

} // namespace node
} // namespace detail
} // namespace compiler

#endif
