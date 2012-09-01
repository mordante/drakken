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
 * Contains the procedure call statement node.
 *
 * This can call both functions and methods. Its return value is not used.
 *
 * @note This code will be changed when functions are added. Also the addition
 * of procedure arguments will probably change this code.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_STATEMENT_PROCEDURE_CALL_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_STATEMENT_PROCEDURE_CALL_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

#include <string>

namespace compiler {
namespace detail {
namespace node {

class tstatement_procedure_call
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @param signature           Initialises @ref signature_.
	 */
	explicit tstatement_procedure_call(const std::string& signature);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);


	/***** ***** Members. ***** *****/

private:

	/**
	 * The signature of the procedure to call.
	 *
	 * This name is already fully qualified and has all arguments set.
	 */
	std::string signature_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
