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

#include "modules/compiler/detail/node/nop.hpp"

namespace compiler {
namespace detail {
namespace node {

void
tnop::generate_code(std::ostream& /*output*/)
{
	/* DO NOTHING */
}

} // namespace node
} // namespace detail
} // namespace compiler
