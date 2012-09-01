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
 * Contains the qualified identifier node.
 *
 * A qualified identifier may have multiple elements; an identifier and a path
 * of scopes used to qualify the name. The identifier can be fully qualified,
 * uniquely identifying a single identifier.
 */

#ifndef MODULES_COMPILER_DETAIL_NODE_QUALIFIED_IDENTIFIER_HPP_INCLUDED
#define MODULES_COMPILER_DETAIL_NODE_QUALIFIED_IDENTIFIER_HPP_INCLUDED

#include "modules/compiler/detail/node/node.hpp"

#include <vector>

namespace compiler {
namespace detail {
namespace node {

class tidentifier;

class tqualified_identifier
	: public tnode_
{
public:

	/***** ***** Constructor, destructor, assignment. ***** *****/

	/**
	 * Constructor.
	 *
	 * @pre                       @p identifier != @c NULL
	 *
	 * @param identifier          The first element to be placed in
	 *                            @ref identifiers_.
	 */
	explicit tqualified_identifier(tidentifier* identifier);


	/***** ***** Operations. ***** *****/

	/**
	 * Adds an identifier to the current object.
	 *
	 * This allows to grow a path for an identifier.
	 *
	 * @pre                       @p identifier != @c NULL
	 *
	 * @param identifier          The element to be added to the back of
	 *                            @ref identifiers_.
	 */
	void
	add(tidentifier* identifier);


	/***** ***** Overriden operations. ***** *****/

	/** Overridden from @ref tnode_. */
	virtual void
	generate_code(std::ostream& output);


	/***** ***** Getters, setters. ***** *****/

	const std::vector<tidentifier*>&
	identifiers() const;

	void
	set_fully_qualified(const bool fully_qualified);


	/***** ***** Members. ***** *****/

private:

	/**
	 * The parts of the identifier.
	 *
	 * The front of the vector contains the highest named scope of the
	 * identifier, the back the identifier itself, the path between are all
	 * named scopes in their parent.
	 */
	std::vector<tidentifier*> identifiers_;

	/**
	 * Whether the identifier is fully qualified.
	 *
	 * If fully qualified the @ref identifiers_ are `anchored' in the global
	 * named scope.
	 */
	bool fully_qualified_;
};

} // namespace node
} // namespace detail
} // namespace compiler

#endif
