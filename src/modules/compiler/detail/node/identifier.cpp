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

#include "modules/compiler/detail/node/identifier.hpp"

#include "lib/utility/validate.tpp"

namespace compiler {
namespace detail {
namespace node {

tidentifier::tidentifier(const std::string* name)
	: name_(*name)
{
	PRE_CONDITION(name);
}

void
tidentifier::generate_code(std::ostream& /*output*/)
{
	/* DO NOTHING */
}

const std::string&
tidentifier::name() const
{
	return name_;
}

} // namespace node
} // namespace detail
} // namespace compiler
