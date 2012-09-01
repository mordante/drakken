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
 * Contains the integer rvalue node.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_RVALUE_INTEGER_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_RVALUE_INTEGER_HPP_INCLUDED

#include "modules/compiler/detail/node/value.hpp"

namespace compiler {
namespace detail {
namespace node {

class trvalue_integer
	: public tvalue_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @param value               Initialises @ref value_.
	 */
	explicit trvalue_integer(const int value);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);

	/** Overridden from @ref tvalue_. */
	virtual void
	load(std::ostream& output, const std::string& reg);


	/***** ***** Getters, Setters. ***** *****/

	int
	value() const;


	/***** ***** Members. ***** *****/

private:

	/** The value of the object. */
	int value_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
