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

#include "modules/compiler/detail/node/qualified_identifier.hpp"

#include "lib/utility/validate.tpp"
#include "modules/compiler/detail/node/identifier.hpp"

namespace compiler {
namespace detail {
namespace node {

tqualified_identifier::tqualified_identifier(tidentifier* identifier)
	: identifiers_(1, identifier)
	, fully_qualified_(false)
{
	PRE_CONDITION(identifier);
}

void
tqualified_identifier::add(tidentifier* identifier)
{
	PRE_CONDITION(identifier);

	identifiers_.push_back(identifier);
}

void
tqualified_identifier::generate_code(std::ostream& /*output*/)
{
	/* DO NOTHING */
}

const std::vector<tidentifier*>&
tqualified_identifier::identifiers() const
{
	return identifiers_;
}

void
tqualified_identifier::set_fully_qualified(const bool fully_qualified)
{
	fully_qualified_ = fully_qualified;
}

} // namespace node
} // namespace detail
} // namespace compiler
