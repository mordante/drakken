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
 * Contains the argument list node.
 *
 * An argument list the list of arguments used to declare and define a
 * procedure. At the moment the definition and the declaration share this list,
 * which might change.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_ARGUMENT_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_ARGUMENT_HPP_INCLUDED

#include "modules/compiler/detail/node/identifier.hpp"

#include <vector>

namespace compiler {
namespace detail {
namespace node {

class targument_list
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	targument_list();


	/***** ***** Operations. ***** *****/

	/**
	 * Adds a argument to the list.
	 *
	 * @param argument          The argument to add.
	 */
	void
	add(tidentifier* argument);

	/**
	 * Returns the signature of the argument list.
	 */
	std::string
	get_signature() const;


	/***** ***** Overriden operations. ***** *****/

	virtual void
	generate_code(std::ostream& output);


	/***** ***** Members. ***** *****/

private:

	/** The arguments given to a procedure. */
	std::vector<tidentifier*> arguments_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
