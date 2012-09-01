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
 * Contains the identifier node.
 *
 * What the identifier identifies depends on where it is used. It can identify
 * variables, named scopes, procedures and in the future possibly more types of
 * elements.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_IDENTIFIER_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_IDENTIFIER_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

#include <string>

namespace compiler {
namespace detail {
namespace node {

class tidentifier
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @pre                       @p name != @c NULL
	 *
	 * @param name                Initialises @ref name_.
	 */
	explicit tidentifier(const std::string* name);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);


	/***** ***** Getters, setters. ***** *****/

	const std::string&
	name() const;


	/***** ***** Members. ***** *****/

private:

	/**
	 * The name of the identifier.
	 *
	 * The name is never qualified, a qualified identifier links multiple
	 * identifiers together.
	 */
	const std::string& name_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
