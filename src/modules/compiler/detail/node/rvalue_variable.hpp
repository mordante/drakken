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

#ifndef MODULES_COMPILER_DETAIL_NODE_RVALUE_VARIABLE_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_RVALUE_VARIABLE_HPP_INCLUDED

/**
 * @file
 * Contains the rvalue variable node.
 *
 * The rvalue variable may only be read from.
 */

#include "modules/compiler/detail/node/value.hpp"

namespace compiler {
namespace detail {
namespace symbol {

class tnamed_scope;
class tvariable;

} // namespace symbol

namespace node {

class trvalue_variable
	: public tvalue_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @param variable            The variable to link to.
	 */
	explicit trvalue_variable(const symbol::tvariable& variable);


	/***** ***** Operations. ***** *****/

	/** Returns the signature of the method. */
	std::string
	get_signature() const;


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);

	/** Overridden from @ref tvalue_. */
	virtual void
	load(std::ostream& output, const std::string& reg);


	/***** ***** Members. ***** *****/

private:

	/** The named scope in which we reside. */
	const symbol::tnamed_scope& scope_;

	/** Contains a like to the identifier with the name of this variable. */
	std::string name_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
