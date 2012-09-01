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
 * Contains the method definition node.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_DEFINITION_METHOD_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_DEFINITION_METHOD_HPP_INCLUDED

#include "modules/compiler/detail/node/argument_list.hpp"

namespace compiler {
namespace detail {
namespace symbol {

class tnamed_scope;

} // namespace symbol

namespace node {

class tdefinition_method
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @pre                       @p name != @c NULL
	 * @pre                       @p argument_list != @c NULL
	 * @pre                       @p statement_list != @c NULL
	 *
	 * @param scope               Initialises @ref scope_.
	 * @param name                Initialises @ref name_.
	 * @param argument_list       Initialises @ref argument_list_.
	 * @param statement_list      Initialises @ref statement_list_.
	 */
	tdefinition_method(
			  const symbol::tnamed_scope& scope
			, tidentifier* name
			, targument_list* argument_list
			, tnode_* statement_list);


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

	/** The named scope in which we reside. */
	const symbol::tnamed_scope& scope_;

	/** Contains a like to the identifier with the name of this method. */
	tidentifier* name_;

	/** The arguments used to call the method. */
	targument_list* argument_list_;

	/** The statements that make up the method. */
	tnode_* statement_list_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
