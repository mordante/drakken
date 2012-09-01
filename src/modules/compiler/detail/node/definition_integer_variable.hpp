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
 * Contains the integer variable defintion node.
 *
 * At the moment an integer definition can only be assigned a value, not an
 * expression.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_DEFINITION_INTEGER_VARIABLE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_DEFINITION_INTEGER_VARIABLE_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

namespace compiler {
namespace detail {
namespace node {

class tidentifier;
class trvalue_integer;

class tdefinition_integer_variable
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @pre                       @p name != @c NULL
	 * @pre                       @p value != @c NULL
	 *
	 * @param name                Initialises @ref name_.
	 * @param value               Initiailises @ref value_.
	 */
	tdefinition_integer_variable(tidentifier* name, trvalue_integer* value);


	/***** ***** Operations. ***** *****/

	/** Returns the signature of the method. */
	std::string
	get_signature() const;


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);


	/***** ***** Members. ***** *****/

private:

	/** The name of the variable. */
	tidentifier* name_;

	/** The value of the variable. */
	trvalue_integer* value_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
